#pragma once
#include "User.h"

namespace C_Network
{
	class UserManager
	{
	public:
		UserManager(uint maxSessionCnt);
		~UserManager();

	private:

		// Accept에서는 차지 않았다가 차는 경우가 존재하지 않는다.
		// [ Server - User Count / Client - Dummy Count], <id, index>
		std::unordered_map<ULONGLONG, ULONGLONG> _userToSessionMap;

		std::vector<Session*> _userArr;
		std::stack<uint> _availableSessionidxList;

		SRWLOCK _mapLock;
		SRWLOCK _indexListLock;
		uint _maxSessionCnt;

		volatile ULONG _curSessionCnt;

	};
}
