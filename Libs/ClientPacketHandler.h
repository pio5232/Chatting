#pragma once

#include <functional>
#include "PacketDefine.h"
#include <unordered_map>
namespace C_Network
{
	/*---------------------------------------
				PacketHandler						// 서버마다 정의한다.
	---------------------------------------*/
	class ClientPacketHandler
	{
	public:
		// uin16 Message크기는 제외한다. 어차피 PacketHandler가 처리하게 되는 것은 하나의 완전한 데이터로 왔을 때 처리하기 때문이다.
		//, uint16) > ; // sessionId, Message 내용 버퍼, Message 크기.
		using PacketFunc = C_Network::NetworkErrorCode(*)(ULONGLONG, C_Utility::CSerializationBuffer&);//std::function<bool(ULONGLONG, char*)>;

		static void Init(class ChattingServer* owner);

		// 직렬화 버퍼에 데이터를 채우자! 가변 템플릿을 활용.
		template <typename PacketType>
		static SharedSendBuffer MakePacket(uint16 packetType, PacketType& packet)//(uint16 packetType, uint16 packetSize, Types... args )
		{
			// TODO : CSerializationBuffer 또한 Pool에서 꺼내서 사용하도록 만든다.

			SharedSendBuffer sendBuffer = std::make_shared<C_Utility::CSerializationBuffer>(PACKET_SIZE_MAX);

			*sendBuffer << packet;

			return sendBuffer;
		}

		static C_Network::NetworkErrorCode ProcessPacket(ULONGLONG sessionId, uint16 packetType, C_Utility::CSerializationBuffer& buffer);

		static C_Network::NetworkErrorCode ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		static C_Network::NetworkErrorCode ProcessChatToRoomPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		static C_Network::NetworkErrorCode ProcessChatToUserPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

	private:
		static std::unordered_map<uint16, PacketFunc> packetFuncs;

		static class ChattingServer* _owner;
	};
}
