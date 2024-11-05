#pragma once

#include <functional>
#include "PacketDefine.h"
#include <unordered_map>
namespace C_Network
{
	/*---------------------------------------
				BasePacketHandler						// �������� ��ӹ޾Ƽ� ����ϵ��� �Ѵ�..
	---------------------------------------*/
	template <typename PacketHandlerType>
	class ClientPacketHandler
	{
	public:
		ClientPacketHandler() { packetFuncs.clear(); }
		// uin16 Messageũ��� �����Ѵ�. ������ PacketHandler�� ó���ϰ� �Ǵ� ���� �ϳ��� ������ �����ͷ� ���� �� ó���ϱ� �����̴�.
		//, uint16) > ; // sessionId, Message ���� ����, Message ũ��.
		using PacketFunc = C_Network::NetworkErrorCode(PacketHandlerType::*)(ULONGLONG, C_Utility::CSerializationBuffer&);//std::function<bool(ULONGLONG, char*)>;

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
			if (packetFuncs.find(packetType) == packetFuncs.end())
				return C_Network::NetworkErrorCode::CANNOT_FIND_PACKET_FUNC;

			return ((reinterpret_cast<PacketHandlerType*>(this))->*packetFuncs[packetType])(sessionId, buffer);
		}
	protected:
		std::unordered_map<uint16, PacketFunc> packetFuncs;

	};

	class ChattingClientPacketHandler : public ClientPacketHandler<ChattingClientPacketHandler>
	{
	public :
		ChattingClientPacketHandler(class ChattingServer* owner) : _owner(owner)
		{
			packetFuncs[CHAT_TO_ROOM_REQUEST_PACKET] = &ChattingClientPacketHandler::ProcessChatToRoomPacket; // Chat To Room Users
			packetFuncs[CHAT_TO_USER_REQUEST_PACKET] = &ChattingClientPacketHandler::ProcessChatToUserPacket; // Chat To Room Users

		}
	private:
		// �Լ� ����
		C_Network::NetworkErrorCode ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		C_Network::NetworkErrorCode ProcessChatToRoomPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		C_Network::NetworkErrorCode ProcessChatToUserPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

		class ChattingServer* _owner;
	};

	// ���߿� ����� �� �߰� ����
	class LogInClientPacketHandler : public ClientPacketHandler<LogInClientPacketHandler>
	{
	public:
		LogInClientPacketHandler(class LogInServer* owner) : _owner(owner)
		{
			packetFuncs[LOG_IN_REQUEST_PACKET] = &LogInClientPacketHandler::ProcessLogInPacket;
		}
	private:
		C_Network::NetworkErrorCode ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		class LogInServer* _owner;
	};

}
