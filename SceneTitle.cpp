#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include"game.h"


void SceneTitle::init()
{
	m_textPosY = 0;
	m_textVecY = 4;
	/*m_handle = -1;*/

	m_handle = LoadGraph("data/îwåi.png");

	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_2)
	{
		// MainÇ…êÿÇËë÷Ç¶
		return (new SceneMain);
	}
	

	return this;
}

void SceneTitle::draw()
{
	DrawGraph(0, 0, m_handle,true);
	SetFontSize(50);
	DrawString(Game::kScreenWidth / 2 - 50 * 4.5, 300, "Ç…ÇÒÇ∂Ç·ÇÇΩÇ®ÇπÅI", GetColor(0, 0, 0));
	SetFontSize(30);
	DrawString(Game::kScreenWidth / 2 - 30 * 4.5, 300, "", GetColor(0, 0, 0));
}
