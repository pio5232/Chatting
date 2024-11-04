#include "LibsPch.h"
#include "ClientPacketHandler.h"
#include "EchoServer.h"
#include "ChattingServer.h"
/*---------------------------------------
			EchoPacketHandler
---------------------------------------*/
std::unordered_map<uint16, C_Network::ClientPacketHandler::PacketFunc> C_Network::ClientPacketHandler::packetFuncs;
C_Network::EchoServer* C_Network::ClientPacketHandler::_echoOwner = nullptr;
C_Network::ChattingServer* C_Network::ClientPacketHandler::_owner = nullptr;

void C_Network::ClientPacketHandler::Init(C_Network::EchoServer* owner) 
{
	_echoOwner = owner;

	packetFuncs.clear();
	packetFuncs[ECHO_PACKET] = ClientPacketHandler::ProcessEchoPacket; // Echo

}
void C_Network::ClientPacketHandler::Init(C_Network::ChattingServer* owner)
{
	_owner = owner;

	packetFuncs.clear();

	// TODO : 로그인 서버 만들면 해당 작업을 로그인 서버로 옮기기
	packetFuncs[LOG_IN_REQUEST_PACKET] = ClientPacketHandler::ProcessLogInPacket;
	
	packetFuncs[CHAT_TO_ROOM_REQUEST_PACKET] = ClientPacketHandler::ProcessChatToRoomPacket; // Chat To Room Users
	packetFuncs[CHAT_TO_USER_REQUEST_PACKET] = ClientPacketHandler::ProcessChatToUserPacket; // Chat To Room Users

}

C_Network::NetworkErrorCode C_Network::ClientPacketHandler::ProcessPacket(ULONGLONG sessionId, uint16 packetType, C_Utility::CSerializationBuffer& buffer)
{
	if (packetFuncs.find(packetType) == packetFuncs.end())
		return C_Network::NetworkErrorCode::CANNOT_FIND_PACKET_FUNC;

	return packetFuncs[packetType](sessionId, buffer);
}

C_Network::NetworkErrorCode C_Network::ClientPacketHandler::ProcessEchoPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	// LOGIC

	EchoPacket echoPacket;

	buffer >> echoPacket.data;

	SharedSendBuffer sendBuffer = MakePacket(ECHO_PACKET, echoPacket);
	
	_echoOwner->Send(sessionId, sendBuffer);

	return C_Network::NetworkErrorCode::NONE;
}

C_Network::NetworkErrorCode C_Network::ClientPacketHandler::ProcessChatToRoomPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	uint16 messageLen;
	
	buffer >> messageLen;

	// TODO : NEW -> POOL
	ChatUserResponsePacket* chatPacket = static_cast<ChatUserResponsePacket*>(malloc(sizeof(ChatUserResponsePacket) + messageLen));
	
	if (!chatPacket)
		return C_Network::NetworkErrorCode::MESSAGE_SEND_FAILED;
	
	chatPacket->size = messageLen + sizeof(chatPacket->messageLen);
	chatPacket->messageLen = messageLen;
	buffer.GetData(chatPacket->payLoad, messageLen);
	
	SharedSendBuffer sendBuffer = MakePacket(CHAT_TO_USER_RESPONSE_PACKET, *chatPacket);
	
	C_Network::NetworkErrorCode result = _owner->SendToAllUser(sendBuffer);

	// TODO : 정상 처리

	return result;
}

C_Network::NetworkErrorCode C_Network::ClientPacketHandler::ProcessChatToUserPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	uint16 messageLen;

	buffer >> messageLen;

	// TODO : NEW -> POOL
	ChatUserResponsePacket* chatPacket = static_cast<ChatUserResponsePacket*>(malloc(sizeof(ChatUserResponsePacket) + messageLen));

	if (!chatPacket)
		return C_Network::NetworkErrorCode::MESSAGE_SEND_FAILED;

	chatPacket->size = messageLen + sizeof(chatPacket->messageLen);
	chatPacket->messageLen = messageLen;
	buffer.GetData(chatPacket->payLoad, messageLen);

	SharedSendBuffer sendBuffer = MakePacket(CHAT_TO_USER_RESPONSE_PACKET, *chatPacket);

	C_Network::NetworkErrorCode result = _owner->SendToRoom(sendBuffer, -1);

	// TODO : 정상 처리

	return result;
}

C_Network::NetworkErrorCode C_Network::ClientPacketHandler::ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	// ID와 비밀번호를 확인한 후 (클라이언트에서 암호화 -> 서버에서 복호화?)
	
	// 로그인 데이터를 DB에서 불러와서 설정 후 로그인 정보를

	// 해당 클라이언트에 전송한다...?
	LogInRequestPacket clientRequestPacket;
	
	
	
	return C_Network::NetworkErrorCode::NONE;
}
