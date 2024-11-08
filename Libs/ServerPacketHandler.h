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
		using PacketFunc = ErrorCode(PacketHandlerType::*)(C_Utility::CSerializationBuffer&);
		
		ServerPacketHandler()
		{
			_packetFuncsDic.clear();
		}
		static SharedSendBuffer MakeSendBuffer(uint packetSize)
		{
			return std::make_shared<C_Utility::CSerializationBuffer>(packetSize);
		}

		// 직렬화 버퍼에 데이터를 채우자! 가변 템플릿을 활용. 길이가 고정되어 있는 경우는 값을 넣어놓고 이 함수를 통해 send.
		template <typename PacketType>
		static SharedSendBuffer MakePacket(uint16 packetSize, PacketType& packet)// (uint16 packetType, PacketType& packet)
		{
			// TODO : CSerializationBuffer 또한 Pool에서 꺼내서 사용하도록 만든다.

			SharedSendBuffer sendBuffer = std::make_shared<C_Utility::CSerializationBuffer>(packetSize);

			*sendBuffer << packet;

			return sendBuffer;
		}
		//// 직렬화 버퍼에 데이터를 채우자! 가변 템플릿을 활용.
		//template <typename PacketType>
		//static SharedSendBuffer MakePacket(uint16 packetType, PacketType& packet)//(uint16 packetType, uint16 packetSize, Types... args )
		//{
		//	// TODO : CSerializationBuffer 또한 Pool에서 꺼내서 사용하도록 만든다.

		//	SharedSendBuffer sendBuffer = std::make_shared<C_Utility::CSerializationBuffer>(PACKET_SIZE_MAX);

		//	*sendBuffer << packet;

		//	return sendBuffer;
		//}

		ErrorCode ProcessPacket(ULONGLONG sessionId, uint16 packetType, C_Utility::CSerializationBuffer& buffer)
		{
			if (_packetFuncsDic.find(packetType) == _packetFuncsDic.end())
				return ErrorCode::CANNOT_FIND_PACKET_FUNC;

			return ((reinterpret_cast<PacketHandlerType*>(this))->*_packetFuncsDic[packetType])(sessionId, buffer);
		}
	protected:
		std::unordered_map<uint16, PacketFunc> _packetFuncsDic;
	};

	//class ChattingServerPacketHandler : public ServerPacketHandler<ChattingServerPacketHandler>
	//{
	//public:
	//	ChattingServerPacketHandler(class ChattingClient* owner) : _owner(owner)
	//	{
	//		_packetFuncsDic[CHAT_TO_USER_RESPONSE_PACKET] = &ChattingServerPacketHandler::ProcessChatToUserPacket; // Chat To Room Users
	//		_packetFuncsDic[CHAT_TO_ROOM_RESPONSE_PACKET] = &ChattingServerPacketHandler::ProcessChatToRoomPacket; // Chat To Room Users
	//		_packetFuncsDic[CHAT_NOTIFY_PACKET] = &ChattingServerPacketHandler::ProcessChatNotifyPacket; // Chat To Room Users
	//	}
	//public:
	//	virtual ErrorCode OnHandlePacket() = 0;
	//private:
	//	// 함수 정의
	//	ErrorCode ProcessChatToUserPacket(C_Utility::CSerializationBuffer& buffer);
	//	ErrorCode ProcessChatToRoomPacket(C_Utility::CSerializationBuffer& buffer);
	//	ErrorCode ProcessChatNotifyPacket(C_Utility::CSerializationBuffer& buffer);
	//	class ChattingClient* _owner;
	//};

}