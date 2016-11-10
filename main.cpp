#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


int main()
{
  const char* filepath = "test.xml";  
  /*TiXmlDocument doc(filepath);  
  bool loadOkay = doc.LoadFile();  
  if (!loadOkay) {      
    cout<<"Could not load test file."<<endl;
    exit( 1 );  
    return 0;
  } */
  string xml_data = "<Server><item><entrust_price>100.00</entrust_price><entrust_amount>1.0</entrust_amount><operator>10000</operator><entrust_direction>1</entrust_direction></item><item><entrust_price>101.00</entrust_price><entrust_amount>2.0</entrust_amount><operator>10001</operator><entrust_direction>2</entrust_direction></item></Server>";
  
  TiXmlDocument *doc = new TiXmlDocument();
  doc->Parse(xml_data.c_str(), 0,TIXML_ENCODING_UNKNOWN); 
  
  TiXmlElement* root = doc->RootElement();  
  

  for( TiXmlNode*  item = root->FirstChild( "item" );  item;  item = item->NextSibling( "item" ) ) {  
 
    TiXmlNode* child = item->FirstChild();  
    const char* entrust_price = child->ToElement()->GetText();  
    if (entrust_price) {  
      cout<<"entrust_price:"<<entrust_price<<endl;
    } else {  
      cout<<"entrust_price:"<<endl;
    }  
  

    child = item->IterateChildren(child);  
    const char* entrust_amount = child->ToElement()->GetText();  
    if (entrust_amount) {  
      cout<<"entrust_amount:"<<entrust_amount<<endl;
    } else {  
      cout<<"entrust_amount:"<<endl;  
    }
  
    child = item->IterateChildren(child);  
    const char* operator_no = child->ToElement()->GetText();  
    if (operator_no) {  
      cout<<"operator_no:"<<operator_no<<endl;
    } else {  
      cout<<"operator_no:"<<endl;
    }  
  
    
    child = item->IterateChildren(child);  
    const char* entrust_direction = child->ToElement()->GetText();  
    if(entrust_direction) {  
        cout<<"entrust_direction:"<<entrust_direction<<endl;
    } else {  
        cout<<"entrust_direction:"<<endl;
    } 
    cout<<endl;
  }
  delete doc;
}
