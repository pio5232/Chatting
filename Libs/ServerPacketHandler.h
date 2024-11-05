#pragma once

#include <functional>
#include "PacketDefine.h"
#include <unordered_map>

namespace C_Network
{
	// �������� �� ��Ŷ�� Ŭ���̾�Ʈ�� ó���Ѵ�.
	// -------------------------------------------------------
	//					BaseServerPacketHandler
	// -------------------------------------------------------

	template <typename PacketHandlerType>
	class ServerPacketHandler
	{
	public:
		// ������ Ŭ���̾�Ʈ�� ó���ϴ� �޽����� �������� �� �޽����̴�.
		using PacketFunc = C_Network::NetworkErrorCode(PacketHandlerType::*)(C_Utility::CSerializationBuffer&);
		
		ServerPacketHandler()
		{
			_packetFuncs.clear();
		}

		// ����ȭ ���ۿ� �����͸� ä����! ���� ���ø��� Ȱ��.
		template <typename PacketType>
		static SharedSendBuffer MakePacket(uint16 packetType, PacketType& packet)//(uint16 packetType, uint16 packetSize, Types... args )
		{
			// TODO : CSerializationBuffer ���� Pool���� ������ ����ϵ��� �����.

			SharedSendBuffer sendBuffer = std::make_shared<C_Utility::CSerializationBuffer>(PACKET_SIZE_MAX);

			*sendBuffer << packet;

			return sendBuffer;
		}

		NetworkErrorCode ProcessPacket(ULONGLONG sessionId, uint16 packetType, C_Utility::CSerializationBuffer& buffer)
		{
			if (_packetFuncs.find(packetType) == _packetFuncs.end())
				return C_Network::NetworkErrorCode::CANNOT_FIND_PACKET_FUNC;

			return ((reinterpret_cast<PacketHandlerType*>(this))->*_packetFuncs[packetType])(sessionId, buffer);
		}
	protected:
		std::unordered_map<uint16, PacketFunc> _packetFuncs;
	};

	class ChattingServerPacketHandler : public ServerPacketHandler<ChattingServerPacketHandler>
	{
	public:
		ChattingServerPacketHandler(class ChattingClient* owner) : _owner(owner)
		{
			_packetFuncs[CHAT_TO_USER_RESPONSE_PACKET] = &ChattingServerPacketHandler::ProcessChatToUserPacket; // Chat To Room Users
		}
	private:
		// �Լ� ����
		C_Network::NetworkErrorCode ProcessChatToUserPacket(C_Utility::CSerializationBuffer& buffer);

		class ChattingClient* _owner;
	};
}