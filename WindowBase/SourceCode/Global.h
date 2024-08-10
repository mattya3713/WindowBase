#pragma once
#include <Windows.h>

//---------------------------------------
//	定数宣言.
//---------------------------------------
constexpr int FPS = 60;			// FPS(基準).
constexpr int WND_W = 960;		// ウィンドウの幅.
constexpr int WND_H = 540;		// ウィンドウの高さ.
constexpr float WND_Wf = 960.f;	// ウィンドウの幅(float).
constexpr float WND_Hf = 540.f;	// ウィンドウの高さ(float).

//---------------------------------------
//	構造体.
//---------------------------------------
typedef struct _GameWindow
{
	HWND	hWnd;		//ウィンドウハンドル.
	HDC		hScreenDC;	//バックバッファ.
	SIZE	size;		//サイズ.
	DWORD	dwFPS;		//FPS( Frame Per Second: フレーム / 秒 ).
	BOOL	isWndClose;	//ウィンドウ閉じてるか確認用.
} GameWindow;

// 座標.
typedef struct _Vector2
{
	float x;
	float y;
} Vector2;