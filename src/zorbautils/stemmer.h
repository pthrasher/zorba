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
 
#ifndef ZORBA_STEMMER_H
#define ZORBA_STEMMER_H

#include <zorba/locale.h>

#include "zorbatypes/zstring.h"

namespace zorba {

/**
 * A %Stemmer is used to "stem" words.
 */
class Stemmer {
public:
  virtual ~Stemmer();

  /**
   * Gets an instance of a %Stemmer for the given language.
   *
   * @param lang The language for the stemmer.
   * @return Returns said %Stemmer or \c NULL if no stemmer is availabe for the
   * given language.
   */
  static Stemmer const* get( locale::iso639_1::type lang );

  /**
   * Gets the stem of the given word.
   *
   * @param word The word to stem.
   * @param result A pointer to the result string.
   */
  virtual void stem( zstring const &word, zstring *result ) const = 0;

protected:
  Stemmer() { }
};

} // namespace zorba
#endif  /* ZORBA_STEMMER_H */
/* vim:set et sw=2 ts=2: */
