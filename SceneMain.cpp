#include "DxLib.h"
#include "SceneMain.h"
#include "ShotBound.h"
#include "ShotPlayer.h"
#include "ShotFall.h"
#include "SceneTitle.h"
#include <cassert>
#include "ShotNormal.h"
#include "game.h"
//aaaaa
namespace
{
	//�V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
	// �O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphicFilename = "data/player.png";
	const char* const kEnemyGraphicFilename = "data/enemy.bmp";
	const char* const kDeadGraphicFilename = "data/DeadEffect.png";


	// �v���C���[�̃T�C�Y
	constexpr int kPlayerGraphicSizeX = Player::kPlayerGraphicSizeX;
	constexpr int kPlayerGraphicSizeY = Player::kPlayerGraphicSizeY;
	// �G�̃T�C�Y
	constexpr int kEnemyGraphicSizeX = Enemy::kEnemyGraphicSizeX;
	constexpr int kEnemyGraphicSizeY = Enemy::kEnemyGraphicSizeY;
	// �V���b�g�̃T�C�Y
	constexpr int kShotGraphicSizeX = 16.0f;
	constexpr int kShotGraphicSizeY = 16.0f;
}

SceneMain::SceneMain()
{
//	m_hPlayerGraphic = -1;
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	for (auto& handle : m_hDeadGraphic)
	{
		handle = -1;
	}

	m_hEnemyGraphic = -1;
	m_hShotGraphic = -1;
}
SceneMain::~SceneMain()
{

}

// ������
void SceneMain::init()
{
	// �O���t�B�b�N�̃��[�h
	LoadDivGraph(kPlayerGraphicFilename, Player::kPlayerGraphicDivNum,
		Player::kPlayerGraphicDivX, Player::kPlayerGraphicDivY,
		Player::kPlayerGraphicSizeX, Player::kPlayerGraphicSizeY, m_hPlayerGraphic);

	LoadDivGraph(kDeadGraphicFilename, kDeadGraphicDivNum,
		kDeadGraphicDivX, kDeadGraphicDivY,
		kDeadGraphicSizeX, kDeadGraphicSizeY, m_hDeadGraphic);

	m_hEnemyGraphic = LoadGraph(kEnemyGraphicFilename);
	m_hShotGraphic = LoadGraph("data/shot.bmp");
	// �T�E���h�̃��[�h
	m_hTestSound = LoadSoundMem("sound/cursor0.mp3");

	for (int i = 0; i < Player::kPlayerGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);
	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);
	m_EnemyHP = 20;
	m_trueCount = 0;
	m_animeNo = 0;
	m_animeFrame = 8;
}

// �I������
void SceneMain::end()
{
	// �O���t�B�b�N�A�����[�h
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}

	for (auto& handle : m_hDeadGraphic)
	{
		DeleteGraph(handle);
	}

	DeleteGraph(m_hEnemyGraphic);
	DeleteGraph(m_hShotGraphic);
	// �T�E���h�A�����[�h
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
}

// ���t���[���̏���
SceneBase* SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Col_ShotPlayer())
	{
		if (m_trueCount == 1)
		{
			WaitVSync(120);
		}		
		
		for (auto& handle : m_hPlayerGraphic)
		{
			DeleteGraph(handle);
		}

		m_animeFrame--;
		if (m_animeFrame == 0)
		{
			m_animeNo++;
			m_animeFrame = 8;
		}

		if (m_animeNo < 9)
		{
			DrawGraph(static_cast<int>(m_player.getPos().x), static_cast<int>(m_player.getPos().y), m_hDeadGraphic[m_animeNo], true);
		}

		if (padState & PAD_INPUT_2)
		{
			// Title�ɐ؂�ւ�
			return (new SceneTitle);
		}
	}
	if (Col_EnemyPlayer())
	{
		DxLib_End();
	}
	if (Col_ShotEnemy())
	{
		m_EnemyHP--;
		if (m_EnemyHP == 0)
		{
			if (m_trueCount == 1)
			{
				WaitVSync(120);
			}

			DeleteGraph(m_hEnemyGraphic);

			m_animeFrame--;
			if (m_animeFrame == 0)
			{
				m_animeNo++;
				m_animeFrame = 8;
			}

			if (m_animeNo < 9)
			{
				DrawGraph(static_cast<int>(m_enemy.getPos().x), static_cast<int>(m_enemy.getPos().y), m_hDeadGraphic[m_animeNo], true);
			}

			if (padState & PAD_INPUT_2)
			{
				// Title�ɐ؂�ւ�
				return (new SceneTitle);
			}
		}

	}
	/*int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);*/
	if (padState & PAD_INPUT_1)
	{
		PlaySoundMem(m_hTestSound, DX_PLAYTYPE_BACK, true);
	}
	if (m_trueCount == 0 && m_EnemyHP >= 0)
	{
		m_player.update();
		m_enemy.update();
	}

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}
	return this;
