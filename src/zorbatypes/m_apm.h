
/* 
 *  M_APM  -  m_apm.h
 *
 *  Copyright (C) 1999 - 2007   Michael C. Ring
 *
 *  Permission to use, copy, and distribute this software and its
 *  documentation for any purpose with or without fee is hereby granted,
 *  provided that the above copyright notice appear in all copies and
 *  that both that copyright notice and this permission notice appear
 *  in supporting documentation.
 *
 *  Permission to modify the software is granted. Permission to distribute
 *  the modified code is granted. Modifications are to be distributed by
 *  using the file 'license.txt' as a template to modify the file header.
 *  'license.txt' is available in the official MAPM distribution.
 *
 *  This software is provided "as is" without express or implied warranty.
 */
#pragma once
#ifndef M__APM__INCLUDED
#define M__APM__INCLUDED

#include <zorba/config.h>

#ifdef __cplusplus
/* Comment this line out if you've compiled the library as C++. */
#define APM_CONVERT_FROM_C
#endif

#ifdef APM_CONVERT_FROM_C
extern "C" {
#endif


typedef unsigned char UCHAR;


typedef struct  
{
  UCHAR * m_apm_data;
  long    m_apm_id;
  int     m_apm_refcount;       /* <- used only by C++ MAPM class */
  int     m_apm_malloclength;
  int     m_apm_datalength;
  int     m_apm_exponent;
  int     m_apm_sign;
} M_APM_struct;


typedef M_APM_struct *M_APM;


#define MAPM_LIB_VERSION \
    "MAPM Library Version 4.9.5  Copyright (C) 1999-2007, Michael C. Ring"
#define MAPM_LIB_SHORT_VERSION "4.9.5"


/*
 * convienient predefined constants
 */

extern  M_APM MM_Zero;
extern  M_APM MM_One;
extern  M_APM MM_Two;
extern  M_APM MM_Three;
extern  M_APM MM_Four;
extern  M_APM MM_Five;
extern  M_APM MM_Ten;

extern  M_APM MM_PI;
extern  M_APM MM_HALF_PI;
extern  M_APM MM_2_PI;
extern  M_APM MM_E;

extern  M_APM MM_LOG_E_BASE_10;
extern  M_APM MM_LOG_10_BASE_E;
extern  M_APM MM_LOG_2_BASE_E;
extern  M_APM MM_LOG_3_BASE_E;


/*
 *  function prototypes
 */

extern  M_APM m_apm_init(void);
extern void  m_apm_free(M_APM);
extern  void  m_apm_free_all_mem(void);
extern  void  m_apm_trim_mem_usage(void);
extern  char *m_apm_lib_version(char *);
extern  char *m_apm_lib_short_version(char *);

extern  void  m_apm_set_string(M_APM, char *);
extern  void  m_apm_set_double(M_APM, double);
extern  void  m_apm_set_long(M_APM, long);

extern  void  m_apm_to_string(char *, int, M_APM);
extern  void  m_apm_to_fixpt_string(char *, int, M_APM);
extern  void  m_apm_to_fixpt_stringex(char *, int, M_APM, char, char, int);
extern  char *m_apm_to_fixpt_stringexp(int, M_APM, char, char, int);
extern  void  m_apm_to_integer_string(char *, M_APM);

extern  void  m_apm_absolute_value(M_APM, M_APM);
extern  void  m_apm_negate(M_APM, M_APM);
extern  void  m_apm_copy(M_APM, M_APM);
extern  void  m_apm_round(M_APM, int, M_APM);
extern  int   m_apm_compare(M_APM, M_APM);
extern  int   m_apm_sign(M_APM);
extern  int   m_apm_exponent(M_APM);
extern  int   m_apm_significant_digits(M_APM);
extern  int   m_apm_is_integer(M_APM);
extern  int   m_apm_is_even(M_APM);
extern  int   m_apm_is_odd(M_APM);

extern  void  m_apm_gcd(M_APM, M_APM, M_APM);
extern  void  m_apm_lcm(M_APM, M_APM, M_APM);

extern  void  m_apm_add(M_APM, M_APM, M_APM);
extern  void  m_apm_subtract(M_APM, M_APM, M_APM);
extern  void  m_apm_multiply(M_APM, M_APM, M_APM);
extern  void  m_apm_divide(M_APM, int, M_APM, M_APM);
extern  void  m_apm_integer_divide(M_APM, M_APM, M_APM);
extern  void  m_apm_integer_div_rem(M_APM, M_APM, M_APM, M_APM);
extern  void  m_apm_reciprocal(M_APM, int, M_APM);
extern  void  m_apm_factorial(M_APM, M_APM);
extern  void  m_apm_floor(M_APM, M_APM);
extern  void  m_apm_ceil(M_APM, M_APM);
extern  void  m_apm_get_random(M_APM);
extern  void  m_apm_set_random_seed(char *);

extern  void  m_apm_sqrt(M_APM, int, M_APM);
extern  void  m_apm_cbrt(M_APM, int, M_APM);
extern  void  m_apm_log(M_APM, int, M_APM);
extern  void  m_apm_log10(M_APM, int, M_APM);
extern  void  m_apm_exp(M_APM, int, M_APM);
extern  void  m_apm_pow(M_APM, int, M_APM, M_APM);
extern  void  m_apm_integer_pow(M_APM, int, M_APM, int);
extern  void  m_apm_integer_pow_nr(M_APM, M_APM, int);

extern  void  m_apm_sin_cos(M_APM, M_APM, int, M_APM);
extern  void  m_apm_sin(M_APM, int, M_APM);
extern  void  m_apm_cos(M_APM, int, M_APM);
extern  void  m_apm_tan(M_APM, int, M_APM);
extern  void  m_apm_arcsin(M_APM, int, M_APM);
extern  void  m_apm_arccos(M_APM, int, M_APM);
extern  void  m_apm_arctan(M_APM, int, M_APM);
extern  void  m_apm_arctan2(M_APM, int, M_APM, M_APM);

extern  void  m_apm_sinh(M_APM, int, M_APM);
extern  void  m_apm_cosh(M_APM, int, M_APM);
extern  void  m_apm_tanh(M_APM, int, M_APM);
extern  void  m_apm_arcsinh(M_APM, int, M_APM);
extern  void  m_apm_arccosh(M_APM, int, M_APM);
extern  void  m_apm_arctanh(M_APM, int, M_APM);

extern  void  m_apm_cpp_precision(int);   /* only for C++ wrapper */

/* more intuitive alternate names for the ARC functions ... */

#define m_apm_asin m_apm_arcsin
#define m_apm_acos m_apm_arccos
#define m_apm_atan m_apm_arctan
#define m_apm_atan2 m_apm_arctan2

#define m_apm_asinh m_apm_arcsinh
#define m_apm_acosh m_apm_arccosh
#define m_apm_atanh m_apm_arctanh

#ifdef APM_CONVERT_FROM_C
}      /* End extern "C" bracket */
#endif

