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
	//ショットの発射間隔
	constexpr int kShotInterval = 16;
	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/player.png";
	const char* const kEnemyGraphicFilename = "data/enemy.bmp";
	const char* const kDeadGraphicFilename = "data/DeadEffect.png";


	// プレイヤーのサイズ
	constexpr int kPlayerGraphicSizeX = Player::kPlayerGraphicSizeX;
	constexpr int kPlayerGraphicSizeY = Player::kPlayerGraphicSizeY;
	// 敵のサイズ
	constexpr int kEnemyGraphicSizeX = Enemy::kEnemyGraphicSizeX;
	constexpr int kEnemyGraphicSizeY = Enemy::kEnemyGraphicSizeY;
	// ショットのサイズ
	constexpr float kShotGraphicSizeX = 16.0f;
	constexpr float kShotGraphicSizeY = 16.0f;
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
	m_MaxEnemyHP = 50;
	m_EnemyHP = 50;
	m_ColPlayerShot = 0;
	m_ColEnemyShot = 0;
	m_ColEnemyPlayer = 0;
	m_animeNo = 0;
	m_animeFrame = 8;
	m_hEnemyGraphic = -1;
	for (int i = 0; i < Player::kPlayerGraphicDivNum; i++)
	{
		m_hPlayerGraphic[i] = -1;
	}
	for (int i = 0; i < kDeadGraphicDivNum; i++)
	{
		m_hPlayerGraphic[i] = -1;
	}
	m_hShotGraphic = -1;
	m_handle = -1;
}
SceneMain::~SceneMain()
{

}

// 初期化
void SceneMain::init()
{
	// グラフィックのロード
	LoadDivGraph(kPlayerGraphicFilename, Player::kPlayerGraphicDivNum,
		Player::kPlayerGraphicDivX, Player::kPlayerGraphicDivY,
		Player::kPlayerGraphicSizeX, Player::kPlayerGraphicSizeY, m_hPlayerGraphic);

	//LoadDivGraph(kDeadGraphicFilename, kDeadGraphicDivNum,
	//	kDeadGraphicDivX, kDeadGraphicDivY,
	//	kDeadGraphicSizeX, kDeadGraphicSizeY, m_hDeadGraphic);

	m_handle = LoadGraph("data/背景.png");
	m_hEnemyGraphic = LoadGraph(kEnemyGraphicFilename);
	m_hShotGraphic = LoadGraph("data/shot.bmp");

	for (int i = 0; i < Player::kPlayerGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);
	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);
	m_MaxEnemyHP = 50;
	m_EnemyHP = 50;
	m_ColPlayerShot = 0;
	m_ColEnemyShot = 0;
	m_ColEnemyPlayer = 0;
	m_animeNo = 0;
	m_animeFrame = 8;
	m_shotNormal.setPos(m_player.getPos());

}

// 終了処理
void SceneMain::end()
{
	// グラフィックアンロード
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


	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
}

// 毎フレームの処理
SceneBase* SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Col_ShotPlayer())
	{
		LoadDivGraph(kDeadGraphicFilename, kDeadGraphicDivNum,
			kDeadGraphicDivX, kDeadGraphicDivY,
			kDeadGraphicSizeX, kDeadGraphicSizeY, m_hDeadGraphic);

		if (m_ColPlayerShot == 1)
		{
			WaitVSync(60);
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

		if (m_animeNo > 9)
		{
			if (padState & PAD_INPUT_2)
			{
				m_ColPlayerShot = 0;
				m_EnemyHP = 0;
				// Titleに切り替え
				return (new SceneTitle);
			}
			if (padState & PAD_INPUT_1)
			{
				m_ColPlayerShot = 0;
				m_EnemyHP = 0;
				// Mainに切り替え
				return (new SceneMain);
			}
		}
	}

	if (Col_EnemyPlayer())
	{
		LoadDivGraph(kDeadGraphicFilename, kDeadGraphicDivNum,
			kDeadGraphicDivX, kDeadGraphicDivY,
			kDeadGraphicSizeX, kDeadGraphicSizeY, m_hDeadGraphic);

		if (m_ColEnemyPlayer == 1)
		{
			WaitVSync(60);
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

		if (m_animeNo > 9)
		{
			if (padState & PAD_INPUT_2)
			{
				m_ColEnemyPlayer = 0;
				m_EnemyHP = 0;
				// Titleに切り替え
				return (new SceneTitle);
			}
			if (padState & PAD_INPUT_1)
			{
				m_ColEnemyPlayer = 0;
				m_EnemyHP = 0;
				// Mainに切り替え
				return (new SceneMain);
			}
		}
	}
	if (Col_ShotEnemy())
	{
		m_EnemyHP--;
		if (m_EnemyHP <= 0)
		{
			LoadDivGraph(kDeadGraphicFilename, kDeadGraphicDivNum,
				kDeadGraphicDivX, kDeadGraphicDivY,
				kDeadGraphicSizeX, kDeadGraphicSizeY, m_hDeadGraphic);

			if (m_ColEnemyShot == m_MaxEnemyHP)
			{
				WaitVSync(60);
				m_ColEnemyShot++;
			}

			DeleteGraph(m_hEnemyGraphic);

			m_animeFrame--;
			if (m_animeFrame == 0)
			{
				m_animeNo++;
				m_animeFrame = 8;
			}

			if (m_animeNo > 9)
			{
				if (padState & PAD_INPUT_2)
				{
					m_ColPlayerShot = 0;
					m_EnemyHP = 0;
					// Titleに切り替え
					return (new SceneTitle);
				}
				if (padState & PAD_INPUT_1)
				{
					m_ColPlayerShot = 0;
					m_EnemyHP = 0;
					// Mainに切り替え
					return (new SceneMain);
				}
			}
		}

	}
	/*int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);*/
	if (m_ColEnemyShot > m_MaxEnemyHP)
	{
		return this;
	}
	if (m_ColPlayerShot != 0)
	{
		return this;
	}
	if (m_ColEnemyPlayer != 0)
	{
		return this;
	}
	m_player.update();
	m_enemy.update();

	/*m_shotNormal.setPos(m_player.getPos());*/

		//m_PlayerPos = m_player.getPos();

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

			//vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}
	return this;
#if false
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot) continue;		//nullの場合処理しない
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vectorの要素削除

		}
	}
