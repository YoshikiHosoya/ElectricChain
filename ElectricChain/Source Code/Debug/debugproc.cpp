//------------------------------------------------------------------------------
//
//デバッグ表記処理  [deugproc.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "debugproc.h"
#include "../scene.h"
#include "../manager.h"
#include "../renderer.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#define FONT_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[CDebugProc::PLACE_MAX][MAX_DATA] = {};
RECT CDebugProc::m_rect[CDebugProc::PLACE_MAX] =
{
	{ 0 , 0 , SCREEN_WIDTH,SCREEN_HEIGHT },		//左側
	{ 700, 0 , SCREEN_WIDTH,SCREEN_HEIGHT }		//右側
};

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CDebugProc::Init(HWND hWnd)
{
	//デバッグフォントの設定
	D3DXCreateFont(CManager::GetRenderer()->GetDevice(),
		14, 7,	//フォントサイズ
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		("ＭＳ ゴシック"),
		&m_pFont);

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CDebugProc::Uninit()
{
	//nullチェック
	if (m_pFont)
	{	//Direct3Dオブジェクトの開放
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//------------------------------------------------------------------------------
//情報受け取り
//------------------------------------------------------------------------------
void CDebugProc::Print(PLACE place, char * fmt, ...)
{
#ifdef _DEBUG

	//可変引数用のリスト
	va_list args;

	//配列スタート
	va_start(args, fmt);

	//m_aStrに加算
	vsprintf(m_aStr[place] + strlen(m_aStr[place]), fmt, args);

	//配列終了
	va_end(args);
#endif //_DEBUG
}
//------------------------------------------------------------------------------
//描画
//------------------------------------------------------------------------------
void CDebugProc::Draw(void)
{
#ifdef _DEBUG

	for (int nCnt = 0; nCnt < CDebugProc::PLACE_MAX; nCnt++)
	{
		//テキスト描画
		m_pFont->DrawText(NULL,
			&m_aStr[nCnt][0],
			-1,
			&m_rect[nCnt],
			DT_LEFT,
			FONT_COLOR);

	}
#endif //_DEBUG
}

//------------------------------------------------------------------------------
//配列の初期化
//------------------------------------------------------------------------------
void CDebugProc::ResetStr()
{
	for (int nCnt = 0; nCnt < CDebugProc::PLACE_MAX; nCnt++)
	{
		//配列の初期化
		m_aStr[nCnt][0] = '\0';
	}
}
