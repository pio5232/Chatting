#include "LibsPch.h"
#include "ChattingServer.h"
#include "ClientPacketHandler.h"

C_Network::ChattingServer::ChattingServer(const NetAddress& netAddr, uint maxSessionCnt) : ServerBase(netAddr, maxSessionCnt)
{
	// TODO : USE POOL
	_packetHandler = new ChattingClientPacketHandler(this);

	const uint roomCnt = 20;
	
	uint maxRoomUserCnt = maxSessionCnt / roomCnt;
	if (maxSessionCnt % roomCnt != 0)
		++maxRoomUserCnt;
	
	_roomMgr = std::make_unique<RoomManager>(this, roomCnt, maxRoomUserCnt);
	_userMgr = std::make_unique<UserManager>(maxSessionCnt);
}

C_Network::ChattingServer::~ChattingServer()
{
	delete _packetHandler;
}

bool C_Network::ChattingServer::OnConnectionRequest(const SOCKADDR_IN& clientInfo)
{
	return false;
}

void C_Network::ChattingServer::OnConnected(const SOCKADDR_IN& clientInfo, ULONGLONG sessionId)
{
}

void C_Network::ChattingServer::OnDisconnected(ULONGLONG sessionId)
{
	// TODO : 해당 세션의 user Id 를 찾아서 데이터 저장 및 제거 필요.
}

void C_Network::ChattingServer::OnError(int errCode, WCHAR* cause)
{
}

void C_Network::ChattingServer::OnRecv(C_Utility::CSerializationBuffer& buffer, ULONGLONG sessionId, uint16 type)
{
	if (_packetHandler->ProcessPacket(sessionId, type, buffer) == C_Network::NetworkErrorCode::CANNOT_FIND_PACKET_FUNC)
		TODO_LOG;
}

C_Network::NetworkErrorCode C_Network::ChattingServer::SendToAllUser(C_Network::SharedSendBuffer& buffer)
{
	return NetworkErrorCode();
}

C_Network::NetworkErrorCode C_Network::ChattingServer::SendToRoom(C_Network::SharedSendBuffer& buffer, uint16 roomNum)
{
	return NetworkErrorCode();
}
