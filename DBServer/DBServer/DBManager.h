#pragma once
class DBManager : public GlobalSingleton<DBManager>
{
public:
	DBManager();

	//���� �˻�
	bool SearchAccount(InputMemoryStream& inInputStream,int nSessionID);
	//ȸ������
	bool SignAccount(InputMemoryStream& inInputStream, int nSessionID);
	//ĳ���� ����
	bool CreateCharactor(InputMemoryStream& inInputStream);

	//ĳ���� ��ġ�� ����
	bool SearchCharatorPos(InputMemoryStream& inInputStream,int nSessionID);
private:
	bool SearchAcountResult(std::string _id, std::string _pw);
	void SetCharactor(OutputMemoryStream &os,std::string _id);
	bool SignAccountReseult(std::string _id, std::string _pw);
private:
	Database db;
	Table tbl;

	//���� ����
	char ErrStr[200];

	//ODBC�� �����ϱ� ���� ���ڿ�
	char CnnStr[200] = "DRIVER={MySQL ODBC 8.0 ANSI Driver};\
				   SERVER=localhost;\
				   DATABASE=iocpserver;\
				   USER=root;\
				   PASSWORD=1111;";
};

#define _DBManager DBManager::Singleton()