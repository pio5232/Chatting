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

		NetworkErrorCode SendToRoom(SharedSendBuffer sharedSendBuffer);

	private:
		uint _curUserCnt;
		uint _maxUserCnt;
		uint _roomNumber; // 몇 번째 방인지 확인한다..

		std::vector<User*> _userList;
		
		class ServerBase* _owner;
	};
}
