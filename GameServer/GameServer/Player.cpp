#include"stdafx.h"

void Player::Update(float dTime)
{
	float vx = GetVelocity().mX;
	float vz = GetVelocity().mZ;

	if (PT == Move)
	{
		if (!_AreaManager.InAreaCheck(AreaIndex, GetPosition()))
		{
			_AreaManager.SearchArea(GetPosition(), AreaIndex);
			std::cout << "������ " << AreaIndex << " �� �迭�� �̵�" << std::endl;
		}
		SetPosition(GetPosition() + GetVelocity() * (Data.Speed * dTime));
		CollisionCheck();
	}
}

void Player::CollisionCheck()
{
	MapData it = _AreaManager.GetCollisionObjects(AreaIndex);
	for (int i = 0; i < it.colData.size(); ++i)
	{
		Vector3 targetPosition(it.colData[i].GetPosition().mX, 0, it.colData[i].GetPosition().mZ);
		float targetRadius = it.colData[i].GetRadius();

		Vector3 delta = targetPosition - GetPosition();
		float distSq = delta.LengthSq();
		float collisionDist = (1 + targetRadius);
		if (distSq < (collisionDist * collisionDist))
		{
			Vector3 dirToTarget = delta;
			dirToTarget.Normaize();
			Vector3 acceptableDeltaFromSourceToTarget = dirToTarget * collisionDist;

			SetPosition(targetPosition - acceptableDeltaFromSourceToTarget);

			Vector3 relVel = GetVelocity();

			float relVelDotDir = Dot(relVel, dirToTarget);

			if (relVelDotDir > 0.f)
			{
				Vector3 impulse = relVelDotDir * dirToTarget;
				Vector3 mVelocity = GetVelocity();
				mVelocity -= impulse;
				mVelocity *= 0.1f;
				SetVelocity(mVelocity);
			}
		}
	}
}

void Player::CalcDamage(float Damage)
{

}

void Player::Write(OutputMemoryStream &os)
{
	std::cout << Data.Name << std::endl;
	os.Write(Data.Name);
	os.Write(static_cast<short>(PT));
	os.Write(GetPosition());
	os.Write(GetVelocity());
}

void Player::Read(InputMemoryStream& is)
{
	//���Ⱚ,���� ��ġ,ȸ������ ����
	Vector3 dir, pos;
	short state;
	is.Read(pos);
	is.Read(dir);
	is.Read(state);
	SetData(pos, dir,state);
}


void Player::SetData(Vector3 _pos, Vector3 _dir,short _playerState)
{
	prevData.SetData(GetPosition(), GetVelocity(), GetRotation());
	//SetPosition(_pos);
	SetVelocity(_dir);
	PT = static_cast<PlayerState>(_playerState);
}