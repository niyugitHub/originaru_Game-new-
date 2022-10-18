#include "ShotNormal.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
	constexpr float kChaseSpeed = 2.0f;
}

void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);
	
	m_vec.x = 0;
	m_vec.y = kShotSpeed;
}

void ShotNormal::update()
{
	if (!m_isExist)return;

	if (m_pos.x > m_player.getPos().x)
		m_pos.x += kChaseSpeed;

	else if (m_pos.x < m_player.getPos().x)
		m_pos.x -= kChaseSpeed;

	m_pos.y += m_vec.y;

	if (m_pos.y > Game::kScreenHeight)
	{
		m_isExist = false;
	}
}