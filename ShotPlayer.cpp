#include "ShotPlayer.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 50.0f;
	constexpr int kPlayerGraphicSizeX = 32;
	constexpr int kPlayerGraphicSizeY = 32;
}

void ShotPlayer::start(Vec2 pos)
{
//	ShotBase::start(pos);

	m_isExist = true;
	m_pos.x = pos.x + 8;
	m_pos.y = pos.y + kPlayerGraphicSizeY - 10;

	m_vec.x = 0;
	m_vec.y = -kShotSpeed;
}

void ShotPlayer::update()
{
	if (!m_isExist)return;
	m_pos += m_vec;

	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}