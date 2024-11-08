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
		using PacketFunc = ErrorCode(PacketHandlerType::*)(C_Utility::CSerializationBuffer&);
		
		ServerPacketHandler()
		{
			_packetFuncsDic.clear();
		}
		static SharedSendBuffer MakeSendBuffer(uint packetSize)
		{
			return std::make_shared<C_Utility::CSerializationBuffer>(packetSize);
		}

		// ����ȭ ���ۿ� �����͸� ä����! ���� ���ø��� Ȱ��. ���̰� �����Ǿ� �ִ� ���� ���� �־���� �� �Լ��� ���� send.
		template <typename PacketType>
		static SharedSendBuffer MakePacket(uint16 packetSize, PacketType& packet)// (uint16 packetType, PacketType& packet)
		{
			// TODO : CSerializationBuffer ���� Pool���� ������ ����ϵ��� �����.

			SharedSendBuffer sendBuffer = std::make_shared<C_Utility::CSerializationBuffer>(packetSize);

			*sendBuffer << packet;

			return sendBuffer;
		}
		//// ����ȭ ���ۿ� �����͸� ä����! ���� ���ø��� Ȱ��.
		//template <typename PacketType>
		//static SharedSendBuffer MakePacket(uint16 packetType, PacketType& packet)//(uint16 packetType, uint16 packetSize, Types... args )
		//{
		//	// TODO : CSerializationBuffer ���� Pool���� ������ ����ϵ��� �����.

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
	//	// �Լ� ����
	//	ErrorCode ProcessChatToUserPacket(C_Utility::CSerializationBuffer& buffer);
	//	ErrorCode ProcessChatToRoomPacket(C_Utility::CSerializationBuffer& buffer);
	//	ErrorCode ProcessChatNotifyPacket(C_Utility::CSerializationBuffer& buffer);
	//	class ChattingClient* _owner;
	//};

}