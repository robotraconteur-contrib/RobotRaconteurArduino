#include <SHA1.h>
#include <Base64.h>
#include "utility/w5100.h"

#ifndef RobotRaconteurServer_h
#define RobotRaconteurServer_h

#define SOCK_CLOSED 255

enum rr_DataTypes
{
  rr_void_t=0,
  rr_double_t,
  rr_single_t,
  rr_int8_t,
  rr_uint8_t,
  rr_int16_t,
  rr_uint16_t,
  rr_int32_t,
  rr_uint32_t,
  rr_int64_t,
  rr_uint64_t,
  rr_string_t,
  rr_structure_t=101,
  rr_vector_t,
  rr_dictionary_t,
  rr_object_t,
  rr_varvalue_t,
  rr_varobject_t,
  rr_multidimarray_t

};

enum rr_MessageEntryTypes
{
  Null=0,
  StreamOp=1,
  StreamOpRet,
  StreamCheckCapability,
  StreamCheckCapabilityRet,
  GetServiceDesc=101,
  GetServiceDescRet,
  ObjectTypeName,
  ObjectTypeNameRet,
  ServiceClosed,
  ServiceClosedRet,
  ConnectClient,
  ConnectClientRet,
  DisconnectClient,
  DisconnectClientRet,
  ConnectionTest,
  ConnectionTestRet,
  GetNodeInfo,
  GetNodeInfoRet,
  ReconnectClient,
  ReconnectClientRet,
  NodeCheckCapability,
  NodeCheckCapabilityRet,
  GetServiceAttributes,
  GetServiceAttributesRet,
  EndpointCheckCapability=501,
  EndpointCheckCapabilityRet,
  ServiceCheckCapabilityReq=1101,
  ServiceCheckCapabilityRet,
  ClientKeepAliveReq=1105,
  ClientKeepAliveRet,
  ClientSessionOpReq=1107,
  ClientSessionOpRet,
  ServicePathReleasedReq,
  ServicePathReleasedRet,
  PropertyGetReq=1111,
  PropertyGetRes,
  PropertySetReq,
  PropertySetRes,
  FunctionCallReq=1121,
  FunctionCallRes,
  EventReq=1131,
  EventRes,
  PipePacket=1141,
  PipePacketRet,
  PipeConnectReq,
  PipeConnectRet,
  PipeDisconnectReq,
  PipeDisconnectRet,
  PipeClosed,
  PipeClosedRet

};

enum rr_MessageErrorTypes 
{

  None=0,
  ConnectionError=1,
  ProtocolError,
  ServiceNotFound,
  ObjectNotFound,
  InvalidEndpoint,
  EndpointCommunicationFatalError,
  NodeNotFound,
  ServiceError,
  MemberNotFound,
  MemberFormatMismatch,
  DataTypeMismatch,
  DataTypeError,
  DataSerializationError,
  MessageEntryNotFound,
  MessageElementNotFound,
  UnknownError,
  RemoteError=100,
  TransactionTimeout,
  AuthenticationError=150,
  ObjectLockedError

};

typedef uint16_t rr_DataType;
typedef uint16_t rr_MessageEntryType;
typedef uint16_t rr_MessageErrorType;





class rr_socket 
{
public:
	enum WebSocketOpcode
	{
		WebSocketOpcode_continuation = 0x0,
		WebSocketOpcode_text = 0x1,
		WebSocketOpcode_binary = 0x2,
		WebSocketOpcode_close = 0x8,
		WebSocketOpcode_ping = 0x9,
		WebSocketOpcode_pong = 0xA
	};

public:
  EthernetClient _client;
  uint16_t _write_length;
  uint16_t _write_pos;
  uint16_t _read_pos;
  static uint8_t _shared_write_buf[300];
  uint16_t _write_stream_pos;
  
  bool _is_websocket;
  bool _recv_websocket_in_frame;
  uint16_t _recv_websocket_frame_pos;
  uint16_t _recv_websocket_frame_len;
  uint8_t _recv_websocket_mask[4];
  bool _recv_websocket_enable_mask;
  uint8_t _recv_websocket_header1[2];
  bool _recv_websocket_header1_recv;


public:
  rr_socket();
  rr_socket(EthernetClient client);
  
  //Functions to read stream
  uint8_t read_uint8();
  uint16_t read_uint16();
  uint32_t read_uint32();
  void read(uint8_t *buf, size_t size);
  int16_t read_available();
  uint16_t read_pos();
  void read_resetpos();
  
  //Functions to write to stream
  void write_uint8(uint8_t val);
  void write_uint16(uint16_t val);
  void write_uint32(uint32_t val);
  void write(const uint8_t* buf, size_t size, bool progmem);
  void write_progmem(const void* progmem, size_t len);
  void write_reset_length();
  size_t write_length();
  uint16_t write_getpos();
  void write_setpos(uint16_t pos);
  
