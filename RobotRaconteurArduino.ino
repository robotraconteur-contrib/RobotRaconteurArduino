#include <Arduino.h>
#include <Base64.h>
#include <CryptoLegacy.h>
#include <SHA1.h>

/*This is a program that demonstrates a Robot Raconteur
running on an Arduino Uno with an ethernet shield.*/

#include <SPI.h>
#include <Ethernet.h>
#include "RobotRaconteurServer.h"

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
PROGMEM const byte nodeid[]={0xc0, 0x39, 0xf3, 0x92, 0xe2, 0xef, 0xff, 0x48, 0x98, 0x2e, 0x88, 0xdd, 0x87, 0xf5, 0x9, 0xab};
PROGMEM const char nodeid_str[]="c039f392-e2ef-ff48-982e-88dd87f509ab";

PROGMEM const char SERVICEDEF[] = {"service arduinotest_interface\nobject obj\nfunction int16 dimmer(int16 v)\nend object\n"};
#define SERVICEDEF_LEN 83
PROGMEM const char OBJECTTYPE[]= {"arduinotest_interface.obj"};
#define OBJECTTYPE_LEN 25
PROGMEM const char SERVICEPATH[] ={ "arduinotest" };
#define SERVICEPATH_LEN 11

RobotRaconteurServer robotraconteur(48653,nodeid,nodeid_str,SERVICEDEF,SERVICEDEF_LEN,OBJECTTYPE,OBJECTTYPE_LEN,SERVICEPATH,SERVICEPATH_LEN);

void setup()
{

  pinMode(9,OUTPUT);
  //Serial.println("Hello world!");
  Ethernet.begin(mac);
  //robotraconteur.loop();
  robotraconteur.startudp();
  robotraconteur.start();

}

unsigned long lastevent=0;
uint32_t loop_count=0;

void loop() {

  robotraconteur.loop();
 
};

void rr_function_call(RobotRaconteurServerConnection* con,char* MemberName,uint16_t ElementCount)
{
  if (strncmp(con->entry_MemberName,"dimmer",6)==0)
  {
    if (con->entry_ElementCount !=1)
    {
      con->SetMemberFormatMismatchError();
    }
    else
    {
      uint16_t fElementSize;
      char* fElementName;
      uint8_t fElementName_len;
      uint16_t fElementType;
      uint16_t fDataCount;
      rr_socket* fsock;

      con->ReadNextMessageElement(&fElementSize,&fElementName,&fElementName_len,&fElementType,&fDataCount,&fsock);

      uint16_t fval=fsock->read_uint16();
      analogWrite(9,fval);

      con->StartWriteMessageElement("return",false,6,rr_int16_t,NULL,false,0,1,&fsock);
      fsock->write_uint16(0);
      con->EndWriteMessageElement();
    }
  }
  else
  {
    con->SetMemberNotFoundError();
  }
}
void rr_property_get(RobotRaconteurServerConnection* con,char* MemberName,uint16_t ElementCount)
{
  con->SetMemberNotFoundError();
}
void rr_property_set(RobotRaconteurServerConnection* con,char* MemberName,uint16_t ElementCount)
{
  con->SetMemberNotFoundError();
}
