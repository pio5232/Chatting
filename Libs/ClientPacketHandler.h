#pragma once

#include <functional>
#include "PacketDefine.h"
#include <unordered_map>
namespace C_Network
{
	/*---------------------------------------
				BasePacketHandler						// 서버마다 상속받아서 사용하도록 한다..
	---------------------------------------*/
	template <typename PacketHandlerType>
	class ClientPacketHandler
	{
	public:
		ClientPacketHandler() { _packetFuncs.clear(); }
		// uin16 Message크기는 제외한다. 어차피 PacketHandler가 처리하게 되는 것은 하나의 완전한 데이터로 왔을 때 처리하기 때문이다.
		//, uint16) > ; // sessionId, Message 내용 버퍼, Message 크기.
		using PacketFunc = C_Network::NetworkErrorCode(PacketHandlerType::*)(ULONGLONG, C_Utility::CSerializationBuffer&);//std::function<bool(ULONGLONG, char*)>;

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
		// 함수 정의
		NetworkErrorCode ProcessRoomListRequestPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		
		NetworkErrorCode ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		NetworkErrorCode ProcessChatToRoomPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);
		NetworkErrorCode ProcessChatToUserPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

		class ChattingServer* _owner;
		class RoomManager* _roomMgr;
		class UserManager* _userMgr;
	};

	// 나중에 만들게 될 중계 서버, 중계 서버가 생기게 되면 패킷 처리에 대한 부분도 이 녀석이 1차로 검증을 한 후에 메인 로직 서버에 전달해야한다.
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
