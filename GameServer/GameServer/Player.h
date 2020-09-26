#pragma once

class Monster;

enum PlayerState
{
	Idle,
	Move,
	Attack
};

struct PlayerData
{
	std::string Name;
	float Speed;
	float storeSpeed;
	float Hp, Mp;
	float Attack;

	void Init(std::string _name, float _speed, float _hp, float _attack)
	{
		Name = _name;
		Speed = _speed;
		storeSpeed = _speed;
		Hp = _hp;
		Mp = 100;
		Attack = _attack;
	}

	void ResetSpeed()
	{
		Speed = 0;
	}

	void SetSpeed()
	{
		Speed = storeSpeed;
	}
};

//��Ŷ �ޱ� ������ ������
struct PrevData
{
	Vector3 pos,dir;
	float rot;

	void SetData(Vector3 _pos, Vector3 _dir, float _rot)
	{
		pos = _pos;
		dir = _dir;
		rot = _rot;
	}
};

class Player : public GameObject
{
public:
	Player() 
	{ 
		_AreaManager.SearchArea(GetPosition(), AreaIndex); 
		std::cout << "���� �� ��ġ �迭 ��ȣ : " << AreaIndex << std::endl;
 	}
	~Player() {}
	void SetData(PlayerData _data, Vector3 _pos) { Data = _data; SetPosition(_pos); }

	void Update(float dTime);

	const char* GetName() { return Data.Name.c_str(); }

	float GetSpeed() { return Data.Speed; }
	void CalcDamage(float Damage);

	void SetData(Vector3 _pos, Vector3 _dir,short _playerState);

	void Write(OutputMemoryStream &os);
	void Read(InputMemoryStream& is);
private:
	void CollisionCheck();
private:
	//�÷��̾� ������
	PlayerData Data;
	//�÷��̾��� ���� ������
	PrevData prevData;

	//���� ������ �迭 �ε���
	int AreaIndex = 0;
	PlayerState PT = Attack;

	float rotDir = 0;
	float dTime = 0;
	float timeStamp = 0;
	float latency = 0;
};

typedef std::shared_ptr<Player> PlayerPtr;