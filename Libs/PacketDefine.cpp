#include "LibsPch.h"
#include "PacketDefine.h"
#include "CSerializationBuffer.h"

serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::EchoPacket& echoPacket)
{
	serialBuffer << echoPacket.size << echoPacket.data;

	return serialBuffer;
}

serializationBuffer& operator<<(serializationBuffer& serialBuffer, C_Network::ChatRoomRequestPacket& chattingPacket)
{
	serialBuffer << chattingPacket.size << chattingPacket.messageLen;

	if (chattingPacket.messageLen > 0)
		serialBuffer.PutData(chattingPacket.payLoad, chattingPacket.messageLen);

	return serialBuffer;
	// TODO: 여기에 return 문을 삽입합니다.
}
