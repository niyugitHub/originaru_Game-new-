#pragma once

#include "ShotBase.h"
#include "SceneMain.h"
class ShotNormal : public ShotBase
{
public:
	ShotNormal()
	{
	}
	virtual ~ShotNormal()
	{
	}

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �����o�ϐ��ɍ��W��ݒ肷�邽�߂̊֐�
	void setPlayerPos();
	// �X�V
	virtual void update();
private:
	// �v���C���[�̈ʒu��ۑ����郁���o�֐�
	Vec2 m_PlayerPos;
};