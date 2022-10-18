#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "SceneBase.h"
#include "enemy.h"

class SceneMain : public SceneBase
{
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

	//�e�̐���
	virtual bool createShotPlayer(Vec2 pos);
	virtual bool createShotNormal(Vec2 pos);
	virtual bool createShotFall(Vec2 pos);
	virtual bool createShotBound(Vec2 pos);

	// �����蔻��
	virtual bool Col_Shot();
	virtual bool Col_Enemy();
private:

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hEnemyGraphic;
	int m_hShotGraphic;

	// �T�E���h�n���h��
	 int m_hTestSound;
	// �v���C���[
	Player m_player;
	// �G
	Enemy m_enemy;
	// �V���b�g
	//ShotBase* m_pShot[kShotMax];
	std::vector<ShotBase*> m_pShotVt;
	/*ShotBound* m_pShotBound[kShotMax];
	ShotNormal* m_pShotNormal[kShotMax];
	ShotFall* m_pShotFall[kShotMax];*/
};