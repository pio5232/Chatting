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

		// Accept������ ���� �ʾҴٰ� ���� ��찡 �������� �ʴ´�.
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
