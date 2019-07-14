#include <Ethernet.h>
#include "RobotRaconteurServer.h"
#include <string.h>
#include <avr/pgmspace.h>
#include <limits.h>

//class rr_socket


PROGMEM const char INDEXDEF[] ={"service RobotRaconteurServiceIndex\nstruct NodeInfo\nfield string NodeName\nfield uint8[16] NodeID\nfield string{int32} ServiceIndexConnectionURL\nend struct\nstruct ServiceInfo\nfield string Name\nfield string RootObjectType\nfield string{int32} RootObjectImplements\nfield string{int32} ConnectionURL\nfield varvalue{string} Attributes\nend struct\nobject ServiceIndex\nfunction ServiceInfo{int32} GetLocalNodeServices()\nfunction NodeInfo{int32} GetRoutedNodes()\nfunction NodeInfo{int32} GetDetectedNodes()\nevent LocalNodeServicesChanged()\nend object"};
#define INDEXDEF_LEN 556
PROGMEM const char INDEXTYPE[] = {"RobotRaconteurServiceIndex.ServiceIndex"};
#define INDEXTYPE_LEN 39
PROGMEM const char STRCONST_RRAC[] = {"RRAC"};
#define STRCONST_RRAC_LEN  4
PROGMEM const char STRCONST_RobotRaconteur_NodeNotFound[] = {"RobotRaconteur.NodeNotFound"};
#define STRCONST_RobotRaconteur_NodeNotFound_LEN 27
PROGMEM const char STRCONST_RobotRaconteur_InvalidEndpoint[] = {"RobotRaconteur.InvalidEndpoint"};
#define STRCONST_RobotRaconteur_InvalidEndpoint_LEN 30
PROGMEM const char STRCONST_RobotRaconteur_ProtocolError[] = {"RobotRaconteur.ProtocolError"};
#define STRCONST_RobotRaconteur_ProtocolError_LEN 28
PROGMEM const char STRCONST_servicedef[] = {"servicedef"};
#define STRCONST_servicedef_LEN 10
PROGMEM const char STRCONST_attributes[] = {"attributes"};
#define STRCONST_attributes_LEN 10
PROGMEM const char STRCONST_RobotRaconteur_ServiceNotFound[] = {"RobotRaconteur.ServiceNotFound"};
#define STRCONST_RobotRaconteur_ServiceNotFound_LEN 30
PROGMEM const char STRCONST_objecttype[] = {"objecttype"};
#define STRCONST_objecttype_LEN 10
PROGMEM const char STRCONST_return[] = {"return"};
#define STRCONST_return_LEN 6
PROGMEM const char STRCONST_RobotRaconteur_MemberNotFound[] = {"RobotRaconteur.MemberNotFound"};
#define STRCONST_RobotRaconteur_MemberNotFound_LEN 29
PROGMEM const char STRCONST_RobotRaconteur_ObjectNotFound[] = {"RobotRaconteur.ObjectNotFound"};
#define STRCONST_RobotRaconteur_ObjectNotFound_LEN 29
PROGMEM const char STRCONST_errorname[] = {"errorname"};
#define STRCONST_errorname_LEN 9
PROGMEM const char STRCONST_errorstring[] = {"errorstring"};
#define STRCONST_errorstring_LEN 11
PROGMEM const char STRCONST_RobotRaconteur_MemberFormatMismatch[] = {"RobotRaconteur.MemberFormatMismatch"};
#define STRCONST_RobotRaconteur_MemberFormatMismatch_LEN 35
//PROGMEM const char STRCONST_RobotRaconteur_MemberNotFound[] = {"RobotRaconteur.MemberNotFound"};
//#define STRCONST_RobotRaconteur_MemberNotFound_LEN 29
PROGMEM const char STRCONST_RobotRaconteurServiceIndex_ServiceInfo[] = {"RobotRaconteurServiceIndex.ServiceInfo"};
#define STRCONST_RobotRaconteurServiceIndex_ServiceInfo_LEN 38;
PROGMEM const char STRCONST_Name[] = {"Name"};
#define STRCONST_Name_LEN 4
PROGMEM const char STRCONST_RootObjectType[] = {"RootObjectType"};
#define STRCONST_RootObjectType_LEN 14
PROGMEM const char STRCONST_arduinotest_interface_obj[] = {"arduinotest_interface.obj"};
#define STRCONST_arduinotest_interface_obj_LEN 25
PROGMEM const char STRCONST_RootObjectImplements[] = {"RootObjectImplements"};
#define STRCONST_RootObjectImplements_LEN 20
PROGMEM const char STRCONST_ConnectionURL[] = {"ConnectionURL"};
#define STRCONST_ConnectionURL_LEN 13
PROGMEM const char STRCONST_Attributes[] = {"Attributes"};
#define STRCONST_Attributes_LEN 10
PROGMEM const char STRCONST_GetRemoteNodeID[] = {"GetRemoteNodeID"};
#define STRCONST_GetRemoteNodeID_LEN 15
PROGMEM const char STRCONST_RobotRaconteurServiceIndex[] = {"RobotRaconteurServiceIndex"};
#define STRCONST_RobotRaconteurServiceIndex_LEN 26
PROGMEM const char STRCONST_GetRoutedNodes[] = {"GetRoutedNodes"};
#define STRCONST_GetRoutedNodes_LEN 14
PROGMEM const char STRCONST_GetDetectedNodes[] = {"GetDetectedNodes"};
#define STRCONST_GetDetectedNodes_LEN 16
PROGMEM const char STRCONST_GetLocalNodeServices[] = {"GetLocalNodeServices"};
#define STRCONST_GetLocalNodeServices_LEN 20

uint8_t rr_socket::_shared_write_buf[300];
rr_socket::rr_socket(uint8_t sock) : _client(sock)
{
	_read_pos=0;
	_write_length=0;
	_write_pos=0;
}

