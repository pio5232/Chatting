#pragma once

#include <functional>
#include "PacketDefine.h"
#include <unordered_map>
namespace C_Network
{
	/*---------------------------------------
				PacketHandler						// �������� �����Ѵ�.
	---------------------------------------*/
	class ClientPacketHandler
	{
	public:
		// uin16 Messageũ��� �����Ѵ�. ������ PacketHandler�� ó���ϰ� �Ǵ� ���� �ϳ��� ������ �����ͷ� ���� �� ó���ϱ� �����̴�.
		//, uint16) > ; // sessionId, Message ���� ����, Message ũ��.
		using PacketFunc = C_Network::NetworkErrorCode(*)(ULONGLONG, C_Utility::CSerializationBuffer&);//std::function<bool(ULONGLONG, char*)>;

		static void Init(class EchoServer* owner);
		static void Init(class ChattingServer* owner);

		// ����ȭ ���ۿ� �����͸� ä����! ���� ���ø��� Ȱ��.
		template <typename PacketType>
		static SharedSendBuffer MakePacket(uint16 packetType, PacketType& packet)//(uint16 packetType, uint16 packetSize, Types... args )
		{
			// TODO : CSerializationBuffer ���� Pool���� ������ ����ϵ��� �����.

			SharedSendBuffer sendBuffer = std::make_shared<C_Utility::CSerializationBuffer>(PACKET_SIZE_MAX);

			*sendBuffer << packet;

			return sendBuffer;
		}

		// ������ �� : CSerializationBuffer�� ���� Operator�� ���ǵǾ� ���� ���� ��쿡�� ����������Ѵ�.!! 
		// ����� ���� �ڷ����� ��쿡�� ���� Contents���� �����ε��� �� �� �ְ� �����س���.
		//template <typename T, typename... Types>
		//static void SetPacket(SharedSendBuffer& bufferRef, T t, Types... args)
		//{
		//	*bufferRef << t;
		//	SetPacket(bufferRef, args...);
		//}

		//template <typename T>
		//static void SetPacket(SharedSendBuffer& bufferRef, T t)
		//{
		//	*bufferRef << t;
		//}

		// processPacket -> packet ó��
		static C_Network::NetworkErrorCode ProcessPacket(ULONGLONG sessionId, uint16 packetType, C_Utility::CSerializationBuffer& buffer);

		static C_Network::NetworkErrorCode ProcessEchoPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

		static C_Network::NetworkErrorCode ProcessChatToRoomPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

		static C_Network::NetworkErrorCode ProcessChatToUserPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

	private:
		static std::unordered_map<uint16, PacketFunc> packetFuncs;
		//static class NetworkBase* _owner;

		// �׽�Ʈ ������ echoServer ���� �ʿ�.
		static class EchoServer* _echoOwner;

		static class ChattingServer* _owner;
	};
}
