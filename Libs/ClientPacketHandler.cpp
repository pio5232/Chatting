#include "LibsPch.h"
#include "ClientPacketHandler.h"
#include "EchoServer.h"
#include "ChattingServer.h"
/*---------------------------------------
			ClientPacketHandler
---------------------------------------*/

ErrorCode C_Network::ChattingClientPacketHandler::ProcessChatToRoomPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	uint16 roomNum;
	uint16 messageLen;

	buffer >> roomNum >> messageLen;
	
	char* payLoad = static_cast<char*>(malloc(messageLen));
	
	buffer.GetData(payLoad, messageLen);

	// TODO : Message 문자열 검사
	// WCHAR* ~~~

	PacketHeader packetHeader;

	packetHeader.size = 0;
	packetHeader.type = CHAT_TO_ROOM_RESPONSE_PACKET; 

	// --- ChatRoomResponsePacket
	C_Network::SharedSendBuffer responseBuffer = MakePacket(sizeof(PacketHeader), packetHeader);
	_owner->Send(sessionId, responseBuffer);

	// --- NotifyPacket
	packetHeader.size = sizeof(sessionId) + sizeof(messageLen) + messageLen;
	packetHeader.type = CHAT_NOTIFY_PACKET;

	C_Network::SharedSendBuffer notifyBuffer = MakeSendBuffer(sizeof(packetHeader) + packetHeader.size);
	
	*notifyBuffer << packetHeader <<  _userMgr->GetUser(sessionId)->GetUserId() << messageLen;
	notifyBuffer->PutData(reinterpret_cast<const char*>(payLoad), messageLen);

	free(payLoad);

	ErrorCode errCode = _roomMgr->SendToRoom(roomNum, notifyBuffer);

	return errCode;
}

ErrorCode C_Network::ChattingClientPacketHandler::ProcessChatToUserPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	ULONGLONG targetSessionId = 0;
	uint16 messageLen = 0;

	buffer >> targetSessionId >> messageLen;

	char* payLoad = static_cast<char*>(malloc(messageLen));

	buffer.GetData(payLoad, messageLen);

	// TODO : Message 문자열 검사
	// WCHAR* ~~~

	PacketHeader packetHeader;

	packetHeader.size = 0;
	packetHeader.type = CHAT_TO_USER_RESPONSE_PACKET;

	// --- ChatUserResponsePacket
	C_Network::SharedSendBuffer responseBuffer = MakePacket(sizeof(PacketHeader), packetHeader);
	_owner->Send(sessionId, responseBuffer);

	// --- NotifyPacket
	packetHeader.size = sizeof(sessionId) + sizeof(messageLen) + messageLen;
	packetHeader.type = CHAT_NOTIFY_PACKET;

	C_Network::SharedSendBuffer notifyBuffer = MakeSendBuffer(sizeof(packetHeader) + packetHeader.size);

	*notifyBuffer << packetHeader << _userMgr->GetUser(sessionId)->GetUserId() << messageLen;
	notifyBuffer->PutData(reinterpret_cast<const char*>(payLoad), messageLen);

	free(payLoad);

	_owner->Send(targetSessionId, notifyBuffer);

	return ErrorCode::NONE;
}

ErrorCode C_Network::ChattingClientPacketHandler::ProcessRoomListRequestPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{
	C_Network::User* userPtr = _userMgr->GetUser(sessionId);

	if (!userPtr)
		return ErrorCode::SESSION_USER_NOT_CONN;
	// User의 정보를 확인한 후 정상적인 상태에 있는 유저라면

	// RoomMgr에게 그 유저에게 정보를 보내라고 한다.

	// TODO : use Pool
	C_Network::SharedSendBuffer sendBuffer = MakeSendBuffer(sizeof(RoomListResponsePacket) + _roomMgr->GetCurElementCount() * sizeof(RoomInfo));

	ErrorCode errCode = _roomMgr->SendToUserRoomInfo(sessionId, sendBuffer);

	return errCode;
}

ErrorCode C_Network::ChattingClientPacketHandler::ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{ 
	LogInRequestPacket clientRequestPacket;

	buffer >> clientRequestPacket;
	// ID와 비밀번호를 확인한 후 (클라이언트에서 암호화 -> 서버에서 복호화?)
	// 검증
	
	// 원래는 DB에서 USER 정보를 얻어와야 하지만, 현재는 DB 적용하지 않았기 때문에 3씩 증가시키도록 한다.
	static volatile ULONGLONG userIdGenerator = 4283;
	
	// TODO : DB에서 얻어오는걸로 변경.
	ULONGLONG userId = InterlockedAdd64((LONGLONG*)&userIdGenerator, 3);

	LogInResponsePacket clientResponsePacket;

	clientResponsePacket.size = sizeof(clientResponsePacket.userId);
	clientResponsePacket.type = LOG_IN_RESPONSE_PACKET;
	clientResponsePacket.userId = userId;

	C_Network::SharedSendBuffer sendBuffer = MakePacket(sizeof(LogInResponsePacket), clientResponsePacket);

	_owner->Send(sessionId, sendBuffer);

	// 로그인 데이터를 DB에서 불러와서 설정 후 로그인 정보를

	// 해당 클라이언트에 전송한다...?

	// 현재는 일단 userId를 전송하도록 한다.
	
	return ErrorCode::NONE;
}
