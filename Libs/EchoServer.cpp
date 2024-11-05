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

// �ϳ��� ��Ŷ���� �Ǻ��� ������. ���⼭ ���� SerializationBuffer�� ��Ʈ��ũ ����� ������ �����͸� �����.
void C_Network::EchoServer::OnRecv(C_Utility::CSerializationBuffer& buffer, ULONGLONG sessionId, uint16 type)
{
	// ���� �� ��Ŷ�� ���°� ���� ������ ���¿� �´��� Ȯ���ϴ� �۾��� �ʿ��ϴ�.

	// TODO : Check PacketHeader (���ǵ� ��Ŷ ����� �´���) 

	// �˸°� �� Packet�� ���� ó��.
	if (_clientPacketHandler->ProcessPacket(sessionId,type,buffer) != C_Network::NetworkErrorCode::NONE)
		TODO_LOG_ERROR;

	return;
	// TODO_LOG;
}

