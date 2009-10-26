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

#include "zorbatypes/datetime.h"
#include "zorbatypes/duration.h"
#include "zorbatypes/numconversions.h"
#include "zorbatypes/datetime/parse.h"

#include "system/globalenv.h"

#include "types/casting.h"

#include "context/static_context.h"
#include "context/dynamic_context.h"

#include "compiler/api/compilercb.h"

#include "runtime/durations_dates_times/durations_dates_times.h"
#include "runtime/core/arithmetic_impl.h"
#include "runtime/api/runtimecb.h"
#include "runtime/visitors/planiter_visitor.h"

#include "store/api/item.h"
#include "store/api/item_factory.h"
#include "store/api/store.h"

namespace zorba
{

/**
 *______________________________________________________________________
 *
 * 10.5.1 fn:years-from-duration
 *
 * fn:years-from-duration($arg as xs:duration?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnYearsFromDurationIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;
  int32_t lYears;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    lYears = itemArg->getDurationValue().getYears();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(lYears)), 
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.2 fn:months-from-duration
 *
 * fn:months-from-duration($arg as xs:duration?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnMonthsFromDurationIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDurationValue().getMonths())),
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.3 fn:days-from-duration
 *
 * fn:days-from-duration($arg as xs:duration?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnDaysFromDurationIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDurationValue().getDays())),
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.4 fn:hours-from-duration
 *
 * fn:hours-from-duration($arg as xs:duration?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnHoursFromDurationIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDurationValue().getHours())),
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.5 fn:minutes-from-duration
 *
 * fn:minutes-from-duration($arg as xs:duration?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnMinutesFromDurationIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDurationValue().getMinutes())),
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.6 fn:seconds-from-duration
 *
 * fn:seconds-from-duration($arg as xs:duration?) as xs:decimal?
 *_______________________________________________________________________*/
bool
FnSecondsFromDurationIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;
  xqp_decimal lDecimal;
  bool lBool;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    lBool = Decimal::parseNativeDouble(itemArg->getDurationValue().getSeconds(), lDecimal);
    ZORBA_ASSERT(lBool);
    STACK_PUSH( GENV_ITEMFACTORY->createDecimal(result, lDecimal), state );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.7 fn:year-from-dateTime
 *
 * fn:year-from-dateTime($arg as xs:dateTime?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnYearFromDatetimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH(
        GENV_ITEMFACTORY->createInteger(
          result,
          Integer::parseInt(itemArg->getDateTimeValue().getYear())), state );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.8 fn:month-from-dateTime
 *
 * fn:month-from-dateTime($arg as xs:dateTime?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnMonthFromDatetimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDateTimeValue().getMonth())), 
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.9 fn:day-from-dateTime
 *
 * fn:day-from-dateTime($arg as xs:dateTime?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnDayFromDatetimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDateTimeValue().getDay())), 
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.10 fn:hours-from-dateTime
 *
 * fn:hours-from-dateTime($arg as xs:dateTime?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnHoursFromDatetimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDateTimeValue().getHours())), 
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.11 fn:minutes-from-dateTime
 *
 * fn:minutes-from-dateTime($arg as xs:dateTime?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnMinutesFromDatetimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDateTimeValue().getMinutes())), 
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.12 fn:seconds-from-dateTime
 *
 * fn:seconds-from-dateTime($arg as xs:dateTime?) as xs:decimal?
 *_______________________________________________________________________*/
bool
FnSecondsFromDatetimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;
  xqp_decimal lDecimal;
  bool lBool;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    lBool = Decimal::parseNativeDouble(itemArg->getDateTimeValue().getSeconds(), lDecimal);
    ZORBA_ASSERT(lBool);
    STACK_PUSH( GENV_ITEMFACTORY->createDecimal(result, lDecimal), state );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.13 fn:timezone-from-dateTime
 *
 * fn:timezone-from-dateTime($arg as xs:dateTime?) as xs:dayTimeDuration?
 *_______________________________________________________________________*/
bool
FnTimezoneFromDatetimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;
  xqp_dayTimeDuration tmpDuration;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    if (0 == Duration::fromTimezone(itemArg->getDateTimeValue().getTimezone(), tmpDuration))
      STACK_PUSH( GENV_ITEMFACTORY->createDayTimeDuration(result, &tmpDuration), state );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.14 fn:year-from-date
 *
 * fn:year-from-date($arg as xs:date?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnYearFromDateIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDateValue().getYear())), 
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.15 fn:month-from-date
 *
 * fn:month-from-date($arg as xs:date?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnMonthFromDateIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDateValue().getMonth())), 
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.16 fn:day-from-date
 *
 * fn:day-from-date($arg as xs:date?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnDayFromDateIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getDateValue().getDay())), 
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.17 fn:timezone-from-date
 *
 * fn:timezone-from-date($arg as xs:date?) as xs:dayTimeDuration?
 *_______________________________________________________________________*/
bool
FnTimezoneFromDateIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;
  xqp_dayTimeDuration tmpDuration;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    if (0 == Duration::fromTimezone(itemArg->getDateValue().getTimezone(), tmpDuration))
      STACK_PUSH( GENV_ITEMFACTORY->createDayTimeDuration(result, &tmpDuration), state );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.18 fn:hours-from-time
 *
 * fn:hours-from-time($arg as xs:time?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnHoursFromTimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getTimeValue().getHours())), 
      state 
    );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.19 fn:minutes-from-time
 *
 * fn:minutes-from-time($arg as xs:time?) as xs:integer?
 *_______________________________________________________________________*/
bool
FnMinutesFromTimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    STACK_PUSH( GENV_ITEMFACTORY->createInteger(
      result,
      Integer::parseInt(itemArg->getTimeValue().getMinutes())), 
      state 
    );
  }
  STACK_END (state);
}



/**
 *______________________________________________________________________
 *
 * 10.5.20 fn:seconds-from-time
 *
 * fn:seconds-from-time($arg as xs:time?) as xs:decimal?
 *_______________________________________________________________________*/
bool
FnSecondsFromTimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;
  xqp_decimal lDecimal;
  bool lBool;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  {
    itemArg = itemArg->getAtomizationValue();
    lBool = Decimal::parseNativeDouble(itemArg->getTimeValue().getSeconds(), lDecimal);
    ZORBA_ASSERT(lBool);
    STACK_PUSH( GENV_ITEMFACTORY->createDecimal(result, lDecimal), state );
  }
  STACK_END (state);
}


/**
 *______________________________________________________________________
 *
 * 10.5.21 fn:timezone-from-time
 *
 * fn:timezone-from-time($arg as xs:time?) as xs:dayTimeDuration?
 *_______________________________________________________________________*/
bool
FnTimezoneFromTimeIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t itemArg;
  xqp_dayTimeDuration tmpDuration;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(itemArg, theChildren[0].getp(), planState))
  if ( itemArg != NULL )
  {
    itemArg = itemArg->getAtomizationValue();
    if (0 == Duration::fromTimezone(itemArg->getTimeValue().getTimezone(), tmpDuration))
      STACK_PUSH( GENV_ITEMFACTORY->createDayTimeDuration(result, &tmpDuration), state );
  }
  STACK_END (state);
}

}
