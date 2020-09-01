#include "stdfx.h"

void PacketProc::CheckPacket(InputMemoryStream& inInputStream, int nSessionID)
{
	std::cout << "��Ŷ ����" << std::endl;
	short type;
	inInputStream.Read(type);

	switch (type)
	{
	case LOGIN_CHECK:
		std::cout << "�α��� äũ Ȯ����" << std::endl;
		_DBManager.SearchAccount(inInputStream, nSessionID);
		break;
	case SIGN_UP:
		std::cout << "ȸ������ Ȯ����" << std::endl;
		_DBManager.SignAccount(inInputStream, nSessionID);
		break;
	}
}