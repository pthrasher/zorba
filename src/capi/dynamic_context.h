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
#ifndef ZORBAC_DYNAMIC_CONTEXT_H
#define ZORBAC_DYNAMIC_CONTEXT_H

#include <zorba/zorbac.h>

namespace zorbac {

  class DynamicContext {
    public:
      static XQC_Error 
      set_context_item (XQC_DynamicContext* context, XQC_Sequence* value);

      static XQC_Error
      set_context_document(XQC_DynamicContext* context, const char* doc_uri, FILE* document);

      static XQC_Error
      set_variable(XQC_DynamicContext* context, const char* qname, XQC_Sequence* value);
      
      static XQC_Error
      set_variable_document(XQC_DynamicContext* context, const char* var_qname, const char* doc_uri, FILE* document);
      
      static XQC_Error 
      set_implicit_timezone(XQC_DynamicContext* context, int timezone);
      
      static void
      free(XQC_DynamicContext* context);

      static void
      assign_functions(XQC_DynamicContext* context);

  }; /* class DynamicContext */

} /* namespace zorbac */

#endif
