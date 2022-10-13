#include "DxLib.h"
#include <cassert>
#include "game.h"
#include "player.h"

#include "SceneMain.h"

namespace
{
	// キャラクターアニメーションの速度
	int kAnimeChangeFrame = 8;
	// X方向、Y方向の速度
	constexpr float kSpeed = 4;
	//ショットの発射間隔
	constexpr float kShotInterval = 16;
}

Player::Player()
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_pMain = nullptr;
	m_shotInterval = 0;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_dirNo = 9;
}

Player::~Player()
{
	
}

void Player::init()
{
	m_pos.x = Game::kScreenWidth / 2 - kPlayerGraphicSizeX / 2;
	m_pos.y = Game::kScreenHeight / 2 - kPlayerGraphicSizeY / 2;
	m_vec.x = kSpeed;
	m_vec.y = kSpeed;
	m_shotInterval = 0;
	m_animeNo = 0;
	m_animeFrame = 0;
	m_dirNo = 9;
}

void Player::update()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//ショットを撃つ処理
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotNormal(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
		if (padState & PAD_INPUT_2)
		{
			if (m_pMain->createShotBound(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
		if (padState & PAD_INPUT_3)
		{
			if (m_pMain->createShotFall(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}

	if (padState & PAD_INPUT_UP)
	{
		m_pos.y -= m_vec.y;
	}
	if (padState & PAD_INPUT_DOWN)
	{
		m_pos.y += m_vec.y;
	}
	if (padState & PAD_INPUT_LEFT)
	{
		m_pos.x -= m_vec.x;
	}
	if (padState & PAD_INPUT_RIGHT)
	{
		m_pos.x += m_vec.x;
	}

	m_animeFrame++;
	if (m_animeFrame >= kPlayerGraphicDivX * kAnimeChangeFrame)
	{
		m_animeFrame = 0;
	}

	int tempAnimeNo = m_animeFrame / kAnimeChangeFrame;
	m_animeNo = m_dirNo + tempAnimeNo;
}

void Player::draw()
{
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
}