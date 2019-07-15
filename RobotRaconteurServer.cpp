#include <Ethernet.h>
#include "RobotRaconteurServer.h"
#include <string.h>
#include <avr/pgmspace.h>
#include <limits.h>

//class rr_socket


PROGMEM const char INDEXDEF[] ={"service RobotRaconteurServiceIndex\nstruct NodeInfo\nfield string NodeName\nfield uint8[16] NodeID\nfield string{int32} ServiceIndexConnectionURL\nend struct\nstruct ServiceInfo\nfield string Name\nfield string RootObjectType\nfield string{int32} RootObjectImplements\nfield string{int32} ConnectionURL\nfield varvalue{string} Attributes\nend struct\nobject ServiceIndex\nfunction ServiceInfo{int32} GetLocalNodeServices()\nfunction NodeInfo{int32} GetRoutedNodes()\nfunction NodeInfo{int32} GetDetectedNodes()\nevent LocalNodeServicesChanged()\nend object"};
#define INDEXDEF_LEN 538
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
#define STRCONST_RobotRaconteurServiceIndex_ServiceInfo_LEN 38
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
PROGMEM const char STRCONST_CreateConnection[] = {"CreateConnection"};
#define STRCONST_CreateConnection_LEN 16
PROGMEM const char STRCONST_RobotRaconteurServiceIndex[] = {"RobotRaconteurServiceIndex"};
#define STRCONST_RobotRaconteurServiceIndex_LEN 26
PROGMEM const char STRCONST_GetRoutedNodes[] = {"GetRoutedNodes"};
#define STRCONST_GetRoutedNodes_LEN 14
PROGMEM const char STRCONST_GetDetectedNodes[] = {"GetDetectedNodes"};
#define STRCONST_GetDetectedNodes_LEN 16
PROGMEM const char STRCONST_GetLocalNodeServices[] = {"GetLocalNodeServices"};
#define STRCONST_GetLocalNodeServices_LEN 20
PROGMEM const char STRCONST_GET1[] = {"GET "};
#define STRCONST_GET1_LEN  4
PROGMEM const char STRCONST_GET2[] = {"GET\t"};
#define STRCONST_GET2_LEN  4
PROGMEM const char STRCONST_HTTP_RESPONSE_1[] = {"HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Protocol: robotraconteur.robotraconteur.com\r\nSec-WebSocket-Version: 13\r\nSec-WebSocket-Accept: "};
#define STRCONST_HTTP_RESPONSE_1_LEN 183
PROGMEM const char STRCONST_HTTP_RESPONSE_2[] =  {"\r\n\r\n"};
#define STRCONST_HTTP_RESPONSE_2_LEN 4
PROGMEM const char STRCONST_HTTP_KEY_UUID[] = {"258EAFA5-E914-47DA-95CA-C5AB0DC85B11"};
#define STRCONST_HTTP_KEY_UUID_LEN  36
PROGMEM const char STRCONST_HTTP_SEC_WEBSOCKET_KEY[] = {"Sec-WebSocket-Key:"};
#define STRCONST_HTTP_SEC_WEBSOCKET_KEY_LEN 18
PROGMEM const char STRCONST_Robot_Raconteur_Node_Discovery_Packet[] = {"Robot Raconteur Node Discovery Packet\n"};
#define STRCONST_Robot_Raconteur_Node_Discovery_Packet_LEN 38
PROGMEM const char STRCONST_URL1[] = {"rr+tcp://"};
#define STRCONST_URL1_LEN 9
PROGMEM const char STRCONST_URL2[]={":3456/?nodeid="};
#define STRCONST_URL2_LEN 14
PROGMEM const char STRCONST_URL3[]={"&service=RobotRaconteurServiceIndex\n"};
#define STRCONST_URL3_LEN 36
PROGMEM const char STRCONST_URL4[]={"&service="};
#define STRCONST_URL4_LEN 9


uint8_t rr_socket::_shared_write_buf[300];

void rr_socket::reset()
{
	_read_pos=0;
	_write_length=0;
	_write_pos=0;
	_write_stream_pos=0;
	_is_websocket=false;
	_is_websocket = false;
    _recv_websocket_in_frame = false;
	_recv_websocket_frame_pos = 0;
	_recv_websocket_enable_mask = false;
	_recv_websocket_header1_recv = false;
	_recv_websocket_frame_len= 0 ;
}