//Functions to read stream
uint8_t rr_socket::read_uint8()
{
  uint8_t o;
  read(&o,1);
  return o;
}
uint16_t rr_socket::read_uint16()
{
  uint16_t o;
  read((uint8_t*)((void*)&o),2);
  return o; 
}
uint32_t rr_socket::read_uint32()
{
  uint32_t o;
  read((uint8_t*)((void*)&o),4);
  return o; 
}

void rr_socket::read(uint8_t *buf, size_t size)
{
  _client.read(buf,size);
  _read_pos+=size;
}

int16_t rr_socket::read_available()
{
  return _client.available();
}

uint16_t rr_socket::read_pos()
{
  return _read_pos; 
}

void rr_socket::read_resetpos()
{
  _read_pos=0; 
}


//Functions to write to stream
void rr_socket::write_uint8(uint8_t val)
{
  write(&val,1,false);
}

void rr_socket::write_uint16(uint16_t val)
{
  write((uint8_t*)((void*)&val),2,false);
}

void rr_socket::write_uint32(uint32_t val)
{
  write((uint8_t*)((void*)&val),4,false);
}

void rr_socket::write(const uint8_t* buf, size_t size, bool progmem)
{
	if (_write_pos + size > sizeof(_shared_write_buf))
	{
		Serial.print("ABORT sent message too large ");
		Serial.println(_write_pos + size);
		delay(1000);
		abort();
	}

	if (progmem)
	{
		memcpy_P(_shared_write_buf + _write_pos, buf, size);
	}
	else
	{
		memcpy(_shared_write_buf + _write_pos, buf, size);
	}

  //W5100.send_data_processing_offset(_sock,_write_pos,buf,size);
    
  _write_pos+=size;
  if (_write_pos > _write_length)
  {
   _write_length=_write_pos; 
  }
}

void rr_socket::write_progmem(const void* progmem, size_t size)
{
  write((const uint8_t*)progmem, size,true);
}

size_t rr_socket::write_length()
{
  return _write_length;
}

void rr_socket::write_reset_length()
{
  _write_pos=0;
  _write_length=0; 
}

uint16_t rr_socket::write_getpos()
{
 return _write_pos; 
}

void rr_socket::write_setpos(uint16_t pos)
{
  _write_pos=pos;
  /*Serial.print("ptr: ");
  Serial.println(W5100.readSnTX_WR(_sock));
  Serial.print("ptr2: ");
  Serial.println(W5100.readSnTX_WR(_sock)+pos);*/
 //W5100.writeSnTX_WR(_sock, W5100.readSnTX_WR(_sock) + pos);
}


int16_t rr_socket::send_freesize()
{
  return sizeof(_shared_write_buf) - _write_pos;
}


uint8_t rr_socket::send()
{
  /*uint8_t statu=status();
  if ((statu != SnSR::ESTABLISHED) && (statu != SnSR::CLOSE_WAIT))
  {
    return  0; 

  }


  W5100.execCmdSn(_sock,Sock_SEND);
  while ( (W5100.readSnIR(_sock) & SnIR::SEND_OK) != SnIR::SEND_OK ) 
  {

    if ( W5100.readSnSR(_sock) == SnSR::CLOSED )
    {
      close();
      return 0;
    }
  }

  W5100.writeSnIR(_sock, SnIR::SEND_OK);
 
  return 1;*/
  return _client.write(_shared_write_buf, _write_length);
}

void rr_socket::send_flush()
{
_write_length=0;
_write_pos=0;
}

void rr_socket::close()
{
  _write_length=0;
  _client.stop();
}

//class RobotRaconteurServerConnection

RobotRaconteurServerConnection::RobotRaconteurServerConnection() : 
_sock(0)
{

  _port=0;
  message_len=0;
}

RobotRaconteurServerConnection::RobotRaconteurServerConnection(uint8_t sock, uint16_t port) :
_sock(sock)
{

  connected=false;
  _port=port;
  message_len=0;
}

void RobotRaconteurServerConnection::loop()
{
  if (!_sock._client.connected())
  {
	  connected=false;
    return;
  }

  if (_sock.read_available()==0)
  {
    return;
  }
  
  int16_t avail=_sock.read_available();
  
  if (avail > 0)
  {
    
    if (message_len==0)
    {
      if (avail>=8)
      {
        _sock.read_resetpos();
        _sock.write_reset_length();
        read_messagelen();
        
        
      }
    }
    
    if (message_len != 0)
    {
      if (avail >= (message_len-8))
      {
        process_message();
        //message_len=0;
      } 
    }
  }

}

void RobotRaconteurServerConnection::read_messagelen()
{
  uint8_t seed[4];
  _sock.read(seed,4);
  message_len=_sock.read_uint32();

  //Serial.print("message_len: ");
  //Serial.println(message_len);
  if (strncmp_P((char*)seed,STRCONST_RRAC,4)!=0 || message_len > 1024)
  {

    _sock.close();
    flush_message();
    message_len=0;
    return;
  }
}




