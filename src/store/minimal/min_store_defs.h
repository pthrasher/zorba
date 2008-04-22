#ifndef ZORBA_MINIMAL_STORE_STORE_DEFS_H
#define ZORBA_MINIMAL_STORE_STORE_DEFS_H


#define GET_STORE() \
  (*(static_cast<SimpleStore*>(&GENV.getStore())))

#define GET_FACTORY() \
        (*(reinterpret_cast<store::BasicItemFactory*>(GET_STORE().getItemFactory())))


#define BASE_NODE(item) (static_cast<XmlNode*>((item).getp()))

#define DOC_NODE(item) (reinterpret_cast<DocumentNode*>((item).getp()))

#define ATTR_NODE(item) (reinterpret_cast<AttributeNode*>((item).getp()))

#define ELEM_NODE(item) (reinterpret_cast<ElementNode*>((item).getp()))

#define TEXT_NODE(item) (reinterpret_cast<TextNode*>((item).getp()))

#define PI_NODE(item) (reinterpret_cast<PiNode*>((item).getp()))

#define COMMENT_NODE(item) (reinterpret_cast<CommentNode*>((item).getp()))

namespace zorba { 

namespace store {


enum SchemaTypeNames
{
  XS_UNTYPED = 0,
  XS_UNTYPED_ATOMIC,

  XS_ANY,
  XS_ANY_SIMPLE,
  XS_ANY_ATOMIC,

  XS_STRING,
  XS_NORMALIZED_STRING,
  XS_LANGUAGE,
  XS_TOKEN,
  XS_NMTOKEN,

  XS_ANY_URI,
  XS_NAME,
  XS_NCNAME,
  XS_QNAME,
  XS_NOTATION,

  XS_ID,
  XS_IDREF,
  XS_ENTITY,

  XS_DATETIME,
  XS_DATE,
  XS_TIME,
  XS_DURATION,
  XS_DT_DURATION,
  XS_YM_DURATION,

  XS_FLOAT,
  XS_DOUBLE,
  XS_DECIMAL,
  XS_INTEGER,
  XS_NON_POSITIVE_INTEGER,
  XS_NON_NEGATIVE_INTEGER,
  XS_NEGATIVE_INTEGER,
  XS_POSITIVE_INTEGER,
  XS_LONG,
  XS_INT,
  XS_SHORT,
  XS_BYTE,
  XS_UNSIGNED_LONG,
  XS_UNSIGNED_INT,
  XS_UNSIGNED_SHORT,
  XS_UNSIGNED_BYTE,

  XS_GYEAR_MONTH,
  XS_GYEAR,
  XS_GMONTH_DAY,
  XS_GDAY,
  XS_GMONTH,

  XS_BASE64BINARY,
  XS_HEXBINARY,
  XS_BOOLEAN,

  XS_LAST
};


}
}
#endif
