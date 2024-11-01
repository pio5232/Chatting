#pragma once

#include "NetworkBase.h"
#include "NetworkUtils.h"
#include "ClientPacketHandler.h"

namespace C_Network
{
	class ChattingServer : public NetServer
	{
	public:
		ChattingServer(const NetAddress& netAddr, uint maxSessionCnt);
		~ChattingServer();

		virtual bool OnConnectionRequest(const SOCKADDR_IN& clientInfo);
		virtual void OnConnected(const SOCKADDR_IN& clientInfo, ULONGLONG sessionId);
		virtual void OnDisconnected(ULONGLONG sessionId);
		virtual void OnError(int errCode, WCHAR* cause);
		virtual void OnRecv(C_Utility::CSerializationBuffer& buffer, ULONGLONG sessionId, uint16 type);

		NetworkErrorCode SendToAllUser(SharedSendBuffer& buffer);
		NetworkErrorCode SendToRoom(SharedSendBuffer& buffer, uint16 roomNum);

	private:
		std::unique_ptr<RoomManager> _roomMgr;
	};
}