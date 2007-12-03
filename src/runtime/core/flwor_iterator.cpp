/*
 *  Copyright 2006-2007 FLWOR Foundation.
 *  Author: Tim Kraska
 *
 */
#include "runtime/core/flwor_iterator.h"
#include "runtime/core/item_iterator.h"
#include "util/zorba.h"
#include "errors/Error.h"
#include "store/api/item.h"
#include "store/api/temp_seq.h"
#include "compiler/expression/expr.h"
#include "runtime/booleans/BooleanImpl.h"
#include "runtime/visitors/planitervisitor.h"

namespace xqp
{

  FLWORIterator::ForLetClause::ForLetClause ( std::vector<var_iter_t> aForVars,
          PlanIter_t& aInput ) :
      type ( FOR ), forVars ( aForVars ), input ( aInput )
  {
  }

  FLWORIterator::ForLetClause::ForLetClause ( std::vector<var_iter_t> aForVars,
          std::vector<var_iter_t> aPosVars, PlanIter_t& aInput ) :
      type ( FOR ), forVars ( aForVars ), posVars ( aPosVars ), input ( aInput )
  {
  }

  FLWORIterator::ForLetClause::ForLetClause ( std::vector<ref_iter_t> aLetVars,
          PlanIter_t& aInput, bool aNeedsMaterialization ) :
      type ( LET ), letVars ( aLetVars ), input ( aInput ),
      needsMaterialization ( aNeedsMaterialization )
  {
  }

  void FLWORIterator::ForLetClause::accept ( PlanIterVisitor& v ) const
  {
    // TODO correct for visitor
    switch ( type )
    {
      case FOR:
//         os << IT_DEPTH << "<for_clause varRefNB=\""<< forVars.size() << "\" posRefNb=\"" << posVars.size() << "\"" << std::endl;
        input->accept(v);
//         os << IT_DEPTH << "</for_clause>" << std::endl;
        break;
      case LET:
//         os << IT_DEPTH << "<let_clause refNb=\"" << letVars.size() << "\">" << std::endl;
        input->accept(v);
//         os << IT_DEPTH << "</let_clause>" << std::endl;
        break;
      default:
        assert ( false );

    }
//     return os;
  }
  

  FLWORIterator::OrderSpec::OrderSpec ( PlanIter_t aOrderByIter, bool aEmpty_least,
                                        bool aDescending ) : orderByIter(aOrderByIter), 
                                        empty_least(aEmpty_least), descending(aDescending)
  {
  }

  FLWORIterator::OrderByClause::OrderByClause (
      std::vector<FLWORIterator::OrderSpec> aOrderSpecs, bool aStable ) : orderSpecs(aOrderSpecs),
      stable(aStable)
  {
  }
  
  void FLWORIterator::OrderSpec::accept ( PlanIterVisitor& v ) const {
    // TODO
//     os << IT_DEPTH << "<order_spec empty_least=\"" << empty_least << "\" descending=\"" << descending << "\" >"<< std::endl;
    orderByIter->accept(v);
//     os << IT_DEPTH <<"</order_spec>" << std::endl;
  }

  
  void FLWORIterator::OrderByClause::accept ( PlanIterVisitor& v ) const {
    // TODO
//     os << IT_DEPTH << "<order_by_clause stable=\"" << stable << "\" >" << std::endl;
    std::vector<OrderSpec>::const_iterator iter;
    for ( iter = orderSpecs.begin() ; iter != orderSpecs.end(); iter++ )
    {
      iter->accept ( v );
    }
//     os << IT_DEPTH << "</order_by_clause>" << std::endl;
  }