#ifdef __cplusplus   /*<- Hides the class below from C compilers */

/*
    This class lets you use M_APM's a bit more intuitively with
    C++'s operator and function overloading, constructors, etc.

    Added 3/24/2000 by Orion Sky Lawlor, olawlor@acm.org
*/

#ifndef ZORBA_FOR_ONE_THREAD_ONLY
#include "zorbautils/mutex.h"
#include "common/common.h"
#endif


extern 
#ifdef APM_CONVERT_FROM_C
"C" 
#endif

// Initialized in mapmcnst.c (to 30)
int MM_cpp_min_precision;



/******************************************************************************

  The M_APM structure stores decimal numbers of unbounded sise and precision.
  Numbers are stored in a normalized and encoded format. Normalization involves
  moving the "." all the way to the left, and then, removing any leading and/or
  trailing zeros. Examples:

  4.234  --> .4234E1
  3.25E2 --> .325E3
  003500 --> .35E4
  0.5    --> .5E0

  After normalization, the digits before the exponent part are called the
  "siginificant" digits.

  Encoding involves storing each pair of significant digits as an 8-bit integer 
  number. For example:

  4234 is encoded in 2 bytes, storing the numbers 42 and 34 respectively.
  (42 is stored in byte 0 of the m_apm_data array, and 34 is stored in byte 1).
  325 is is encoded in 2 bytes, storing the numbers 32 and 50 respectively.
  (If the number of significant digits is odd, the last (right-most) digit
  is encoded as the number 10*N, where N is the actual digit.)

  The M_APM structure is implemented as a reference-counted, copy-on-write data
  structure. This makes copies very fast, but that's why it's so ugly. A MAPM
  obj is basically just a wrapper around a (possibly shared) M_APM_struct.


  m_apm_id           : A sanity mark to check whether the struct has been
                       corrupted.
  m_apm_refcount     : Ref counter for memory management. Initialized to 1.
  m_apm_data         : uchar array that stores the encoded significant digits
                       of the number.
  m_apm_malloclength : If N is the number of allocated bytes for the m_apm_data
                       array, then m_apm_malloclength is set to N - 4. Why the
                       -4 ????
  m_apm_datalength   : Number of significant digits in the number.
  m_apm_exponent     : The exponent part of the number, after normalization.
  m_apm_sign         : +1 means the number is positive, -1 means the number is
                       negative, and 0 means the number is 0.

  typedef struct  
  {
    UCHAR * m_apm_data;
    long    m_apm_id;
    int     m_apm_refcount;
    int     m_apm_malloclength;
    int     m_apm_datalength;
    int     m_apm_exponent;
    int     m_apm_sign;
  } M_APM_struct;

  typedef M_APM_struct* M_APM;


  m_apm_lc.h mapmutl1.c mapmutl2.c mapmcnst.c mapmutil.c mapm_set.c
*******************************************************************************/
class MAPM 
{
protected:
  static zorba::Mutex theMAPMMutex;

protected:

