//-----------------------------------------------------------------------------
//
// モードの規定クラス [basemode.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "basemode.h"
#include "modelcharacter.h"
#include "character.h"
#include "particle.h"
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "keyboard.h"

//-----------------------------------------------------------------------------
//デバッグコマンド
//-----------------------------------------------------------------------------
void CBaseMode::DebugCommand()
{
	//キーボード取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//デバッグテキスト
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "[F1] : デバッグ情報 on/off\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "[F3] : 一時停止 ポーズと併用するとバグるon/off\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "[F4] : 一時停止中に1コマ送り\n");

	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "テンキー [0] : 現在のModeに遷移\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "テンキー [1] : Titleに遷移\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "テンキー [2] : Tutorialに遷移\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "テンキー [3] : Gameに遷移\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "テンキー [4] : Resultに遷移\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "テンキー [5] : Rankingに遷移\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "テンキー [9] : モーションビューワ起動\n");

	//デバッグ情報表示非表示
	if (pKeyboard->GetTrigger(DIK_F1))
	{
		CManager::GetRenderer()->SetDispDebugInfo(CManager::GetRenderer()->CheckShoeDebugInfo() ^ 1);
	}

	//判定線
	if (pKeyboard->GetTrigger(DIK_F2))
	{

	}

	//一時停止
	if (pKeyboard->GetTrigger(DIK_F3))
	{
		CScene::SetStop(CScene::CheckStop() ^ 1);
	}

	//1Fだけ更新
	if (pKeyboard->GetTrigger(DIK_F4))
	{
		CScene::Set1FAction();
	}

	//現在のモード再始動
	if (pKeyboard->GetTrigger(DIK_NUMPAD0))
	{
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::GetMode());
	}
	//タイトル
	if (pKeyboard->GetTrigger(DIK_NUMPAD1))
	{
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
	}
	//チュートリアル
	if (pKeyboard->GetTrigger(DIK_NUMPAD2))
	{
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TUTORIAL);
	}
	//ゲーム
	if (pKeyboard->GetTrigger(DIK_NUMPAD3))
	{
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
	}
	//リザルト
	if (pKeyboard->GetTrigger(DIK_NUMPAD4))
	{
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RESULT);
	}
	//ランキング
	if (pKeyboard->GetTrigger(DIK_NUMPAD5))
	{
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RANKING);
	}
	//モーションビューワ
	if (pKeyboard->GetTrigger(DIK_NUMPAD9))
	{
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_DEBUG_MOTION_VIEWER);
	}

	//オーバーライド
	ShowDebugInfo();

}
//-----------------------------------------------------------------------------
//使うテクスチャやモデルの読み込み
//-----------------------------------------------------------------------------
void CBaseMode::BaseLoad(HWND hWnd)
{
	//テクスチャロード
	CTexture::TexLoad(hWnd);

	//モデル読み込み
	if (FAILED(CModelCharacter::Load()))
	{
		//失敗
		MessageBox(hWnd, "モデル情報読み込み失敗", "CModelCharacter", MB_OK | MB_ICONHAND);
	}
	//モーション読み込み
	if (FAILED(CMotion::Load()))
	{
		//失敗
		MessageBox(hWnd, "モーション読み込み失敗", "CMotion", MB_OK | MB_ICONHAND);
	}

	//キャラクターの初期パラメータ読み込み
	if (FAILED(CCharacter::LoadDefaultParam()))
	{
		//失敗
		MessageBox(hWnd, "パラメータ読み込み失敗", "CCharacter", MB_OK | MB_ICONHAND);
	}

	//パーティクルのテクスチャと頂点確報
	if (FAILED(CParticle::MakeVertex()))
	{
		//失敗
		MessageBox(hWnd, "テクスチャ読み込み失敗", "CParticle", MB_OK | MB_ICONHAND);
	}

	//スコア読み込み
	if (FAILED(CScore::LoadScore()))
	{
		//失敗
		MessageBox(hWnd, "スコア読み込み失敗", "CScore", MB_OK | MB_ICONHAND);
	}
}

//-----------------------------------------------------------------------------
//生成したものを全て破棄
//----------------------------------------------------------------------------
void CBaseMode::BaseUnload()
{
	//テクスチャ破棄
	CTexture::TexUnload();

	//モデルに関するもの
	CModelCharacter::UnLoad();
	CMotion::UnLoad();

	//パーティクルの頂点情報開放
	CParticle::ReleaseVertex();

}
