#pragma once

#include "ShotBase.h"

class ShotPlayer : public ShotBase
{
public:
	ShotPlayer()
	{
	}
	virtual ~ShotPlayer()
	{
	}

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
};