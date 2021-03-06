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
#pragma once
#ifndef ZORBA_COMPILER_VAR_EXPR
#define ZORBA_COMPILER_VAR_EXPR

#include "annotations/annotations.h"
#include "compiler/expression/expr_base.h"

namespace zorba
{

class flwor_clause;
class forletwin_clause;
class forlet_clause;
class copy_clause;
class var_expr;
class VarInfo;
class var_set_expr;
class block_expr;


/******************************************************************************

  var_expr represents a variable. There is one var_expr for each distinct
  variable declared anywhere inside a query body or prolog.

  var_expr represents both the var declaration and all references of the var.
  However, each distinct reference to a var is wrapped in wrapper_expr. For
  example, the exprs F($x) and G($x) are modelled in the expr tree as:

       F               G
       |               |
   wrapper_expr    wrapper_expr
         \             /
          \           /
           var_expr($x)


  For context vars with a defining expr, the mapping between the var qname and
  the defining expr is explicitly stored by creating an
  fn:ctxvar-assign(qname_expr, def_expr) expr (see method
  wrap_in_globalvar_assign() in translator.cpp).

  For vars declared in FOR, LET, or WINDOW clauses, their defining expr is
  stored in the associated clause (see theForletClause data member below).

  theUniqueId:
  ------------
  A unique numeric id for variales whose value is stored in the dynamic context,
  ie, prolog and local vars. It is used as an index into an array that stores
  the values.

  theKind:
  --------
  The kind of the variable (see var_kind enum below)

  theVarName:
  -----------
  The fully expanded qname of the var (qname item)

  theDeclaredType:
  ----------------
  The type, if any, specified in the declaration of the variable

  theBlockExpr:
  -------------
  If this is a prolog or a local var, theBlockExpr points to the block expr
  where the var is declared at (prolog and local vars are always declared 
  in block exprs).

  theFlworClause:
  ---------------
  If this is a var declared in flwor clause, theFlworClause points to the
  defining clause. That clause also contains the defining expr for the var
  and a pointer back to this var_exr.

  theCopyClause:
  --------------
  If this is a var declared in a copy clause of a transform expr, theCopyClause
  points to that clause. That clause contains the defining expr for the var and
  a pointer back to this var_exr.

  theParamPos:
  ------------
  For arg vars, it is the position, within the param list, of the parameter that
  is bound to this arg var.

  theSetExprs:
  ------------
  For global and local vars, this vector contains a pointer to the var_decl_expr
  for the variable and to each var_set_expr for the same var.

  theIsExternal:
  --------------
  Whether this is an external variable or not (for prolog vars only).

  theIsPrivate:
  -------------
  Whether this is a private variable or not (for prolog vars only).

  theIsMutable:
  -------------
  Whether this is a mutable variable or not (for prolog and local vars).

  theHasInitializer:
  ------------------
   Whether the variable has an initializing expr or not (for prolog vars only).
*******************************************************************************/
class var_expr : public expr
{
  friend class expr;
  friend class ExprManager;
  friend class VarInfo;

public:
  typedef std::vector<var_set_expr*> VarSetExprs;

  enum var_kind
  {
    unknown_var = 0,

    eval_var,  // TODO: remove (it is used only in the debugger_expr)

    for_var,
    let_var,
    pos_var,
    score_var,
    win_var,
    wincond_out_var,
    wincond_out_pos_var,
    wincond_in_var,
    wincond_in_pos_var,
    count_var,
    groupby_var,
    non_groupby_var,

    copy_var,

    catch_var,

    prolog_var,

    local_var,

    arg_var
  };

protected:
  ulong                 theUniqueId;

  var_kind              theVarKind;

  store::Item_t         theName;

  xqtref_t              theDeclaredType;

  block_expr          * theBlockExpr;

  flwor_clause        * theFlworClause;

  copy_clause         * theCopyClause;

  csize                 theParamPos;

  VarSetExprs           theSetExprs;

  VarInfo             * theVarInfo;

  AnnotationList        theAnnotations;

  csize                 theNumRefs;

  bool                  theIsExternal;

  bool                  theIsPrivate;

  bool                  theIsMutable;

  bool                  theHasInitializer;

public:
  static std::string decode_var_kind(enum var_kind);

protected:
  var_expr(
      CompilerCB* ccb,
      static_context* sctx,
      user_function* udf,
      const QueryLoc& loc,
      var_kind k,
      store::Item* name);

  var_expr(user_function* udf, const var_expr& source);

  virtual ~var_expr();

public:
  void set_var_info(VarInfo* v);

  AnnotationList const& get_annotations() const {
    return theAnnotations;
  }

  void swap_annotations( AnnotationList &a ) {
    theAnnotations.swap( a );
  }

  VarInfo* get_var_info() const { return theVarInfo; }

  ulong get_unique_id() const { return theUniqueId; }

  void set_unique_id(ulong v);

  store::Item* get_name() const;

  var_kind get_kind() const { return theVarKind; }

  void set_kind(var_kind k) { theVarKind = k; }

  csize get_num_refs() const { return theNumRefs; }

  void add_ref() { ++theNumRefs; }

  bool is_private() const { return theIsPrivate; }

  void set_private(bool v) { theIsPrivate = v; }

  bool is_external() const { return theIsExternal; }

  void set_external(bool v);

  bool has_initializer() const { return theHasInitializer; }

  void set_has_initializer(bool v);

  bool is_mutable() const { return theIsMutable; }

  void set_mutable(bool v) { theIsMutable = v; }

  xqtref_t get_type() const;

  void set_type(xqtref_t t);

  void set_block_expr(const block_expr* b) { theBlockExpr = const_cast<block_expr*>(b); }

  block_expr* get_block_expr() const { return theBlockExpr; }

  void set_flwor_clause(flwor_clause* c) { theFlworClause = c; }

  flwor_clause* get_flwor_clause() const { return theFlworClause; }

  forletwin_clause* get_forletwin_clause() const;

  forlet_clause* get_forlet_clause() const;

  copy_clause* get_copy_clause() const { return theCopyClause; }

  void set_copy_clause(copy_clause* c) { theCopyClause = c; }

  expr* get_domain_expr() const;

  const var_expr* get_pos_var() const;

  csize get_param_pos() const { return theParamPos; }

  void set_param_pos(csize pos) { theParamPos = pos; }

  void add_set_expr(expr* e);

  void remove_set_expr(expr* e);

  csize num_set_exprs() const { return theSetExprs.size(); }

  var_set_expr* get_set_expr(csize i) const { return theSetExprs[i]; }

  VarSetExprs::const_iterator setExprsBegin() const { return theSetExprs.begin(); }

  VarSetExprs::const_iterator setExprsEnd() const { return theSetExprs.end(); }

  bool is_context_item() const;

  void compute_scripting_kind();

  void accept(expr_visitor&);

  std::ostream& put(std::ostream&) const;
};


struct GlobalBinding
{
  var_expr  * theVar;
  expr      * theExpr;
  bool        theIsExternal;

public:
  GlobalBinding() : theIsExternal(false) {}

  GlobalBinding(var_expr* v, expr* e, bool external)
    :
    theVar(v),
    theExpr(e),
    theIsExternal(external)
  {
  }

  virtual ~GlobalBinding() {}

  bool is_extern() const { return theIsExternal; }
};


}

#endif  // ZORBA_VAR_EXPR_H

/*
 * Local variables:
 * mode: c++
 * End:
 */
/* vim:set et sw=2 ts=2: */
