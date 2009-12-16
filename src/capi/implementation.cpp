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
#include "capi/implementation.h"

#include <sstream>
#include <memory>
#include <zorba/zorba.h>

#include "capi/query.h"
#include "capi/static_context.h"
#include "capi/capi_util.h"
#include "capi/error.h"

#include "api/staticcontextimpl.h"
#include "api/xqueryimpl.h"

#include "context/static_context.h"


using namespace zorba;

#define ZORBA_IMPLEMENTATION_TRY try {

#define ZORBA_IMPLEMENTATION_CATCH_NOTIFY \
    return XQC_NO_ERROR; \
    } catch (QueryException& qe) { \
      if (handler) { \
        handler->error(handler, Error::convert_xquery_error(qe.getErrorCode()), \
                       ZorbaException::getErrorCodeAsString(qe.getErrorCode()).c_str(), \
                       qe.getDescription().c_str(), \
                       qe.getQueryURI().c_str(), \
                       qe.getLineBegin(), \
                       qe.getColumnBegin()); \
      } \
      return Error::convert_xquery_error(qe.getErrorCode());      \
    } catch (ZorbaException &ze) { \
      return Error::convert_xquery_error(ze.getErrorCode());  \
    } catch (...) { \
      return XQC_INTERNAL_ERROR; \
    }

namespace zorbac {

  XQC_Error
  Implementation::create_context(XQC_Implementation* impl, XQC_StaticContext** context)
  {
    try {
      Zorba* lZorba = static_cast<Zorba*>(impl->data);

      std::auto_ptr<XQC_StaticContext_s> lContext(new XQC_StaticContext_s());
      std::auto_ptr<zorbac::StaticContext> lInnerContext(new zorbac::StaticContext());

      lInnerContext->theContext = lZorba->createStaticContext();

      zorbac::StaticContext::assign_functions(lContext.get());

      (*context) = lContext.release();
      (*context)->data = lInnerContext.release();

      return XQC_NO_ERROR;
    } catch (ZorbaException& e) {
      return Error::convert_xquery_error(e.getErrorCode());
    } catch (...) {
      return XQC_INTERNAL_ERROR; 
    }
  }

  XQC_Error 
  Implementation::prepare(XQC_Implementation* impl, 
                          const char* query_string,
                          XQC_StaticContext* context, 
                          XQC_ErrorHandler* handler,
                          XQC_Query** query)
  {
    ZORBA_IMPLEMENTATION_TRY
      Zorba* lZorba = static_cast<Zorba*>(impl->data);

      std::auto_ptr<XQC_Query_s>   lQuery(new XQC_Query_s());
      std::auto_ptr<zorbac::Query> lInnerQuery(new zorbac::Query());
      if (handler)
        lInnerQuery->theErrorHandler = handler;

      if (context) {
        zorba::StaticContext_t lContext = 
              (static_cast<zorbac::StaticContext*> (context->data))->theContext;

        // reference counting in the smartptr takes care of garbage collection
        lInnerQuery->theQuery = lZorba->compileQuery(query_string, lContext);
      } else {
        lInnerQuery->theQuery = lZorba->compileQuery(query_string);
      }

      Query::assign_functions(lQuery.get());

      (*query)   = lQuery.release();
      (*query)->data = lInnerQuery.release(); 
    ZORBA_IMPLEMENTATION_CATCH_NOTIFY
  }

  XQC_Error 
  Implementation::prepare_file(XQC_Implementation* impl, 
                               FILE* query_file,
                               XQC_StaticContext* context, 
                               XQC_ErrorHandler* handler,
                               XQC_Query** query)
  {
    ZORBA_IMPLEMENTATION_TRY 
      Zorba* lZorba = static_cast<Zorba*>(impl->data);

      std::auto_ptr<XQC_Query_s>   lQuery(new XQC_Query_s());
      std::auto_ptr<zorbac::Query> lInnerQuery(new zorbac::Query());
      if (handler)
        lInnerQuery->theErrorHandler = handler;

      std::stringstream lStream;
      CAPIUtil::getIStream(query_file, lStream);

      if (context) {
        zorba::StaticContext_t lContext = 
              (static_cast<zorbac::StaticContext*> (context->data))->theContext;
        lInnerQuery->theQuery = lZorba->compileQuery(lStream, lContext);
      } else {
        lInnerQuery->theQuery = lZorba->compileQuery(lStream);
      }

      Query::assign_functions(lQuery.get());

      *query   = lQuery.release();
      (*query)->data = lInnerQuery.release();

      return XQC_NO_ERROR;
    ZORBA_IMPLEMENTATION_CATCH_NOTIFY
  }

  XQC_Error
  Implementation::prepare_stream(XQC_Implementation* impl, 
                                 XQC_InputStream* stream,
                                 XQC_StaticContext* context, 
                                 XQC_ErrorHandler* handler,
                                 XQC_Query **query)
  {
    ZORBA_IMPLEMENTATION_TRY 
      Zorba* lZorba = static_cast<Zorba*>(impl->data);

      std::auto_ptr<XQC_Query_s> lQuery(new XQC_Query_s());
      std::auto_ptr<zorbac::Query> lInnerQuery(new zorbac::Query());
      if (handler)
        lInnerQuery->theErrorHandler = handler;

      std::stringstream lStream;
      {
        char lBuf[1024];
        memset(lBuf, 0, 1024);
        int lRead = 0;
        while ( (lRead = stream->read(stream, lBuf, 1024)) >= 1024 ) {
          lStream.write(lBuf, lRead);
        }
        if (lRead > 0) {
          assert (lRead < 1024);
          lStream.write(lBuf, lRead);
        }

        stream->free(stream);
        if (lRead == -1) {
          // QQQ right error?
          return XQC_STATIC_ERROR; 
        }
      }

      if (context) {
        zorba::StaticContext_t lContext = 
              (static_cast<zorbac::StaticContext*> (context->data))->theContext;
        lInnerQuery->theQuery = lZorba->compileQuery(lStream, lContext);
      } else {
        lInnerQuery->theQuery = lZorba->compileQuery(lStream);
      }

      Query::assign_functions(lQuery.get());

      *query   = lQuery.release();
      (*query)->data = lInnerQuery.release();

    ZORBA_IMPLEMENTATION_CATCH_NOTIFY 
  }

  void
  Implementation::free(XQC_Implementation* impl)
  {
    try {
      Zorba* lZorba = static_cast<Zorba*>(impl->data);
      lZorba->shutdown();

      delete impl;
    } catch (ZorbaException&) {
      assert(false);
    } catch (...) {
      assert(false);
    }
  }

  void
  Implementation::assign_functions(XQC_Implementation* impl)
  {
    impl->create_context = Implementation::create_context;
    impl->prepare        = Implementation::prepare;
    impl->prepare_file   = Implementation::prepare_file;
    impl->prepare_stream = Implementation::prepare_stream;
    impl->free           = Implementation::free;
  }

} /* namespace zorbac */
