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
		ClientPacketHandler() { _packetFuncs.clear(); }
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
			if (_packetFuncs.find(packetType) == _packetFuncs.end())
				return C_Network::NetworkErrorCode::CANNOT_FIND_PACKET_FUNC;

			return ((reinterpret_cast<PacketHandlerType*>(this))->*_packetFuncs[packetType])(sessionId, buffer);
		}
	protected:
		std::unordered_map<uint16, PacketFunc> _packetFuncs;

	};

	class ChattingClientPacketHandler : public ClientPacketHandler<ChattingClientPacketHandler>
	{
	public :
		ChattingClientPacketHandler(class ChattingServer* owner, class RoomManager* roomMgr, class UserManager* userMgr) : _owner(owner), _roomMgr(roomMgr), _userMgr(userMgr)
		{
			_packetFuncs[ROOM_LIST_REQUEST_PACKET] = &ChattingClientPacketHandler::ProcessRoomListRequestPacket;

			_packetFuncs[CHAT_TO_ROOM_REQUEST_PACKET] = &ChattingClientPacketHandler::ProcessChatToRoomPacket; // Chat To Room Users
			_packetFuncs[CHAT_TO_USER_REQUEST_PACKET] = &ChattingClientPacketHandler::ProcessChatToUserPacket; // Chat To Room Users
		}
	private:
		// �Լ� ����
		NetworkErrorCode ProcessRoomListRequestPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		
		NetworkErrorCode ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		NetworkErrorCode ProcessChatToRoomPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		NetworkErrorCode ProcessChatToUserPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

		class ChattingServer* _owner;
		class RoomManager* _roomMgr;
		class UserManager* _userMgr;
	};

	// ���߿� ����� �� �߰� ����, �߰� ������ ����� �Ǹ� ��Ŷ ó���� ���� �κе� �� �༮�� 1���� ������ �� �Ŀ� ���� ���� ������ �����ؾ��Ѵ�.
	class LogInClientPacketHandler : public ClientPacketHandler<LogInClientPacketHandler>
	{
	public:
		LogInClientPacketHandler(class LogInServer* owner) : _owner(owner)
		{
			_packetFuncs[LOG_IN_REQUEST_PACKET] = &LogInClientPacketHandler::ProcessLogInPacket;
		}
	private:
		NetworkErrorCode ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		class LogInServer* _owner;
	};

}
