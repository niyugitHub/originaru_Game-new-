#pragma once

#include "ShotBase.h"
#include"Player.h"

class ShotFall : public ShotBase
{
public:
	ShotFall()
	{
	}
	virtual ~ShotFall()
	{
	}

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();

private:
	Player m_player;
};