  M_APM myVal;  /* myVal is a pointer to a ref-counted M_APM_struct */

public:
  static MAPM& getMaxUInt64()
  {
    static MAPM lInstance("18446744073709551615");
    return lInstance;
  }

  static MAPM& getMaxInt64()
  {
    static MAPM lInstance("9223372036854775807");
    return lInstance;
  }

  static MAPM& getMinInt64()
  {
    static MAPM lInstance("-9223372036854775808");
    return lInstance;
  }

  static MAPM& getMaxUInt32()
  {
    static MAPM lInstance("4294967295");
    return lInstance;
  }

  static MAPM& getMaxInt32()
  {
    static MAPM lInstance("2147483647");
    return lInstance;
  }

  static MAPM& getMinInt32()
  {
    static MAPM lInstance("-2147483648");
    return lInstance;
  }

  static MAPM& get0_5()
  {
    static MAPM lInstance(0.5);
    return lInstance;
  }

protected:

  static M_APM makeNew(void) 
  {
    // Allocate M_APM_struct plus 84 bytes of "data" within this struct.
    // Initialize refcount to 1.
    M_APM val = m_apm_init();
    return val;  
  }

  static void ref(M_APM val) 
  {
    val->m_apm_refcount++;
  }

  static void unref(M_APM val) 
  {
    val->m_apm_refcount--;
    if (val->m_apm_refcount == 0)
      m_apm_free(val);
  }

protected:
  void create(void) 
  {
    myVal = makeNew();
  }

  void destroy(void)
  {
    unref(myVal); myVal = 0;
  }

  void copyFrom(M_APM Nval) 
  {
     M_APM oldVal = myVal;
     myVal = Nval;
     ref(myVal);
     unref(oldVal);
  }
  
  /**
   * This routine is used to implement copy-on-write: If there are more than 1
   * references to the underlying M_APM_struct, a copy of the struct is created 
   * and myVal is set to point to that copy; otherwise nothing is done.
   */
  M_APM val(void) 
  {
    if (myVal->m_apm_refcount == 1) 
      return myVal;

    M_APM oldVal = myVal;

    myVal = makeNew();
    m_apm_copy(myVal, oldVal);

    unref(oldVal);
    return myVal;
  }
  
  /*
    BAD: C M_APM routines doesn't use "const" where they should--
    hence we have to cast to a non-const type here (FIX THIS!).
    (in due time.... MCR)
  */
  M_APM cval(void) const 
  {
    return (M_APM)myVal;
  }


  /**
   * This is the default number of digits to use for 1-ary functions like sin,
   * cos, tan, etc. It's the larger of my digits and cpp_min_precision.
   */
  int myDigits(void) const 
  {
    int maxd = m_apm_significant_digits(cval());
    if (maxd < MM_cpp_min_precision)
      maxd = MM_cpp_min_precision;
    return maxd;
  }


