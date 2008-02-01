/* -*- mode: c++; indent-tabs-mode: nil; tab-width: 2 -*-
 *
 *  $Id: item_factory.h,v 1.1 2007/08/09 07:07:59 $
 *
 *	Copyright 2006-2007 FLWOR Foundation.
 *  Author: David Graf, Donald Kossmann, Tim Kraska
 *
 */

#ifndef XQP_ITEM_FACTORY_H
#define XQP_ITEM_FACTORY_H

#ifdef WIN32
#include "util/win32/compatib_defs.h"
#endif

#include "util/rchandle.h"
#include "types/representations.h"


namespace xqp
{
template <class Object> class rchandle;

typedef rchandle<class Item> Item_t;
typedef rchandle<class AnyUriItem> AnyUriItem_t;
typedef rchandle<class NodeItem> NodeItem_t;

typedef rchandle<class Iterator> Iterator_t;
typedef rchandle<class TempSeq> TempSeq_t;

typedef std::vector<std::pair<xqpString, xqpString> > NsBindings;

class ItemFactory
{
public:
  virtual ~ItemFactory() {}
  
public:
			
  /**
   * @param namespace namespace of the qname
   * @param prefix prefix of the qname
   * @param localName local name of the qname
   */
  virtual Item_t createQName(
        const xqpStringStore_t& namespace_p,
        const xqpStringStore_t& prefix,
        const xqpStringStore_t& localName) = 0;

  virtual Item_t createQName(
        const xqp_string& namespace_p,
        const xqp_string& prefix,
        const xqp_string& localName) = 0;

  virtual Item_t createQName(
        const char* ns,
        const char* pre,
        const char* ln) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#NCName]
   * @param value string representation of the value
   */
  virtual Item_t createNCName(xqpStringStore* value) = 0;
  virtual Item_t createNCName(const xqp_string& value) = 0;
    
  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#anyURI]
   * @param value parsed value
   */
  virtual Item_t createAnyURI(const xqpStringStore_t& value) = 0;
  virtual Item_t createAnyURI(const xqp_string& value) = 0;
  virtual Item_t createAnyURI(const char* value) = 0;

