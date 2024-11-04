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
		const uint _maxRoomUserCnt; // room당 최대 user 수
		std::vector<Room*> _roomList;

		ServerBase* _owner;
	};
}