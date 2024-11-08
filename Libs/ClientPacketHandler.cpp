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

	// TODO : Message ���ڿ� �˻�
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

	// TODO : Message ���ڿ� �˻�
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
	// User�� ������ Ȯ���� �� �������� ���¿� �ִ� �������

	// RoomMgr���� �� �������� ������ ������� �Ѵ�.

	// TODO : use Pool
	C_Network::SharedSendBuffer sendBuffer = MakeSendBuffer(sizeof(RoomListResponsePacket) + _roomMgr->GetCurElementCount() * sizeof(RoomInfo));

	ErrorCode errCode = _roomMgr->SendToUserRoomInfo(sessionId, sendBuffer);

	return errCode;
}

ErrorCode C_Network::ChattingClientPacketHandler::ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer)
{ 
	LogInRequestPacket clientRequestPacket;

	buffer >> clientRequestPacket;
	// ID�� ��й�ȣ�� Ȯ���� �� (Ŭ���̾�Ʈ���� ��ȣȭ -> �������� ��ȣȭ?)
	// ����
	
	// ������ DB���� USER ������ ���;� ������, ����� DB �������� �ʾұ� ������ 3�� ������Ű���� �Ѵ�.
	static volatile ULONGLONG userIdGenerator = 4283;
	
	// TODO : DB���� �����°ɷ� ����.
	ULONGLONG userId = InterlockedAdd64((LONGLONG*)&userIdGenerator, 3);

	LogInResponsePacket clientResponsePacket;

	clientResponsePacket.size = sizeof(clientResponsePacket.userId);
	clientResponsePacket.type = LOG_IN_RESPONSE_PACKET;
	clientResponsePacket.userId = userId;

	C_Network::SharedSendBuffer sendBuffer = MakePacket(sizeof(LogInResponsePacket), clientResponsePacket);

	_owner->Send(sessionId, sendBuffer);

	// �α��� �����͸� DB���� �ҷ��ͼ� ���� �� �α��� ������

	// �ش� Ŭ���̾�Ʈ�� �����Ѵ�...?

	// ����� �ϴ� userId�� �����ϵ��� �Ѵ�.
	
	return ErrorCode::NONE;
}
