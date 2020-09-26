#include "stdafx.h"

AreaManager::AreaManager()
{
	
}

void AreaManager::CreateMapText(const char* filename)
{
	std::ifstream ifs(filename);
	if (ifs.fail())
	{
		std::cout << "����� ������ ���ų� ���� �����Դϴ�" << std::endl;
		std::cout << filename << std::endl;
		return;
	}

	MapData _data;
	Vector3 _pos;
	int _ct;
	float _radius;
	int nodeCount, colCount;
	std::string line;

	//ù �ٿ��� ���� ������ ����� ������ ���ԵǾ� �ִ�.
	getline(ifs, line);
	sscanf(line.data(), "%d;", &nodeCount);

	//����� ������ ŭ for���� ���� �����͸� �о�´�.
	for (int i = 0; i < nodeCount; ++i)
	{
		ColliderData _colData;
		//���� ù ��ǥ�� �� ��ǥ
		getline(ifs, line);
		sscanf(line.data(), "%f;%f;%f;%f;", &_data.sx, &_data.sy, &_data.ex, &_data.ey);
		//�ʿ� �ִ� ������Ʈ ���� ������
		getline(ifs, line);
		sscanf(line.data(), "%d;", &colCount);

		//���� �ʿ� �ִ� ������Ʈ���� ������ 0�� �ƴϸ� ������Ʈ�� �о�´�
		if (colCount > 0)
		{
			for (int j = 0; j < colCount; ++j)
			{
				getline(ifs, line);
				sscanf(line.data(), "%f;%f;%f;%d;%f;", &_pos.mX, &_pos.mY, &_pos.mZ, &_ct, &_radius);
				_colData.SetData(_pos, _radius, _ct);
				_data.PushColData(_colData);
			}
		}
		data.push_back(_data);
		_data.Reset();
	}

	std::cout << "�� ������ �ε� �Ϸ�" << std::endl;
}

bool AreaManager::SearchArea(Vector3 _pos, int&index)
{
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i].sx <= _pos.mX && _pos.mX  <= data[i].ex&&
			data[i].ey <= _pos.mZ && _pos.mZ <= data[i].sy)
		{
			index = i;
			break;
		}
	}

	return false;
}

bool AreaManager::InAreaCheck(int index, Vector3 _pos)
{
	if (data[index].sx <= _pos.mX && _pos.mX <= data[index].ex&&
		data[index].ey <= _pos.mZ && _pos.mZ <= data[index].sy)
	{
		return true;
	}
	else
	{
		return false;
	}
}