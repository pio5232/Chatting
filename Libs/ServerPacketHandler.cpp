#include "LibsPch.h"
#include "ServerPacketHandler.h"
#include "ChattingClient.h"

// -------------------------------------------------------
//					ServerPacketHandler
// -------------------------------------------------------

std::unordered_map<uint16, C_Network::ServerPacketHandler::PacketFunc> C_Network::ServerPacketHandler::packetFuncs;
C_Network::ChattingClient* C_Network::ServerPacketHandler::_owner = nullptr;

void C_Network::ServerPacketHandler::Init(ChattingClient* owner)
{
	_owner = owner;

	packetFuncs.clear();
	packetFuncs[CHAT_TO_USER_RESPONSE_PACKET] = ServerPacketHandler::ProcessChatToUserPacket; // Chat To Room Users
}

C_Network::NetworkErrorCode C_Network::ServerPacketHandler::ProcessPacket(uint16 packetType, C_Utility::CSerializationBuffer& buffer)
{
	if (packetFuncs.find(packetType) == packetFuncs.end())
		return C_Network::NetworkErrorCode::CANNOT_FIND_PACKET_FUNC;

	return packetFuncs[packetType](buffer);
}


C_Network::NetworkErrorCode C_Network::ServerPacketHandler::ProcessChatToUserPacket(C_Utility::CSerializationBuffer& buffer)
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
