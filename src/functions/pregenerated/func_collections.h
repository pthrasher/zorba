/*
 * Copyright 2006-2012 The FLWOR Foundation.
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
 
// ******************************************
// *                                        *
// * THIS IS A GENERATED FILE. DO NOT EDIT! *
// * SEE .xml FILE WITH SAME NAME           *
// *                                        *
// ******************************************



#ifndef ZORBA_FUNCTIONS_COLLECTIONS_H
#define ZORBA_FUNCTIONS_COLLECTIONS_H


#include "common/shared_types.h"
#include "functions/function_impl.h"


namespace zorba {


void populate_context_collections(static_context* sctx);




//zorba-store-static-collections-ddl:create
class zorba_store_static_collections_ddl_create : public function
{
public:
  zorba_store_static_collections_ddl_create(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 1; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-ddl:delete
class zorba_store_static_collections_ddl_delete : public function
{
public:
  zorba_store_static_collections_ddl_delete(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return false; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-ddl:is-available-collection
class zorba_store_static_collections_ddl_is_available_collection : public function
{
public:
  zorba_store_static_collections_ddl_is_available_collection(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-ddl:available-collections
class zorba_store_static_collections_ddl_available_collections : public function
{
public:
  zorba_store_static_collections_ddl_available_collections(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  CODEGEN_DECL();
};


//fn:collection
class fn_collection : public function
{
public:
  fn_collection(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  bool isSource() const { return true; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:collection
class zorba_store_static_collections_dml_collection : public function
{
public:
  zorba_store_static_collections_dml_collection(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  xqtref_t getReturnType(const fo_expr* caller) const;

  bool isSource() const { return true; }

  FunctionConsts::AnnotationValue producesDistinctNodes() const 
  {
    return FunctionConsts::YES;
  }

  FunctionConsts::AnnotationValue producesSortedNodes() const 
  {
    return FunctionConsts::YES;
  }

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:collection-name
class zorba_store_static_collections_dml_collection_name : public function
{
public:
  zorba_store_static_collections_dml_collection_name(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return false; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:index-of
class zorba_store_static_collections_dml_index_of : public function
{
public:
  zorba_store_static_collections_dml_index_of(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return false; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:apply-insert
class zorba_store_static_collections_dml_apply_insert : public function
{
public:
  zorba_store_static_collections_dml_apply_insert(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return APPLYING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool propagatesInputNodes(expr* fo, csize producer) const;

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 1; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:insert-after
class zorba_store_static_collections_dml_insert_after : public function
{
public:
  zorba_store_static_collections_dml_insert_after(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 2; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:insert-before
class zorba_store_static_collections_dml_insert_before : public function
{
public:
  zorba_store_static_collections_dml_insert_before(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 2; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:insert-first
class zorba_store_static_collections_dml_insert_first : public function
{
public:
  zorba_store_static_collections_dml_insert_first(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 1; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:insert-last
class zorba_store_static_collections_dml_insert_last : public function
{
public:
  zorba_store_static_collections_dml_insert_last(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 1; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:apply-insert-first
class zorba_store_static_collections_dml_apply_insert_first : public function
{
public:
  zorba_store_static_collections_dml_apply_insert_first(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return APPLYING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool propagatesInputNodes(expr* fo, csize producer) const;

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 1; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:apply-insert-last
class zorba_store_static_collections_dml_apply_insert_last : public function
{
public:
  zorba_store_static_collections_dml_apply_insert_last(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return APPLYING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool propagatesInputNodes(expr* fo, csize producer) const;

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 1; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:apply-insert-before
class zorba_store_static_collections_dml_apply_insert_before : public function
{
public:
  zorba_store_static_collections_dml_apply_insert_before(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return APPLYING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool propagatesInputNodes(expr* fo, csize producer) const;

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 2; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:apply-insert-after
class zorba_store_static_collections_dml_apply_insert_after : public function
{
public:
  zorba_store_static_collections_dml_apply_insert_after(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return APPLYING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool propagatesInputNodes(expr* fo, csize producer) const;

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 2; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:delete
class zorba_store_static_collections_dml_delete : public function
{
public:
  zorba_store_static_collections_dml_delete(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  BoolAnnotationValue ignoresSortedNodes(expr* fo, csize producer) const;

  BoolAnnotationValue ignoresDuplicateNodes(expr* fo, csize producer) const;

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 0; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:delete-first
class zorba_store_static_collections_dml_delete_first : public function
{
public:
  zorba_store_static_collections_dml_delete_first(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return false; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:delete-last
class zorba_store_static_collections_dml_delete_last : public function
{
public:
  zorba_store_static_collections_dml_delete_last(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return false; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:edit
class zorba_store_static_collections_dml_edit : public function
{
public:
  zorba_store_static_collections_dml_edit(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 1; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:insert
class zorba_store_static_collections_dml_insert : public function
{
public:
  zorba_store_static_collections_dml_insert(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  bool mustCopyInputNodes(expr* fo, csize producer) const { return producer == 1; }

  void processPragma(expr*, const std::vector<pragma*>&) const;

  CODEGEN_DECL();
};


//zorba-store-static-collections-dml:truncate
class zorba_store_static_collections_dml_truncate : public function
{
public:
  zorba_store_static_collections_dml_truncate(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  unsigned short getScriptingKind() const { return UPDATING_EXPR; }

  bool accessesDynCtx() const { return true; }

  CODEGEN_DECL();
};


//zorba-store-indexes-static-ddl:is-available-index
class zorba_store_indexes_static_ddl_is_available_index : public function
{
public:
  zorba_store_indexes_static_ddl_is_available_index(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  CODEGEN_DECL();
};


//zorba-store-indexes-static-ddl:available-indexes
class zorba_store_indexes_static_ddl_available_indexes : public function
{
public:
  zorba_store_indexes_static_ddl_available_indexes(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  CODEGEN_DECL();
};


//zorba-store-static-integrity-constraints-ddl:is-activated-integrity-constraint
class zorba_store_static_integrity_constraints_ddl_is_activated_integrity_constraint : public function
{
public:
  zorba_store_static_integrity_constraints_ddl_is_activated_integrity_constraint(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  CODEGEN_DECL();
};


//zorba-store-static-integrity-constraints-ddl:activated-integrity-constraints
class zorba_store_static_integrity_constraints_ddl_activated_integrity_constraints : public function
{
public:
  zorba_store_static_integrity_constraints_ddl_activated_integrity_constraints(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  bool accessesDynCtx() const { return true; }

  CODEGEN_DECL();
};


//zorba-store-static-collections-ddl:is-declared-collection
class zorba_store_static_collections_ddl_is_declared_collection : public function
{
public:
  zorba_store_static_collections_ddl_is_declared_collection(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};


//zorba-store-static-collections-ddl:declared-collections
class zorba_store_static_collections_ddl_declared_collections : public function
{
public:
  zorba_store_static_collections_ddl_declared_collections(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};


//zorba-store-indexes-static-ddl:is-declared-index
class zorba_store_indexes_static_ddl_is_declared_index : public function
{
public:
  zorba_store_indexes_static_ddl_is_declared_index(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};


//zorba-store-indexes-static-ddl:declared-indexes
class zorba_store_indexes_static_ddl_declared_indexes : public function
{
public:
  zorba_store_indexes_static_ddl_declared_indexes(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};


//zorba-store-static-integrity-constraints-ddl:is-declared-integrity-constraint
class zorba_store_static_integrity_constraints_ddl_is_declared_integrity_constraint : public function
{
public:
  zorba_store_static_integrity_constraints_ddl_is_declared_integrity_constraint(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};


//zorba-store-static-integrity-constraints-ddl:declared-integrity-constraints
class zorba_store_static_integrity_constraints_ddl_declared_integrity_constraints : public function
{
public:
  zorba_store_static_integrity_constraints_ddl_declared_integrity_constraints(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {

  }

  CODEGEN_DECL();
};


//fn:uri-collection
class fn_uri_collection_3_0 : public function
{
public:
  fn_uri_collection_3_0(const signature& sig, FunctionConsts::FunctionKind kind)
    : 
    function(sig, kind)
  {
theXQueryVersion = StaticContextConsts::xquery_version_3_0;
  }

  CODEGEN_DECL();
};


} //namespace zorba


#endif
/*
 * Local variables:
 * mode: c++
 * End:
 */ 