  FLWORIterator::FLWORIterator ( const yy::location& loc,
                                 std::vector<FLWORIterator::ForLetClause> &aForLetClauses,
                                 PlanIter_t& aWhereClause, FLWORIterator::OrderByClause* aOrderByClause,
                                 PlanIter_t& aReturnClause, bool aWhereClauseReturnsBooleanPlus ) :
      Batcher<FLWORIterator> ( loc ), forLetClauses ( aForLetClauses ),
      whereClause ( aWhereClause ), orderByClause ( aOrderByClause ),
      returnClause ( aReturnClause ),
      whereClauseReturnsBooleanPlus ( aWhereClauseReturnsBooleanPlus ),
      bindingsNb ( aForLetClauses.size() ),
      orderMap(0)
  {
    std::cout << "*********************Size" << orderByClause->orderSpecs.size()  << std::endl;
    if(orderByClause != 0 && orderByClause->orderSpecs.size() > 0){
      orderMap = new order_map_t( &(orderByClause->orderSpecs) );
    }else{
      orderByClause = 0;
    }
    store = zorba::getStore();
  }
  
  FLWORIterator::~FLWORIterator(){
    delete orderByClause;
    if(orderMap != 0){
      delete orderMap;
    }
  }
  
  

  Item_t FLWORIterator::nextImpl ( PlanState& planState )
  {
    int curVar = 0;
    PlanIteratorState* state;
    vector<string>::iterator iter;
    Item_t curItem;
    STACK_INIT ( PlanIteratorState, state, planState );
    varBindingState = new int[forLetClauses.size() ];
    for ( xqp_uint i = 0; i < forLetClauses.size(); i++ )
    {
      varBindingState[i] = 0;
    }
    while ( true )
    {

      while ( curVar != bindingsNb )
      {
        if ( bindVariable ( curVar, planState ) )
        {
          curVar++;
        }
        else
        {
          resetInput ( curVar, planState );
          curVar--;
          //FINISHED
          if ( curVar == -1 )
          {
            if(orderByClause != 0){
              curOrderPos = orderMap->begin();             
              while(curOrderPos != orderMap->end()){
                curOrderResultSeq = curOrderPos->second;
                curItem = curOrderResultSeq->next();
                while(curItem != 0){
                  STACK_PUSH(curItem, state);
                  curItem = curOrderResultSeq->next();
                }
                curOrderPos++;
              }
            }
            STACK_PUSH ( NULL, state );
            goto stop;
          }
        }
      }
      if ( evalWhereClause ( planState ) ) {
        if(orderByClause == 0){
          while ( true )
          {
            curItem = this->consumeNext ( returnClause, planState );
            if ( curItem == NULL )
            {
              curVar = bindingsNb - 1;
              this->resetChild ( returnClause, planState );
              break;
            }
            else
            {
              STACK_PUSH ( curItem, state );
            }
          }
        }else{
          matResultAndOrder(planState);
          curVar = bindingsNb - 1;
        }
      } else {
        curVar = bindingsNb - 1;
      }
    }
  stop:
    STACK_PUSH ( NULL, state );
    STACK_END();
  }


  void FLWORIterator::matResultAndOrder (PlanState& planState){
    assert(orderByClause != 0);
    vector<OrderSpec> lOrderSpecs = orderByClause->orderSpecs;
    //FIXME hould be a const iterator after the change of Plan_Iter
    std::vector<OrderSpec>::iterator lSpecIter = lOrderSpecs.begin();
    std::vector<Item_t> orderKey;
    while(lSpecIter != lOrderSpecs.end()){
      Item_t lItem = consumeNext(lSpecIter->orderByIter, planState);
      orderKey.push_back(lItem);
      //Test for singleton
      if(lItem != 0){
        lItem = consumeNext(lSpecIter->orderByIter, planState);
        if(lItem != 0){
           ZORBA_ERROR_ALERT(
              error_messages::XPTY0004_STATIC_TYPE_ERROR,
              error_messages::STATIC_ERROR,
              NULL,
              false,
              "Expected a singleton");
        }
      }
      resetChild(lSpecIter->orderByIter, planState);
      ++lSpecIter;
    }
    Iterator_t iterWrapper = new PlanIterWrapper ( returnClause, planState );
    TempSeq_t result = store->createTempSeq ( iterWrapper, false );
    orderMap->insert(std::pair<std::vector<Item_t> , Iterator_t>(orderKey, result->getIterator()));
    this->resetChild ( returnClause, planState );
  }