  /**
   * @param value string value of the untyped atomic
   */
  virtual Item_t createUntypedAtomic(const xqp_string& value) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#string]
   * @param value string representation of the value
   */
  virtual Item_t createString(xqpStringStore* value) = 0;
  virtual Item_t createString(const xqp_string& value) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#base64Binary]
   * @param value)?
   */
  virtual Item_t createBase64Binary(xqp_base64Binary value) = 0;
  
  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#bool]
   * @param value
   */
  virtual Item_t createBoolean(xqp_boolean value) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#decimal]
   * @param value
   */
  virtual Item_t createDecimal ( xqp_decimal value) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#integer]
   * @param value
   */
  virtual Item_t createInteger ( xqp_integer value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#long]
   * @param value
   */
  virtual Item_t createLong ( xqp_long value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#int]
   * @param value
   */
  virtual Item_t createInt ( xqp_int value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#short]
   * @param value
   */
  virtual Item_t createShort ( xqp_short value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#byte]
   * @param value
   */
  virtual Item_t createByte ( xqp_byte value ) = 0;


  virtual Item_t createDate ( xqp_date& value ) = 0;
  
  /**
   * @param year
   * @param month
   * @param day
   */
  virtual Item_t createDate ( short year, short month, short day ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#date]
   * @param value string representation of the value
   */
  virtual Item_t createDate ( const xqp_string& value ) = 0;

  virtual Item_t createDateTime(xqp_dateTime& value) = 0;
            
  /**
   * @param year
   * @param month
   * @param day
   * @param hour
   * @param minute
   * @param second
   */
  virtual Item_t createDateTime ( 
        short year,
        short month,
        short day,
        short hour,
        short minute,
        short second) = 0;

  /**
   * @param year
   * @param month
   * @param day
   * @param hour
   * @param minute
   * @param second
   * @param timeZone Difference in hours to UTC
   */
  virtual Item_t createDateTime ( 
				short year , short month, short day, short hour, short minute, short second, short timeZone 
			) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#dateTime]
   * @param value string representation of the value
   */
  virtual Item_t createDateTime ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xpath-functions/] Section 5.2
   *
   * @param xs:date Item (might be NULL)
   * @param xs:time Item (might be NULL)
   */
  virtual Item_t createDateTime ( const Item_t&, const Item_t& ) = 0;

  /**
   * @param value double value
   */
  virtual Item_t createDouble ( xqp_double value ) = 0;

  virtual Item_t createDuration(xqp_duration& value ) = 0;
  
  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#duration]
   * @param value string representation of the value
   */
  virtual Item_t createDuration ( const xqp_string& value ) = 0;

  /**
   * @param years
   * @param months
   * @param days
   * @param hours
   * @param minutes
   * @param seconds
			  */
  virtual Item_t createDuration (
			    short years, short months, short days, short hours, short minutes, short seconds
			) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#ENTITIES]
   * @param value string representation of the value
   */
  virtual Item_t createENTITIES ( const xqp_string& value ) = 0;
  
  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#ENTITY]
   * @param value string representation of the value
   */
  virtual Item_t createENTITY ( const xqp_string& value ) = 0;

  /**
   * @param value
   */
  virtual Item_t createFloat ( xqp_float value ) = 0;

  virtual Item_t createGDay ( xqp_gDay& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#gDay]
   * @param value string representation of the value
   */
  virtual Item_t createGDay ( const xqp_string& value ) = 0;

  /**
   * @param day
   */
  virtual Item_t createGDay ( short day ) = 0;

  virtual Item_t createGMonth ( xqp_gMonth& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#gMonth]
   * @param value string representation of the value
   */
  virtual Item_t createGMonth ( const xqp_string& value ) = 0;

  /**
   * @param month
   */
  virtual Item_t createGMonth ( short month ) = 0;

  virtual Item_t createGMonthDay ( xqp_gMonthDay& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#gMonthDay]
   * @param value string representation of the value
   */
  virtual Item_t createGMonthDay ( const xqp_string& value ) = 0;

  /**
   * @param month
   * @param day
   */
  virtual Item_t createGMonthDay ( short month, short day ) = 0;

  virtual Item_t createGYear ( xqp_gYear& value ) = 0;
  
  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#gYear]
   * @param value string representation of the value
   */
  virtual Item_t createGYear ( const xqp_string& value ) = 0;

  /**
   * @param year
   */
  virtual Item_t createGYear ( short year ) = 0;

  virtual Item_t createGYearMonth ( xqp_gYearMonth& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#gYearMonth]
   * @param value string representation of the value
   */
  virtual Item_t createGYearMonth ( const xqp_string& value ) = 0;

  /**
   * @param year
   * @param month
   */
  virtual Item_t createGYearMonth ( short year, short month ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#hexBinary]
   * @param value
   */
  virtual Item_t createHexBinary ( xqp_hexBinary value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#ID]
   * @param value string representation of the value
   */
  virtual Item_t createID ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#IDREF]
   * @param value string representation of the value
   */
  virtual Item_t createIDREF ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#IDREFS]
   * @param value string representation of the value
   */
  virtual Item_t createIDREFS ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#language]
   * @param value string representation of the value
   */
  virtual Item_t createLanguage ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#NMTOKEN]
   * @param value string representation of the value
   */
  virtual Item_t createNMTOKEN ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#NMTOKENS]
   * @param value string representation of the value
   */
  virtual Item_t createNMTOKENS ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#NOTATION]
   * @param value string representation of the value
   */
  virtual Item_t createNOTATION ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#Name]
   * @param value string representation of the value
   */
  virtual Item_t createName ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#negativeInteger]
   * @param value
   */
  virtual Item_t createNegativeInteger ( xqp_integer value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#nonNegativeInteger]
   * @param value
   */
  virtual Item_t createNonNegativeInteger ( xqp_uinteger value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#nonPositiveInteger]
   * @param value
   */
  virtual Item_t createNonPositiveInteger ( xqp_integer value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#normalizedString]
   * @param value string representation of the value
   */
  virtual Item_t createNormalizedString ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#positiveInteger]
   * @param value
   */
  virtual Item_t createPositiveInteger ( xqp_uinteger value ) = 0;

  virtual Item_t createTime (xqp_time& value) = 0;
  
  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#time]
   * @param value string representation of the value
   */
  virtual Item_t createTime ( const xqp_string& value ) = 0;

  /**
   * @param hour
   * @param minute
   * @param second
   */
  virtual Item_t createTime ( short hour, short minute, short second ) = 0;

  /**
   * @param hour
   * @param minute
   * @param second
   * @param timeZone Difference in hours to UTC
   */
  virtual Item_t createTime ( short hour, short minute, short second, short timeZone ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#token]
   * @param value string representation of the value
   */
  virtual Item_t createToken ( const xqp_string& value ) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#unsignedByte]
   * @param value
   */
  virtual Item_t createUnsignedByte(xqp_ubyte value) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#unsignedInt]
   * @param value
   */
  virtual Item_t createUnsignedInt(xqp_uint value) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#unsignedLong]
   * @param value
   */
  virtual Item_t createUnsignedLong(xqp_ulong value) = 0;

  /**
   * Specification: [http://www.w3.org/TR/xmlschema-2/#unsignedShort]
   * @param value
   */
  virtual Item_t createUnsignedShort(xqp_ushort value) = 0;

  /**
   * @param baseUri The base URI of the document.
   * @param docUri The document URI of the document.
   * @param children Content of the Document(root element + comment nodes + PI nodes). 
   * 								The item factory does not check if the parameter contains exactly one root element!
   * @param createId Does the created item need an ID?
   */
  virtual Item_t createDocumentNode(
        unsigned long   qid,
        xqpStringStore* baseURI,
        xqpStringStore* docURI,
        Iterator*       children,
        bool            isRoot,
        bool            copy,
        bool            typePreserve,
        bool            nsPreserve,
        bool            nsInherit) = 0;

  /**
   * @param name QName which contains the name of the element
   * @param type QName which contains the type of the element
   * @param children Content of the element
   * @param attributes Attributes of the element
   * @param namespaces Namespace definitions of this element
   * @param copy Should the children of the element be copied? (for element construction)
   * @param newTypes Have the children to be checked agains the type of the parent?
   * @param createId Does the created item need an ID?
   */
  virtual Item_t createElementNode (
        unsigned long     qid,
        Item*             name,
        Item*             type,
        Iterator*         childrenIte,
        Iterator*         attributesIte,
        Iterator*         namespacesIte,
        const NsBindings& contextBindings,
        const NsBindings& localBindings,
        bool              isRoot,
        bool              copy,
        bool              typePreserve,
        bool              nsPreserve,
        bool              nsInherit) = 0;

  /**
   * @param name QName which contains the name of the element
   * @param type QName which contains the type of the element
   * @param lexicalValue lexical value (atomic) of the attribute element
   * @param typedValue typed value (atomic) of the attribute element
   * @param createId Does the created item need an ID?
   *
   * Implementations might only store the typed value.
   */
  virtual Item_t createAttributeNode(
        unsigned long qid,
        Iterator*     nameIter,
        Item*         type,
        Iterator*     valueIter,
        bool          isRoot) = 0;

  /**
   * @param value text
   * @param createId Does the created item need an ID (default == false)?
   */
  virtual Item_t createTextNode(
        unsigned long   qid,
        Iterator*       valueIter,
        bool            isRoot) = 0;

  virtual Item_t createTextNode(
        unsigned long   qid,
        xqpStringStore* value,
        bool            isRoot) = 0;

  /**
   * @param target The QName for the processing instruction.
   * @param data The content of the processing instruction.
   * @param createId Does the created item need an ID?
   */
  virtual Item_t createPiNode(
        unsigned long   qid,
        xqpStringStore* target,
        xqpStringStore* data,
        bool            isRoot) = 0;

  /**
   * @param comment
   * @param createId Does the created item need an ID (default == false)?
   */
  virtual Item_t createCommentNode(
        unsigned long   qid,
        xqpStringStore* comment,
        bool            isRoot) = 0;
};

}/* namespace xqp */

#endif
