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

#include "stdafx.h"

// standard
#include <cstring>

// API
#include <zorba/xquery_stack_trace.h>
#include <zorba/util/uri.h>
#include <zorba/xquery_functions.h>

// Zorba
#include "util/ascii_util.h"
#include "util/fs_util.h"
#include "util/indent.h"
#include "util/omanip.h"
#include "util/uri_util.h"
#include "zorbatypes/URI.h"

// local
#include "dict.h"
#include "xquery_exception.h"

#define if_inc_indent if_do( do_indent, inc_indent )
#define if_dec_indent if_do( do_indent, dec_indent )

#undef if_nl
#define if_nl if_emit( do_indent, '\n' )

using namespace std;

namespace zorba {

///////////////////////////////////////////////////////////////////////////////

XQueryException::XQueryException( Diagnostic const &diagnostic,
                                  char const *raise_file, line_type raise_line,
                                  char const *message ) :
  ZorbaException( diagnostic, raise_file, raise_line, message )
{
}

XQueryException::XQueryException( XQueryException const &from ) :
  ZorbaException( from ),
  source_loc_( from.source_loc_ ),
  data_loc_( from.data_loc_ ),
  applied_loc_( from.applied_loc_ ),
  query_trace_( from.query_trace_ )
{
  // This copy constructor isn't necessary: the compiler-generated default copy
  // constructor would work just fine.  It is defined explicitly, however, so
  // as to future-proof the code and keep ABI compatibility.
}

XQueryException::XQueryException( serialization::Archiver &ar ) :
  ZorbaException( ar )
{
}

XQueryException::~XQueryException() throw() {
  // out-of-line since it's virtual
}

XQueryException& XQueryException::operator=( XQueryException const &from ) {
  //
  // This assignment operator isn't necessary: the compiler-generated default
  // assignment operator would work just fine.  It is defined explicitly,
  // however, so as to future-proof the code and keep ABI compatibility.
  //
  if ( &from != this ) {
    ZorbaException::operator=( from );
    source_loc_  = from.source_loc_;
    data_loc_    = from.data_loc_;
    applied_loc_ = from.applied_loc_;
    query_trace_ = from.query_trace_;
  }
  return *this;
}

unique_ptr<ZorbaException> XQueryException::clone() const {
  return unique_ptr<ZorbaException>( new XQueryException( *this ) );
}

int XQueryException::get_ios_trace_index() {
  static int const index = ios_base::xalloc();
  return index;
}

void XQueryException::set_applied( char const *uri,
                                   line_type line,
                                   column_type col,
                                   line_type line_end,
                                   column_type col_end ) {
  if ( !uri || !*uri )
    uri = source_loc_.file();
  applied_loc_.set( uri, line, col, line_end, col_end );
}

void XQueryException::set_data( char const *uri,
                                line_type line,
                                column_type col,
                                line_type line_end,
                                column_type col_end ) {
  if ( !uri || !*uri )
    uri = source_loc_.file();
  data_loc_.set( uri, line, col, line_end, col_end );
}

void XQueryException::set_source( char const *uri,
                                  line_type line,
                                  column_type col,
                                  line_type line_end,
                                  column_type col_end ) {
  source_loc_.set( uri, line, col, line_end, col_end );
}

void XQueryException::polymorphic_throw() const {
  throw *this;
}

ostream& XQueryException::print_impl( ostream &o ) const {
  print_format const format = get_print_format( o );
  bool const as_xml = format != format_text;
  bool const do_indent = format == format_xml_indented;

  if ( as_xml ) {
    ZorbaException::print_impl( o );
    if ( has_source() ) {
      o << indent << "<location";
      print_uri( o, source_uri() );
      o << " line-begin=\"" << source_line() << '"';
      if ( source_column() )
        o << " column-begin=\"" << source_column() << '"';
      if ( source_line_end() )
        o << " line-end=\"" << source_line_end() << '"';
      if ( source_column_end() )
        o << " column-end=\"" << source_column_end() << '"';
      o << "/>" << if_nl; // <location ...

      if ( has_data() ) {
        o << indent << "<data-location";
        if ( data_uri() && ::strcmp( data_uri(), source_uri() ) != 0 )
          print_uri( o, applied_uri() );
        o << " line=\"" << data_line() << '"';
        if ( data_column() )
          o << " column=\"" << data_column() << '"';
        o << "/>" << if_nl; // <data-location ...
      }

      if ( has_applied() ) {
        o << indent << "<applied-at";
        if ( applied_uri() && ::strcmp( applied_uri(), source_uri() ) != 0 )
          print_uri( o, applied_uri() );
        o << " line=\"" << applied_line() << '"';
        if ( applied_column() )
          o << " column=\"" << applied_column() << '"';
        o << "/>" << if_nl; // <applied-at ...
      }

      if ( get_print_trace( o ) )
        print_stack_trace( o );
    }
    return o;
  } else {
    if ( has_source() ) {
      if ( !print_uri( o, source_uri() ) )
        o << "(" << diagnostic::dict::lookup( ZED( NoSourceURI ) ) << ")";
      o << ":" << source_line();
      if ( source_column() )
        o << "," << source_column();

      if ( has_data() && data_loc_ != source_loc_ ) {
        o << " (" << diagnostic::dict::lookup( ZED( InData ) ) << ' ';
        if ( data_uri() && ::strcmp( data_uri(), source_uri() ) != 0 ) {
          if ( print_uri( o, data_uri() ) )
            o << ':';
        }
        o << data_line();
        if ( data_column() )
          o << ',' << data_column();
        o << ')';
      }

      if ( has_applied() ) {
        o << " (" << diagnostic::dict::lookup( ZED( AppliedAt ) ) << ' ';
        if ( applied_uri() && ::strcmp( applied_uri(), source_uri() ) != 0 ) {
          if ( print_uri( o, applied_uri() ) )
            o << ':';
        }
        o << applied_line();
        if ( applied_column() )
          o << ',' << applied_column();
        o << ')';
      }

      o << ": ";
    }
    return ZorbaException::print_impl( o );
  }
}

ostream& XQueryException::print_stack_trace( ostream &o ) const {
  XQueryStackTrace const &trace = query_trace();
  if ( !trace.empty() ) {
    print_format const format = get_print_format( o );
    bool const as_xml = format != format_text;
    bool const do_indent = format == format_xml_indented;

    if ( as_xml )
      o << indent << "<stack>" << if_nl << if_inc_indent;
    FOR_EACH( XQueryStackTrace, it, trace ) {
      XQueryStackTrace::fn_name_type const &fn_name = it->getFnName();
      char const *const fn_prefix = fn_name.prefix();
      XQueryStackTrace::fn_arity_type fn_arity = it->getFnArity();

      zstring filename( it->getFileName() );
      if ( ZA_BEGINS_WITH( filename, "file:" ) ) {
        URI::decode_file_URI( filename, filename );
        while ( ZA_BEGINS_WITH( filename, "//" ) )
          filename = filename.substr(1);
      }

      if ( as_xml ) {
        o << indent << "<call";
        if ( fn_prefix && *fn_prefix )
          o << " prefix=\"" << fn_prefix << '"';

        o << " namespace=\"" << fn_name.ns() << '"'
          << " local-name=\"" << fn_name.localname()
          << " arity=\"" << fn_arity << '"'
          << "\">" << if_nl; // <call ...

        o << if_inc_indent << indent << "<location uri=\"" << filename << '"';

        o << " line-begin=\"" << it->getLine() << '"';
        if ( it->getColumn() )
          o << " column-begin=\"" << it->getColumn() << '"';
        if ( it->getLineEnd() )
          o << " line-end=\"" << it->getLineEnd() << '"';
        if ( it->getColumnEnd() )
          o << " column-end=\"" << it->getColumnEnd() << '"';

        o << "/>" << if_nl // <location ...
          << if_dec_indent << "</call>" << if_nl;
      } else {
        o << fn_name << '#' << fn_arity
          << " <" << fn_name.ns() << "> "
          << '"' << filename << "\":"
          << it->getLine() << ',' << it->getColumn()
          << '\n';
      }
    } // FOR_EACH
    if ( as_xml )
      o << indent << "</stack>" << if_nl << if_dec_indent;
  }
  return o;
}

bool XQueryException::print_uri( ostream &o, char const *uri ) {
  if ( uri && *uri ) {
    bool const as_xml = get_print_format( o ) != format_text;
    switch ( uri::get_scheme( uri ) ) {
      case uri::none:
      case uri::file:
        try {
          o << (as_xml ? " uri=\"" : "<") 
            << fs::normalize_path( uri ) 
            << (as_xml ? '"' : '>');
          break;
        }
        catch ( ... ) {
          // fall back to printing as a URI
        }
        // no break;
      default:
        o << (as_xml ? " uri=\"" : "<" ) << uri << (as_xml ? '"' : '>');
    } // switch
    return true;
  } // if
  return false;
}

///////////////////////////////////////////////////////////////////////////////

XQueryException
make_xquery_exception( char const *raise_file,
                       ZorbaException::line_type raise_line,
                       Diagnostic const &diagnostic,
                       internal::diagnostic::parameters const &params,
                       internal::diagnostic::location const &loc ) {
  internal::diagnostic::parameters::value_type message( diagnostic.message() );
  params.substitute( &message );
  XQueryException xe( diagnostic, raise_file, raise_line, message.c_str() );
  if ( loc )
    xe.set_source(
      loc.file(), loc.line(), loc.column(), loc.line_end(), loc.column_end()
    );
  return xe;
}

XQueryException*
new_xquery_exception( char const *raise_file,
                      ZorbaException::line_type raise_line,
                      Diagnostic const &diagnostic,
                      internal::diagnostic::parameters const &params,
                      internal::diagnostic::location const &loc ) {
  internal::diagnostic::parameters::value_type message( diagnostic.message() );
  params.substitute( &message );
  XQueryException *const xe =
    new XQueryException( diagnostic, raise_file, raise_line, message.c_str() );
  if ( loc )
    xe->set_source(
      loc.file(), loc.line(), loc.column(), loc.line_end(), loc.column_end()
    );
  return xe;
}

void set_applied( ZorbaException &ze, char const *file,
                  XQueryException::line_type line,
                  XQueryException::column_type col,
                  XQueryException::line_type line_end,
                  XQueryException::column_type col_end,
                  bool overwrite ) {
  if ( XQueryException *const xe = dynamic_cast<XQueryException*>( &ze ) ) {
    if ( !xe->has_applied() || overwrite )
      xe->set_applied( file, line, col, line_end, col_end );
  } else {
    XQueryException new_xe(
      ze.diagnostic(), ze.raise_file(), ze.raise_line(), ze.what()
    );
    new_xe.set_applied( file, line, col, line_end, col_end );
    throw new_xe;
  }
}

void set_data( ZorbaException &ze, char const *file,
               XQueryException::line_type line,
               XQueryException::column_type col,
               XQueryException::line_type line_end,
               XQueryException::column_type col_end,
               bool overwrite ) {
  if ( XQueryException *const xe = dynamic_cast<XQueryException*>( &ze ) ) {
    if ( !xe->has_data() || overwrite )
      xe->set_data( file, line, col, line_end, col_end );
  } else {
    XQueryException new_xe(
      ze.diagnostic(), ze.raise_file(), ze.raise_line(), ze.what()
    );
    new_xe.set_data( file, line, col, line_end, col_end );
    throw new_xe;
  }
}

void set_source( ZorbaException &ze, char const *file,
                 XQueryException::line_type line,
                 XQueryException::column_type col,
                 XQueryException::line_type line_end,
                 XQueryException::column_type col_end,
                 bool overwrite ) {
  if ( XQueryException *const xe = dynamic_cast<XQueryException*>( &ze ) ) {
    if ( !xe->has_source() || overwrite )
      xe->set_source( file, line, col, line_end, col_end );
  } else {
    XQueryException new_xe(
      ze.diagnostic(), ze.raise_file(), ze.raise_line(), ze.what()
    );
    new_xe.set_source( file, line, col, line_end, col_end );
    throw new_xe;
  }
}

///////////////////////////////////////////////////////////////////////////////

} // namespace zorba
/* vim:set et sw=2 ts=2: */