void RobotRaconteurServerConnection::process_message()
{

  //Read in the message header

  if (_sock.read_uint16()!=2)
  {
    flush_message();
    _sock.close();
    message_len=0; 
  }

  //read header length
  _sock.read_uint16();

  uint8_t SenderNodeID[16];
  uint8_t ReceiverNodeID[16];

  _sock.read(SenderNodeID,16);
  _sock.read(ReceiverNodeID,16);

  uint32_t SenderEndpoint=_sock.read_uint32();
  uint32_t ReceiverEndpoint=_sock.read_uint32();

  //Ignore sender node name
  uint16_t pname_s=_sock.read_uint16();
  for (uint16_t i=0; i<pname_s; i++) {
    _sock.read_uint8();
  }

  uint16_t pname_r=_sock.read_uint16();

  char ReceiverNodeName[16];
  memset(ReceiverNodeName,0,16);

  uint8_t ReceiverNodeName_len=0;
  for (uint16_t i=0; i<pname_r; i++)
  {
    uint8_t c=_sock.read_uint8();
    if (i<32) {
      ReceiverNodeName[i]=(char)c;
      ReceiverNodeName_len=(uint8_t)(i+1);
    }

  }

  //Ignore meta-data
  uint16_t meta_s = _sock.read_uint16();
  for (uint16_t i=0; i<meta_s; i++) {
    _sock.read_uint8();
  }

  uint16_t message_EntryCount1=_sock.read_uint16();
  if (message_EntryCount1 > 255)
  {
    message_EntryCount=255; 
  }
  else
  {
    message_EntryCount=(uint8_t)message_EntryCount1; 
  }
  _sock.read_uint16();
  _sock.read_uint16();


  Serial.print("Sender endpoint: ");
  Serial.println(SenderEndpoint);
  Serial.print("Entry count: ");
  Serial.println(message_EntryCount);
  //write the return message header.  Save the ptr positions for
  //variables that may need to be changed after being written

  
  _sock.write((const uint8_t*)STRCONST_RRAC,STRCONST_RRAC_LEN,true);
  send_message_length_pos=_sock.write_getpos();
  _sock.write_uint32(0);
  _sock.write_uint16(2);
  send_message_header_length_pos=_sock.write_getpos();
  _sock.write_uint16(0);
  _sock.write(RobotRaconteurServer::NodeID,16,true);
  _sock.write(SenderNodeID,16,false);
  send_message_sender_endpoint_pos=_sock.write_getpos();
  _sock.write_uint32(send_message_sender_endpoint);
  _sock.write_uint32(SenderEndpoint);
  _sock.write_uint16(0);//SenderNodeName
  _sock.write_uint16(0);//ReceiverNodeName
  _sock.write_uint16(0);//MetaData
  send_message_entry_count_pos=_sock.write_getpos();
  _sock.write_uint16(0);//EntryCount
  _sock.write_uint16(0);//MessageID
  _sock.write_uint16(0);//MessageResID
  
  

  //Update the header length field
  
  uint16_t headerlen=_sock.write_length();
  //uint16_t ptr=_sock.write_getptr();
  _sock.write_setpos(send_message_header_length_pos);
  _sock.write_uint16(headerlen);
  _sock.write_setpos(_sock.write_length());
  //_sock.write_setptr(ptr);
  
  //We are now ready to process some message entries!
   
  send_message_entry_count=0;

  for (uint8_t i=0; i<message_EntryCount; i++)
  {
    //read in messag entry
    entry_start_pos=_sock.read_pos();
    
    entry_EntrySize=_sock.read_uint32();
        
    entry_EntryType=_sock.read_uint16();
    _sock.read_uint16();
    
    entry_ServicePath_len=0;
    uint16_t entry_ServicePath_len1=_sock.read_uint16();
    for (uint16_t i=0; i<entry_ServicePath_len1; i++)
    {
      uint8_t c=_sock.read_uint8();
      if (i<32) {
        entry_ServicePath[i]=(char)c;
        entry_ServicePath_len=(uint8_t)(i+1);
      }
    }
    
    entry_MemberName_len=0;    
    uint16_t entry_MemberName_len1=_sock.read_uint16();
    for (uint16_t i=0; i<entry_MemberName_len1; i++)
    {
      uint8_t c=_sock.read_uint8();
      if (i<32) {
        entry_MemberName[i]=(char)c;
        entry_MemberName_len=(uint8_t)(i+1);
      }
    }
    entry_TransactionID=_sock.read_uint32();
    entry_Error=_sock.read_uint16();
       
    
    //Ignore meta-data
    uint16_t meta_s1 = _sock.read_uint16();
    for (uint16_t i=0; i<meta_s1; i++) {
      _sock.read_uint8();
    }
    
    entry_ElementCount=_sock.read_uint16();
    entry_element_count_enum=entry_ElementCount;
    
    if (entry_EntryType % 2 ==0)
    {
      Serial.println("Flush...");
      flush_message_entry();
      continue; 
    }
    
    //Start sending message element data    

    send_entry_start_pos=_sock.write_getpos();
    send_entry_length_pos=_sock.write_getpos();
    _sock.write_uint32(0);
    _sock.write_uint16(entry_EntryType+1);
    _sock.write_uint16(0);
    //Serial.print("entry_SPL: ");
    //Serial.println(entry_ServicePath_len);
    _sock.write_uint16((uint16_t)entry_ServicePath_len);
    for (int i=0; i<entry_ServicePath_len; i++) {_sock.write_uint8(entry_ServicePath[i]);}

    _sock.write_uint16(entry_MemberName_len);
    for (int i=0; i<entry_MemberName_len; i++) {_sock.write_uint8(entry_MemberName[i]);}
    _sock.write_uint32(entry_TransactionID);
    
    send_entry_error_pos=_sock.write_getpos();
    
    _sock.write_uint16(0); //error
    _sock.write_uint16(0); //metadata
    
    send_entry_element_count_pos=_sock.write_getpos();
    _sock.write_uint16(0); //elementcount
    
    send_entry_element_count=0;
    
    
    //Execute the message entry
    
    uint8_t is_any_nodeid=true;
    for (int j=0; j<16; j++) {if (ReceiverNodeID[j]!=0) {is_any_nodeid=false;}}
    
    uint8_t is_my_nodeid=true;
    for (int j=0; j<16; j++) {if (ReceiverNodeID[j]!=pgm_read_byte(RobotRaconteurServer::NodeID+j)) {is_my_nodeid=false;}}

    if ((entry_EntryType<=500 && (!is_any_nodeid && !is_my_nodeid)) || (entry_EntryType > 500 && !is_my_nodeid))
    {
      //Invalid endpoint
      //Send error from endpoint 0
      //ptr=_sock.write_getptr();
      _sock.write_setpos(send_message_sender_endpoint_pos);
      _sock.write_uint32(0);
      _sock.write_setpos(_sock.write_length());
     // _sock.write_setptr(ptr);
      
      //Set the error state
      SetMessageElementError((uint16_t)NodeNotFound,STRCONST_RobotRaconteur_NodeNotFound,true,STRCONST_RobotRaconteur_NodeNotFound_LEN,NULL,false,0);
    }
        
    else if ((entry_EntryType <=500 && ReceiverEndpoint !=0) || (entry_EntryType >500 && (ReceiverEndpoint !=send_message_sender_endpoint || send_message_sender_endpoint==0)))
    {
      //Invalid endpoint error...
      //This error has to come from endpoint 0
     
     // ptr=_sock.write_getptr();
      _sock.write_setpos(send_message_sender_endpoint_pos);
      _sock.write_uint32(0);
      _sock.write_setpos(_sock.write_length());
      //_sock.write_setptr(ptr);
      
      //Set the error state
      SetMessageElementError((uint16_t)InvalidEndpoint,STRCONST_RobotRaconteur_InvalidEndpoint,true,STRCONST_RobotRaconteur_InvalidEndpoint_LEN,NULL,false,0);
    }
    else
    {
    
    if (entry_EntryType==StreamOp)
    {
       if (strncmp_P(entry_MemberName,STRCONST_GetRemoteNodeID, 15)==0)
       {
         //Serial.println("Remote node id request");         
       }
       else
       {
         SetMessageElementError((uint16_t)ProtocolError,STRCONST_RobotRaconteur_ProtocolError,true,STRCONST_RobotRaconteur_ProtocolError_LEN,"",false,0);
       }
      
    }
    else if (entry_EntryType==GetServiceDesc)
    {
      rr_socket* sock;
      if (strncmp_P(entry_ServicePath,STRCONST_RobotRaconteurServiceIndex,26)==0)
      {
        
        StartWriteMessageElement(STRCONST_servicedef,true, STRCONST_servicedef_LEN,rr_string_t,NULL,false,0,INDEXDEF_LEN,&sock);
        _sock.write_progmem(INDEXDEF,INDEXDEF_LEN);
        EndWriteMessageElement();
        
        StartWriteMessageElement(STRCONST_attributes,true,STRCONST_attributes_LEN,rr_dictionary_t,NULL,false,0,0,&sock);
        EndWriteMessageElement();
      }
      else if (strncmp_P(entry_ServicePath,RobotRaconteurServer::ServicePath,RobotRaconteurServer::ServicePath_len)!=0)
      {
    	  Serial.print("Got reuest for service path: ");
    	  Serial.write(entry_ServicePath,entry_ServicePath_len);
    	  Serial.println();
        SetMessageElementError((uint16_t)ServiceNotFound,STRCONST_RobotRaconteur_ServiceNotFound,true,STRCONST_RobotRaconteur_ServiceNotFound_LEN,NULL,false,0);
        
      }
      else
      {
        StartWriteMessageElement(STRCONST_servicedef,true,STRCONST_servicedef_LEN,rr_string_t,NULL,false,0,RobotRaconteurServer::ServiceDef_len,&sock);
        _sock.write_progmem(RobotRaconteurServer::ServiceDef,RobotRaconteurServer::ServiceDef_len);
        EndWriteMessageElement();
        
        StartWriteMessageElement(STRCONST_attributes,true,STRCONST_attributes_LEN,rr_dictionary_t,NULL,false,0,0,&sock);
        EndWriteMessageElement();
      }
    }
    else if (entry_EntryType==ConnectionTest)
    {

    }
    else if (entry_EntryType==ObjectTypeName || entry_EntryType==ConnectClient || entry_EntryType==DisconnectClient || entry_EntryType==ClientKeepAliveReq || entry_EntryType==FunctionCallReq )
    {
      if (strncmp_P(entry_ServicePath,STRCONST_RobotRaconteurServiceIndex,26)==0)
      {
        if (entry_EntryType==ObjectTypeName)
        {
          rr_socket* sock;
          StartWriteMessageElement(STRCONST_objecttype,true,STRCONST_objecttype_LEN,rr_string_t,NULL,false,0,INDEXTYPE_LEN,&sock);
          _sock.write_progmem(INDEXTYPE,INDEXTYPE_LEN);
          EndWriteMessageElement();
        }
        else if (entry_EntryType==ConnectClient)
        {
          //Set the sender endpoint field and in the output buffer
          send_message_sender_endpoint=_sock._client.getSocketNumber() +100;
          //ptr=_sock.write_getptr();
          _sock.write_setpos(send_message_sender_endpoint_pos);
          _sock.write_uint32(send_message_sender_endpoint);
          _sock.write_setpos(_sock.write_length());
          //_sock.write_setptr(ptr);
          

        }
        else if (entry_EntryType==DisconnectClient)
        {
          connected=false;
        }
        else if (entry_EntryType==FunctionCallReq)
        {
          if (strncmp_P(entry_MemberName,STRCONST_GetRoutedNodes,14)==0 || strncmp_P(entry_MemberName,STRCONST_GetDetectedNodes,16)==0 )
          {
            rr_socket* sock;
            StartWriteMessageElement(STRCONST_return,true,STRCONST_return_LEN,rr_vector_t,NULL,false,0,0,&sock);
            
            EndWriteMessageElement();
          }
          else if (strncmp_P(entry_MemberName,STRCONST_GetLocalNodeServices,20)==0)
          {
            RobotRaconteurServer::GetLocalNodeServices(this);
          }        
          else
          {
            SetMessageElementError((uint16_t)MemberNotFound,STRCONST_RobotRaconteur_MemberNotFound,true,STRCONST_RobotRaconteur_MemberNotFound_LEN,NULL,false,0);
          }
        }
        else if (entry_EntryType==ClientKeepAliveReq)
        {
         //Serial.println("Client keep alive"); 
        }
        else
        {
        SetMessageElementError((uint16_t)MemberNotFound,STRCONST_RobotRaconteur_MemberNotFound,true,STRCONST_RobotRaconteur_MemberNotFound_LEN,NULL,false,0);
        }
      }
      else if (!strncmp_P(entry_ServicePath,RobotRaconteurServer::ServicePath,RobotRaconteurServer::ServicePath_len)==0)
      {
        SetMessageElementError((uint16_t)ObjectNotFound,STRCONST_RobotRaconteur_ObjectNotFound,true,STRCONST_RobotRaconteur_ObjectNotFound_LEN,NULL,false,0);
      }
      else
      {
        if (entry_EntryType==ObjectTypeName)
        {
          rr_socket* sock;
          StartWriteMessageElement(STRCONST_objecttype,true,STRCONST_objecttype_LEN,rr_string_t,NULL,false,0,RobotRaconteurServer::ObjectType_len,&sock);
          _sock.write_progmem(RobotRaconteurServer::ObjectType,RobotRaconteurServer::ObjectType_len);
          EndWriteMessageElement();
        }
        else if (entry_EntryType==ConnectClient)
        {
          //Set the sender endpoint field and in the output buffer
          send_message_sender_endpoint=_sock._client.getSocketNumber() + 100;
          //ptr=_sock.write_getptr();
          _sock.write_setpos(send_message_sender_endpoint_pos);
          _sock.write_uint32(send_message_sender_endpoint);
          _sock.write_setpos(_sock.write_length());
          //_sock.write_setptr(ptr);
          
          connected=true;
          remote_Endpoint=SenderEndpoint;
          memcpy(remote_NodeID,SenderNodeID,16);
        }
        else if (entry_EntryType==PropertyGetReq)
        {
         rr_property_get(this,entry_MemberName,entry_ElementCount); 
        }
        else if (entry_EntryType==PropertySetReq)
        {
         rr_property_set(this,entry_MemberName,entry_ElementCount); 
        }
        else if (entry_EntryType==FunctionCallReq)
        {
        	Serial.println("Start rr_function_call");
          rr_function_call(this,entry_MemberName,entry_ElementCount);
          Serial.println("End rr_function_call");
          
        }
      }
      
    }
    else
    {
      SetMessageElementError((uint16_t)ProtocolError,STRCONST_RobotRaconteur_ProtocolError,true,28,NULL,false,0);
    }
    }
    
    //Update the entry length field

    uint16_t entrylen=_sock.write_length()-send_entry_start_pos;
    //ptr=_sock.write_getptr();
    _sock.write_setpos(send_entry_length_pos);
    _sock.write_uint32(entrylen);
    //_sock.write_setpos(_sock.write_length());
    //_sock.write_setptr(ptr);
    //Serial.print("send_elp: ");
    //Serial.println(send_entry_length_pos);
    //Serial.print("send_el: ");
    //Serial.println(entrylen);
    
    _sock.write_setpos(send_entry_element_count_pos);
    _sock.write_uint16(send_entry_element_count);
    _sock.write_setpos(_sock.write_length());
    //_sock.write_setptr(ptr);
    
    
    send_message_entry_count++;

  }

  if(send_message_entry_count==0)
  {
    //Serial.println("Flushing message");
    _sock.send_flush();
  }
  else
  {
    uint16_t meslen=_sock.write_length();
    //ptr=_sock.write_getptr();
    _sock.write_setpos(send_message_length_pos);
    _sock.write_uint32(meslen);
    //_sock.write_setpos(_sock.write_length());
    //_sock.write_setptr(ptr);
    Serial.print("Sent message len: ");
    Serial.println(meslen);
    
    //ptr=_sock.write_getptr();
    _sock.write_setpos(send_message_entry_count_pos);
    _sock.write_uint32(send_message_entry_count);
    _sock.write_setpos(_sock.write_length());
    //_sock.write_setptr(ptr);
    _sock.send();
  } 
    
  flush_message();
  message_len=0;

}

