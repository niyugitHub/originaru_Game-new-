#pragma once

#include "ShotBase.h"

//#include "SceneMain.h"

class SceneMain;

class ShotNormal : public ShotBase
{
public:
	ShotNormal()
	{
	}
	virtual ~ShotNormal()
	{
	}

	// SceneMain��ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	//�V���b�g�J�n
	virtual void start(Vec2 pos);

	// �X�V
	virtual void update();
private:

	SceneMain* m_pMain;
	// �v���C���[�̈ʒu��ۑ����郁���o�֐�
	Vec2 m_PlayerPos;

	Vec2 m_vec;
};