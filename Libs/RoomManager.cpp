#include "LibsPch.h"
#include "RoomManager.h"
#include "NetworkBase.h"

C_Network::RoomManager::RoomManager(C_Network::NetworkBase* owner, uint maxRoomCount, uint maxRoomUserCnt) : _owner(owner), _maxRoomUserCnt(maxRoomUserCnt)
{
	_roomList.reserve(maxRoomCount);

	for (int i = 0; i < maxRoomCount; i++)
	{
		// TODO : ROOM POOL »ç¿ë
		Room* room = new Room(_owner, _maxRoomUserCnt);

		_roomList.push_back(room);
	}
}

C_Network::RoomManager::~RoomManager()
{
	// TODO : USEI TO ROOM POOL 
	for (auto roomPtr : _roomList)
	{
		delete roomPtr;
	}
}

C_Network::NetworkErrorCode C_Network::RoomManager::SendToAllUser(C_Utility::CSerializationBuffer& buffer)
{
	return NetworkErrorCode();
}

C_Network::NetworkErrorCode C_Network::RoomManager::SendToRoom(C_Utility::CSerializationBuffer& buffer, uint16 roomNum)
{
	return NetworkErrorCode();
}
