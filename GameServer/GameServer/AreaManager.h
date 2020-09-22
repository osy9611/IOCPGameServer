#pragma once



struct MapData
{
	float sx, sy, ex, ey;
	std::vector<ColliderData> colData;

	void Reset()
	{
		colData.clear();
	}

	void PushColData(ColliderData _data)
	{
		colData.push_back(_data);
	}
};

class AreaManager :public GlobalSingleton<AreaManager>
{
public:
	AreaManager();
	void CreateMapText(const char* filename);

	//ó�� ĳ���� ��ġ�� ����ϱ� ����
	bool SearchArea(Vector3 _pos,int& index);

	//��ġ üũ
	bool InAreaCheck(int index,Vector3 _pos);
private:
	std::vector<MapData> data;
};

#define _AreaManager AreaManager::Singleton()