#include "ShotFall.h"
#include "game.h"

namespace
{	//���ɍs���X�s�[�h
	constexpr float kShotSpeedX = 8.0f;
	//�c�ɍs���X�s�[�h
	constexpr float kShotSpeedY = 0.0f;
	//�d��z
	constexpr float kGravity = 0.4f;
}

void ShotFall::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = kShotSpeedX;
	m_vec.y = kShotSpeedY;
}

void ShotFall::update( )
{
	if (!m_isExist)return;
	m_pos += m_vec;
	m_vec.y += kGravity;

	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}