int8_t RobotRaconteurServerConnection::ReadNextMessageElement(uint16_t* ElementSize, char** ElementName, uint8_t* ElementName_len,
  uint16_t* ElementType, uint16_t* DataCount, rr_socket** sock)
{
  if(entry_element_count_enum<1) 
  {
   return -1; 
  }
  
  entry_element_count_enum--;
  
  element_start_pos=_sock.read_pos();
  
  
  element_ElementSize=_sock.read_uint32();
  element_ElementName_len=0;
  uint16_t element_ElementName_len1=_sock.read_uint16();
  
  for (uint16_t i=0; i<element_ElementName_len1; i++)
  {
    uint8_t c=_sock.read_uint8();
    if (i<32) {
      element_ElementName[i]=(char)c;
      element_ElementName_len=(uint8_t)(i+1);
    }
  }
  
  element_ElementType=_sock.read_uint16();
  uint16_t etypenamelen=_sock.read_uint16();
  for (int i=0; i<etypenamelen; i++) _sock.read_uint8();
  uint16_t emetalen=_sock.read_uint16();
  for (int i=0; i<emetalen; i++) _sock.read_uint8();
  element_DataCount=_sock.read_uint32();
  
  *ElementSize=(uint16_t)element_ElementSize;
  *ElementName=element_ElementName;
  *ElementName_len=element_ElementName_len;
  *ElementType=element_ElementType;
  *DataCount=(uint16_t)element_DataCount;  
  
  *sock=&_sock;
  
  
  
  return entry_element_count_enum;
}

