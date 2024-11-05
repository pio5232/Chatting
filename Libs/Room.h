#pragma once

#include "User.h"
namespace C_Network
{
	class Room
	{
	public :
		Room(class ServerBase* owner, int maxUserCnt);

		void EnterRoom(ULONGLONG userId);
		void LeaveRoom(ULONGLONG userId);

		uint16 GetCurUserCnt() const { return _curUserCnt; }
		uint16 GetMaxUserCnt() const { return _curUserCnt; }
		uint16 GetRoomNum() const { return _roomNumber; }
		ULONGLONG GetOwnerId() const { return _ownerId; }

		NetworkErrorCode SendToRoom(SharedSendBuffer sharedSendBuffer);

	private:
		ULONGLONG _ownerId; // == userId;
		uint16 _curUserCnt;
		uint16 _maxUserCnt;
		uint16 _roomNumber; // 몇 번째 방인지 확인한다..

		std::vector<User*> _userList;
		
		class ServerBase* _owner;
	};
}
