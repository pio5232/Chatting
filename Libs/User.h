#pragma once

namespace C_Network
{
	// Session - Network / User - Contents ����.
	class User
	{
	public:
		User(ULONGLONG sessionId);
	private:
		ULONGLONG _sessionId; // Session�� ������ �� �ִ� ����. �̰ɷ� Network �۾��� ��û�Ѵ�.
		
		std::string _nickName; // ���� id
		uint _winCnt;
		uint _loseCnt;
	};
}
