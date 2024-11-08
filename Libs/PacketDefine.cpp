#include "LibsPch.h"
#include "PacketDefine.h"
#include "CSerializationBuffer.h"

serializationBuffer& operator<< (serializationBuffer& serialBuffer, C_Network::PacketHeader& packetHeader)
{
	serialBuffer << packetHeader.size << packetHeader.type;

	return serialBuffer;
}

serializationBuffer& operator<<(serializationBuffer& serialBuffer, C_Network::ChatUserRequestPacket& chatUserRequestPacket)
{
	serialBuffer << chatUserRequestPacket.size << chatUserRequestPacket.type << chatUserRequestPacket.targetUserId << chatUserRequestPacket.messageLen;
	serialBuffer.PutData(chatUserRequestPacket.payLoad, chatUserRequestPacket.messageLen);
	
	return serialBuffer;
}

serializationBuffer& operator<<(serializationBuffer& serialBuffer, C_Network::ChatUserResponsePacket& chatUserResponsePacket)
{
	serialBuffer << chatUserResponsePacket.size << chatUserResponsePacket.type << chatUserResponsePacket.sendUserId << chatUserResponsePacket.messageLen;
	serialBuffer.PutData(chatUserResponsePacket.payLoad, chatUserResponsePacket.messageLen);

	return serialBuffer;
}

serializationBuffer& operator<<(serializationBuffer& serialBuffer, C_Network::ChatRoomResponsePacket& chatUserResponsePacket)
{
	serialBuffer << chatUserResponsePacket.size << chatUserResponsePacket.type;
	return serialBuffer;
	// TODO: 여기에 return 문을 삽입합니다.
}

serializationBuffer& operator<<(serializationBuffer& serialBuffer, C_Network::ChatRoomRequestPacket& chatRoomRequestPacket)
{
	serialBuffer << chatRoomRequestPacket.size << chatRoomRequestPacket.type << chatRoomRequestPacket.roomNum << chatRoomRequestPacket.messageLen;
	serialBuffer.PutData(chatRoomRequestPacket.payLoad, chatRoomRequestPacket.messageLen);

	return serialBuffer;
}

serializationBuffer& operator<<(serializationBuffer& serialBuffer, C_Network::LogInRequestPacket& logInPacket)
{
	serialBuffer << logInPacket.size << logInPacket.type << logInPacket.logInId << logInPacket.logInPw;

	return serialBuffer;
}

serializationBuffer& operator<<(serializationBuffer& serialBuffer, C_Network::LogInResponsePacket& logInResponsePacket)
{
	serialBuffer << logInResponsePacket.size << logInResponsePacket.type << logInResponsePacket.userId;

	return serialBuffer;
}



// ------------------------------  operator >>  (빼내기), PacketHeader 뺄 필요 없다. --------------------------------

serializationBuffer& operator>>(serializationBuffer& serialBuffer, C_Network::ChatUserRequestPacket& chatUserRequestPacket)
{
	serialBuffer >> chatUserRequestPacket.targetUserId >> chatUserRequestPacket.messageLen;
	serialBuffer.GetData(chatUserRequestPacket.payLoad, chatUserRequestPacket.messageLen);

	return serialBuffer;
}

serializationBuffer& operator>>(serializationBuffer& serialBuffer, C_Network::ChatUserResponsePacket& chatUserResponsePacket)
{
	serialBuffer >> chatUserResponsePacket.sendUserId >> chatUserResponsePacket.messageLen;
	serialBuffer.GetData(chatUserResponsePacket.payLoad, chatUserResponsePacket.messageLen);

	return serialBuffer;
}

serializationBuffer& operator>>(serializationBuffer& serialBuffer, C_Network::ChatRoomRequestPacket& chatRoomRequestPacket)
{
	serialBuffer >> chatRoomRequestPacket.roomNum >> chatRoomRequestPacket.messageLen;
	serialBuffer.GetData(chatRoomRequestPacket.payLoad, chatRoomRequestPacket.messageLen);
	
	return serialBuffer;
}

serializationBuffer& operator>>(serializationBuffer& serialBuffer, C_Network::LogInRequestPacket& logInRequestPacket)
{
	serialBuffer >> logInRequestPacket.logInId >> logInRequestPacket.logInPw;

	return serialBuffer;
}

serializationBuffer& operator>>(serializationBuffer& serialBuffer, C_Network::LogInResponsePacket& logInResponsePacket)
{
	serialBuffer >> logInResponsePacket.userId;

	return serialBuffer;
}
