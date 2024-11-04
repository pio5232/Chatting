#pragma once


using serializationBuffer = C_Utility::CSerializationBuffer;

namespace C_Network
{
	const int ServerPort = 6000;

	const int MAX_PACKET_SIZE = 1000;
	TODO_DEFINITION;
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

		LEAVE_ROOM_REQUEST_PACKET,
		LEAVE_ROOM_RESPONSE_PACKET,

		CLIENT_LOG_OUT_PACKET,

		// Ŭ���̾�Ʈ�� ��û
		CHAT_TO_ROOM_REQUEST_PACKET, // �� ���� �������� �޽��� ���� ��û, RoomNum�� -1�̸� ��� �濡 ����.
		CHAT_TO_USER_REQUEST_PACKET, // �ϳ��� �������� �޽��� ���� ��û.

		// ������ ����.
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

		//uint16 type; // EchoServer�� �׽�Ʈ�� ���� type�� ����.
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
		// TODO : ����
	public:
		uint16 messageLen = 0;
		uint16 roomNum = -1; // -1 => ��ü ä��, roomNum -> �ش� room���� ����.
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
	
	// ��ȣȭ.. ��ȣȭ?
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
// Packet ������ �� ��Ŷ�� �´� ����ȭ���� << operator�� ����������Ѵ�.
serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::EchoPacket& echoPacket);

serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::ChatUserResponsePacket& chattingPacket);

serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::LogInRequestPacket& logInPacket);
//serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::ChatUserRequestPacket& chattingPacket);