  /**
   * This is the default number of digits to use for 2-ary functions like divide,
   * atan2, etc. It's the larger of my digits, his digits, and cpp_min_precision.
  */
  int digits(const MAPM &otherVal) const 
  {
    int maxd = myDigits();
    int his = m_apm_significant_digits(otherVal.cval());
    if (maxd < his)
      maxd = his;
    return maxd;
  }

public:
  /**
   * Create an mapm number and set it to 0. This takes 2 memory allocations!
   */
  MAPM(void) 
  {
    create();
  }

  /** 
   * Make a "shallow" copy of an mapm number. Only the ref count of the
   * undelying mapm object is inceremented.
   */
  MAPM(const MAPM& m) 
  {
    myVal = (M_APM)m.cval(); 
    ref(myVal); 
  }

  /** 
   * Make a "shallow" copy of an mapm number. Only the ref count of the
   * undelying mapm object is inceremented.
   */
  MAPM(M_APM m) 
  {

    myVal = (M_APM)m; 
    ref(myVal);
  }

  /**
   * Create an mapm number from a string. This takes at least 2 memory
   * allocations!
   */
  MAPM(const char* s) 
  { 
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    create();
    m_apm_set_string(val(), (char*)s);
  }

  MAPM(double d)
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    create();
    m_apm_set_double(val(), d);
  }

  MAPM(int l) 
  { 
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    create();
    m_apm_set_long(val(), l);
  }

  MAPM(long l) 
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    create(); 
    m_apm_set_long(val(), l); 
  }

  ~MAPM() 
  {
    destroy();
  }
  
  /* Extracting string descriptions: */
  void toString(char* dest, int decimalPlaces) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_to_string(dest, decimalPlaces, cval());
  }

  void toFixPtString(char* dest, int decimalPlaces) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_to_fixpt_string(dest, decimalPlaces, cval());
  }

  void toFixPtStringEx(char* dest, int dp, char a, char b, int c) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_to_fixpt_stringex(dest, dp, cval(), a, b, c);
  }

  char* toFixPtStringExp(int dp,char a,char b,int c) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    return (m_apm_to_fixpt_stringexp(dp, cval(), a, b, c));
  }

  void toIntegerString(char* dest) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_to_integer_string(dest, cval());
  }

  /* Basic operators: */
  MAPM& operator=(const MAPM& m) /* Assigment operator */
  {
    copyFrom((M_APM)m.cval());
    return *this;
  }

  MAPM& operator=(const char* s) /* Assigment operator */
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_set_string(val(), (char *)s);
    return *this;
  }

  MAPM& operator=(double d) /* Assigment operator */
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_set_double(val(),d);
    return *this;
  }

  MAPM& operator=(int l) /* Assigment operator */
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_set_long(val(),l);
    return *this;
  }

  MAPM& operator=(long l) /* Assigment operator */
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_set_long(val(),l);
    return *this;
  }

  MAPM operator++() /* Prefix increment operator */
  {
    return *this = *this + MM_One;
  }

  MAPM operator--() /* Prefix decrement operator */
  {
    return *this = *this - MM_One;
  }

  const MAPM operator++(int)  /* Postfix increment operator */
  {
    MAPM old = *this;
    ++(*this);          /* Call prefix increment */
    return old;
  }

  const MAPM operator--(int)  /* Postfix decrement operator */
  {
    MAPM old = *this;
    --(*this);          /* Call prefix decrement */
    return old;
  }
  

  /* Comparison operators */
  bool operator==(const MAPM &m) const /* Equality operator */
  {
    return m_apm_compare(cval(),m.cval()) == 0;
  }

  bool operator!=(const MAPM &m) const /* Inequality operator */
  {
    return m_apm_compare(cval(),m.cval()) != 0;
  }

  bool operator<(const MAPM &m) const
  {
    return m_apm_compare(cval(),m.cval()) < 0;
  }

  bool operator<=(const MAPM &m) const
  {
    return m_apm_compare(cval(),m.cval()) <= 0;
  }

  bool operator>(const MAPM &m) const
  {
    return m_apm_compare(cval(), m.cval()) > 0;
  }

  bool operator>=(const MAPM &m) const
  {
    return m_apm_compare(cval(),m.cval()) >= 0;
  }

  long compare(const MAPM &m) const
  {
    return m_apm_compare(cval(),m.cval());
  }


  /* Basic arithmetic operators */
  friend MAPM operator+(const MAPM& a, const MAPM& b)
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_add(ret.val(),a.cval(),b.cval());
    return ret;
  }

  friend MAPM operator-(const MAPM& a, const MAPM& b)
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_subtract(ret.val(), a.cval(), b.cval());
    return ret;
  }

  friend MAPM operator*(const MAPM &a,const MAPM &b)
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_multiply(ret.val(),a.cval(),b.cval());
    return ret;
  }

  friend MAPM operator%(const MAPM& a, const MAPM& b)
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM quot,ret;
    m_apm_integer_div_rem(quot.val(), ret.val(), a.cval(), b.cval());
    return ret;
  }

  /* Default division keeps larger of cpp_min_precision, numerator 
     digits of precision, or denominator digits of precision. */
  friend MAPM operator/(const MAPM& a, const MAPM& b) 
  {
    return a.divide(b, a.digits(b));
  }
  
  MAPM divide(const MAPM& m, int toDigits) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_divide(ret.val(), toDigits,cval(), m.cval());
    return ret;
  }

  MAPM divide(const MAPM& m) const 
  {
    return divide(m, digits(m));
  }
  
  /* Assignment arithmetic operators */
  MAPM &operator+=(const MAPM &m) {*this = *this+m; return *this;}

  MAPM &operator-=(const MAPM &m) {*this = *this-m; return *this;}

  MAPM &operator*=(const MAPM &m) {*this = *this*m; return *this;}

  MAPM &operator/=(const MAPM &m) {*this = *this/m; return *this;}

  MAPM &operator%=(const MAPM &m) {*this = *this%m; return *this;}
  
  /* Extracting/setting simple information: */
  int sign(void) const { return m_apm_sign(cval()); }

  int exponent(void) const { return m_apm_exponent(cval()); }

  int significant_digits(void) const { return m_apm_significant_digits(cval()); }

  int is_integer(void) const { return m_apm_is_integer(cval()); }

  int is_even(void) const { return m_apm_is_even(cval()); }

  int is_odd(void) const { return m_apm_is_odd(cval()); }

  int is_zero(void) const { return (m_apm_compare(cval(), MM_Zero) == 0); }

  int is_one(void) const { return (m_apm_compare(cval(), MM_One) == 0); }

  /* Functions: */
  MAPM abs(void) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_absolute_value(ret.val(),cval());
    return ret;
  }

  MAPM neg(void) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_negate(ret.val(),cval());
    return ret;
  }

  MAPM round(int toDigits) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_round(ret.val(),toDigits,cval());
    return ret;
  }

  MAPM operator-(void) const 
  {
    return neg();
  }

