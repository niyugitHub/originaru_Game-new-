#pragma once
#include "Vec2.h"

class Shot
{
public:
	Shot();
	virtual ~Shot();

	void setHandle(int handle) { m_handle = handle; }

	//ショット開始
	void start(Vec2 pos);

	// 更新
	void update();
	// 表示
	void draw();

	//存在るするか
	bool isExist() const { return m_isExist; }

private:
	// グラフィックハンドル
	int m_handle;
	// 表示位置
	Vec2	m_pos;
	// 移動
	Vec2	m_vec;
	//存在するか
	bool    m_isExist;

	int  m_shotInterval;
};