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

#include <vector>
#include <cstdio>
#include <sstream>

#include <zorba/zorba_string.h>
#include <zorba/iterator.h>
#include <zorba/item_factory.h>
#include <zorba/store_consts.h>
#include <zorba/user_exception.h>
#include <zorba/xquery_functions.h>

#include "mime_handler.h"
#include "email_function.h"

namespace zorba
{
  namespace emailmodule
  {
  //helper function for retrieving the NodeName of an Item
  static zorba::String
  get_nodename(const Item aElement)
  {
    Item lNodeName;
    aElement.getNodeName(lNodeName);
    return lNodeName.getLocalName();
  }

  //helper function for retrieving the string value of a Text Node
  static void
  get_text_value(const Item aElement,
                  zorba::String& aValue)
  {
    Iterator_t lChildrenIt;
    Item       lChild;

    aValue = String();
    lChildrenIt = aElement.getChildren();
    lChildrenIt->open();
    while (lChildrenIt->next(lChild))
      if (lChild.getNodeKind() == store::StoreConsts::textNode)
        aValue = lChild.getStringValue();

    lChildrenIt->close();
  }

  void CClientMimeHandler::begin(const Item& aMimeItem)
  {
    Iterator_t    childrenIt;

    //initialize ENVELOPE
    theEnvelope = mail_newenvelope ();
  

    //initialize BODY
    theBody = mail_newbody ();
    mail_initbody(theBody);

    //set theMessageItem
    childrenIt = aMimeItem.getChildren();
    childrenIt->open();
    childrenIt->next(theEnvelopeItem);
    childrenIt->next(theBodyItem);
    childrenIt->close();
  }