void RobotRaconteurServerConnection::StartWriteMessageElement(const char* ElementName, bool ElementName_progmem, uint8_t ElementName_len,
  uint16_t ElementType, const char* ElementTypeName, bool ElementTypeName_progmem, uint8_t ElementTypeName_len, uint16_t DataCount, rr_socket** sock)
{
  send_element_start_pos=_sock.write_length();
  send_element_length_pos=_sock.write_getpos();
  
  _sock.write_uint32(0);
  _sock.write_uint16(ElementName_len);
  _sock.write((uint8_t*)ElementName,ElementName_len,ElementName_progmem);
  _sock.write_uint16(ElementType);
  _sock.write_uint16(ElementTypeName_len);
  if (ElementTypeName_len > 0)
  {
   _sock.write((uint8_t*)ElementTypeName,ElementTypeName_len,ElementTypeName_progmem);
  }
  _sock.write_uint16(0);//MetaData
  _sock.write_uint32(DataCount);
  
  *sock=&_sock;
  
}

void RobotRaconteurServerConnection::EndWriteMessageElement()
{
  uint32_t len=_sock.write_length()-send_element_start_pos;
  //Serial.print("Element len: ");
  //Serial.println(len);
  //Serial.print("Element len pos: ");
  //Serial.println(send_element_length_pos);
  //uint16_t ptr=_sock.write_getptr();
  _sock.write_setpos(send_element_length_pos);
  _sock.write_uint32(len);
  _sock.write_setpos(_sock.write_length());
  //_sock.write_setptr(ptr);
  send_entry_element_count++;  
  
}