  bool FLWORIterator::evalWhereClause ( PlanState& planState )
  {
    if ( whereClause == NULL )
    {
      return true;
    }
    if ( whereClauseReturnsBooleanPlus )
    {
      Item_t boolValue = this->consumeNext ( whereClause, planState );
      if ( boolValue == NULL )
      {
        return false;
      }
      bool value = boolValue->getBooleanValue();
      return value;
    }
    Item_t item = FnBooleanIterator::effectiveBooleanValue ( loc, planState, whereClause );
    this->resetChild ( whereClause, planState );
    return item->getBooleanValue();
  }

  void FLWORIterator::resetInput ( int varNb, PlanState& planState )
  {
    FLWORIterator::ForLetClause lForLetClause = forLetClauses[varNb];
    this->resetChild ( lForLetClause.input, planState );
    varBindingState[varNb] = 0;
  }


  bool FLWORIterator::bindVariable ( int varNb, PlanState& planState )
  {
    FLWORIterator::ForLetClause lForLetClause = forLetClauses[varNb];
    switch ( lForLetClause.type )
    {
      case ForLetClause::FOR :
      {
        Item_t lItem = this->consumeNext ( lForLetClause.input, planState );
        if ( lItem == NULL )
        {
          return false;
        }
        ++varBindingState[varNb];
        for ( std::vector<var_iter_t>::iterator forIter = lForLetClause.forVars.begin(); forIter
                != lForLetClause.forVars.end(); forIter++ )
        {
          var_iter_t variable = ( *forIter );
          variable->bind ( lItem );
        }
        if ( !lForLetClause.posVars.empty() )
        {
          Item_t posItem = zorba::getItemFactory()->createInteger ( varBindingState[varNb] );
          for ( std::vector<var_iter_t>::iterator posIter = lForLetClause.posVars.begin(); posIter != lForLetClause.posVars.end(); posIter++ )
          {
            var_iter_t variable = ( *posIter );
            variable->bind ( posItem );
          }
        }
        //TODO Pos Bindings
        return true;
      }
      case ForLetClause::LET :
      {
        //return false if the Var-Variable was already bound
        if ( varBindingState[varNb] == 1 )
        {
          return false;
        }
        Iterator_t iterWrapper = new PlanIterWrapper ( lForLetClause.input, planState );
        if ( lForLetClause.needsMaterialization )
        {
          TempSeq_t tmpSeq = store->createTempSeq ( iterWrapper, true );
          for ( std::vector<ref_iter_t>::iterator letIter = lForLetClause.letVars.begin(); letIter
                  != lForLetClause.letVars.end(); letIter++ )
          {
            ( *letIter )->bind ( tmpSeq->getIterator() );
          }
        }
        else
        {
          for ( std::vector<ref_iter_t>::iterator letIter = lForLetClause.letVars.begin(); letIter
                  != lForLetClause.letVars.end(); letIter++ )
          {
            ( *letIter )->bind ( iterWrapper );
          }
        }
        ++varBindingState[varNb];
        return true;
      }
      default:
        assert ( false );
    }
    return false;
  }

  void FLWORIterator::resetImpl ( PlanState& planState )
  {
  }

  void FLWORIterator::releaseResourcesImpl ( PlanState& planState )
  {
  }