  bool
  CClientMimeHandler::envelope(std::stringstream& aDiagnostics)
  {
    Iterator_t    lChildrenIt;
    zorba::Item   lChild;
    char line[MAILTMPLEN];
    bool          lRes = true;
    zorba::String lValue;

    if( theEnvelopeItem.isNull() )
    {
      aDiagnostics << "The message could not be parsed.";
      return false;
    }

    //set the date from the client.
    //If this is not set it defaults to the date of the SMTP server.
    rfc822_date (line);
    
    theEnvelope->date = (unsigned char *) fs_get (1+strlen (line));
    strcpy ((char *)theEnvelope->date,line);

    lChildrenIt = theEnvelopeItem.getChildren();
    lChildrenIt->open();
    while (lChildrenIt->next(lChild) && lRes)
    {
        get_text_value(lChild, lValue);

          String lLowerNodeName = fn::lower_case(get_nodename(lChild));
          if(lLowerNodeName == "date") {
            char lDate[MAILTMPLEN]; 
            parseXmlDateTime(lValue, lDate);
            theEnvelope->date = (unsigned char *) fs_get (1+strlen (lDate));
  
            strcpy ((char *)theEnvelope->date, lDate);

      
          } else if(lLowerNodeName == "from")
          {
            std::string lName;
            std::string lMailbox;
            std::string lHost;
            SMTPFunction::getNameAndEmailAddress(lChild, lName, lMailbox, lHost);
            theEnvelope->from = mail_newaddr ();
            theEnvelope->from->personal = cpystr(const_cast<char*>(lName.c_str()));
            theEnvelope->from->mailbox = cpystr(const_cast<char*>(lMailbox.c_str()));
            theEnvelope->from->host = cpystr(const_cast<char*>(lHost.c_str()));
          }
          else if(lLowerNodeName == "sender")
          {
            std::string lName;
            std::string lMailbox;
            std::string lHost;
            SMTPFunction::getNameAndEmailAddress(lChild, lName, lMailbox, lHost);
            theEnvelope->sender= mail_newaddr ();
            theEnvelope->sender->personal = cpystr(const_cast<char*>(lName.c_str()));
            theEnvelope->sender->mailbox = cpystr(const_cast<char*>(lMailbox.c_str()));
            theEnvelope->sender->host = cpystr(const_cast<char*>(lHost.c_str()));
          }
          else if(lLowerNodeName == "replyto")
          {
            std::string lName;
            std::string lMailbox;
            std::string lHost;
            SMTPFunction::getNameAndEmailAddress(lChild, lName, lMailbox, lHost);
            theEnvelope->reply_to= mail_newaddr ();
            theEnvelope->reply_to->personal = cpystr(const_cast<char*>(lName.c_str()));
            theEnvelope->reply_to->mailbox = cpystr(const_cast<char*>(lMailbox.c_str()));
            theEnvelope->reply_to->host = cpystr(const_cast<char*>(lHost.c_str()));
          }
          else if(lLowerNodeName == "subject") {
            theEnvelope->subject = cpystr ((char*)lValue.c_str());
          } else if (lLowerNodeName == "recipient") { 
         
            Iterator_t lRecipentChildren = lChild.getChildren(); 
            lRecipentChildren->open();
            Item lRecipentChild;
            lRecipentChildren->next(lRecipentChild);
            lLowerNodeName = fn::lower_case( get_nodename(lRecipentChild) );
            lRecipentChildren->close();

            if(lLowerNodeName == "to")
            {
              std::string lName;
              std::string lMailbox;
              std::string lHost;
              SMTPFunction::getNameAndEmailAddress(lRecipentChild, lName, lMailbox, lHost);
              // there can be multiple to nodes, iterate to the next free one!
              ADDRESS** lNext = &theEnvelope->to;
              while (*lNext) {
                lNext = &((*lNext)->next);
              }  
              *lNext = mail_newaddr ();
              (*lNext)->personal = cpystr(const_cast<char*>(lName.c_str()));
              (*lNext)->mailbox = cpystr(const_cast<char*>(lMailbox.c_str()));
              (*lNext)->host = cpystr(const_cast<char*>(lHost.c_str()));
              
            }
            else if(lLowerNodeName == "cc")
            {
              std::string lName;
              std::string lMailbox;
              std::string lHost;
              SMTPFunction::getNameAndEmailAddress(lRecipentChild, lName, lMailbox, lHost);
              ADDRESS** lNext = &theEnvelope->cc;
              while (*lNext) {
                lNext = &((*lNext)->next);
              }  
              *lNext = mail_newaddr ();
              (*lNext)->personal = cpystr(const_cast<char*>(lName.c_str()));
              (*lNext)->mailbox = cpystr(const_cast<char*>(lMailbox.c_str()));
              (*lNext)->host = cpystr(const_cast<char*>(lHost.c_str()));
            }
            else if(lLowerNodeName == "bcc")
            {
              std::string lName;
              std::string lMailbox;
              std::string lHost;
              SMTPFunction::getNameAndEmailAddress(lRecipentChild, lName, lMailbox, lHost);
            
              ADDRESS** lNext = &theEnvelope->bcc;
              while (*lNext) {
                lNext = &((*lNext)->next);
              }  
           
              *lNext = mail_newaddr ();
              (*lNext)->personal = cpystr(const_cast<char*>(lName.c_str()));
              (*lNext)->mailbox = cpystr(const_cast<char*>(lMailbox.c_str()));
              (*lNext)->host = cpystr(const_cast<char*>(lHost.c_str()));
            }
        }       
    }
    lChildrenIt->close();

    return lRes;
  }

  bool
  CClientMimeHandler::body
      (std::stringstream& aDiagnostics)
  {
    Iterator_t    lChildrenIt;
    zorba::Item   lChild;
    bool          lRes = true;
    zorba::String lValue;

    theBody->type = TYPEOTHER;

    lChildrenIt = theBodyItem.getChildren();
    lChildrenIt->open();
    while (lChildrenIt->next(lChild))
    {
        get_text_value(lChild, lValue);
        // content case
        String const lc( fn::lower_case( get_nodename(lChild) ) );
        if(fn::ends_with(lc,"tent"))
          parse_content(theBody, lChild);
        // multipart case
        else if(fn::ends_with(lc,"rt"))
          parse_multipart(theBody, lChild);
    }
    lChildrenIt->close();

    return lRes;
  }