rr_socket::rr_socket(EthernetClient client) : _client(client)
{
	reset();
}

rr_socket::rr_socket() : _client()
{
	reset();
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
  size_t read_len=0;
  int rv;
  do
  {

	  rv = _client.read(buf+read_len,size-read_len);
	  if (rv < 0)
	  {
		  Serial.println("Read error");
		  delay(1000);
		abort();
	  }
	  read_len += rv;
  }
  while (read_len < size);

  if (_is_websocket && _recv_websocket_enable_mask)
  {
	  for (int i = 0; i < size; i++)
	  {
		  buf[i] ^= _recv_websocket_mask[(_recv_websocket_frame_pos + i) % 4];
	  }
	  _recv_websocket_frame_pos += size;
  }

  _read_pos += size;
}

int16_t rr_socket::read_available()
{
	int a=_client.available();
	if (!_is_websocket)
	{
		return a;
	}

	if (a <= 0 )
	{
		return a;
	}

	 if (_recv_websocket_frame_pos == _recv_websocket_frame_len && _recv_websocket_in_frame)
	{
	  //reset for next websocket frame
	  _recv_websocket_frame_pos = 0;
	  _recv_websocket_frame_len = 0;
	  _recv_websocket_in_frame = false;
	  _recv_websocket_header1_recv = false;
	}

	if (!_recv_websocket_in_frame)
	{
	  //receive websocket frame header
	  if (!_recv_websocket_header1_recv)
	  {
		  if (a < 2) return 0;
		  _client.read(_recv_websocket_header1, 2);
		  a -= 2;

		  //TODO: handle pings
		  uint8_t opcode_recv1 = _recv_websocket_header1[0] & 0x0F;
		  if (opcode_recv1 != WebSocketOpcode_binary)
		  {
			  close();
			  return 0;
		  }
		  _recv_websocket_header1_recv = true;
	  }

	  if (_recv_websocket_header1_recv)
	  {
		  uint8_t l=0;
		  uint8_t count1 = _recv_websocket_header1[1] & 0x7F;
		  if (count1 <= 125)
		  {
			  l = 0;
		  }
		  else if (count1 == 126)
		  {
			  l = 2;
		  }
		  else
		  {
			  close();
			  return 0;
		  }

		  _recv_websocket_enable_mask = (0x80 & _recv_websocket_header1[1]) != 0;
		  if (_recv_websocket_enable_mask)
		  {
			  l += 4;
		  }

		  uint8_t header2_recv[6];
		  if (l > 0)
		  {
			  if (a < l) return 0;
			  _client.read(header2_recv, l);
			  a -= l;
		  }

		  if (count1 <= 125)
		  {
			  _recv_websocket_frame_len = count1;
			  if (_recv_websocket_enable_mask)
			  {
				  memcpy(_recv_websocket_mask, header2_recv, 4);
			  }
		  }
		  else
		  {
			  uint8_t* len1 = (uint8_t*)&_recv_websocket_frame_len;
			  len1[0] = header2_recv[1];
			  len1[1] = header2_recv[0];

			  if (_recv_websocket_enable_mask)
			  {
				  memcpy(_recv_websocket_mask, header2_recv + 2, 4);
			  }
		  }


	  }
	  _recv_websocket_in_frame = true;
	  if (a <= 0) return a;
	}
	else
	{
	  //Truncate available if bigger than frame
	  if (a > _recv_websocket_frame_len - _recv_websocket_frame_pos)
	  {
		  a = _recv_websocket_frame_len - _recv_websocket_frame_pos;
	  }
	}

	return a;
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
		Serial.println("Message too large! " );
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


static uint16_t getSnTX_FSR(uint8_t s)
{
        uint16_t val, prev;

        prev = W5100.readSnTX_FSR(s);
        while (1) {
                val = W5100.readSnTX_FSR(s);
                if (val == prev) {
			return val;
		}
                prev = val;
        }
}


static void write_data(uint8_t s, uint16_t data_offset, const uint8_t *data, uint16_t len)
{
	uint16_t ptr = W5100.readSnTX_WR(s);
	ptr += data_offset;
	uint16_t offset = ptr & W5100.SMASK;
	uint16_t dstAddr = offset + W5100.SBASE(s);

	if (W5100.hasOffsetAddressMapping() || offset + len <= W5100.SSIZE) {
		W5100.write(dstAddr, data, len);
	} else {
		// Wrap around circular buffer
		uint16_t size = W5100.SSIZE - offset;
		W5100.write(dstAddr, data, size);
		W5100.write(W5100.SBASE(s), data + size, len - size);
	}
	ptr += len;
	W5100.writeSnTX_WR(s, ptr);
}

void rr_socket::begin_queue_direct()
{
	_write_stream_pos=0;
}

void rr_socket::queue_direct(const uint8_t* buf, size_t size, bool progmem)
{
	uint8_t status=0;
	uint16_t ret=0;
	uint16_t freesize=0;
	uint8_t s = _client.getSocketNumber();
	ret = size;
	do {
			SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
			freesize = getSnTX_FSR(s);
			status = W5100.readSnSR(s);
			SPI.endTransaction();
			if ((status != SnSR::ESTABLISHED) && (status != SnSR::CLOSE_WAIT)) {
				ret = 0;
				break;
			}
			yield();
		} while (freesize < ret);

	SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
	if (!progmem)
	{
		write_data(s, _write_stream_pos, (uint8_t *)buf, ret);
	}
	else
	{
		for (uint16_t i=0; i<size; i++)
		{
			uint8_t c = pgm_read_byte(buf + i);
			write_data(s, _write_stream_pos + i, &c, 1);
		}
	}
	SPI.endTransaction();
	_write_stream_pos += size;
}

void rr_socket::send_direct()
{
	uint8_t s = _client.getSocketNumber();
	SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
	W5100.execCmdSn(s, Sock_SEND);
	while ( (W5100.readSnIR(s) & SnIR::SEND_OK) != SnIR::SEND_OK ) {

			if ( W5100.readSnSR(s) == SnSR::CLOSED ) {
				SPI.endTransaction();
				return;
			}
			SPI.endTransaction();
			yield();
			SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
		}

		W5100.writeSnIR(s, SnIR::SEND_OK);
		SPI.endTransaction();
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
	if (_is_websocket)
	{
		//Write websocket header
		if (_write_length <= 125)
		{
			uint8_t ws_header[2];
			ws_header[0] = 0x80 | (WebSocketOpcode_binary & 0xF);
			ws_header[1] = (uint8_t)_write_length;
			_client.write(ws_header, 2);
		}
		else
		{
			uint8_t ws_header[4];
			ws_header[0] = 0x80 | (WebSocketOpcode_binary & 0xF);
			ws_header[1] = (uint8_t)126;
			uint8_t* write_length_8 = (uint8_t*)&_write_length;
			ws_header[2] = write_length_8[1];
			ws_header[3] = write_length_8[0];
			_client.write(ws_header, 4);
		}
	}

  _client.write(_shared_write_buf, _write_length);
  _client.flush();

  write_reset_length();
  return 1;
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

void rr_socket::enable_websocket_protocol()
{
	_is_websocket = true;
}


//class RobotRaconteurServerConnection

RobotRaconteurServerConnection::RobotRaconteurServerConnection() : 
_sock(0)
{

  _port=0;
  message_len=0;
  started=false;
  connected=false;
  send_message_sender_endpoint=0;
  remote_Endpoint=0;
  in_http_header = false;
  http_line_empty = true;
  http_line_pos = 0;
  http_is_sec_websocket_key_line = true;


}

RobotRaconteurServerConnection::RobotRaconteurServerConnection(uint16_t port) :
_sock()
{

  connected=false;
  _port=port;
  message_len=0;
  started=false;
  connected=false;
  send_message_sender_endpoint=0;
  remote_Endpoint=0;
  in_http_header = false;
  http_line_empty = true;
  http_line_pos = 0;
  http_is_sec_websocket_key_line = true;
}

void RobotRaconteurServerConnection::loop()
{

  //if(_sock._client.status() == 0)
  /*{
  Serial.print("Socket status: ");
  Serial.print(_sock._client.status());
  Serial.print(" socket: ");
  Serial.println(_sock._client.getSocketNumber());
  }*/
  //Serial.print("Data available: ");
  //Serial.println(_sock._client.available());

  uint8_t status = _sock._client.status();


  if (status != SnSR::ESTABLISHED)
  {
	connected=false;
	started=false;
	_sock._client = EthernetClient();
	_sock.reset();
    return;
  }

  int16_t avail=_sock.read_available();
  
  if (!started)
    {
  	  if (_sock.read_available() < 8)
  	  {
  		  return;
  	  }

  	  char seed[4];
  	  _sock.read((uint8_t*)seed, 4);
  	  started = true;
  	  if (memcmp_P(seed, STRCONST_RRAC, 4) != 0)
  	  {
  		  if (memcmp_P(seed, STRCONST_GET1, 4) == 0 || memcmp_P(seed, STRCONST_GET2, 4) == 0)
  		  {
  			  in_http_header = true;
  			  http_key_sha1.clear();
  		  }
  		  else
  		  {
  			  Serial.println("Get a corrupted message");
  			  _sock.close();
  			  return;
  		  }
  	  }
  	  else
  	  {
  		message_len=_sock.read_uint32();
  	  }

   }

  while (in_http_header)
    {
  	  //printf("Got http header\n");

  	  if (_sock.read_available() < 1) continue;

  		char a1;
  		_sock.read((uint8_t*)&a1, 1);
  		if (a1 == '\n')
  		{
  			http_line_pos = 0;
  			http_is_sec_websocket_key_line = true;
  			if (http_line_empty)
  			{
  				in_http_header = false;

  				for (uint8_t i=0; i<STRCONST_HTTP_KEY_UUID_LEN; i++)
  				{
  					uint8_t c = pgm_read_byte(STRCONST_HTTP_KEY_UUID + i);
  					http_key_sha1.update(&c,1);
  				}

  				//http_key_sha1.update((const uint8_t*)http_key_uuid, strlen(http_key_uuid));
  				SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
  				_sock.queue_direct((const uint8_t*)STRCONST_HTTP_RESPONSE_1, STRCONST_HTTP_RESPONSE_1_LEN, true);
  				uint8_t accept_key_buf[20];
  				char accept_key_buf_b64[29];
  				http_key_sha1.finalize(accept_key_buf,sizeof(accept_key_buf));
  				Base64.encode(accept_key_buf_b64, (char*)accept_key_buf, sizeof(accept_key_buf));
  				_sock.queue_direct((const uint8_t*)accept_key_buf_b64, 28,false);
  				_sock.queue_direct((const uint8_t*)STRCONST_HTTP_RESPONSE_2, STRCONST_HTTP_RESPONSE_2_LEN,true);
  				_sock.send_direct();
  				_sock.enable_websocket_protocol();
  				_sock.read_resetpos();

  				avail = _sock.read_available();
  			}
  			else
  			{
  				http_line_empty = true;
  				_sock.read_resetpos();
  			}
  		}
  		else
  		{

  			if (a1 != '\r')
  			{
  				if (http_line_pos < STRCONST_HTTP_SEC_WEBSOCKET_KEY_LEN)
  				{
  					if (memcmp_P(&a1,STRCONST_HTTP_SEC_WEBSOCKET_KEY + http_line_pos,1) != 0)
  					{
  						http_is_sec_websocket_key_line=false;
  					}
  				}
  				else
  				{
  					if (http_is_sec_websocket_key_line)
  					{
  						if (a1 != '\r' && a1 != ' ' && a1 != '\t')
  						{
  							http_key_sha1.update(&a1,1);
  						}

  					}

  				}
  				http_line_empty = false;
  			}
  			http_line_pos++;
  			_sock.read_resetpos();
  		}
    }

  
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
    for (int j=0; j<16; j++)
    {
    	if (ReceiverNodeID[j]!=pgm_read_byte(RobotRaconteurServer::NodeID+j))
    	{
    		is_my_nodeid=false;
    	}
    }

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
       if (strncmp_P(entry_MemberName,STRCONST_CreateConnection,STRCONST_CreateConnection_LEN)==0)
       {

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
        
    	//INDEXDEF won't fit in send buffer, do some workarounds...
    	  uint16_t messagelen = _sock.write_length() + 16 + STRCONST_servicedef_LEN+INDEXDEF_LEN + 16 + STRCONST_attributes_LEN;
    	  uint16_t entrylen=messagelen-send_entry_start_pos;
    	  _sock.write_setpos(send_message_length_pos);
    	  _sock.write_uint32(messagelen);
    	  _sock.write_setpos(send_message_entry_count_pos);
    	  _sock.write_uint32(1);
    	  _sock.write_setpos(send_entry_length_pos);
    	  _sock.write_uint32(entrylen);
    	  _sock.write_setpos(send_entry_element_count_pos);
    	  _sock.write_uint16(2);
    	  _sock.write_setpos(_sock.write_length());
    	  _sock.send();

        //StartWriteMessageElement(STRCONST_servicedef,true, STRCONST_servicedef_LEN,rr_string_t,NULL,false,0,INDEXDEF_LEN,&sock);
        //_sock.write_progmem(INDEXDEF,INDEXDEF_LEN);
        //EndWriteMessageElement();
    	_sock.write_reset_length();
    	_sock.write_uint32(16 + STRCONST_servicedef_LEN+INDEXDEF_LEN);
		_sock.write_uint16(STRCONST_servicedef_LEN);
		_sock.write((const uint8_t*)STRCONST_servicedef,STRCONST_servicedef_LEN,true);
		_sock.write_uint16(rr_string_t);
		_sock.write_uint16(0);
		_sock.write_uint16(0);
		_sock.write_uint32(INDEXDEF_LEN);
    	_sock.send();
    	_sock.begin_queue_direct();
    	_sock.queue_direct((const uint8_t*)INDEXDEF,INDEXDEF_LEN,true);
    	_sock.send_direct();
        //StartWriteMessageElement(STRCONST_attributes,true,STRCONST_attributes_LEN,rr_dictionary_t,NULL,false,0,0,&sock);
        //EndWriteMessageElement();
    	_sock.write_reset_length();
        _sock.write_uint32(16 + STRCONST_attributes_LEN);
        _sock.write_uint16(STRCONST_attributes_LEN);
        _sock.write((const uint8_t*)STRCONST_attributes,STRCONST_attributes_LEN,true);
        _sock.write_uint16(rr_dictionary_t);
        _sock.write_uint16(0);
        _sock.write_uint16(0);
        _sock.write_uint32(0);
        _sock.send();
        
        flush_message();
        message_len=0;
        return;

      }
      else if (strncmp_P(entry_ServicePath,RobotRaconteurServer::ServicePath,RobotRaconteurServer::ServicePath_len)!=0)
      {
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
            GetLocalNodeServices();
            flush_message();
            message_len=0;
            return;
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
          Serial.println("Client connected");
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
          rr_function_call(this,entry_MemberName,entry_ElementCount);
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

SHA1 RobotRaconteurServerConnection::http_key_sha1;

//class RobotRaconteurServer

uint8_t* RobotRaconteurServer::NodeID;
char* RobotRaconteurServer::NodeID_str;
char RobotRaconteurServer::ipstr[24];

RobotRaconteurServer::RobotRaconteurServer(uint16_t port_, uint8_t* nodeid, char* nodeid_str,char* service_def, uint32_t service_def_len, char* object_type, uint32_t object_type_len,char* service_path, uint16_t service_path_len)
	: ethernet_server(port_)
{
  NodeID_str=nodeid_str;
  NodeID=nodeid;
  
  //Serial.println("huh?");
  for (uint8_t i=0; i<RR_MAX_SERVER_SOCK; i++)
  {
    //Serial.println(i);
    connections[i]=RobotRaconteurServerConnection(port_);
  }
  
  ServiceDef=service_def;
  ServiceDef_len=service_def_len;
  ObjectType=object_type;
  ObjectType_len=object_type_len;
  ServicePath=service_path;
  ServicePath_len=service_path_len;
  //

  broadcast_send_time=0;
  port=port_;


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

  for (uint8_t i=0; i<RR_MAX_SERVER_SOCK; i++)
  {
    connections[i].loop();
  }

  for (uint8_t i=0; i<RR_MAX_SERVER_SOCK; i++)
  {
	  if (connections[i]._sock._client.getSocketNumber() >= 4)
	  {
		  connections[i]._sock._client = ethernet_server.accept();
		  connections[i]._sock.reset();
		  break;
	  }
  }


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

static void udp_write_progmem(EthernetUDP& Udp, const void* ptr, size_t len)
{
	const uint8_t* ptr2 = (uint8_t*)ptr;
	for(size_t i = 0; i<len; i++)
	{
		uint8_t c = pgm_read_byte(ptr+i);
		Udp.write(c);
	}
}

void RobotRaconteurServer::SendAnnouncePacket()
{
  
 Serial.println("Begin send UDP");

 //IPAddress broadcastip(0xFF,0xFF,0xFF,0xFF);
 IPAddress broadcastip(255,255,255,255);

 //Udp.beginMulticast(broadcastip,48653);
 int res = Udp.beginPacket(broadcastip, 48653);
 if (res == 0)
 {
	 return;
 }
 uint16_t pos=0;
 udp_write_progmem(Udp,STRCONST_Robot_Raconteur_Node_Discovery_Packet,STRCONST_Robot_Raconteur_Node_Discovery_Packet_LEN);
 udp_write_progmem(Udp,NodeID_str,strlen_P(NodeID_str));
 Udp.write((const uint8_t*)"\n",1);
 udp_write_progmem(Udp,STRCONST_URL1,STRCONST_URL1_LEN);
 Udp.write((const uint8_t*)ipstr,strlen(ipstr));
 udp_write_progmem(Udp,STRCONST_URL2,STRCONST_URL2_LEN);
 udp_write_progmem(Udp,NodeID_str,strlen_P(NodeID_str));
 udp_write_progmem(Udp,STRCONST_URL3,STRCONST_URL3_LEN);
 Udp.endPacket();
}

void RobotRaconteurServerConnection::GetLocalNodeServices()
{
  //Assemble the url

  uint16_t strl=STRCONST_URL1_LEN+STRCONST_URL2_LEN+STRCONST_URL4_LEN+strlen_P(RobotRaconteurServer::NodeID_str) + strlen(RobotRaconteurServer::ipstr) + RobotRaconteurServer::ServicePath_len;

  uint16_t element_data_len =16+1+STRCONST_RobotRaconteurServiceIndex_ServiceInfo_LEN
		  /**/+16+STRCONST_Name_LEN+RobotRaconteurServer::ServicePath_len/**/+16+STRCONST_RootObjectType_LEN+STRCONST_arduinotest_interface_obj_LEN
		  /**/+16+STRCONST_RootObjectImplements_LEN/**/+16+STRCONST_ConnectionURL_LEN+16+1+strl/**/+16+STRCONST_Attributes_LEN;

  uint16_t messagelen = _sock.write_length() + 16 + STRCONST_return_LEN + element_data_len;
  uint16_t entrylen=messagelen-send_entry_start_pos;
  _sock.write_setpos(send_message_length_pos);
  _sock.write_uint32(messagelen);
  _sock.write_setpos(send_message_entry_count_pos);
  _sock.write_uint32(1);
  _sock.write_setpos(send_entry_length_pos);
  _sock.write_uint32(entrylen);
  _sock.write_setpos(send_entry_element_count_pos);
  _sock.write_uint16(1);
  _sock.write_setpos(_sock.write_length());
  _sock.send();

  //StartWriteMessageElement(STRCONST_return,true,STRCONST_return_LEN,rr_vector_t,NULL,false,0,1,&_sock);

  //Write out the Robot Raconteur structure manually because the message element code
  //doesn't support nested message elements
  
  //uint16_t struct_start_pos=_sock->write_length();
  //uint16_t struct_len_pos=_sock->write_getpos();
  
  _sock.write_reset_length();
  _sock.write_uint32(16 + STRCONST_return_LEN + element_data_len);
  _sock.write_uint16(STRCONST_return_LEN);
  _sock.write((const uint8_t*)STRCONST_return,STRCONST_return_LEN,true);
  _sock.write_uint16(rr_vector_t);
  _sock.write_uint16(0);
  _sock.write_uint16(0);
  _sock.write_uint32(1);
  _sock.send();

  //Write out the first entry in the vector (the only entry)

  _sock.write_reset_length();
  _sock.write_uint32(element_data_len);
  _sock.write_uint16(1);
  _sock.write((const uint8_t*)"0",1,false);
  _sock.write_uint16(rr_structure_t);
  _sock.write_uint16(38);
  _sock.write((const uint8_t*)STRCONST_RobotRaconteurServiceIndex_ServiceInfo,STRCONST_RobotRaconteurServiceIndex_ServiceInfo_LEN,true);
  _sock.write_uint16(0);
  _sock.write_uint32(5);
  _sock.send();
  
  //Write out the service name
  _sock.write_reset_length();
  _sock.write_uint32(16+STRCONST_Name_LEN+RobotRaconteurServer::ServicePath_len);
  _sock.write_uint16(STRCONST_Name_LEN);
  _sock.write((const uint8_t*)STRCONST_Name,STRCONST_Name_LEN,true);
  _sock.write_uint16(rr_string_t);
  _sock.write_uint16(0);
  _sock.write_uint16(0);
  _sock.write_uint32(RobotRaconteurServer::ServicePath_len);
  _sock.write((const uint8_t*)RobotRaconteurServer::ServicePath,RobotRaconteurServer::ServicePath_len,true);
  _sock.send();
  
  //Write out the RootObjectType
  _sock.write_reset_length();
  _sock.write_uint32(16+STRCONST_RootObjectType_LEN+STRCONST_arduinotest_interface_obj_LEN);
  _sock.write_uint16(STRCONST_RootObjectType_LEN);
  _sock.write((const uint8_t*)STRCONST_RootObjectType,STRCONST_RootObjectType_LEN,true);
  _sock.write_uint16(rr_string_t);
  _sock.write_uint16(0);
  _sock.write_uint16(0);
  _sock.write_uint32(STRCONST_arduinotest_interface_obj_LEN);
  _sock.write((const uint8_t*)STRCONST_arduinotest_interface_obj,STRCONST_arduinotest_interface_obj_LEN,true);
  _sock.send();

  //Write out the RootObjectImplements
  _sock.write_reset_length();
  _sock.write_uint32(16+STRCONST_RootObjectImplements_LEN);
  _sock.write_uint16(STRCONST_RootObjectImplements_LEN);
  _sock.write((const uint8_t*)STRCONST_RootObjectImplements,STRCONST_RootObjectImplements_LEN,true);
  _sock.write_uint16(rr_vector_t);
  _sock.write_uint16(0);
  _sock.write_uint16(0);
  _sock.write_uint32(0);
  _sock.send();
    
  //Write out the ConnectionURL field
  
  
  
  
  //Write out the vector header
  _sock.write_reset_length();
  _sock.write_uint32(16+STRCONST_ConnectionURL_LEN+16+1+strl);
  _sock.write_uint16(STRCONST_ConnectionURL_LEN);
  _sock.write((const uint8_t*)STRCONST_ConnectionURL,STRCONST_ConnectionURL_LEN,true);
  _sock.write_uint16(rr_vector_t);
  _sock.write_uint16(0);
  _sock.write_uint16(0);
  _sock.write_uint32(1);
  _sock.send();
  
  //Write out the connection url
  _sock.write_reset_length();
  _sock.write_uint32(16+1+strl);
  _sock.write_uint16(1);
  _sock.write((const uint8_t*)"0",1,false);
  _sock.write_uint16(rr_string_t);
  _sock.write_uint16(0);
  _sock.write_uint16(0);
  _sock.write_uint32(strl);
  _sock.write((const uint8_t*)STRCONST_URL1,STRCONST_URL1_LEN,true);
  _sock.write((const uint8_t*)RobotRaconteurServer::ipstr,strlen(RobotRaconteurServer::ipstr),false);
  _sock.write((const uint8_t*)STRCONST_URL2,STRCONST_URL2_LEN,true);
  _sock.write((const uint8_t*)RobotRaconteurServer::NodeID_str,strlen_P(RobotRaconteurServer::NodeID_str),true);
  _sock.write((const uint8_t*)STRCONST_URL4,STRCONST_URL4_LEN,true);
  _sock.write((const uint8_t*)RobotRaconteurServer::ServicePath,RobotRaconteurServer::ServicePath_len,true);
  _sock.send();
  
  //Write out the Attributes
  _sock.write_reset_length();
  _sock.write_uint32(16+STRCONST_Attributes_LEN);
  _sock.write_uint16(10);
  _sock.write((const uint8_t*)STRCONST_Attributes,STRCONST_Attributes_LEN,true);
  _sock.write_uint16(rr_dictionary_t);
  _sock.write_uint16(0);
  _sock.write_uint16(0);
  _sock.write_uint32(0);
  _sock.send();
  
  //EndWriteMessageElement();
}

char* RobotRaconteurServer::ServiceDef;
uint32_t RobotRaconteurServer::ServiceDef_len;
char* RobotRaconteurServer::ObjectType;
uint32_t RobotRaconteurServer::ObjectType_len;
char* RobotRaconteurServer::ServicePath;
uint16_t RobotRaconteurServer::ServicePath_len;
