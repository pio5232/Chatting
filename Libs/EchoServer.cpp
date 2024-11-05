#include "LibsPch.h"
#include "ClientPacketHandler.h"
#include "EchoServer.h"

C_Network::EchoServer::EchoServer(const NetAddress& netAddr, uint maxSessionCnt) : ServerBase(netAddr, maxSessionCnt)
{
	_clientPacketHandler = new EchoClientPacketHandler(this);
}

C_Network::EchoServer::~EchoServer() {}

bool C_Network::EchoServer::OnConnectionRequest(const SOCKADDR_IN& clientInfo)
{
	return false;
}

void C_Network::EchoServer::OnConnected(const SOCKADDR_IN& clientInfo, ULONGLONG sessionId)
{
}

void C_Network::EchoServer::OnDisconnected(ULONGLONG sessionId)
{
}

void C_Network::EchoServer::OnError(int errCode, WCHAR* cause)
{
}

// 하나의 패킷으로 판별이 끝났다. 여기서 오는 SerializationBuffer는 네트워크 헤더를 제외한 데이터만 들었다.
void C_Network::EchoServer::OnRecv(C_Utility::CSerializationBuffer& buffer, ULONGLONG sessionId, uint16 type)
{
	// 이제 그 패킷의 형태가 내가 정의한 형태와 맞는지 확인하는 작업이 필요하다.

	// TODO : Check PacketHeader (정의된 패킷 헤더가 맞는지) 

	// 알맞게 온 Packet에 대한 처리.
	if (_clientPacketHandler->ProcessPacket(sessionId,type,buffer) != C_Network::NetworkErrorCode::NONE)
		TODO_LOG_ERROR;

	return;
	// TODO_LOG;
}