  void
  CClientMimeHandler::set_text_body
      (BODY* aBody,
       String& aMessage)
  {
    
    String lMessage;
    // special case for encoding of base64 which needs a new line after 64 characters
    if (aBody->encoding == ENCBASE64) {
      std::stringstream lInStream;
      std::stringstream lOutStream;
      // for loop that counts to 64 and then makes a new line
      lInStream << const_cast<char*>(aMessage.c_str());
      char next;
      int counter = 0;
      while (lInStream >> next) {
        if (++counter == 64) {
          lOutStream << "\r\n";
          counter = 1;
        }
        lOutStream << next;
      }  
      lMessage = lOutStream.str(); 
    } else {  
      lMessage = aMessage;
    }  
    
    char *text = (char *) fs_get (strlen(lMessage.c_str()));
    text = cpystr (lMessage.c_str());
    aBody->contents.text.size = strlen(text);
    aBody->contents.text.data = (unsigned char *) text;   //message body

  }

  PARAMETER *
  CClientMimeHandler::create_param
      (const char* aAttribute,
       const char * aValue,
       PARAMETER * aPrevious)
  {
    PARAMETER *lParam;
    lParam = mail_newbody_parameter();
    lParam->attribute = cpystr (aAttribute);
    lParam->value = cpystr (aValue);

    if(aPrevious)
      aPrevious->next = lParam;

    return lParam;
  }

  void
  CClientMimeHandler::set_encoding
      (BODY* aBody,
       zorba::String& aEncoding)
  {
    //all encodings should start with ENC so we only check the rest of the string
    zorba::String const lUpperEncSuffix = fn::upper_case( aEncoding.substr(3) );

    if(lUpperEncSuffix == "7BIT")
      aBody->encoding = ENC7BIT;
    else if (lUpperEncSuffix == "8BIT")
      aBody->encoding = ENC8BIT;
    else if (lUpperEncSuffix == "BINARY")
      aBody->encoding = ENCBINARY;
    else if (lUpperEncSuffix == "BASE64")
      aBody->encoding = ENCBASE64;
    else if (lUpperEncSuffix == "QUOTEDPRINTABLE")
      aBody->encoding = ENCQUOTEDPRINTABLE;
    else
      aBody->encoding = ENCOTHER;
  }

  bool
  CClientMimeHandler::set_content_type_value
      (BODY* aBody,
       zorba::String& aValue)
  {
    bool          lRes = true;
    int           lPos = aValue.find('/');
    zorba::String const lLowerType = fn::lower_case(aValue.substr(0, lPos));

    //set the BODY content type
    if(lLowerType == "text")
      aBody->type = TYPETEXT;
    else if(lLowerType == "multipart")
      aBody->type = TYPEMULTIPART;
    else if(lLowerType == "message")
      aBody->type = TYPEMESSAGE;
    else if(lLowerType == "application")
      aBody->type = TYPEAPPLICATION;
    else if(lLowerType == "image")
      aBody->type = TYPEIMAGE;
    else if(lLowerType == "audio")
      aBody->type = TYPEAUDIO;
    else if(lLowerType == "video")
      aBody->type = TYPEVIDEO;
    else
    {
      aBody->type = TYPEOTHER;
      lRes = false;
    }
    if(lRes) //set the BODY content subtype
    {
      // the list of subtypes of each type is available at
      // http://www.iana.org/assignments/media-types/
      zorba::String lSubtype = aValue.substr(lPos + 1,aValue.length() - lPos);
      aBody->subtype = cpystr((char*) fn::upper_case(lSubtype).c_str());
    }

    return lRes;
  }