void RobotRaconteurServerConnection::SetMessageElementError(uint16_t errcode, const char* errname, bool errname_progmem, uint8_t errname_len,
     const char* errmessage, bool errmessage_progmem, uint8_t errmessage_len)
{

  rr_socket* sock;
  uint16_t currpos=_sock.write_getpos();
  //uint16_t ptr=_sock.write_getptr();
  _sock.write_setpos(send_entry_error_pos);
  _sock.write_uint16(errcode);
  _sock.write_setpos(currpos);
  //_sock.write_setptr(ptr);
  
  StartWriteMessageElement(STRCONST_errorname,true,STRCONST_errorname_LEN,rr_string_t,NULL,false,0,errname_len,&sock);
  _sock.write((uint8_t*)errname,errname_len,errname_progmem);
  EndWriteMessageElement();
  
  StartWriteMessageElement(STRCONST_errorstring, true, STRCONST_errorstring_LEN,rr_string_t,NULL,false, 0,errmessage_len,&sock);
  _sock.write((uint8_t*)errmessage,errmessage_len,errmessage_progmem);
  EndWriteMessageElement();
  
  Serial.print("error: ");
  Serial.print(errcode);
  Serial.write((const uint8_t*)entry_MemberName,entry_MemberName_len);
  Serial.println();
  flush_message_entry();
}

void RobotRaconteurServerConnection::flush_message()
{
  //Flush the buffer if we haven't consumed all the input
  int32_t diff=message_len-_sock.read_pos();
  for (int32_t i=0; i<diff; i++)
  {
    _sock.read_uint8();

  }

  message_len=0;

}

void RobotRaconteurServerConnection::flush_message_entry()
{
  //Flush the buffer if we haven't consumed all the input
  int32_t diff=(entry_EntrySize + entry_start_pos) - _sock.read_pos();
  for (int32_t i=0; i<diff; i++)
  {
    _sock.read_uint8();

  } 

}

void RobotRaconteurServerConnection::flush_message_element()
{
  //Flush the buffer if we haven't consumed all the input
  int32_t diff=(element_ElementSize + element_start_pos) - _sock.read_pos();
  for (int32_t i=0; i<diff; i++)
  {
    _sock.read_uint8();

  } 

}

/*void RobotRaconteurServerConnection::StartSendEvent(char* MemberName, uint8_t MemberName_len)
{
  _sock.write_reset_length();
  */
  //_sock.write((uint8_t*)/*"RRAC"*/ "",4);
  /*send_message_length_pos=_sock.write_getpos();
  _sock.write_uint32(0);
  _sock.write_uint16(2);
  send_message_header_length_pos=_sock.write_getpos();
  _sock.write_uint16(0);
  _sock.write(RobotRaconteurServer::NodeID,16);
  _sock.write(remote_NodeID,16);
  send_message_sender_endpoint_pos=_sock.write_getpos();
  _sock.write_uint32(send_message_sender_endpoint);
  _sock.write_uint32(remote_Endpoint);
  _sock.write_uint16(0);//SenderNodeName
  _sock.write_uint16(0);//ReceiverNodeName
  _sock.write_uint16(0);//MetaData
  send_message_entry_count_pos=_sock.write_getpos();
  _sock.write_uint16(0);//EntryCount
  _sock.write_uint16(0);//MessageID
  _sock.write_uint16(0);//MessageResID
  
  send_entry_start_pos=_sock.write_getpos();
  send_entry_length_pos=_sock.write_getpos();
  _sock.write_uint32(0);
  _sock.write_uint16(EventReq);
  _sock.write_uint16(0);
  //Serial.print("entry_SPL: ");
  //Serial.println(entry_ServicePath_len);
  _sock.write_uint16(RobotRaconteurServer::ServicePath_len);
  _sock.write((const uint8_t*)RobotRaconteurServer::ServicePath,RobotRaconteurServer::ServicePath_len);
 
  _sock.write_uint16(MemberName_len);
  for (int i=0; i<MemberName_len; i++) {_sock.write_uint8(MemberName[i]);}
  _sock.write_uint32(0);
  
  send_entry_error_pos=_sock.write_getpos();
  
  _sock.write_uint16(0); //error
  _sock.write_uint16(0); //metadata
  
  send_entry_element_count_pos=_sock.write_getpos();
  _sock.write_uint16(0); //elementcount
  
  send_message_entry_count=0;
  send_entry_element_count=0;
   
  
}*/

/*void RobotRaconteurServerConnection::EndSendEvent()
{
   uint16_t entrylen=_sock.write_length()-send_entry_start_pos;
    //ptr=_sock.write_getptr();
    _sock.write_setpos(send_entry_length_pos);
    _sock.write_uint32(entrylen);
    //_sock.write_setpos(_sock.write_length());
    //_sock.write_setptr(ptr);
    //Serial.print("send_elp: ");
    //Serial.println(send_entry_length_pos);
    //Serial.print("send_el: ");
    //Serial.println(entrylen);
    
    _sock.write_setpos(send_entry_element_count_pos);
    _sock.write_uint16(send_entry_element_count);
    _sock.write_setpos(_sock.write_length());
    //_sock.write_setptr(ptr);
    
    
    send_message_entry_count++;
  
    uint16_t meslen=_sock.write_length();
    //ptr=_sock.write_getptr();
    _sock.write_setpos(send_message_length_pos);
    _sock.write_uint32(meslen);
    //_sock.write_setpos(_sock.write_length());
    //_sock.write_setptr(ptr);
    //Serial.print("Sent message len: ");
    //Serial.println(meslen);
    
    //ptr=_sock.write_getptr();
    _sock.write_setpos(send_message_entry_count_pos);
    _sock.write_uint32(send_message_entry_count);
    _sock.write_setpos(_sock.write_length());
    //_sock.write_setptr(ptr);
    _sock.send();
}*/