  uint32_t FLWORIterator::getStateSizeOfSubtree() const
  {
    int32_t size = 0;
    std::vector<FLWORIterator::ForLetClause>::const_iterator iter;
    for ( iter = forLetClauses.begin() ; iter != forLetClauses.end(); iter++ )
    {
      size += iter->input->getStateSizeOfSubtree();
    }

    size += returnClause->getStateSizeOfSubtree();

    if ( whereClause != NULL )
      size += whereClause->getStateSizeOfSubtree();

    if(orderByClause != NULL){
      std::vector<OrderSpec>::const_iterator iter;
      for ( iter = orderByClause->orderSpecs.begin() ; iter != orderByClause->orderSpecs.end(); iter++ )
      {
        size += iter->orderByIter->getStateSizeOfSubtree();
      }
    }


    return this->getStateSize() + size;
  }

  void FLWORIterator::setOffset ( PlanState& planState, uint32_t& offset )
  {
    this->stateOffset = offset;
    offset += this->getStateSize();

    std::vector<FLWORIterator::ForLetClause>::const_iterator iter;
    for ( iter = forLetClauses.begin() ; iter != forLetClauses.end(); iter++ )
    {
      iter->input->setOffset ( planState, offset );
    }

    returnClause->setOffset ( planState, offset );

    if ( whereClause != NULL )
      whereClause->setOffset ( planState, offset );
      
    if(orderByClause != NULL){
      std::vector<OrderSpec>::const_iterator iter;
      for ( iter = orderByClause->orderSpecs.begin() ; iter != orderByClause->orderSpecs.end(); iter++ )
      {
        iter->orderByIter->setOffset ( planState, offset );
      }
    }

  }

  void FLWORIterator::accept ( PlanIterVisitor& v ) const
  {
    // TODO
    v.beginVisit(*this);
    std::vector<FLWORIterator::ForLetClause>::const_iterator iter;
    for ( iter = forLetClauses.begin() ; iter != forLetClauses.end(); iter++ )
    {
      iter->accept(v);
    }
    if ( whereClause != NULL )
    {
//       os << "<where_clause>" << std::endl;
      whereClause->accept ( v );
//       os << "</where_clause>" << std::endl;
    }
    if ( orderByClause != NULL )
    {
      orderByClause->accept ( v );
    }
    returnClause->accept ( v );
  }

  int8_t 
  FLWORIterator::OrderKeyCmp::compare(const Item_t& s1, const Item_t& s2, bool desc, bool emptyLeast) const{
    if(s1 == 0){
      if(s2 == 0){
        return descAsc(0, desc);
      }
      if(emptyLeast){
        return descAsc(-1, desc);
      }else{
        return descAsc(1, desc);
      }
    }else if(s2 == 0){
      if(emptyLeast){
        return descAsc(1, desc);
      }else{
        return descAsc(-1, desc);
      }
    }else{

      return descAsc(CompareIterator::valueCompare(s1 , s2), desc);
    }
  }
  
  int8_t 
  FLWORIterator::OrderKeyCmp::descAsc(int8_t result, bool desc) const {
    if(desc){
      switch(result){
      case -1:
        return 1;
      case 1:
        return -1;
      case 0:
        return 0;
      }
    }else{
      return result;
    }
    assert(false);
  }

  bool
  FLWORIterator::OrderKeyCmp::operator() ( const std::vector<Item_t>& s1, const std::vector<Item_t>& s2 ) const  { 
    std:cerr << "s1: " << s1.size() << "s2:" << s2.size() << "order" << mOrderSpecs->size() << std::endl;
    assert(s1.size() == s2.size());
    assert(s1.size() == mOrderSpecs->size());
    std::vector<Item_t>::const_iterator s1iter = s1.begin();
    std::vector<Item_t>::const_iterator s2iter = s2.begin();
    std::vector<OrderSpec>::const_iterator orderSpecIter = mOrderSpecs->begin();
    while(s1iter != s1.end()){
      int8_t cmp = compare(*s1iter, *s2iter, orderSpecIter->descending, orderSpecIter->empty_least);
      if(cmp == 1){
        return false;
      }else if(cmp == -1){
        return true;
      }
      ++s1iter;
      ++s2iter;
      ++orderSpecIter;
    }
    return false;    
  }
}
