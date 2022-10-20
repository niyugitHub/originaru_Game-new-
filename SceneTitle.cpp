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
	if (padState & PAD_INPUT_1)
	{
		// Mainに切り替え
		return (new SceneMain);
	}
	if (padState & PAD_INPUT_2)
	{
		// 終了
		DxLib_End();
	}

	return this;
}

void SceneTitle::draw()
{
	DrawGraph(0, 0, m_handle, true);
	SetFontSize(50);
	DrawString(Game::kScreenWidth / 2 - 50 * 4.5, 300, "にんじゃをたおせ！", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 50 * 2, 400, "プレイ:A", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 50 * 2, 500, "やめる:B", GetColor(0, 0, 0));

}
