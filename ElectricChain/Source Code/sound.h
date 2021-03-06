//------------------------------------------------------------------------------
//
// サウンド処理 [sound.h]
// Author : Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------
#include "main.h"
#include "xaudio2.h"


class CSound
{
public:

	// サウンドファイル
	typedef enum
	{
		LABEL_BGM_TITLE = 0,						//タイトル
		LABEL_BGM_TUTORIAL,							//リザルト
		LABEL_BGM_GAME,								//ゲーム
		LABEL_BGM_RESULT,							//リザルト
		LABEL_BGM_RANKING,							//ランキング
		LABEL_BGM_RAIN,								//雨音

		//キャラクターアクション
		LABEL_SE_SLASH,								//斬撃
		LABEL_SE_SLASH_STAN,						//斬撃 スタン時
		LABEL_SE_SLASH_PLAYER,						//斬撃　プレイヤーヒット
		LABEL_SE_SWING,								//素振り
		LABEL_SE_WALK,								//歩く
		LABEL_SE_JUMP,								//ジャンプ
		LABEL_SE_LANDING,							//着地
		LABEL_SE_APPEAR,							//出現


		//エフェクト
		LABEL_SE_EXPLOSION,							//爆発
		LABEL_SE_SPARK,								//電撃
		LABEL_SE_START_CHAIN,						//連鎖開始の雷
		LABEL_SE_CHAINING_SPARK,					//連鎖中の電撃
		LABEL_SE_THUNDER,							//落雷

		//タイトル用
		LABEL_SE_TITLE_SPARKING,					//タイトル　ビリビリー
		LABEL_SE_TITLE_EXPLOSION,					//タイトル　バーンって感じの
		LABEL_SE_RANKING_THUNDER,					//ランキング　数字出てくるときの

		//環境音とか
		LABEL_SE_DECISION,							//決定
		LABEL_SE_CANCEL,							//キャンセル
		LABEL_SE_SELECT,							//選択
		LABEL_SE_PAUSE,								//ポーズ
		LABEL_SE_GAMEOVER,							//ゲームオーバー
		LABEL_SE_GAMECLEAR,							//ゲームクリア

		LABEL_MAX,
	} LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void StopAll(void);

private:

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[LABEL_MAX] = {};						// オーディオデータサイズ


	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	// 各音素材のパラメータ
	SOUNDPARAM m_aParam[LABEL_MAX] =
	{
		{ "data/BGM/title.wav", -1 },							//BGM
		{ "data/BGM/tutorial.wav", -1 },						//BGM
		{ "data/BGM/game.wav", -1 },							//BGM
		{ "data/BGM/result.wav", -1 },							//BGM
		{ "data/BGM/ranking.wav", -1 },							//BGM
		{ "data/BGM/rain.wav", -1 },							//BGM

		//キャラクターアクション
		{ "data/SE/CharacterAction/slash.wav", 0 },				//SE 斬撃
		{ "data/SE/CharacterAction/slash_stan.wav", 0 },		//SE 斬撃
		{ "data/SE/CharacterAction/player_hit.wav", 0 },		//SE 斬撃　プレイヤーヒット
		{ "data/SE/CharacterAction/swing.wav", 0 },				//SE 素振り
		{ "data/SE/CharacterAction/walking.wav", 0 },			//SE 歩く
		{ "data/SE/CharacterAction/jump.wav", 0 },				//SE ジャンプ
		{ "data/SE/CharacterAction/landing.wav", 0 },			//SE 着地
		{ "data/SE/CharacterAction/appear.wav", 0 },			//SE 出現

		//エフェクト
		{ "data/SE/Effect/explosion.wav", 0 },					//SE 爆発
		{ "data/SE/Effect/spark.wav", 0 },						//SE 電撃
		{ "data/SE/Effect/ChainStartThunder.wav", 0 },			//SE 電撃
		{ "data/SE/Effect/ChainingSpark.wav", 0 },				//SE 電撃
		{ "data/SE/Effect/Thunder.wav", 0 },					//SE 落雷

		//タイトル用
		{ "data/SE/Title/Sparking.wav", 0 },					//SE ビリビリ
		{ "data/SE/Title/Title_Explosion.wav", 0 },				//SE バーン
		{ "data/SE/Ranking/Ranking_Thunder.wav", 0 },			//SE 数字出てくるときの雷

		//環境音
		{ "data/SE/System/decision.wav", 0 },					//SE 決定
		{ "data/SE/System/cancel.wav", 0 },						//SE キャンセル
		{ "data/SE/System/select.wav", 0 },						//SE 選択
		{ "data/SE/System/pause.wav", 0 },						//SE ポーズ
		{ "data/SE/System/gameover.wav", 0 },					//SE ゲームオーバー
		{ "data/SE/System/gameclear.wav", 0 },					//SE ゲームクリア

	};

};


#endif