  void
  CClientMimeHandler::set_contentTypeCharsetCTF(BODY* aBody,
                                                const Item& aContentOrMultipartItem) {
      
    Iterator_t lAttributes = aContentOrMultipartItem.getAttributes();
    lAttributes->open();
    Item lAttributeItem;
    String lValue;
    while(lAttributes->next(lAttributeItem)) {
      String lName = get_nodename(lAttributeItem); 
      lValue = lAttributeItem.getStringValue();
      if (fn::ends_with(lName,"ype")) {
        // contentType ...
        set_content_type_value(aBody, lValue);
      } else if (fn::ends_with(lName,"set")) {
        // charset ...
        aBody->parameter = create_param("charset", const_cast<char*>(fn::upper_case(lValue).c_str()), NIL);
      } else if (fn::ends_with(lName,"ing")) {
        // contentTranferEncoding ...
        set_encoding(aBody, lValue);  
      } else if (fn::ends_with(lName,"ion")) {
        // contentDisposition ..
        aBody->disposition.type = cpystr(const_cast<char*>(fn::upper_case(lValue).c_str())); 
      } else if (fn::ends_with(lName,"ame")) {
        // contentDisposition-filename
        if (!aBody->disposition.parameter) {  
          aBody->disposition.parameter = create_param("filename", const_cast<char*>(lValue.c_str()), NIL);
        } else {
          aBody->disposition.parameter->next = create_param("filename", const_cast<char*>(lValue.c_str()), NIL);
        }
      } else if (fn::ends_with(lName,"ate")) {
        // contentDisposition-modification-date
        char lDate[MAILTMPLEN];
        parseXmlDateTime(lValue, lDate);      
        if (!aBody->disposition.parameter) {
          aBody->disposition.parameter = create_param("modification-date", lDate); 
        } else {
          aBody->disposition.parameter->next = create_param("modification-date", lDate);
        } 
     }
    }
      
    lAttributes->close();
  }


  bool
  CClientMimeHandler::parse_content
      (BODY* aBody,
       const Item aItemContent)
  {
    zorba::String lValue;

    // set the contentType, charset and contentTransferEncoding (which are attributes of a content node)
    set_contentTypeCharsetCTF(aBody, aItemContent);
    
    lValue = aItemContent.getStringValue();
    set_text_body(aBody, lValue);
        
    return true;
  }

  bool
  CClientMimeHandler::parse_multipart
      (BODY* aBody,
       const Item aItemMultipart)
  {
    Iterator_t    lChildrenIt;
    Item          lChild;
    zorba::String lValue;
    PART*         lPartRoot = NIL;
    PART*         lPartPrev = NIL;
 
    set_contentTypeCharsetCTF(aBody, aItemMultipart);
    
    // a multipart node constists of several content or multipart nodes
    lChildrenIt = aItemMultipart.getChildren();
    lChildrenIt->open();
    while (lChildrenIt->next(lChild))
    {

        // a simple content item
        String const lc( fn::lower_case( get_nodename(lChild) ) );
        if(fn::ends_with(lc,"tent"))
        {
          PART* lPart;
          lPart = mail_newbody_part();
          parse_content(&lPart->body, lChild);
          if (lPartPrev) {
            lPartPrev->next = lPart;
          }  else {
            lPartRoot = lPart;
          }  
          lPartPrev = lPart;
        }

        // a multipart item ... this calls for recursion 
        else if(fn::ends_with(lc,"ipart"))
        {
          PART* lPart;
          lPart = NIL;
          lPart = mail_newbody_part();

          parse_multipart(&lPart->body,lChild);
        
          if (lPartPrev) {
            lPartPrev->next = lPart;
          }  else {
            lPartRoot = lPart;
          }  
          lPartPrev = lPart;
        }
      
    }
    lChildrenIt->close();

    if(lPartRoot)
      aBody->nested.part = lPartRoot;

    return true;
  }

