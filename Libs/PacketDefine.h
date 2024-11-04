#pragma once


using serializationBuffer = C_Utility::CSerializationBuffer;

namespace C_Network
{
	const int ServerPort = 6000;

	const int MAX_PACKET_SIZE = 1000;
	TODO_DEFINITION;
	enum PacketType : uint16 // packet order
	{
		// C_S, REQUEST = 클라이언트 -> 서버
		// S_C, RESPONSE = 서버 -> 클라이언트
		LOG_IN_REQUEST_PACKET = 0, //
		LOG_IN_RESPONSE_PACKET,

		ROOM_LIST_REQUEST_PACKET,
		ROOM_LIST_RESPONSE_PACKET,

		ENTER_ROOM_REQUEST_PACKET,
		ENTER_ROOM_RESPONSE_PACKET,

		LEAVE_ROOM_REQUEST_PACKET,
		LEAVE_ROOM_RESPONSE_PACKET,

		CLIENT_LOG_OUT_PACKET,

		// 클라이언트의 요청
		CHAT_TO_ROOM_REQUEST_PACKET, // 방 안의 유저에게 메시지 전송 요청, RoomNum이 -1이면 모든 방에 전송.
		CHAT_TO_USER_REQUEST_PACKET, // 하나의 유저에게 메시지 전송 요청.

		// 서버의 응답.
		CHAT_TO_USER_RESPONSE_PACKET, // 

		ECHO_PACKET = 65535,
	};

	// 항상 padding이 존재하는지 확인해야한다.
	enum PacketSize
	{
		PACKET_SIZE_ECHO = 10,

		PACKET_SIZE_MAX = 500,
	};
	// size = payload의 size
	// 네트워크 코드에서 PacketHeader를 분리하게 되면 PacketHeader만큼의 사이즈는 사용하지 않는다.
	struct PacketHeader
	{
	public:
		//void SetSize(uint16 headerSize) { size = headerSize; }
		uint16 size;

		//uint16 type; // EchoServer를 테스트할 때는 type이 없다.
	};

	// Request
	struct EchoPacket : public PacketHeader
	{
	public:
		EchoPacket() : data(0) { size = sizeof(__int64); }
		__int64 data;
	};

	struct ChatRoomRequestPacket : public PacketHeader
	{
		// TODO : 수정
	public:
		uint16 messageLen = 0;
		uint16 roomNum = -1; // -1 => 전체 채팅, roomNum -> 해당 room에만 전송.
		char payLoad[0];
	};
	struct ChatUserRequestPacket : public PacketHeader
	{
	public:
		//ULONGLONG sendUserId = 0;
		ULONGLONG targetUserId = 0;
		uint16 messageLen = 0;
		char payLoad[0];
	};
	
	// 암호화.. 복호화?
	struct LogInRequestPacket : public PacketHeader
	{
		ULONGLONG logInId;
		ULONGLONG logInPw;
	};

	struct LogOutRequestPacket : public PacketHeader
	{

	};

	struct EnterRoomRequestPacket : public PacketHeader
	{

	};

	// Response
	struct ChatUserResponsePacket : public PacketHeader
	{
	public:
		ULONGLONG sendUserId = 0;
		//ULONGLONG targetUserId = 0;
		uint16 messageLen = 0;
		char payLoad[0];
	};


	struct LogInResponsePacket : public PacketHeader
	{
		ULONGLONG userId;
	};

	struct LogOutResponsePacket : public PacketHeader
	{

	};

	struct LeaveRoomResponsePacket : public PacketHeader
	{

	};
}
// Packet 정의할 때 패킷에 맞는 직렬화버퍼 << operator를 정의해줘야한다.
serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::EchoPacket& echoPacket);

serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::ChatUserResponsePacket& chattingPacket);

serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::LogInRequestPacket& logInPacket);
//serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::ChatUserRequestPacket& chattingPacket);