  int16_t send_freesize();
  
  uint8_t send();
  void send_flush();
  
  void close();

  void begin_queue_direct();
  void queue_direct(const uint8_t* buf, size_t size, bool progmem);
  void send_direct();

  void enable_websocket_protocol();

  void reset();
};



class RobotRaconteurServerConnection
{
public:
  rr_socket _sock;
  uint16_t _port;
  
  uint32_t remote_Endpoint;
  uint8_t remote_NodeID[16];
  bool connected;
  bool started;
  bool in_http_header;
  bool http_line_empty;
  uint16_t http_line_pos;
  bool http_is_sec_websocket_key_line;
  static SHA1 http_key_sha1;
  
public:
  //message variables
  static uint16_t message_len;
  static uint16_t message_EntryCount;
  
   
  //message entry variables
  static uint16_t entry_start_pos;
  static uint32_t entry_EntrySize;
  static uint16_t entry_EntryType;
    
  static char entry_ServicePath[32];
  static uint8_t entry_ServicePath_len;
  static char entry_MemberName[32];
  static   uint8_t entry_MemberName_len;
  static uint32_t entry_TransactionID;
  static uint16_t entry_Error;
  
  static uint8_t entry_ElementCount;
  static uint8_t entry_element_count_enum;
  
  //message element variables
  static uint16_t element_start_pos;
  static uint32_t element_ElementSize;
  static uint8_t element_ElementName_len;
  static char element_ElementName[32];
  static uint16_t element_ElementType;
  static uint32_t element_DataCount;
  
 
  
  static uint16_t send_message_length_pos;
  static uint16_t send_message_header_length_pos;
  static uint16_t send_message_sender_endpoint_pos;
  uint32_t send_message_sender_endpoint;
  static uint16_t send_message_entry_count_pos;
  static uint16_t send_message_entry_count;
  static uint16_t send_entry_error_pos;
  static uint16_t send_entry_start_pos;
  static uint16_t send_entry_length_pos;
  static uint16_t send_entry_element_count_pos;
  static uint16_t send_entry_element_count;
  static uint16_t send_element_start_pos;
  static uint16_t send_element_length_pos;
  
public:
  
  RobotRaconteurServerConnection();
  RobotRaconteurServerConnection(uint16_t port);
  
  int8_t ReadNextMessageElement(uint16_t* ElementSize, char** ElementName, uint8_t* ElementName_len,
    uint16_t* ElementType, uint16_t* DataCount, rr_socket** sock);
  
  void StartWriteMessageElement(const char* ElementName, bool ElementName_progmem, uint8_t ElementName_len,
    uint16_t ElementType, const char* ElementTypeName, bool ElementTypeName_progmem, uint8_t ElementTypeName_len, uint16_t DataCount,
    rr_socket** sock);

  void EndWriteMessageElement();
  
  void SetMessageElementError(uint16_t errcode, const char* errname, bool errname_progmem, uint8_t errname_len,
     const char* errmessage, bool errmessage_progmem, uint8_t errmessage_len);
  
  void loop();
  
  //void StartSendEvent(char* MemberName, uint8_t MemberName_len);
  
  //void EndSendEvent();
  
  void SetMemberFormatMismatchError();
  void SetMemberNotFoundError();
  
  void GetLocalNodeServices();

protected:
  void read_messagelen();
  void process_message();
  void flush_message();
  void flush_message_entry();
  void flush_message_element();
  
};

#define RR_MAX_SERVER_SOCK 3

class RobotRaconteurServer
{
public:
  
  RobotRaconteurServerConnection connections[RR_MAX_SERVER_SOCK];
  
  RobotRaconteurServer(uint16_t port, uint8_t* nodeid, char* nodeid_str, char* service_def, uint32_t service_def_len, char* object_type, uint32_t object_type_len, char* service_path, uint16_t service_path_len);
  
  void start();

  void loop();
  
  void SendAnnouncePacket();
  
  static uint8_t* NodeID;
  static char* NodeID_str;
  static char ipstr[24];
  
  EthernetUDP Udp;
  unsigned long broadcast_send_time;
  void startudp();
  
  static char* ServiceDef;
  static uint32_t ServiceDef_len;
  static char* ObjectType;
  static uint32_t ObjectType_len;
  static char* ServicePath;
  static uint16_t ServicePath_len;
  uint16_t port;
  
  EthernetServer ethernet_server;
};

void rr_function_call(RobotRaconteurServerConnection* con,char* MemberName,uint16_t ElementCount);
void rr_property_get(RobotRaconteurServerConnection* con,char* MemberName,uint16_t ElementCount);
void rr_property_set(RobotRaconteurServerConnection* con,char* MemberName,uint16_t ElementCount);

#endif
