#include "LibsPch.h"
#include "UserManager.h"

C_Network::UserManager::UserManager(uint maxUserCnt) : C_Utility::ManagerPool<User>(maxUserCnt)
{
	InitializeSRWLock(&_mapLock);
}

C_Network::UserManager::~UserManager()
{
	C_Utility::ManagerPool<User>::~ManagerPool();
}

C_Network::User* C_Network::UserManager::GetUser(ULONGLONG userId)
{
	SRWLockGuard lockGuard(&_mapLock);

	auto userIter = _sessionToUserIdxMap.find(userId);
	if (userIter == _sessionToUserIdxMap.end())
		return nullptr;

	return _elementArr[userIter->second];
}
