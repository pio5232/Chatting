#pragma once

namespace C_Network
{
	// Session - Network / User - Contents 영역.
	class User
	{
	public:
		User(ULONGLONG sessionId);
	private:
		ULONGLONG _sessionId; // Session과 연결할 수 있는 수단. 이걸로 Network 작업을 요청한다.
		ULONGLONG _userId;
		std::string _nickName; // 유저 id
		uint _winCnt;
		uint _loseCnt;
	};
}
