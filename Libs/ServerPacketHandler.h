#pragma once

#include <functional>
#include "PacketDefine.h"
#include <unordered_map>

namespace C_Network
{
	// �������� �� ��Ŷ�� Ŭ���̾�Ʈ�� ó���Ѵ�.
	// -------------------------------------------------------
	//					ServerPacketHandler
	// -------------------------------------------------------
	class ServerPacketHandler
	{
	public:
		// ������ Ŭ���̾�Ʈ�� ó���ϴ� �޽����� �������� �� �޽����̴�.
		using PacketFunc = C_Network::NetworkErrorCode(*)(C_Utility::CSerializationBuffer&);

		static void Init(class ChattingClient* owner);

		// ����ȭ ���ۿ� �����͸� ä����! ���� ���ø��� Ȱ��.
		template <typename PacketType>
		static SharedSendBuffer MakePacket(uint16 packetType, PacketType& packet)//(uint16 packetType, uint16 packetSize, Types... args )
		{
			// TODO : CSerializationBuffer ���� Pool���� ������ ����ϵ��� �����.

			SharedSendBuffer sendBuffer = std::make_shared<C_Utility::CSerializationBuffer>(PACKET_SIZE_MAX);

			*sendBuffer << packet;

			return sendBuffer;
		}

		static C_Network::NetworkErrorCode ProcessPacket(uint16 packetType, C_Utility::CSerializationBuffer& buffer);

		static C_Network::NetworkErrorCode ProcessChatToUserPacket(C_Utility::CSerializationBuffer& buffer);

	private:
		static std::unordered_map<uint16, PacketFunc> packetFuncs;
		
		static class ChattingClient* _owner;

	};
}
