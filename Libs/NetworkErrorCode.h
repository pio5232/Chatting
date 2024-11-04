#pragma once

namespace C_Network
{
	enum class NetworkErrorCode : uint16
	{
		NONE = 0, // ���� ó��.
		WSA_START_UP_ERROR, 

		// SERVER ERROR CODE
		CREATE_COMPLETION_PORT_FAILED = 100, // 
		CREATE_SOCKET_FAILED,
		LISTEN_FAILED,
		BIND_FAILED,
		//
		 
		// CLIENT ERROR CODE
		CLIENT_CONNECT_FAILED,
		
		// COMMON
		SET_SOCK_OPT_FAILED,

		RECV_BUF_OVERFLOW = 200, // ���� ���۰� ������ų �� �ִ� ũ�⺸�� ũ�� transferredBytes�� �� �� �߻���.
		RECV_BUF_DEQUE_FAILED, // ���� �Ͼ�� �ȵǴ� ����. �߻����� ���� ������ ���踦 Ȯ���ؾ���.

		SEND_LEN_ZERO = 300, // 0 Byte Send
		MESSAGE_SEND_FAILED,// �޽����� SEND �����ߴ�.. 

		//

		CANNOT_FIND_PACKET_FUNC = 1000, // PacketHandler�� �ش� ��Ŷ�� ó���� �� �ִ� �Լ��� ��ϵ��� ����.
	};
}