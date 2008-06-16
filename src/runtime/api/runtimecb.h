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
#ifndef XQP_RUNTIMECB_H
#define XQP_RUNTIMECB_H

#include <stack>


namespace zorba {

namespace store
{
  class Item;
}

  class static_context;
  class dynamic_context;
  class CollationCache;
  

class RuntimeCB 
{
public:
  RuntimeCB() 
    :
    theStaticContext(0),
    theDynamicContext(0),
    theCollationCache(0)
  {
  }

  // TODO remove the static context from here
  static_context           * theStaticContext;  
  dynamic_context          * theDynamicContext; 
  CollationCache           * theCollationCache; 

  std::stack<store::Item*>   theNodeConstuctionPath; 
};

} /* namespace zorba */
#endif
