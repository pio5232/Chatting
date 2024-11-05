#pragma once

#include <functional>
#include "PacketDefine.h"
#include <unordered_map>

namespace C_Network
{
	/*---------------------------------------
				PacketHandler						// �������� �����Ѵ�.
	---------------------------------------*/
	template <typename PacketHandlerType>
	class ClientPacketHandler
	{
	public:
		// uin16 Messageũ��� �����Ѵ�. ������ PacketHandler�� ó���ϰ� �Ǵ� ���� �ϳ��� ������ �����ͷ� ���� �� ó���ϱ� �����̴�.
		//, uint16) > ; // sessionId, Message ���� ����, Message ũ��.
		using PacketFunc = C_Network::NetworkErrorCode(PacketHandlerType::*)(ULONGLONG, C_Utility::CSerializationBuffer&);//std::function<bool(ULONGLONG, char*)>;

		// ����ȭ ���ۿ� �����͸� ä����! ���� ���ø��� Ȱ��.
		template <typename PacketType>
		SharedSendBuffer MakePacket(uint16 packetType, PacketType& packet)//(uint16 packetType, uint16 packetSize, Types... args ) 
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

		NetworkErrorCode ProcessPacket(ULONGLONG sessionId, uint16 packetType, C_Utility::CSerializationBuffer& buffer)
		{
			if (packetFuncs.find(packetType) == packetFuncs.end())
				return C_Network::NetworkErrorCode::CANNOT_FIND_PACKET_FUNC;

			return ((reinterpret_cast<PacketHandlerType*>(this))->*packetFuncs[packetType])(sessionId, buffer);
		}
	private:

		//C_Network::NetworkErrorCode ProcessChatToRoomPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

		//C_Network::NetworkErrorCode ProcessChatToUserPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

		//C_Network::NetworkErrorCode ProcessLogInPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

	protected:
		
		std::unordered_map<uint16, PacketFunc> packetFuncs;
		//static class NetworkBase* _owner;

		// �׽�Ʈ ������ echoServer ���� �ʿ�.
		//class ChattingServer* _owner;
	};

	class EchoClientPacketHandler : public ClientPacketHandler<EchoClientPacketHandler>
	{
	public: 
		// ��ӹ��� �Լ����� ��� �� ������ Ÿ�Կ� �°� �����ؼ� ����Ѵ�.
		EchoClientPacketHandler(class EchoServer* owner) : _owner(owner)
		{
			packetFuncs[ECHO_PACKET] = &EchoClientPacketHandler::ProcessEchoPacket; // Echo
		}
		
	private:
		C_Network::NetworkErrorCode ProcessEchoPacket(ULONGLONG sessionId, C_Utility::CSerializationBuffer& buffer);

		class EchoServer* _owner;

		//class EchoServer* _owner;
	};
}
