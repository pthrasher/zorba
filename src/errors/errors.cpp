/**
 * @file errors.cpp
 * @author Paul Pedersen
 * @copyright 2006-2007 FLWOR Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "errors/errors.h"
//#include"../errors/xqp_exception.h"

#include <string>

using namespace std;
namespace xqp {
  

string errors_english::err_decode(enum errcode e)
{
#define TRIVIAL_ERR( e ) case e: return #e
	switch (e) {
	case XPST0001_STATIC_CONTEXT_COMPONENT_MISSING:
		return "XPST0001_STATIC_CONTEXT_COMPONENT_MISSING";
	case XPDY0002_DYNAMIC_CONTEXT_COMPONENT_MISSING:
		return "XPDY0002_DYNAMIC_CONTEXT_COMPONENT_MISSING";
	case XPST0003_STATIC_GRAMMAR_ERROR:
		return "XPST0003_STATIC_GRAMMAR_ERROR";
	case XPTY0004_STATIC_TYPE_ERROR:
		return "XPTY0004_STATIC_TYPE_ERROR";
	case XPST0005_STATIC_ILLEGAL_EMPTY_SEQUENCE:
		return "XPST0005_STATIC_ILLEGAL_EMPTY_SEQUENCE";
	case XPST0008_STATIC_ILLEGAL_REFERENCE:
		return "XPST0008_STATIC_ILLEGAL_REFERENCE";
	case XQST0009_STATIC_SCHEMA_IMPORT_NOT_SUPPORTED:
		return "XQST0009_STATIC_SCHEMA_IMPORT_NOT_SUPPORTED";
	case XPST0010_STATIC_AXIS_NOT_SUPPORTED:
		return "XPST0010_STATIC_AXIS_NOT_SUPPORTED";
	case XQST0012_STATIC_SCHEMA_NOT_VALID:
		return "XQST0012_STATIC_SCHEMA_NOT_VALID";
	case XQST0013_STATIC_PRAGMA_NOT_VALID:
		return "XQST0013_STATIC_PRAGMA_NOT_VALID";
	case XQST0016_STATIC_MODULE_IMPORT_NOT_SUPPORTED:
		return "XQST0016_STATIC_MODULE_IMPORT_NOT_SUPPORTED";
	case XPST0017_STATIC_FUNCTION_NOT_FOUND:
		return "XPST0017_STATIC_FUCTION_NOT_FOUND";
	case XPTY0018_TYPE_MIXED_PATHEXPR:
		return "XPTY0018_TYPE_MIXED_PATHEXPR";
	case XPTY0019_TYPE_STEP_IS_ATOMIC:
		return "XPTY0019_TYPE_STEP_IS_ATOMIC";
	case XPTY0020_TYPE_CONTEXT_NOT_A_NODE:
		return "XPTY0020_TYPE_CONTEXT_NOT_A_NODE";
	case XQST0022_STATIC_NAMESPACE_DECL_NOT_A_URI:
		return "XQST0022_STATIC_NAMESPACE_DECL_NOT_A_URI";
	case XQTY0024_TYPE_ATTRIBUTE_NODE_OUT_OF_ORDER:
		return "XQTY0024_TYPE_ATTRIBUTE_NODE_OUT_OF_ORDER";
	case XQDY0025_DYNAMIC_DUPLICATE_ATTRIBUTE_NAME:
		return "XQDY0025_DYNAMIC_DUPLICATE_ATTRIBUTE_NAME";
	case XQDY0026_DYNAMIC_ILLEGAL_CONTENT:
		return "XQDY0026_DYNAMIC_ILLEGAL_CONTENT";
	case XQDY0027_DYNAMIC_VALIDATION_FAILED:
		return "XQDY0027_DYNAMIC_VALIDATION_FAILED";
	case XQTY0030_TYPE_VALIDATION_BAD_ARG:
		return "XQTY0030_TYPE_VALIDATION_BAD_ARG";
	case XQST0031_STATIC_BAD_VERSION:
		return "XQST0031_STATIC_BAD_VERSION";
	case XQST0032_STATIC_DUPLICATE_BASE_URI:
		return "XQST0032_STATIC_DUPLICATE_BASE_URI";
	case XQST0033_STATIC_DUPLICATE_NAMESPACE_PREFIX:
		return "XQST0033_STATIC_DUPLICATE_NAMESPACE_PREFIX";
	case XQST0034_STATIC_DUPLICATE_FUNCTIONS:
		return "XQST0034_STATIC_DUPLICATE_FUNCTIONS";
	case XQST0035_STATIC_DUPLICATE_SCHEMAS:
		return "XQST0035_STATIC_DUPLICATE_SCHEMAS";
	case XQST0036_STATIC_MISSSING_IMPORTED_SCHEMA_TYPES:
		return "XQST0036_STATIC_MISSSING_IMPORTED_SCHEMA_TYPES";
	case XQST0038_STATIC_DUPLICATE_DEFAULT_COLLATION:
		return "XQST0038_STATIC_DUPLICATE_DEFAULT_COLLATION";
	case XQST0039_STATIC_DUPLICATE_FUNARG_NAME:
		return "XQST0039_STATIC_DUPLICATE_FUNARG_NAME";
	case XQST0040_STATIC_DUPLICATE_ATTRIBUTE_NAME:
		return "XQST0040_STATIC_DUPLICATE_ATTRIBUTE_NAME";
	case XQDY0041_DYNAMIC_PI_NON_NCNAME:
		return "XQDY0041_DYNAMIC_PI_NON_NCNAME";
	case XQDY0044_DYNAMIC_ILLEGAL_ATTRIBUTE_NAME:
		return "XQDY0044_DYNAMIC_ILLEGAL_ATTRIBUTE_NAME";
	case XQST0045_STATIC_ILLEGAL_FUNCTION_NAME:
		return "XQST0045_STATIC_ILLEGAL_FUNCTION_NAME";
	case XQST0046_STATIC_ILLEGAL_URI_LITERAL:
		return "XQST0046_STATIC_ILLEGAL_URI_LITERAL";
	case XQST0047_STATIC_DUPLICATE_IMPORTED_TARGET_NS:
		return "XQST0047_STATIC_DUPLICATE_IMPORTED_TARGET_NS";
	case XQST0048_STATIC_MISSING_TARGET_NAMESPACE:
		return "XQST0048_STATIC_MISSING_TARGET_NAMESPACE";
	case XQST0049_STATIC_DUPLICATE_IMPORTED_VARIABLES:
		return "XQST0049_STATIC_DUPLICATE_IMPORTED_VARIABLES";
	case XPDY0050_DYNAMIC_TREAT_FAILED:
		return "XPDY0050_DYNAMIC_TREAT_FAILED	";
	case XPST0051_STATIC_MISSING_SCHEMA_TYPE:
		return "XPST0051_STATIC_MISSING_SCHEMA_TYPE";
	case XQST0054_STATIC_CIRCULAR_INITIALIZATION:
		return "XQST0054_STATIC_CIRCULAR_INITIALIZATION";
	case XQST0055_STATIC_DUPLICATE_COPY_NAMESPACE:
		return "XQST0055_STATIC_DUPLICATE_COPY_NAMESPACE";
	case XQST0057_STATIC_MISSING_TARGET_NAMESPACE:
		return "XQST0057_STATIC_MISSING_TARGET_NAMESPACE";
	case XQST0058_STATIC_DUPLICATE_TARGET_NAMESPACE:
		return "XQST0058_STATIC_DUPLICATE_TARGET_NAMESPACE";
	case XQST0059_STATIC_TARGET_NAMESPACE_NOT_FOUND:
		return "XQST0059_STATIC_TARGET_NAMESPACE_NOT_FOUND";
	case XQST0060_STATIC_FUNCTION_MISSING_NAMESPACE:
		return "XQST0060_STATIC_FUNCTION_MISSING_NAMESPACE";
	case XQDY0061_DYNAMIC_VALIDATE_BAD_DOCUMENT:
		return "XQDY0061_DYNAMIC_VALIDATE_BAD_DOCUMENT";
	case XQDY0064_DYNAMIC_ILLEGAL_PI_NAME:
		return "XQDY0064_DYNAMIC_ILLEGAL_PI_NAME";
	case XQST0065_STATIC_DUPLICATE_ORDERING_MODE_DECL:
		return "XQST0065_STATIC_DUPLICATE_ORDERING_MODE_DECL";
	case XQST0066_STATIC_DUPLICATE_DEFAULT_NAMESPACE_DECL:
		return "XQST0066_STATIC_DUPLICATE_DEFAULT_NAMESPACE_DECL";
	case XQST0067_STATIC_DUPLICATE_CONSTRUCTION_DECL:
		return "XQST0067_STATIC_DUPLICATE_CONSTRUCTION_DECL";
	case XQST0068_STATIC_DUPLICATE_BOUNDARY_SPACE_DECL:
		return "XQST0068_STATIC_DUPLICATE_BOUNDARY_SPACE_DECL";
	case XQST0069_STATIC_DUPLICATE_EMPTY_ORDER_DECL:
		return "XQST0069_STATIC_DUPLICATE_EMPTY_ORDER_DECL";
	case XQST0070_STATIC_RESERVED_PREFIX:
		return "XQST0070_STATIC_RESERVED_PREFIX";
	case XQST0071_STATIC_DUPLICATE_NS_ATTRIBUTES:
		return "XQST0071_STATIC_DUPLICATE_NS_ATTRIBUTES";
	case XQDY0072_DYNAMIC_ILLEGAL_HYPHENS:
		return "XQDY0072_DYNAMIC_ILLEGAL_HYPHENS";
	case XQST0073_STATIC_CYCLIC_MODULE_IMPORT:
		return "XQST0073_STATIC_CYCLIC_MODULE_IMPORT";
	case XQDY0074_DYNAMIC_BAD_ELEM_ATTR_QNAME:
		return "XQDY0074_DYNAMIC_BAD_ELEM_ATTR_QNAME";
	case XQST0075_STATIC_VALIDATION_NOT_SUPPORTED:
		return "XQST0075_STATIC_VALIDATION_NOT_SUPPORTED";
	case XQST0076_STATIC_UNRECOGNIZED_COLLATION:
		return "XQST0076_STATIC_UNRECOGNIZED_COLLATION";
	case XQST0079_STATIC_UNRECOGNIZE_EXTENSION_EXPR:
		return "XQST0079_STATIC_UNRECOGNIZE_EXTENSION_EXPR";
	case XPST0080_STATIC_BAD_CAST_EXPR:
		return "XPST0080_STATIC_BAD_CAST_EXPR";
	case XPST0081_STATIC_BAD_QNAME_PREFIX:
		return "XPST0081_STATIC_BAD_QNAME_PREFIX";
	case XQDY0084_DYNAMIC_UNKNOWN_VALIDATED_ELEMENT:
		return "XQDY0084_DYNAMIC_UNKNOWN_VALIDATED_ELEMENT";
	case XQST0085_STATIC_EMPTY_NAMESPACE_URI:
		return "XQST0085_STATIC_EMPTY_NAMESPACE_URI";
	case XQTY0086_TYPE_NODE_COPY_LOOSES_NAMESPACES:
		return "XQTY0086_TYPE_NODE_COPY_LOOSES_NAMESPACES";
	case XQST0087_STATIC_ILLEGAL_ENCODING:
		return "XQST0087_STATIC_ILLEGAL_ENCODING";
	case XQST0088_STATIC_EMPTY_IMPORT_TARGET_NAMESPACE:
		return "XQST0088_STATIC_EMPTY_IMPORT_TARGET_NAMESPACE";
	case XQST0089_STATIC_POSVAR_SHADOW:
		return "XQST0089_STATIC_POSVAR_SHADOW";
	case XQST0090_STATIC_ILLEGAL_CHARREF:
		return "XQST0090_STATIC_ILLEGAL_CHARREF";
	case XQP0001_DYNAMIC_ITERATOR_OVERRUN:
		return "XQP0001_DYNAMIC_ITERATOR_OVERRUN";
	case XQP0002_DYNAMIC_ILLEGAL_NODE_CHILD:
		return "XQP0002_DYNAMIC_ILLEGAL_NODE_CHILD";
	case XQP0003_DYNAMIC_TARGET_NAMESPACE_NOT_FOUND:
		return "XQP0003_DYNAMIC_TARGET_NAMESPACE_NOT_FOUND";
  case XQP0005_SYSTEM_ASSERT_FAILED:
    return "Assertion `/s' failed in /s";
  TRIVIAL_ERR (XQP0014_SYSTEM_SHOUD_NEVER_BE_REACHED);
  case XQP0004_SYSTEM_NOT_SUPPORTED:
    return "XQP0004_SYSTEM_NOT_SUPPORTED";    
  case XQP0016_LOADER_IO_ERROR:
    return "XQP0016_LOADER_IO_ERROR";
  case XQP0017_LOADER_NOT_WELL_FORMED_XML:
    return "XQP0016_LOADER_NOT_WELL_FORMED_XML \n/s";
  case XQP0018_NODEID_OUT_OF_RANGE:
    return "A nodeid component is too large to be encoded";
  case API0005_COLLECTION_ALREADY_EXISTS:
    return "A collection with URI `/s' exists already";
  case API0006_COLLECTION_NOT_FOUND:
    return "A collection with URI `/s' does not exist";
  case API0007_COLLECTION_ITEM_MUST_BE_A_NODE:
    return "Cannot insert a non-node item to a collection";

  case FODC0002_Error_retrieving_resource:
    return "FODC0002_Error_retrieving_resource: Error retrieving resource";
    
	default: return "<Unknown errcode> /s /s";
	}
} 

std::string errors_english::errtype_decode(enum error_type errtype)
{
	switch(errtype)
	{
	case STATIC_ERROR: return "Static: ";
	case RUNTIME_ERROR: return "Runtime: ";
	case SYSTEM_ERROR: return "System: ";
	case USER_ERROR: return "User";
	}

	return "";
}

std::string errors_english::warning_decode(enum warning_code)
{
	return "?";
}

std::string errors_english::notify_event_decode(enum NotifyEvent_code n)
{
	switch(n)
	{
	case NOTIF_EXECUTION_STEP:
		return "Notify execution step: /s /s";
	}
	return "?";
}

std::string errors_english::ask_user_decode(enum AskUserString_code)
{
	return "?";
}

std::string errors_english::ask_user_options_decode(enum AskUserStringOptions_code)
{
	return "";
}

/* Finds next place for param in err_decoded, and puts the param in that place.
 * A place for param looks like "/s".
 */
string::size_type error_messages::ApplyParam(
    string *err_decoded,
    const string *param1,
    string::size_type start)
{
	std::string::size_type off;
  const static string empty;

	off = err_decoded->find ("/s", start);

	if (off == string::npos)
		return err_decoded->length ();

  if (param1 == NULL) param1 = &empty;

	err_decoded->replace (off, 2, *param1);
  return off + param1->length ();
}

void error_messages::ApplyParams(
    string *err_decoded,
    const string *param1,
    const string *param2)
{
  string::size_type off = ApplyParam (err_decoded, param1, 0);
  ApplyParam (err_decoded, param2, off);
}

errors_string_table::errors_string_table( std::string file_name )
{
}

}///end namespace xqp