#if false
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot) continue;		//null�̏ꍇ�������Ȃ�
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�̗v�f�폜

		}
	}
#endif
}

// ���t���[���̕`��
void SceneMain::draw()
{
	m_player.draw();
	m_enemy.draw();
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}

	/*if (m_animeFrame == 0)
	{
		m_animeNo++;
		m_animeFrame = 0;
	}
	DrawGraph(static_cast<int>(m_player.getPos().x), static_cast<int>(m_player.getPos().y), m_hDeadGraphic[m_animeNo], true);*/
	//���ݑ��݂��Ă���e�̐���\��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�e�̐�:%d", m_pShotVt.size());
	DrawBox(0, 0, m_EnemyHP * (Game::kScreenWidth / 20), 100,GetColor(0,255,0),true);
}

bool SceneMain::createShotPlayer(Vec2 pos)
{
	ShotPlayer* pShot = new ShotPlayer;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotFall(Vec2 pos)
{
	ShotFall* pShot = new ShotFall;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::Col_ShotPlayer()
{
	m_player.getPos();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->getPos();

		float shotLeft = pShot->getPos().x;
		float shotRight = pShot->getPos().x + kShotGraphicSizeX;
		float shotTop = pShot->getPos().y;
		float shotBottom = pShot->getPos().y + kShotGraphicSizeY;

		float playerLeft = m_player.getPos().x + 10;
		float playerRight = m_player.getPos().x + kPlayerGraphicSizeX - 10;
		float playerTop = m_player.getPos().y + 10;
		float playerBottom = m_player.getPos().y + kPlayerGraphicSizeY - 10;

		if (playerLeft > shotRight)
		{
			it++;
			continue;
		}
		if (playerRight < shotLeft)
		{
			it++;
			continue;
		}
		if (playerTop > shotBottom)
		{
			it++;
			continue;
		}
		if (playerBottom < shotTop)
		{
			it++;
			continue;
		}

		m_trueCount++;
		return true;
	}
	if (m_trueCount != 0) return true;
	return false;
	
}

bool SceneMain::Col_EnemyPlayer()
{
	m_player.getPos();
	m_enemy.getPos();

	float playerLeft = m_player.getPos().x + 10;
	float playerRight = m_player.getPos().x + kPlayerGraphicSizeX - 10;
	float playerTop = m_player.getPos().y + 10;
	float playerBottom = m_player.getPos().y + kPlayerGraphicSizeY - 10;

	float enemyLeft = m_enemy.getPos().x + 10;
	float enemyRight = m_enemy.getPos().x + kEnemyGraphicSizeX - 10;
	float enemyTop = m_enemy.getPos().y + 10;
	float enemyBottom = m_enemy.getPos().y + kEnemyGraphicSizeY - 10;

	if (playerLeft > enemyRight) return false;
	if (playerRight < enemyLeft) return false;
	if (playerTop > enemyBottom) return false;
	if (playerBottom < enemyTop) return false;

	return true;
}

bool SceneMain::Col_ShotEnemy()
{
	m_enemy.getPos();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->getPos();

		float shotLeft = pShot->getPos().x;
		float shotRight = pShot->getPos().x + kShotGraphicSizeX;
		float shotTop = pShot->getPos().y;
		float shotBottom = pShot->getPos().y + kShotGraphicSizeY;

		float enemyLeft = m_enemy.getPos().x + 10;
		float enemyRight = m_enemy.getPos().x + kEnemyGraphicSizeX - 10;
		float enemyTop = m_enemy.getPos().y + 10;
		float enemyBottom = m_enemy.getPos().y + kEnemyGraphicSizeY - 10;

		if (enemyLeft > shotRight)
		{
			it++;
			continue;
		}
		if (enemyRight < shotLeft)
		{
			it++;
			continue;
		}
		if (enemyTop > shotBottom)
		{
			it++;
			continue;
		}
		if (enemyBottom < shotTop)
		{
			it++;
			continue;
		}
		m_trueCount++;
		return true;
	}
	if (m_trueCount >= m_EnemyHP) return true;
	return false;
}