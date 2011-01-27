/*
 * Copyright 2006-2008 The FLWOR Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define DEBUG_THESAURUS 0
#define DEBUG_READ_THESAURUS 0

#include <fstream>

#include <zorba/store_consts.h>

#include "store/api/iterator.h"
#include "store/api/store.h"
#include "util/fs_util.h"
#if DEBUG_THESAURUS || DEBUG_READ_THESAURUS
#include "util/oseparator.h"
#endif
#include "util/uri_util.h"
#include "util/utf8_util.h"
#include "zorbaerrors/error_manager.h"

#include "xqftts_thesaurus.h"

using namespace std;
using namespace zorba::locale;

namespace zorba {
namespace xqftts {

///////////////////////////////////////////////////////////////////////////////

inline zstring const& get_local_name( store::Item_t const &item ) {
  return item->getNodeName()->getLocalName();
}

inline bool is_element( store::Item_t const &item ) {
  return  item->isNode() &&
          item->getNodeKind() == store::StoreConsts::elementNode;
}

///////////////////////////////////////////////////////////////////////////////

thesaurus::candidate_queue_t::value_type const thesaurus::LevelMarker =
  make_pair( (synonym_t*)0, iso2788::neutral );

thesaurus::thesaurus( zstring const &path, iso639_1::type lang,
                      zstring const &phrase, zstring const &relationship,
                      ft_int at_least, ft_int at_most ) :
  relationship_( relationship_ ),
  at_least_( at_least ), at_most_( at_most ), level_( 0 )
{
  read_xqftts_file( path );
# if DEBUG_THESAURUS
  cout << "==================================================" << endl;
  cout << "query phrase: " << phrase << endl;
# endif
  result_queue_.push_back( phrase );
  lookup( phrase, iso2788::get_dir( relationship_.get_iso2788() ) );
}

thesaurus::~thesaurus() {
  MUTATE_EACH( thesaurus_t, entry, thesaurus_ )
    delete_ptr_seq( entry->second );
}

void thesaurus::lookup( term_t const &word, iso2788::rel_dir dir ) {
  thesaurus_t::const_iterator const entry = thesaurus_.find( word );
  if ( entry != thesaurus_.end() ) {
    FOR_EACH( synonym_set_t, i, entry->second ) {
      synonym_t const *const candidate_ptr = *i;
      iso2788::rel_dir candidate_dir;
      bool found_congruous = false;
      FOR_EACH( relationship_set_t, r, candidate_ptr->relationships ) {
        iso2788::rel_dir const d = iso2788::get_dir( r->get_iso2788() );
        if ( iso2788::congruous( dir, d ) ) {
          candidate_dir = d;
          found_congruous = true;
          break;
        }
      }
      if ( found_congruous )
        candidate_queue_.push_back(
          make_pair( candidate_ptr, dir + candidate_dir )
        );
    }
    if ( !candidate_queue_.empty() ) {
      //
      // All the candidates added constitute a "level", so add the sentinel to
      // the queue to increment the level.
      //
      candidate_queue_.push_back( LevelMarker );
    }
  }
}

bool thesaurus::next( zstring *synonym ) {
  while ( result_queue_.empty() ) {
#   if DEBUG_THESAURUS
    cout << "--------------------------------------------------" << endl;
    cout << "result_queue is empty" << endl;
#   endif

    if ( candidate_queue_.empty() ) {
#     if DEBUG_THESAURUS
      cout << "candidate_queue is empty --> no more synonyms" << endl;
#     endif
      return false;
    }

    candidate_t const candidate( pop_front( candidate_queue_ ) );
    synonym_t const *const candidate_ptr = candidate.first;
    iso2788::rel_dir const candidate_dir = candidate.second;

    if ( candidate_ptr == LevelMarker.first ) {
#     if DEBUG_THESAURUS
      cout << "+ found LevelMarker" << endl;
#     endif
      if ( ++level_ > at_most_ ) {
#       if DEBUG_THESAURUS
        cout << "+ level (" << level_ << ") > at_most (" << at_most_
             << ") --> no more synonyms" << endl;
#       endif
        return false;
      }

      //
      // We've just incremented the level, so all candidates that have been
      // added to the queue since the last time we were here constitute a
      // "level": therefore, add the level marker so we know when to increment
      // the level next time.
      //
      // Note that we do this only if the queue isn't empty, otherwise the
      // queue would never become empty.
      //
      if ( !candidate_queue_.empty() )
        candidate_queue_.push_back( LevelMarker );

      continue;
    }

    if ( level_ >= at_least_ ) {
      zstring const &word = candidate_ptr->term;
      if ( synonyms_seen_.insert( word ).second )
        result_queue_.push_back( word );
    }

    lookup( candidate_ptr->term, candidate_dir );
  } // while

  *synonym = pop_front( result_queue_ );
# if DEBUG_THESAURUS
  cout << "--> synonym=" << *synonym << endl;
# endif
  return true;
}

#define THROW_BAD_XML_EXCEPTION(WHAT,MSG) \
  ZORBA_ERROR_PARAM( XQP0024_XML_DOES_NOT_MATCH_SCHEMA, WHAT, MSG )

void thesaurus::read_xqftts_file( zstring const &uri ) {
  ZORBA_ASSERT( !uri.empty() );
  zstring thesaurus_xml_path;
  bool is_temp_file;
  uri::fetch( uri, &thesaurus_xml_path, &is_temp_file );
  fs::auto_remover<zstring> file_remover;
  if ( is_temp_file )
    file_remover.reset( thesaurus_xml_path );

  ifstream ifs( thesaurus_xml_path.c_str() );
  store::LoadProperties props;
  props.setStoreDocument( false );
  store::Item_t doc = GENV_STORE.loadDocument( "", "", ifs, props );

  store::Iterator_t i = doc->getChildren();
  i->open();
  store::Item_t item;
  if ( i->next( item ) ) {
    store::Iterator_t i = item->getChildren();
    i->open();
    //
    // For each <entry> ...
    //
    while ( i->next( item ) ) {
      if ( !is_element( item ) )
        continue;
      store::Iterator_t i = item->getChildren();
      i->open();
      term_t new_term;
      synonym_set_t new_set;
      //
      // For each <term> or <synonym> ...
      //
      while ( i->next( item ) ) {
        if ( !is_element( item ) )
          continue;
        zstring const &element_name = get_local_name( item );
        if ( element_name == "term" ) {
          if ( !new_term.empty() )
            THROW_BAD_XML_EXCEPTION( "term", "already specified" );
          item->getStringValue2( new_term );
          utf8::to_lower( new_term );
        } else if ( element_name == "synonym" ) {
          store::Iterator_t i = item->getChildren();
          i->open();
          term_t syn_term;
          relationship::string_t syn_relationship;
          //
          // For each synonym <term> or <relationship> ...
          //
          while ( i->next( item ) ) {
            if ( !is_element( item ) )
              continue;
            zstring const &element_name = get_local_name( item );
            if ( element_name == "term" ) {
              if ( !syn_term.empty() )
                THROW_BAD_XML_EXCEPTION( "term", "already specified" );
              item->getStringValue2( syn_term );
              utf8::to_lower( syn_term );
            } else if ( element_name == "relationship" ) {
              if ( !syn_relationship.empty() )
                THROW_BAD_XML_EXCEPTION( "relationship", "already specified" );
              item->getStringValue2( syn_relationship );
              utf8::to_lower( syn_relationship );
            } else
              THROW_BAD_XML_EXCEPTION( element_name, "unexpected element" );
          }
          if ( syn_term.empty() )
            THROW_BAD_XML_EXCEPTION( "term", "not specified" );
          if ( syn_relationship.empty() )
            THROW_BAD_XML_EXCEPTION( "relationship", "not specified" );
          //
          // We now have a (possibly) new synonym for the new synonym set
          // being built.
          //
          auto_ptr<synonym_t> new_syn( new synonym_t( syn_term ) );
          synonym_set_t::iterator syn_it = new_set.find( new_syn.get() );
          if ( syn_it != new_set.end() )
            (*syn_it)->relationships.insert( syn_relationship );
          else {
            new_syn->relationships.insert( syn_relationship );
            new_set.insert( new_syn.release() );
          }
        } else
          THROW_BAD_XML_EXCEPTION( element_name, "unexpected element" );
      }

      if ( new_term.empty() )
        THROW_BAD_XML_EXCEPTION( "term", "not specified" );
      if ( !new_set.empty() ) {
        //
        // We now have a (possibly) new term and one or more synonyms for it:
        // merge it into the thesaurus.
        //
        synonym_set_t &cur_set = thesaurus_[ new_term ];
        if ( cur_set.empty() )
          cur_set.swap( new_set );
        else {
          FOR_EACH( synonym_set_t, new_it, new_set ) {
            synonym_set_t::iterator const cur_it = cur_set.find( *new_it );
            if ( cur_it != cur_set.end() ) {
              //
              // The same synonym for the term already exists: just add in
              // the relationships.
              //
              copy_set( (*new_it)->relationships, (*cur_it)->relationships );
            } else
              cur_set.insert( *new_it );
          }
        }
      }
    }
#if DEBUG_READ_THESAURUS
    FOR_EACH( thesaurus_t, entry, thesaurus_ ) {
      cout << entry->first << endl;
      FOR_EACH( synonym_set_t, syn, entry->second ) {
        cout  << "  " << (*syn)->term << " (";
        oseparator comma;
        FOR_EACH( relationship_set_t, r, (*syn)->relationships )
          cout << comma << *r;
        cout << ')' << endl;
      }
    }
#endif /* DEBUG_READ_THESAURUS */
  }
}

///////////////////////////////////////////////////////////////////////////////

} // namespace xqftts
} // namespace zorba
/* vim:set et sw=2 ts=2: */