#include "LibsPch.h"
#include "ServerPacketHandler.h"
#include "ChattingClient.h"

// -------------------------------------------------------
//					ServerPacketHandler
// -------------------------------------------------------


C_Network::NetworkErrorCode C_Network::ChattingServerPacketHandler::ProcessChatToUserPacket(C_Utility::CSerializationBuffer& buffer)
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

	//// TODO : ���� ó��

	//return result;
	return C_Network::NetworkErrorCode::NONE;
}
