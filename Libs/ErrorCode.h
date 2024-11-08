#pragma once

// Packet 처리 과정에서 발생한 에러 또는 네트워크가 아닌 에러.
enum class ErrorCode : uint16 // 클라에서 요청한 작업이 서버에서 잘 처리가 되었는지 진행 결과를 출력, 전송
{
	NONE = 0, // 정상

	CREATE_ROOM_FAILED,
	CANNOT_FIND_ROOM, // roomNum으로 room을 찾지 못함.

	SESSION_USER_NOT_CONN, // UserManager에서 관리하는 sessionId <-> userIdx 에 대한 맵핑이 제대로 되지 않음 (여러가지 이유로)
	CANNOT_FIND_PACKET_FUNC, // PacketHandler가 해당 패킷에 대한 함수를 처리할 수 없음.
	ALLOC_FAILED,	// malloc, new 등 메모리 할당 실패
};