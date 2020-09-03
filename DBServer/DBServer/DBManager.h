#pragma once
class DBManager : public GlobalSingleton<DBManager>
{
public:
	DBManager();

	//���� �˻�
	bool SearchAccount(InputMemoryStream& inInputStream,int nSessionID);
	bool SignAccount(InputMemoryStream& inInputStream, int nSessionID);
	bool a(std::string _id, std::string _pw);
	bool a1(std::string _id, std::string _pw);
private:
	bool SearchAcountResult(std::string _id, std::string _pw);
	
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
				   PASSWORD=@ppgk38629;";
};

#define _DBManager DBManager::Singleton()