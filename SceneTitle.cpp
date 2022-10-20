#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include"game.h"


void SceneTitle::init()
{
	m_textPosY = 0;
	m_textVecY = 4;
	/*m_handle = -1;*/

	m_handle = LoadGraph("data/背景.png");

	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_4)
	{
		// Mainに切り替え
		return (new SceneMain);
	}
	

	return this;
}

void SceneTitle::draw()
{
	DrawGraph(0, 0, m_handle,true);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, "タイトル画面", GetColor(0, 0, 0));
}
