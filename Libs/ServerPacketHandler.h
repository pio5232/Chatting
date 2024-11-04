#pragma once

#include <functional>
#include "PacketDefine.h"
#include <unordered_map>

namespace C_Network
{
	// 서버에서 온 패킷을 클라이언트가 처리한다.
	// -------------------------------------------------------
	//					ServerPacketHandler
	// -------------------------------------------------------
	class ServerPacketHandler
	{
	public:
		// 어차피 클라이언트가 처리하는 메시지는 서버에서 온 메시지이다.
		using PacketFunc = C_Network::NetworkErrorCode(*)(C_Utility::CSerializationBuffer&);

		static void Init(class ChattingClient* owner);

		// 직렬화 버퍼에 데이터를 채우자! 가변 템플릿을 활용.
		template <typename PacketType>
		static SharedSendBuffer MakePacket(uint16 packetType, PacketType& packet)//(uint16 packetType, uint16 packetSize, Types... args )
		{
			// TODO : CSerializationBuffer 또한 Pool에서 꺼내서 사용하도록 만든다.

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