#endif
}

// 毎フレームの描画
void SceneMain::draw()
{
	DrawGraph(0, 0, m_handle, true);
	m_player.draw();
	m_enemy.draw();

	

	if (m_animeNo < 9 && m_ColPlayerShot != 0)
	{
		DrawGraph(static_cast<int>(m_player.getPos().x - 20),
			static_cast<int>(m_player.getPos().y - 20), m_hDeadGraphic[m_animeNo], true);
	}

	if (m_animeNo > 9 && m_ColPlayerShot != 0)
	{
		SetFontSize(50);
		DrawString(static_cast<int>(Game::kScreenWidth / 2 - 50 * 3), 300, "お前の負け！", GetColor(0, 0, 0));
		DrawString(static_cast<int>(Game::kScreenWidth / 2 - 50 * 2.5), 400, "B:タイトル", GetColor(0, 0, 0));
		DrawString(static_cast<int>(Game::kScreenWidth / 2 - 50 * 2.5), 500, "A:もういちど", GetColor(0, 0, 0));
	}

	if (m_animeNo < 9 && m_ColEnemyPlayer != 0)
	{
		DrawGraph(static_cast<int>(m_player.getPos().x - 20),
			static_cast<int>(m_player.getPos().y - 20), m_hDeadGraphic[m_animeNo], true);
	}

	if (m_animeNo > 9 && m_ColEnemyPlayer != 0)
	{
		SetFontSize(50);
		DrawString(static_cast<int>(Game::kScreenWidth / 2 - 50 * 3), 300, "お前の負け！", GetColor(0, 0, 0));
		DrawString(static_cast<int>(Game::kScreenWidth / 2 - 50 * 2.5), 400, "B:タイトル", GetColor(0, 0, 0));
		DrawString(static_cast<int>(Game::kScreenWidth / 2 - 50 * 2.5), 500, "A:もういちど", GetColor(0, 0, 0));
	}

	if (m_animeNo < 9 && m_EnemyHP <= 0)
	{
		DrawGraph(static_cast<int>(m_enemy.getPos().x),
			static_cast<int>(m_enemy.getPos().y), m_hDeadGraphic[m_animeNo], true);
	}

	if (m_animeNo > 9 && m_EnemyHP <= 0)
	{
		SetFontSize(50);
		DrawString(static_cast<int>(Game::kScreenWidth / 2 - 50 * 3), 300, "お前の勝ち！", GetColor(0, 0, 0));
		DrawString(static_cast<int>(Game::kScreenWidth / 2 - 50 * 2.5), 400, "B:タイトル", GetColor(0, 0, 0));
		DrawString(static_cast<int>(Game::kScreenWidth / 2 - 50 * 2.5), 500, "A:もういちど", GetColor(0, 0, 0));
	}

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
	//現在存在している弾の数を表示
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "弾の数:%d", m_pShotVt.size());
	DrawBox(0, 20, m_MaxEnemyHP * (Game::kScreenWidth / m_MaxEnemyHP), 80, GetColor(255, 0, 0), true);
	DrawBox(0, 20, m_EnemyHP * (Game::kScreenWidth / m_MaxEnemyHP), 80, GetColor(0, 255, 0), true);
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
		m_ColPlayerShot++;
		return true;
	}
	if (m_ColPlayerShot != 0) return true;
	return false;
	
}

bool SceneMain::Col_EnemyPlayer()
{
	m_player.getPos();
	m_enemy.getPos();

	if (m_ColEnemyPlayer != 0)
	{
		m_ColEnemyPlayer++;
		return true;
	}
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

	m_ColEnemyPlayer++;
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
		m_ColEnemyShot++;
		return true;
	}
	if (m_ColEnemyShot >= m_MaxEnemyHP) return true;
	return false;
}