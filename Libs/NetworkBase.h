#pragma once
#include <unordered_map>
#include "RoomManager.h"
#include "Session.h"
#include "PacketDefine.h"
#include <iostream>

namespace C_Network
{

	/*-----------------------
			NetworkBase
	-----------------------*/
	class NetworkBase
	{
	public:
		NetworkBase(const NetAddress& netAddr, uint maxSessionCnt);
		virtual ~NetworkBase() = 0;

		virtual NetworkErrorCode Begin();
		virtual NetworkErrorCode End();

		virtual bool OnConnectionRequest(const SOCKADDR_IN& clientInfo);
		virtual void OnConnected(const SOCKADDR_IN& clientInfo, ULONGLONG sessionId); 
		virtual void OnDisconnected(ULONGLONG sessionId);
		virtual void OnError(int errCode, WCHAR* cause);
		virtual void OnRecv(C_Utility::CSerializationBuffer& buffer, ULONGLONG sessionId, uint16 type);

		void Send(ULONGLONG sessionId, C_Network::SharedSendBuffer buffer);
		const NetAddress GetNetAddr() const { return _netAddr; }
		bool CanConnect() { return !_sessionMgr->IsFull(); } // 현재는 세션이 초과되었는지만 확인.
	private:
		void ProcessAccept(Session* sessionPtr, DWORD transferredBytes = 0);
		void ProcessConnect(Session* sessionPtr, DWORD transferredBytes = 0);
		C_Network::NetworkErrorCode ProcessRecv(Session* sessionPtr, DWORD transferredBytes = 0);
		C_Network::NetworkErrorCode ProcessSend(Session* sessionPtr, DWORD transferredBytes = 0);
		bool ProcessDisconnect(Session* sessionPtr, DWORD transferredBytes = 0);

	private:
		volatile bool _monitoringFlag = false;
		volatile ULONG _sendCount = 0; // 1초에 몇 번씩 send 완료통지처리 / recv 완료통지 처리 체크,
		volatile ULONG _recvCount = 0;
		NetworkErrorCode ProcessMonitoring();
		
		//void AddSession();
		//void DeleteSession();
		void Dispatch(IocpEvent* iocpEvent, DWORD transferredBytes);
		void WorkerThread();
		HANDLE _iocpHandle;
		std::vector<std::thread> _workerThreads;
		std::thread _fileLogThread;

		std::thread _monitorThread;
		//std::unordered_map<ULONGLONG, SharedSession> _sessionMap; // [ Server - User Count / Client - Dummy Count]


	protected:
		Session* CreateSession(SOCKET sock, SOCKADDR_IN* pSockAddr);
		const NetAddress _netAddr; 
	private:
		std::unique_ptr<SessionManager> _sessionMgr;
		std::unique_ptr<C_Utility::FileLogger> _logger;

		// NetServer -> listen EndPoint
		// NetClient -> dest EndPoint
	};


	/*-----------------------
			NetServer
	-----------------------*/
	class NetServer : public NetworkBase
	{
	public:
		NetServer(const NetAddress& netAddr, uint maxSessionCnt);
		virtual ~NetServer();

		virtual C_Network::NetworkErrorCode Begin() override final;
		virtual C_Network::NetworkErrorCode End() override final;

	private:
		void AcceptThread();

	private:
		SOCKET _listenSock;
		std::thread _acceptThread;
	};



	/*-----------------------
			NetClient
	-----------------------*/
	class NetClient : public NetworkBase
	{
	public:
		NetClient(NetAddress destEndPoint, uint maxSessionCnt);
		virtual ~NetClient();
	};
}