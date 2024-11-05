#include "LibsPch.h"
#include "ClientPacketHandler.h"
#include "EchoServer.h"
#include "ChattingServer.h"
/*---------------------------------------
			ClientPacketHandler
---------------------------------------*/

C_Network::NetworkErrorCode C_Network::ChattingClientPacketHandler::ProcessChatToRoomPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	ChatRoomRequestPacket* chatRoomRequestPacket = static_cast<ChatRoomRequestPacket*>(malloc(sizeof(PacketHeader) + buffer.GetDataSize()));

	if (!chatRoomRequestPacket)
		return C_Network::NetworkErrorCode::MESSAGE_SEND_FAILED_MEMORY;

	buffer >> *chatRoomRequestPacket;

	ChatUserResponsePacket* chatRoomResponsePacket = static_cast<ChatUserResponsePacket*>(malloc(sizeof(ChatUserResponsePacket) + chatRoomRequestPacket->messageLen));

	if (!chatRoomResponsePacket)
		return C_Network::NetworkErrorCode::MESSAGE_SEND_FAILED_MEMORY;


	//uint16 messageLen;
	//
	//buffer >> messageLen;

	//// TODO : NEW -> POOL
	//ChatUserResponsePacket* chatPacket = static_cast<ChatUserResponsePacket*>(malloc(sizeof(ChatUserResponsePacket) + messageLen));
	//
	//if (!chatPacket)
	//	return C_Network::NetworkErrorCode::MESSAGE_SEND_FAILED;
	//
	//chatPacket->size = messageLen + sizeof(chatPacket->messageLen);
	//chatPacket->messageLen = messageLen;
	//buffer.GetData(chatPacket->payLoad, messageLen);
	//
	//SharedSendBuffer sendBuffer = MakePacket(CHAT_TO_USER_RESPONSE_PACKET, *chatPacket);
	//
	//C_Network::NetworkErrorCode result = _owner->SendToAllUser(sendBuffer);

	//// TODO : 정상 처리

	//return result;
}

C_Network::NetworkErrorCode C_Network::ChattingClientPacketHandler::ProcessChatToUserPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	//uint16 messageLen;

	//buffer >> messageLen;

	//// TODO : NEW -> POOL
	//ChatUserResponsePacket* chatPacket = static_cast<ChatUserResponsePacket*>(malloc(sizeof(ChatUserResponsePacket) + messageLen));

	//if (!chatPacket)
	//	return C_Network::NetworkErrorCode::MESSAGE_SEND_FAILED;

	//chatPacket->size = messageLen + sizeof(chatPacket->messageLen);
	//chatPacket->messageLen = messageLen;
	//buffer.GetData(chatPacket->payLoad, messageLen);

	//SharedSendBuffer sendBuffer = MakePacket(CHAT_TO_USER_RESPONSE_PACKET, *chatPacket);

	//C_Network::NetworkErrorCode result = _owner->SendToRoom(sendBuffer, -1);

	//// TODO : 정상 처리

	//return result;

	return C_Network::NetworkErrorCode::NONE;
}

C_Network::NetworkErrorCode C_Network::ChattingClientPacketHandler::ProcessRoomListRequestPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	_roomMgr->
	return NetworkErrorCode();
}

C_Network::NetworkErrorCode C_Network::ChattingClientPacketHandler::ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	LogInRequestPacket clientRequestPacket;

	buffer >> clientRequestPacket;
	// ID와 비밀번호를 확인한 후 (클라이언트에서 암호화 -> 서버에서 복호화?)
	// 검증
	
	// 로그인 데이터를 DB에서 불러와서 설정 후 로그인 정보를

	// 해당 클라이언트에 전송한다...?

	// 현재는 일단 userId를 전송하도록 한다.
	
	return C_Network::NetworkErrorCode::NONE;
}
