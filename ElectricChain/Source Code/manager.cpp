//------------------------------------------------------------------------------
//
//マネージャー処理  [manager.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "keyboard.h"
#include "pad_XInput.h"
#include "mouse.h"
#include "fade.h"
#include "game.h"
#include "title.h"
#include "tutorial.h"
#include "demoplay.h"
#include "result.h"
#include "ranking.h"
#include "basemode.h"
#include "scene.h"
#include "enemy.h"
#include "Debug/debug_motionviewer.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
std::unique_ptr<CRenderer> CManager::m_pRenderer = nullptr;
std::unique_ptr<CSound> CManager::m_pSound = nullptr;
std::unique_ptr<CKeyboard> CManager::m_pKeyboard = nullptr;
std::unique_ptr<CMouse> CManager::m_pMouse = nullptr;
std::unique_ptr<CPad_XInput> CManager::m_pXInput = nullptr;

std::unique_ptr<CBaseMode> CManager::m_pBaseMode = nullptr;
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;
HWND CManager::m_hWnd = nullptr;
int CManager::m_nNumChangeMode = 0;
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//メモリ確保
	m_pRenderer.reset(new CRenderer);
	m_pSound.reset(new CSound);
	m_pKeyboard.reset(new CKeyboard);
	m_pMouse.reset(new CMouse);
	m_pXInput.reset(new CPad_XInput);
	m_nNumChangeMode = 0;

	m_hWnd = hWnd;

	//レンダラー初期化
	if (FAILED(m_pRenderer->Init(hInstance, hWnd, bWindow)))
	{
		//失敗
		MessageBox(hWnd, "レンダラー設定失敗", "Renderer", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}
	//レンダラー初期化
	if (FAILED(m_pSound->Init(hWnd)))
	{
		//失敗
		MessageBox(hWnd, "サウンド設定失敗", "Sound", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//キーボード初期化
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		//失敗
		MessageBox(hWnd, "初期化失敗", "KeyBoard", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//マウス初期化
	if (FAILED(m_pMouse->Init(hInstance, hWnd)))
	{
		//失敗
		MessageBox(hWnd, "初期化失敗", "Mouse", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//ゲームパッド初期化
	if (FAILED(m_pXInput->Init(hInstance, hWnd)))
	{
		//失敗
		MessageBox(hWnd, "初期化失敗", "m_pXInput", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//ライブラリ生成
	if (FAILED(CHossoLibrary::InitImgui(hWnd)))
	{
		//失敗
		MessageBox(hWnd, "初期化失敗", "InputMacro", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//ベースの素材生成
	CBaseMode::BaseLoad(hWnd);

	//モード設定
	SetMode(m_mode);

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CManager::Uninit()
{
	//ImGui終了
	CHossoLibrary::UninitImgui();

	//ベースの素材破棄
	CBaseMode::BaseUnload();

	//メモリ開放
	if (m_pRenderer)
	{	//レンダラー
		m_pRenderer->Uninit();
		m_pRenderer.reset();
	}

	if (m_pKeyboard)
	{	//キーボード
		m_pKeyboard->Uninit();
		m_pKeyboard.reset();
	}

	if (m_pMouse)
	{	//マウス
		m_pMouse->Uninit();
		m_pMouse.reset();
	}

	if (m_pXInput)
	{	//ゲームパッド
		m_pXInput->Uninit();
		m_pXInput.reset();
	}
	if (m_pBaseMode)
	{
		//モード
		m_pBaseMode->Uninit();
		m_pBaseMode.reset();

	}

	if (m_pSound)
	{//サウンド
		m_pSound->Uninit();
		m_pSound.reset();
		m_pSound = nullptr;
	}
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CManager::Update()
{
	//更新
	if (m_pKeyboard)
	{	//キーボード
		m_pKeyboard->Update();
	}

	if (m_pMouse)
	{	//マウス
		m_pMouse->Update();
	}

	if (m_pXInput)
	{	//ゲームパッド
		m_pXInput->Update();
	}


	//スティックの情報更新
	CHossoLibrary::ResetStickInfo();

	if (m_pRenderer)
	{	//レンダラー
		m_pRenderer->Update();

	}
	if (m_pBaseMode)
	{	//モード
		m_pBaseMode->Update();
	}
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CManager::Draw()
{
	if (m_pBaseMode)
	{	//モード
		m_pBaseMode->Draw();
	}
	if (m_pRenderer)
	{
		//レンダラー
		m_pRenderer->Draw();
	}
}

//------------------------------------------------------------------------------
//モード設定
//------------------------------------------------------------------------------
void CManager::SetMode(MODE nextmode)
{
	//カウント
	m_nNumChangeMode++;
	std::cout << "SetMode - " << m_nNumChangeMode << NEWLINE;;

	//サウンドストップ
	m_pSound->StopAll();

	//nullcheck
	if (m_pBaseMode)
	{
		//終了処理
		m_pBaseMode->Uninit();

		//メモリ開放
		m_pBaseMode.reset();
		std::cout << "delete BaseMode" << NEWLINE;;
		m_pBaseMode = nullptr;

	}

	m_mode = nextmode;

	//次のモードのメモリ確保
	switch (nextmode)
	{
		//title
	case MODE_TITLE:
		m_pBaseMode.reset(new CTitle);
		std::cout << "new BaseMode[Title]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;

		//demoplay
	case MODE_DEMOPLAY:
		m_pBaseMode.reset(new CDemoPlay);
		std::cout << "new BaseMode[Demoplay]" << NEWLINE;
		break;

		//tutorial
	case MODE_TUTORIAL:
		m_pBaseMode.reset(new CTutorial);
		std::cout << "new BaseMode[Tutorial]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_TUTORIAL);
		break;

		//game
	case MODE_GAME:
		m_pBaseMode.reset(new CGame);
		std::cout << "new BaseMode[Game]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_GAME);
		break;

		//result
	case MODE_RESULT:
		m_pBaseMode.reset(new CResult);
		std::cout << "new BaseMode[result]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_RESULT);
		break;

		//ranking
	case MODE_RANKING:
		m_pBaseMode.reset(new CRanking);
		std::cout << "new BaseMode[ranking]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_RANKING);
		break;

		//debug
	case MODE_DEBUG_MOTION_VIEWER:
		m_pBaseMode.reset(new CDebug_MotionViewer);
		std::cout << "new BaseMode[CDebug_MotionViewer]" << NEWLINE;
		break;

		//gameend
	case MODE_END:
		PostQuitMessage(0);
		break;

		//それ以外
	default:
		//エラー
		MessageBox(m_hWnd, "遷移失敗", "Manager", MB_OK | MB_ICONHAND);
		break;
	}

	//敵の情報初期化
	CEnemy:: ResetEnemyStaticInfo();

	//nullcheck
	if (m_pBaseMode)
	{
		//初期化
		if (FAILED(m_pBaseMode->Init(m_hWnd)))
		{
			//失敗
			MessageBox(m_hWnd, "初期化失敗", "BaseMode", MB_OK | MB_ICONHAND);
		}
	}
	CScene::SetStop(false);
}

//------------------------------------------------------------------------------
//ベースモードの情報取得
//------------------------------------------------------------------------------
CBaseMode * CManager::GetBaseMode()
{
	//nullcheck
	if (m_pBaseMode)
	{
		return m_pBaseMode.get();
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//ゲーム情報取得処理
//------------------------------------------------------------------------------
CGame * CManager::GetGame()
{
	//ゲーム中かどうか
	if (m_mode == CManager::MODE_GAME)
	{
		//nullcheck
		if (m_pBaseMode)
		{
			//キャスト
			CGame *pGame = ((CGame*)m_pBaseMode.get());

			//nullcheck
			if (pGame)
			{
				return pGame;
			}
		}
	}
	return nullptr;
}
