#pragma once


using serializationBuffer = C_Utility::CSerializationBuffer;

namespace C_Network
{
	const int ServerPort = 6000;

	const int MAX_PACKET_SIZE = 1000;
	TODO_DEFINITION;
	enum
	{
		ROOM_NAME_MAX_LEN = 60,
	};
	enum PacketType : uint16 // packet order
	{
		// C_S, REQUEST = Ŭ���̾�Ʈ -> ����
		// S_C, RESPONSE = ���� -> Ŭ���̾�Ʈ
		LOG_IN_REQUEST_PACKET = 0, //
		LOG_IN_RESPONSE_PACKET,

		ROOM_LIST_REQUEST_PACKET,
		ROOM_LIST_RESPONSE_PACKET,

		ENTER_ROOM_REQUEST_PACKET,
		ENTER_ROOM_RESPONSE_PACKET,
		ENTER_ROOM_NOTIFY_PACKET,

		LEAVE_ROOM_REQUEST_PACKET,
		LEAVE_ROOM_RESPONSE_PACKET,
		LEAVE_ROOM_NOTIFY_PACKET,

		CLIENT_LOG_OUT_PACKET,

		// Ŭ���̾�Ʈ�� ��û
		CHAT_TO_ROOM_REQUEST_PACKET, // �� ���� �������� �޽��� ���� ��û, RoomNum�� -1�̸� ��� �濡 ����.
		CHAT_TO_USER_REQUEST_PACKET, // �ϳ��� �������� �޽��� ���� ��û.
		CHAT_NOTIFY_PACKET,

		// ������ ����.
		CHAT_TO_ROOM_RESPONSE_PACKET,
		CHAT_TO_USER_RESPONSE_PACKET, // 

		ECHO_PACKET = 65535,
	};

	// �׻� padding�� �����ϴ��� Ȯ���ؾ��Ѵ�.
	enum PacketSize
	{
		PACKET_SIZE_ECHO = 10,

		PACKET_SIZE_MAX = 500,
	};
	// size = payload�� size
	// ��Ʈ��ũ �ڵ忡�� PacketHeader�� �и��ϰ� �Ǹ� PacketHeader��ŭ�� ������� ������� �ʴ´�.
	struct PacketHeader
	{
	public:
		//void SetSize(uint16 headerSize) { size = headerSize; }
		uint16 size;
		uint16 type; 
	};

	// ECHO REQUEST / RESPONSE
	struct EchoPacket : public PacketHeader
	{
	public:
		EchoPacket() : data(0) { size = sizeof(__int64), type = ECHO_PACKET; }
		__int64 data;
	};

	// CHAT 

	struct ChatUserRequestPacket : public PacketHeader
	{
	public:
		//ULONGLONG sendUserId = 0;
		ULONGLONG targetUserId = 0;
		uint16 messageLen = 0;
		WCHAR payLoad[0];
	};
	struct ChatRoomRequestPacket : public PacketHeader
	{
		// TODO : ����
	public:
		uint16 roomNum = -1; // -1 => ��ü ä��, roomNum -> �ش� room���� ����.
		uint16 messageLen = 0;
		WCHAR payLoad[0];
	};
	
	struct ChatUserResponsePacket : public PacketHeader
	{
	public:
		ULONGLONG sendUserId = 0;
		//ULONGLONG targetUserId = 0;
		uint16 messageLen = 0;
		WCHAR payLoad[0];
	};

	// LOG_IN
	// ��ȣȭ.. ��ȣȭ?
	struct alignas (32) LogInRequestPacket : public PacketHeader
	{
		ULONGLONG logInId;
		ULONGLONG logInPw;
	};

	struct alignas (16) LogInResponsePacket : public PacketHeader
	{
		ULONGLONG userId;
	};

	// LOG_OUT
	struct LogOutRequestPacket : public PacketHeader
	{

	};
	struct LogOutResponsePacket : public PacketHeader
	{

	};

	// ENTER_ROOM
	struct EnterRoomRequestPacket : public PacketHeader
	{

	};
	struct EnterRoomResponsePacket : public PacketHeader
	{

	};

	// LEAVE_ROOM
	struct LeaveRoomRequestPacket : public PacketHeader
	{

	};
	struct LeaveRoomResponsePacket : public PacketHeader
	{

	};

	struct RoomInfo
	{
		ULONGLONG ownerId;
		uint16 roomNum;
		uint16 curUserCnt;
		uint16 maxUserCnt;
		uint16 roomNameLen;
		WCHAR roomName[0];
	};

	// REQUEST ROOM LIST
	struct RoomListRequestPacket : public PacketHeader
	{};
	struct RoomListResponsePacket : public PacketHeader
	{
		uint16 roomCnt;
		RoomInfo roomInfos[0];
	};
}


// Packet ������ �� ��Ŷ�� �´� ����ȭ���� << operator�� ����������Ѵ�, PacketHeader�� ������ ����� �س��� ���¿����Ѵ�!  operator << >> �� �Է� / ��¸� ���� ���̴�.
serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::ChatUserRequestPacket& chatUserRequestPacket);
serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::ChatRoomRequestPacket& chatRoomRequestPacket);
serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::ChatUserResponsePacket& chatUserResponsePacket);

serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::LogInRequestPacket& logInRequestPacket);
serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::LogInResponsePacket& logInResponsePacket);

// >> opeartor ����, >> operator�� PacketHeader�� ���� �и��� �����߱⿡ packetHeader�� �����ʹ� �Ű澲�� �ʾƵ� �ȴ�.
serializationBuffer& operator>> (serializationBuffer& serialBuffer, C_Network::ChatUserRequestPacket& chatUserRequestPacket);
serializationBuffer& operator>> (serializationBuffer& serialBuffer, C_Network::ChatRoomRequestPacket& chatRoomRequestPacket);
serializationBuffer& operator>> (serializationBuffer& serialBuffer, C_Network::ChatUserResponsePacket& chatUserResponsePacket);

serializationBuffer& operator>> (serializationBuffer& serialBuffer, C_Network::LogInRequestPacket& logInRequestPacket);
serializationBuffer& operator>> (serializationBuffer& serialBuffer, C_Network::LogInResponsePacket& logInResponsePacket);