  void 
  CClientMimeHandler::parseXmlDateTime(String& aXmlDateTime, char* aCDateTime) {
      // first we get year, month, day, hour, minute and seconds as zorba strings      

      int lTempIndex;
      lTempIndex = aXmlDateTime.find('-');
      String lYearString = aXmlDateTime.substr(0, lTempIndex);
      aXmlDateTime = aXmlDateTime.substr(lTempIndex+1);
  
      lTempIndex = aXmlDateTime.find('-');
    
      String lMonthString = aXmlDateTime.substr(0, lTempIndex);
      aXmlDateTime = aXmlDateTime.substr(lTempIndex+1);
      
      lTempIndex = aXmlDateTime.find('T');

      String lDayString = aXmlDateTime.substr(0, lTempIndex);
      aXmlDateTime = aXmlDateTime.substr(lTempIndex+1);
            
      lTempIndex = aXmlDateTime.find(':');
      
      String lHourString = aXmlDateTime.substr(0, lTempIndex);
      aXmlDateTime = aXmlDateTime.substr(lTempIndex+1);
      
      lTempIndex = aXmlDateTime.find(':');
      
      String lMinutesString = aXmlDateTime.substr(0, lTempIndex);
      aXmlDateTime = aXmlDateTime.substr(lTempIndex+1);
     
      // the next two digits specify the seconds
      String lSecondsString = aXmlDateTime.substr(0, 2);
      



      MESSAGECACHE * lDummyCache = mail_new_cache_elt (0);
      unsigned int lTempDatePart;
     

      // now, according to the specification of the dateTime xml type, we can have either: nothing, a Z (for UTC), -XXXX or +XXXX)
      String lUTCString = aXmlDateTime.substr(2);

      if (fn::starts_with(lUTCString,"+") || fn::starts_with(lUTCString,"-")) {
        lTempIndex = lUTCString.find(':');
        String lUTCHours = lUTCString.substr(1, lTempIndex-1);
        String lUTCMinutes = lUTCString.substr(lTempIndex + 1);
        
        std::stringstream lHoursConverter;
        lHoursConverter << lUTCHours.c_str();
        lHoursConverter >> lTempDatePart;
        lDummyCache->zhours  = lTempDatePart;
         
                     
        std::stringstream lMinutesConverter;
        lMinutesConverter << lUTCMinutes.c_str();
        lMinutesConverter >> lTempDatePart;
        lDummyCache->zminutes = lTempDatePart;
       
        if (fn::starts_with(lUTCString,"-")) { 
          lDummyCache->zoccident = 1;
        }
      }      
 
      // now we convert them and throw them into a dummy message cache
      {
        std::stringstream lConverter;
        lConverter << lYearString.c_str();
        lConverter >> lTempDatePart;      
        lTempDatePart -= 1970;
        lDummyCache->year = lTempDatePart;
      }

      {
        std::stringstream lConverter;
        lConverter << lMonthString.c_str();
        lConverter >> lTempDatePart;
        lDummyCache->month = lTempDatePart;
      }

      {
        std::stringstream lConverter;
        lConverter << lDayString.c_str();
        lConverter >> lTempDatePart;
        lDummyCache->day = lTempDatePart;
      }
      
      {
        std::stringstream lConverter;
        lConverter << lHourString.c_str();
        lConverter >> lTempDatePart;
        lDummyCache->hours = lTempDatePart;
      }

      {
        std::stringstream lConverter;
        lConverter << lMinutesString.c_str();
        lConverter >> lTempDatePart;
        lDummyCache->minutes = lTempDatePart;
      }
      
      {
        std::stringstream lConverter;
        lConverter << lSecondsString.c_str();
        lConverter >> lTempDatePart;
        lDummyCache->seconds = lTempDatePart;
      }
          
      mail_cdate(aCDateTime, lDummyCache); 
  
      // like this, we have a string of the form: Sun Aug  8 08:40:40 2010 +0000\n
      // what we actually would like is follwing: Fri, 10 Dec 2010 14:14:28 +0100 (CET)

      std::stringstream lDate(aCDateTime);
      
      std::string lDayAsWord;
      std::string lMonthAsWord;
      std::string lDay;
      std::string lTime;
      std::string lYear;
      std::string lUTC;

      lDate >> lDayAsWord >> lMonthAsWord >> lDay >> lTime >> lYear >> lUTC;
      
      lDate.str(std::string());
      lDate << lDayAsWord << ", " << lDay << " " <<  lMonthAsWord << " " << lYear << " " << lTime << " " << lUTC << " (UTF)";  
    
      strcpy(aCDateTime, lDate.str().c_str());
  }



  //destroy theBody and theEnvelope
  void CClientMimeHandler::end()
  {
  }

  CClientMimeHandler::~CClientMimeHandler()
  {
    //if( theEnvelope )
    //  mail_free_envelope( &theEnvelope );

    //mail_free_body(&theBody);
  }

  } //namespace email
} //namespace zorba
/* vim:set et sw=2 ts=2: */
