#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "SceneBase.h"
#include "enemy.h"
#include "Vec2.h"

class SceneMain : public SceneBase
{
public:
	// �萔��`

	// �v���C���[�O���t�B�b�N������
	static constexpr int kDeadGraphicDivX = 3;
	static constexpr int kDeadGraphicDivY = 3;
	static constexpr int kDeadGraphicDivNum = kDeadGraphicDivX * kDeadGraphicDivY;

	// �v���C���[�O���t�B�b�N�T�C�Y
	static constexpr int kDeadGraphicSizeX = 75;
	static constexpr int kDeadGraphicSizeY = 75;

public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	virtual void init();

	// �I������
	virtual void end();

	// ���t���[���̏���
	virtual SceneBase* update();
	// ���t���[���̕`��
	virtual void draw();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }

	//�e�̐���
	virtual bool createShotPlayer(Vec2 pos);
	virtual bool createShotNormal(Vec2 pos);
	virtual bool createShotFall(Vec2 pos);
	virtual bool createShotBound(Vec2 pos);

	// �����蔻��
	virtual bool Col_ShotPlayer();
	virtual bool Col_EnemyPlayer();
	virtual bool Col_ShotEnemy();

private:

	// �L�����N�^�[�̃A�j���[�V����
	int m_animeNo;	// �\������ԍ�
	int m_animeFrame;

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hDeadGraphic[kDeadGraphicDivNum];
	int m_hEnemyGraphic;
	int m_hShotGraphic;

	// �T�E���h�n���h��
	 int m_hTestSound;
	 // �G�̗�
	 int m_EnemyHP;
	 // �G�̗�
	 //�v���C���[�����񂾉�
	 int m_DeadPlayerCount;
	 //�G�����񂾉�
	 int m_DeadEnemyCount;
	// �v���C���[
	Player m_player;
	// �G
	Enemy m_enemy;
	// �\���ʒu
	Vec2 m_pos;
	// �V���b�g
	//ShotBase* m_pShot[kShotMax];
	std::vector<ShotBase*> m_pShotVt;
	/*ShotBound* m_pShotBound[kShotMax];
	ShotNormal* m_pShotNormal[kShotMax];
	ShotFall* m_pShotFall[kShotMax];*/
};