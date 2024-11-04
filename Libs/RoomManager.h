#pragma once

#include "Room.h"

namespace C_Network
{
	class RoomManager
	{
	public:
		RoomManager(class ServerBase* owner, uint maxRoomCount, uint maxRoomUserCnt);
		~RoomManager();

		NetworkErrorCode SendToAllUser(C_Utility::CSerializationBuffer& buffer);
		NetworkErrorCode SendToRoom(C_Utility::CSerializationBuffer& buffer, uint16 roomNum);

	private:
		const uint _maxRoomUserCnt; // room�� �ִ� user ��
		std::vector<Room*> _roomList;

		ServerBase* _owner;
	};
}