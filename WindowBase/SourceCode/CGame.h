#pragma once
#include <Windows.h>
#include "Global.h"		
#include "CPlayer.h"

#pragma comment( lib, "msimg32.lib" )	// 指定色を透過して描画で使用する.
										// 半透明の描画でも使用する.

/**************************************************
*	ゲームクラス.
**/
class CGame
{
public:
	CGame();	// コンストラクタ.
	CGame( GameWindow* pGameWnd );// コンストラクタ(引数あり).
	~CGame();	// デストラクタ.

	// 構築関数.
	bool Create();
	// 破棄関数.
	void Destroy();
	// 更新関数(キー入力や動作処理を行う).
	void Update();
	// 描画関数(画像の表示処理を行う).
	void Draw();

	//ウィンドウを閉じているか確認.
	BOOL IsWindowClosed() const { return m_pGameWnd->isWndClose; }
	//FPSを取得.
	DWORD GetFPS() const { return m_pGameWnd->dwFPS; }
	//バックバッファを取得.
	HDC GetScreenDC() const { return m_pGameWnd->hScreenDC; }
	//ウィンドウハンドルを取得.
	HWND GetWnd() const { return m_pGameWnd->hWnd; }

private:
	// 画像の読み込み.
	bool LoadBmp(HBITMAP* phBmp, const char* fileName);

	// 画像を透過して表示.
	bool TransBlt(
		float xDest, float yDest, float wDest, float hDest,
		HDC hdcSrc, float xSrc, float ySrc);
	
private:
	GameWindow*	m_pGameWnd;		// ゲームウィンドウ構造体.
	HDC			m_hMemDC;		// メモリデバイスコンテキスト.
	HDC			m_hWorkMemDC;	// 作業用DC.
	HBITMAP		m_hWorkBmp;		// 作業用BMP.
	HFONT		m_hFont;		// フォントハンドル.

	HBITMAP		m_BackImage;	// 背景の画像.
	HBITMAP		m_PlayerImage;	// プレイヤーの画像.

	CPlayer*	m_pPlayer;		// プレイヤー.
};
