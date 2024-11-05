#pragma once

#include <functional>
#include "PacketDefine.h"
#include <unordered_map>

namespace C_Network
{
	// 서버에서 온 패킷을 클라이언트가 처리한다.
	// -------------------------------------------------------
	//					BaseServerPacketHandler
	// -------------------------------------------------------

	template <typename PacketHandlerType>
	class ServerPacketHandler
	{
	public:
		// 어차피 클라이언트가 처리하는 메시지는 서버에서 온 메시지이다.
		using PacketFunc = C_Network::NetworkErrorCode(PacketHandlerType::*)(C_Utility::CSerializationBuffer&);
		
		ServerPacketHandler()
		{
			_packetFuncs.clear();
		}

		// 직렬화 버퍼에 데이터를 채우자! 가변 템플릿을 활용.
		template <typename PacketType>
		static SharedSendBuffer MakePacket(uint16 packetType, PacketType& packet)//(uint16 packetType, uint16 packetSize, Types... args )
		{
			// TODO : CSerializationBuffer 또한 Pool에서 꺼내서 사용하도록 만든다.

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
		// 함수 정의
		C_Network::NetworkErrorCode ProcessChatToUserPacket(C_Utility::CSerializationBuffer& buffer);

		class ChattingClient* _owner;
	};
}