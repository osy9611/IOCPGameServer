#include "stdafx.h"


int main()
{
	std::cout << "���� �۵���" << std::endl;
	_IOCP.Initialize();
	_DBManager.ConnectToDBServer();
	_AreaManager.CreateMapText("../Map/World.txt");
	_GameObjectManager.Init();

	while (true)
	{
		_GameObjectManager.Update();
	}

	return 0;
}