void RobotRaconteurServerConnection::SetMemberFormatMismatchError()
{
 SetMessageElementError((uint16_t)MemberFormatMismatch,STRCONST_RobotRaconteur_MemberFormatMismatch,true,STRCONST_RobotRaconteur_MemberFormatMismatch_LEN,NULL,false,0);
 
}

void RobotRaconteurServerConnection::SetMemberNotFoundError()
{
  SetMessageElementError((uint16_t)MemberNotFound,STRCONST_RobotRaconteur_MemberNotFound,true,STRCONST_RobotRaconteur_MemberNotFound_LEN,NULL,false,0);
}

uint16_t RobotRaconteurServerConnection::message_len;
uint16_t RobotRaconteurServerConnection::message_EntryCount;

 
//message entry variables
uint16_t RobotRaconteurServerConnection::entry_start_pos;
uint32_t RobotRaconteurServerConnection::entry_EntrySize;
uint16_t RobotRaconteurServerConnection::entry_EntryType;
  
char RobotRaconteurServerConnection::entry_ServicePath[32];
uint8_t RobotRaconteurServerConnection::entry_ServicePath_len;
char RobotRaconteurServerConnection::entry_MemberName[32];
uint8_t RobotRaconteurServerConnection::entry_MemberName_len;
uint32_t RobotRaconteurServerConnection::entry_TransactionID;
uint16_t RobotRaconteurServerConnection::entry_Error;

uint8_t RobotRaconteurServerConnection::entry_ElementCount;
uint8_t RobotRaconteurServerConnection::entry_element_count_enum;

//message element variables
uint16_t RobotRaconteurServerConnection::element_start_pos;
uint32_t RobotRaconteurServerConnection::element_ElementSize;
uint8_t RobotRaconteurServerConnection::element_ElementName_len;
char RobotRaconteurServerConnection::element_ElementName[32];
uint16_t RobotRaconteurServerConnection::element_ElementType;
uint32_t RobotRaconteurServerConnection::element_DataCount;

 

uint16_t RobotRaconteurServerConnection::send_message_length_pos;
uint16_t RobotRaconteurServerConnection::send_message_header_length_pos;
uint16_t RobotRaconteurServerConnection::send_message_sender_endpoint_pos;
//uint32_t RobotRaconteurServerConnection::send_message_sender_endpoint;
uint16_t RobotRaconteurServerConnection::send_message_entry_count_pos;
uint16_t RobotRaconteurServerConnection::send_message_entry_count;
uint16_t RobotRaconteurServerConnection::send_entry_error_pos;
uint16_t RobotRaconteurServerConnection::send_entry_start_pos;
uint16_t RobotRaconteurServerConnection::send_entry_length_pos;
uint16_t RobotRaconteurServerConnection::send_entry_element_count_pos;
uint16_t RobotRaconteurServerConnection::send_entry_element_count;
uint16_t RobotRaconteurServerConnection::send_element_start_pos;
uint16_t RobotRaconteurServerConnection::send_element_length_pos;


//class RobotRaconteurServer

uint8_t RobotRaconteurServer::NodeID[16];
char* RobotRaconteurServer::NodeID_str;
char RobotRaconteurServer::ipstr[24];

RobotRaconteurServer::RobotRaconteurServer(uint16_t port, uint8_t* nodeid, char* nodeid_str,char* service_def, uint32_t service_def_len, char* object_type, uint32_t object_type_len,char* service_path, uint16_t service_path_len)
    : ethernet_server(port)
{
  NodeID_str=nodeid_str;
  memcpy(RobotRaconteurServer::NodeID,nodeid,16);
  
  //Serial.println("huh?");
  for (uint8_t i=0; i<RR_MAX_SERVER_SOCK; i++)
  {
    //Serial.println(i);
    connections[i]=RobotRaconteurServerConnection(i,port); 
  }
  
  ServiceDef=service_def;
  ServiceDef_len=service_def_len;
  ObjectType=object_type;
  ObjectType_len=object_type_len;
  ServicePath=service_path;
  ServicePath_len=service_path_len;
  //

  broadcast_send_time=0;


}

void RobotRaconteurServer::start()
{
	ethernet_server.begin();

}

