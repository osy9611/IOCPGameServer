#include "stdafx.h"


void DBManager::ConnectToDBServer()
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "��Ĺ ���� ����" << std::endl;
	}

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(DBPORT);
	int ret = connect(m_socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (ret == SOCKET_ERROR)
	{
		std::cout << "���� ����" << std::endl;
	}

	FD_ZERO(&read);
	FD_ZERO(&write);
	FD_SET(m_socket, &read);
	Run();
}

void DBManager::Run()
{
	while (true)
	{

		int ret = select(m_socket +1, &read, &write, NULL, NULL);
		if (ret == SOCKET_ERROR)
		{
			std::cout << "Select ����" << std::endl;
			break;
		}

		if (FD_ISSET(m_socket, &read))
		{
			//������ �ޱ�
			ret = recv(m_socket, (char*)&cBuffer, MAX_BUF_SIZE, 0);

			if (ret == 0 || ret == SOCKET_ERROR)
			{
				continue;
			}
			
			Handle_Receive(cBuffer, ret);
		}
	}

}

void DBManager::Send(OutputMemoryStream& os)
{
	int ret = send(m_socket, (char*)os.GetBufferPtr(), os.GetDataLength(), 0);
}

void DBManager::SetLoginPacket(InputMemoryStream& io, int nSessionID)
{
	std::string id;
	std::string pw;
	io.Read(id);
	io.Read(pw);

	OutputMemoryStream os;
	os.Write((short)LOGIN_CHECK);
	os.Write(id);
	os.Write(pw);
	os.Write((short)nSessionID);
	os.SetSize();
	Send(os);
}


void DBManager::SetLoginResultPacket(InputMemoryStream& io)
{
	bool result;
	short SessionID;
	io.Read(result);
	io.Read(SessionID);

	OutputMemoryStream os;
	os.Write((short)LOG_IN_RESULT);
	os.Write(result);
	os.SetSize();
	_IOCP.SendPlayer(SessionID, os.GetBufferPtr(), os.GetDataLength());
}

void DBManager::SetSignUpPacket(InputMemoryStream& io, int nSessionID)
{
	std::string id;
	std::string pw;
	io.Read(id);
	io.Read(pw);

	OutputMemoryStream os;
	os.Write((short)SIGN_UP);
	os.Write(id);
	os.Write(pw);
	os.Write((short)nSessionID);
	os.SetSize();
	Send(os);
}

void DBManager::SetSignUpResultPacket(InputMemoryStream& io)
{
	bool result;
	short SessionID;
	io.Read(result);
	io.Read(SessionID);

	OutputMemoryStream os;
	os.Write((short)SIGN_UP_RESULT);
	os.Write(result);
	os.SetSize();
	_IOCP.SendPlayer(SessionID, os.GetBufferPtr(), os.GetDataLength());
}

void DBManager::Handle_Receive(const char * data, int size)
{
	/*
	��Ʈ��ũ Ư���� Ŭ���̾�Ʈ���� ������ �����͸� ������ ��û�� ���ÿ� ���� �� �ϸ�, ���������� Ŭ���̾�Ʈ���� ������ ������� ���� �ʴ´�.
	�Ѳ����� ��� ���� ���� �ְ� ������ ������ ���� �� �ִ�.(��, Ŭ���̾�Ʈ�� Send�� �� �� �ߴµ�, ���������� Receive�� �� ���� �߻��Ѵ�.)
	�̷�, ��츦 ó���ϱ� ���ؼ� ���� ���� ������ mPacketBuffer�� ������ �� Ŭ���̾�Ʈ�� ���ÿ� ������ ��û�ϸ鼭 ������ �� ���� �� �����Ƿ�,
	�� ��û���� ������ ó���Ѵ�. �׸��� Ŭ���̾�Ʈ�� ���� �������� �Ϻ� ������ ���, �켱�� ó������ �ʰ� ���ܳ��Ҵٰ� ������ ���� �����Ϳ� �����Ͽ�
	ó���Ѵ�.
	*/

	//���� �����͸� ��Ŷ ���ۿ� ����
	memcpy(&mPacketBuffer[mPacketBufferMark], data, size);

	int nPacketData = mPacketBufferMark + size;
	int nReadData = 0;

	while (nPacketData > 0)	//���� �����͸� ��� ó���� ������ �ݺ�
	{
		//���� �����Ͱ� ��Ŷ ������� ������ �ߴ�
		if (nPacketData < sizeof(PacketHeader))
		{
			break;
		}

		PacketHeader* pHeader = (PacketHeader*)&mPacketBuffer[nReadData];

		if (pHeader->size <= nPacketData)	//ó���� �� �ִ� ��ŭ �����Ͱ� �ִٸ� ��Ŷ�� ó��
		{
			InputMemoryStream io((char*)data, pHeader->size);
			_PacketProc.CheckPacket(io);
			nPacketData -= pHeader->size;
			nReadData += pHeader->size;
		}
		else
		{
			break;	//��Ŷ���� ó���� �� ���� ��ŭ�� �ƴϸ� �ߴ�
		}
	}

	if (nPacketData > 0)
	{
		char TempBuffer[MAX_RECEIVE_BUFFER_LEN * 2] = { 0, };
		memcpy(&TempBuffer[0], &mPacketBuffer[nReadData], nPacketData);
		memcpy(&mPacketBuffer[0], &TempBuffer[0], nPacketData);
	}

	//���� ������ ���� �����ϰ� ������ �ޱ� ��û
	mPacketBufferMark = nPacketData;
}
