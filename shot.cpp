#include "DxLib.h"
#include "shot.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
}

Shot::Shot()
{
	m_handle = -1;
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_shotInterval = 8;

	m_isExist = false;
}

Shot::~Shot()
{

}

void Shot::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;

	m_vec.x = kShotSpeed;
	m_vec.y = 0.0f;
}

void Shot::update()
{
	if (!m_isExist)return;
	m_pos += m_vec;

	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}
// •\Ž¦
void Shot::draw()
{
	if (!m_isExist)return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}
