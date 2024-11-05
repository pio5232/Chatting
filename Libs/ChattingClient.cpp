#include "LibsPch.h"
#include "ChattingClient.h"

C_Network::NetworkErrorCode C_Network::ChattingClient::OnEnterServer()
{
	TODO_LOG; // ENTER SERVER LOG
	//LogInRequestPacket

	return C_Network::NetworkErrorCode::NONE;
}

C_Network::NetworkErrorCode C_Network::ChattingClient::OnLeave()
{
	return C_Network::NetworkErrorCode();
}
