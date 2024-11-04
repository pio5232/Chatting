#pragma once

#include "NetworkBase.h"

namespace C_Network
{
	class ChattingClient : public ClientBase
	{
	public:
		ChattingClient(const NetAddress& targetEndPoint) : ClientBase(targetEndPoint) {}
		virtual ~ChattingClient() {}
		virtual C_Network::NetworkErrorCode OnEnterServer() override;
		virtual C_Network::NetworkErrorCode OnLeave() override;
	};
}