/* I got tired of typing the various declarations for a simple 
   1-ary real-to-real function on MAPM's; hence this define:
   The digits-free versions return my digits of precision or 
   cpp_min_precision, whichever is bigger.
*/

#define MAPM_1aryFunc(func)                                       \
  MAPM func(int toDigits) const                                   \
  {                                                               \
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));                       \
    MAPM ret;                                                     \
    m_apm_##func(ret.val(), toDigits, cval());                    \
    return ret;                                                   \
  }                                                               \
                                                                  \
  MAPM func(void) const { return func(myDigits()); }

  MAPM_1aryFunc(sqrt)
  MAPM_1aryFunc(cbrt)
  MAPM_1aryFunc(log)
  MAPM_1aryFunc(exp)
  MAPM_1aryFunc(log10)
  MAPM_1aryFunc(sin)
  MAPM_1aryFunc(asin)
  MAPM_1aryFunc(cos)
  MAPM_1aryFunc(acos)
  MAPM_1aryFunc(tan)
  MAPM_1aryFunc(atan)
  MAPM_1aryFunc(sinh)
  MAPM_1aryFunc(asinh)
  MAPM_1aryFunc(cosh)
  MAPM_1aryFunc(acosh)
  MAPM_1aryFunc(tanh)
  MAPM_1aryFunc(atanh)
