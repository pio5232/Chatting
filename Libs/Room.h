#pragma once

#include "User.h"
namespace C_Network
{
	class Room
	{
	public :
		Room(class NetworkBase* owner, int maxUserCnt);

		void EnterRoom(ULONGLONG userId);
		void LeaveRoom(ULONGLONG userId);

		NetworkErrorCode SendToRoom(SharedSendBuffer sharedSendBuffer);

	private:
		uint _curUserCnt;
		uint _maxUserCnt;
		uint _roomNumber; // �� ��° ������ Ȯ���Ѵ�..

		std::vector<User*> _userList;
		
		class NetworkBase* _owner;
	};
}
