#include "ShotNormal.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 50.0f;
}

void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = 0;
	m_vec.y = -kShotSpeed;
}

void ShotNormal::update()
{
	if (!m_isExist)return;
	m_pos += m_vec;

	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}