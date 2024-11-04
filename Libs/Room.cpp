#include "LibsPch.h"
#include "Room.h"
#include "NetworkBase.h"

C_Network::Room::Room(C_Network::ServerBase* owner, int maxUserCnt) :_owner(owner), _maxUserCnt(maxUserCnt), _curUserCnt(0)
{
	static uint roomGenerator = 0;
	
	_roomNumber = ++roomGenerator;

	_userList.reserve(maxUserCnt);
}

void C_Network::Room::EnterRoom(ULONGLONG userId)
{
	
}

void C_Network::Room::LeaveRoom(ULONGLONG userId)
{
}
