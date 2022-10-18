#include "ShotFall.h"
#include "game.h"

namespace
{	//���ɍs���X�s�[�h
	constexpr float kShotSpeedX = 4.0f;
	//�c�ɍs���X�s�[�h
	constexpr float kShotSpeedY = 4.0f;
	//�d��z
	constexpr float kGravity = 0.4f;
}

void ShotFall::start(Vec2 pos)
{
	//	ShotBase::start(pos);

	m_isExist = true;
	m_pos.x = m_player.getPos().x + 10;
	m_pos.y = m_player.getPos().y + 10;
	
	m_vec.x = kShotSpeedX;
	m_vec.y = kShotSpeedY;
}

void ShotFall::update()
{
	if (!m_isExist)return;

	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;

	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}