void RobotRaconteurServer::startudp()
{
  uint8_t broadcastip[]={0xFF,0xFF,0xFF,0xFF};

  Udp.begin(48653);
  //Udp.beginMulticast(broadcastip,48653);

  IPAddress ip= Ethernet.localIP();
 sprintf(ipstr,"%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
}

void RobotRaconteurServer::loop()
{

  ethernet_server.accept();
  for (uint8_t i=0; i<RR_MAX_SERVER_SOCK; i++)
  {
    connections[i].loop();
  }
  return;
  unsigned long time=millis();
  
  if (time < ULONG_MAX/2 && broadcast_send_time > ULONG_MAX/2)
  {
    unsigned long diff=(ULONG_MAX-broadcast_send_time) + time;
    if (diff > 5000)
    {
     SendAnnouncePacket();
     broadcast_send_time=time+5000; 
    }
  }
  else if (time > broadcast_send_time)
  {
    SendAnnouncePacket();
    if ((ULONG_MAX - time) < 5000)
    {
      broadcast_send_time=5000-(ULONG_MAX-time); 
    }
    else
    {
      broadcast_send_time=time+5000;
    }
  }
}

void RobotRaconteurServer::SendAnnouncePacket()
{
  
 Serial.println("Begin send UDP");

 //IPAddress broadcastip(0xFF,0xFF,0xFF,0xFF);
 IPAddress broadcastip(255,255,255,255);

 //Udp.beginMulticast(broadcastip,48653);
 int res;// = Udp.beginPacket(broadcastip, 48653);
 Serial.println(res);
 if (res == 0)
 {
	 Serial.println("No socket available");
	 return;
 }
 uint16_t pos=0;
 Udp.write((const uint8_t*)"Robot Raconteur Node Discovery Packet\n",38);
 /*Udp.write((const uint8_t*)NodeID_str,strlen(NodeID_str));
 Udp.write((const uint8_t*)"\n",1);
 Udp.write((const uint8_t*)"rr+tcp://",10);
 Udp.write((const uint8_t*)ipstr,strlen(ipstr));
 Udp.write((const uint8_t*)":3456/?nodeid=",14);
 Udp.write((const uint8_t*)NodeID_str,strlen(NodeID_str));
 Udp.write((const uint8_t*)"&service=RobotRaconteurServiceIndex\n",29);*/
 //Udp.endPacket();
 Serial.println("Sent UDP packet");
  
}

void RobotRaconteurServer::GetLocalNodeServices(RobotRaconteurServerConnection* con)
{
  //Assemble the url
  char* str1="tcp://";
  char* str2=":3456/[";
  char* str3="]/";
  
  uint16_t strl=6+7+2+strlen(NodeID_str) + strlen(ipstr) + ServicePath_len;
  
  
  rr_socket* _sock;
  
  con->StartWriteMessageElement(STRCONST_return,true,STRCONST_return_LEN,rr_vector_t,NULL,false,0,1,&_sock);
  
  //Write out the Robot Raconteur structure manually because the message element code
  //doesn't support nested message elements
  
  //uint16_t struct_start_pos=_sock->write_length();
  //uint16_t struct_len_pos=_sock->write_getpos();
  
  //Write out the first entry in the vector (the only entry)
  _sock->write_uint32(16+4+ServicePath_len/**/+16+14+25/**/+16+20/**/+16+13+16+1+strl/**/+16+10 );
  _sock->write_uint16(1);
  _sock->write((const uint8_t*)"0",false,1);
  _sock->write_uint16(rr_structure_t);
  _sock->write_uint16(38);
  _sock->write((const uint8_t*)STRCONST_RobotRaconteurServiceIndex_ServiceInfo,38,true);
  _sock->write_uint16(0);
  _sock->write_uint32(5);
  
  //Write out the service name
  _sock->write_uint32(16+4+11);
  _sock->write_uint16(4);
  _sock->write((const uint8_t*)STRCONST_Name,STRCONST_Name_LEN,true);
  _sock->write_uint16(rr_string_t);
  _sock->write_uint16(0);
  _sock->write_uint16(0);
  _sock->write_uint32(ServicePath_len);
  _sock->write((const uint8_t*)ServicePath,ServicePath_len,true);
  
  //Write out the RootObjectType
  _sock->write_uint32(16+14+25);
  _sock->write_uint16(14);
  _sock->write((const uint8_t*)STRCONST_RootObjectType,STRCONST_RootObjectType_LEN,true);
  _sock->write_uint16(rr_string_t);
  _sock->write_uint16(0);
  _sock->write_uint16(0);
  _sock->write_uint32(25);
  _sock->write((const uint8_t*)STRCONST_arduinotest_interface_obj,STRCONST_arduinotest_interface_obj_LEN,true);
    
  //Write out the RootObjectImplements
  _sock->write_uint32(16+20);
  _sock->write_uint16(20);
  _sock->write((const uint8_t*)STRCONST_RootObjectImplements,STRCONST_RootObjectImplements_LEN,true);
  _sock->write_uint16(rr_dictionary_t);
  _sock->write_uint16(0);
  _sock->write_uint16(0);
  _sock->write_uint32(0);
    
  //Write out the ConnectionURL field
  
  
  
  
  //Write out the vector header
  _sock->write_uint32(16+13+16+1+strl);
  _sock->write_uint16(13);
  _sock->write((const uint8_t*)STRCONST_ConnectionURL,STRCONST_ConnectionURL_LEN,true);
  _sock->write_uint16(rr_vector_t);
  _sock->write_uint16(0);
  _sock->write_uint16(0);
  _sock->write_uint32(1);
  
  //Write out the connection url
  _sock->write_uint32(16+1+strl);
  _sock->write_uint16(1);
  _sock->write((const uint8_t*)"0",1,false);
  _sock->write_uint16(rr_string_t);
  _sock->write_uint16(0);
  _sock->write_uint16(0);
  _sock->write_uint32(strl);
  _sock->write((const uint8_t*)str1,6,false);
  _sock->write((const uint8_t*)ipstr,strlen_P(ipstr),true);
  _sock->write((const uint8_t*)str2,7,false);
  _sock->write((const uint8_t*)NodeID_str,strlen_P(NodeID_str),true);
  _sock->write((const uint8_t*)str3,2,false);
  _sock->write((const uint8_t*)ServicePath,ServicePath_len,true);
  
  //Write out the Attributes
  _sock->write_uint32(16+10);
  _sock->write_uint16(10);
  _sock->write((const uint8_t*)STRCONST_Attributes,STRCONST_Attributes_LEN,true);
  _sock->write_uint16(rr_dictionary_t);
  _sock->write_uint16(0);
  _sock->write_uint16(0);
  _sock->write_uint32(0);
  
  
  con->EndWriteMessageElement();
}

char* RobotRaconteurServer::ServiceDef;
uint32_t RobotRaconteurServer::ServiceDef_len;
char* RobotRaconteurServer::ObjectType;
uint32_t RobotRaconteurServer::ObjectType_len;
char* RobotRaconteurServer::ServicePath;
uint16_t RobotRaconteurServer::ServicePath_len;
