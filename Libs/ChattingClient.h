#pragma once

#include "NetworkBase.h"
#include "UserManager.h"

namespace C_Network
{
	class ChattingClient : public ClientBase
	{
	public:
		ChattingClient(const NetAddress& targetEndPoint, uint maxSessionCnt = 1) : ClientBase(targetEndPoint, maxSessionCnt) {}
		virtual ~ChattingClient() {}
		virtual C_Network::NetworkErrorCode OnEnterServer() override;
		virtual C_Network::NetworkErrorCode OnLeave() override;
	private:
		std::unique_ptr<UserManager> _userMgr;
	};
}
