#pragma once

#include "ShotBase.h"

class ShotFall : public ShotBase
{
public:
	ShotFall()
	{
	}
	virtual ~ShotFall()
	{
	}

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
};