#undef MAPM_1aryFunc
  
  void sincos(MAPM& sinR, MAPM& cosR, int toDigits)
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_sin_cos(sinR.val(), cosR.val(), toDigits,cval());
  }

  void sincos(MAPM &sinR,MAPM &cosR)
  {
    sincos(sinR, cosR, myDigits());
  }

  MAPM pow(const MAPM &m,int toDigits) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_pow(ret.val(), toDigits,cval(), m.cval());
    return ret;
  }

  MAPM pow(const MAPM &m) const 
  {
    return pow(m, digits(m));
  }

  MAPM atan2(const MAPM &x,int toDigits) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_arctan2(ret.val(),toDigits,cval(), x.cval());
    return ret;
  }

  MAPM atan2(const MAPM& x) const
  {
    return atan2(x,digits(x));
  }

  MAPM gcd(const MAPM &m) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_gcd(ret.val(),cval(),m.cval());
    return ret;
  }

  MAPM lcm(const MAPM &m) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_lcm(ret.val(),cval(),m.cval());
    return ret;
  }

  static MAPM random(void)
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_get_random(ret.val());
    return ret;
  }

  MAPM floor(void) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_floor(ret.val(),cval());
    return ret;
  }

  MAPM ceil(void) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_ceil(ret.val(),cval());
    return ret;
  }

  /* Functions defined only on integers: */
  MAPM factorial(void) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_factorial(ret.val(),cval());
    return ret;
  }

  MAPM ipow_nr(int p) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_integer_pow_nr(ret.val(), cval(), p);
    return ret;
  }

  MAPM ipow(int p, int toDigits) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_integer_pow(ret.val(), toDigits,cval(),p);
    return ret;
  }

  MAPM ipow(int p) const
  {
    return ipow(p,myDigits());
  }

  MAPM integer_divide(const MAPM &denom) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    MAPM ret;
    m_apm_integer_divide(ret.val(),cval(), denom.cval());
    return ret;
  }

  void integer_div_rem(const MAPM &denom, MAPM &quot, MAPM &rem) const
  {
    SYNC_CODE(zorba::AutoMutex lock(&theMAPMMutex));
    m_apm_integer_div_rem(quot.val(),rem.val(),cval(), denom.cval());
  }

  MAPM div(const MAPM &denom) const
  {
    return integer_divide(denom);
  }

  MAPM rem(const MAPM& denom) const
  {
    MAPM ret, ignored;
    integer_div_rem(denom,ignored,ret);
    return ret;
  }
};


/* math.h-style functions: */

inline MAPM fabs(const MAPM &m) {return m.abs();}
inline MAPM factorial(const MAPM &m) {return m.factorial();}
inline MAPM floor(const MAPM &m) {return m.floor();}
inline MAPM ceil(const MAPM &m) {return m.ceil();}
inline MAPM get_random(void) {return MAPM::random();}

/* I got tired of typing the various declarations for a simple 
   1-ary real-to-real function on MAPM's; hence this define:
*/
#define MAPM_1aryFunc(func) \
  inline MAPM func(const MAPM &m) {return m.func();} \
  inline MAPM func(const MAPM &m,int toDigits) {return m.func(toDigits);}

/* Define a big block of simple functions: */
  MAPM_1aryFunc(sqrt)
  MAPM_1aryFunc(cbrt)
  MAPM_1aryFunc(log)
  MAPM_1aryFunc(exp)
  MAPM_1aryFunc(log10)
  MAPM_1aryFunc(sin)
  MAPM_1aryFunc(asin)
  MAPM_1aryFunc(cos)
  MAPM_1aryFunc(acos)
  MAPM_1aryFunc(tan)
  MAPM_1aryFunc(atan)
  MAPM_1aryFunc(sinh)
  MAPM_1aryFunc(asinh)
  MAPM_1aryFunc(cosh)
  MAPM_1aryFunc(acosh)
  MAPM_1aryFunc(tanh)
  MAPM_1aryFunc(atanh)
#undef MAPM_1aryFunc

/* Computes x to the power y */
inline MAPM pow(const MAPM &x,const MAPM &y,int toDigits)
    {return x.pow(y,toDigits);}

inline MAPM pow(const MAPM &x,const MAPM &y)
    {return x.pow(y);}

inline MAPM atan2(const MAPM &y,const MAPM &x,int toDigits)
    {return y.atan2(x,toDigits);}

inline MAPM atan2(const MAPM &y,const MAPM &x)
    {return y.atan2(x);}

inline MAPM gcd(const MAPM &u,const MAPM &v)
    {return u.gcd(v);}

inline MAPM lcm(const MAPM &u,const MAPM &v)
    {return u.lcm(v);}
#endif
#endif
/*
 * Local variables:
 * mode: c++
 * End:
 */
/* vim:set et sw=2 ts=2: */
