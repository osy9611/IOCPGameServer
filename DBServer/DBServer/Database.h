#pragma once
#define _CRT_SECURE_NO_WARNING

#define CATCHERROR(ptr,a)	catch(_com_error &e)\
							{\
								ErrorHandler(e,m_ErrStr);\
								ptr=NULL;\
								return a;\
							}

#define CATCHERRGET			catch(_com_error &e)\
							{\
								ErrorHandler(e,m_ErrStr);\
								sprintf(m_ErrStr,"%s\n**For Field Name:%s",m_ErrStr,FieldName);\
								return 0;\
							}

#import "C:\Program Files\Common Files\System\ado\msado15.dll" \
              rename("EOF", "EndOfFile")

typedef ADODB::_RecordsetPtr	RecPtr;
typedef ADODB::_ConnectionPtr	CnnPtr;

class Database;
class Table;

class Database
{
public:
	CnnPtr m_Cnn;
	char m_ErrStr[500];
	Database();
	bool Open(const char* UserName, const char* Pwd, const char* CnnStr);
	bool OpenTbl(int Mode, char* CmdStr, Table& Tbl);
	bool Execute(char* CmdStr);
	bool Execute(const char* CmdStr, Table& Tbl);
	void GetErrorErrStr(char* ErrStr);
};

class Table
{
public:
	RecPtr m_Rec;
	char m_ErrStr[500];
	Table();
	void GetErrorErrStr(char* ErrStr);
	int ISEOF();

	//DirectX�� ���� ������Ʈ ������Ʈ�� ��������ִ�.
	HRESULT MoveNext();
	HRESULT MovePrevious();
	HRESULT MoveFirst();
	HRESULT MoveLast();
	int AddNew();
	int Update();
	int Add(char* FieldName, char* FieldValue);
	int Add(char* FieldName, int FieldValue);
	int Add(char* FieldName, float FieldValue);
	int Add(char* FieldName, double FieldValue);
	int Add(char* FieldName, long FieldValue);
	bool Get(char* FieldName, char* FieldValue);
	template<typename T>
	bool Get(char* FieldName, T& FieldValue)
	{
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"�Ϲ� �б�� �⺻ ������ ���� �� �����մϴ�");

		_variant_t vtValue;
		vtValue = m_Rec->Fields->GetItem(FieldName)->GetValue();
		FieldValue = vtValue.intVal;

		//CATCHERRGET
			//sprintf(m_ErrStr, "Successs");
		return true;
	}

	bool Get(char* FieldName, std::string& inString);
};

