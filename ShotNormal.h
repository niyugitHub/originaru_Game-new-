#pragma once

#include "ShotBase.h"

//#include "SceneMain.h"

class SceneMain;

class ShotNormal : public ShotBase
{
public:
	ShotNormal();

	virtual ~ShotNormal()
	{
	}

	
	virtual void setPos(Vec2 pos) { m_PlayerPos = pos; }

	//�V���b�g�J�n
	virtual void start(Vec2 pos);

	// �X�V
	virtual void update();
private:

	SceneMain* m_pMain;
	// �v���C���[�̈ʒu��ۑ����郁���o�ϐ�
	Vec2 m_PlayerPos;

	Vec2 m_vec;
};