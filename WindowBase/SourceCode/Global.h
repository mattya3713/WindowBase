#pragma once
#include <Windows.h>

//---------------------------------------
//	�萔�錾.
//---------------------------------------
constexpr int FPS = 60;			// FPS(�).
constexpr int WND_W = 960;		// �E�B���h�E�̕�.
constexpr int WND_H = 540;		// �E�B���h�E�̍���.
constexpr float WND_Wf = 960.f;	// �E�B���h�E�̕�(float).
constexpr float WND_Hf = 540.f;	// �E�B���h�E�̍���(float).

//---------------------------------------
//	�\����.
//---------------------------------------
typedef struct _GameWindow
{
	HWND	hWnd;		//�E�B���h�E�n���h��.
	HDC		hScreenDC;	//�o�b�N�o�b�t�@.
	SIZE	size;		//�T�C�Y.
	DWORD	dwFPS;		//FPS( Frame Per Second: �t���[�� / �b ).
	BOOL	isWndClose;	//�E�B���h�E���Ă邩�m�F�p.
} GameWindow;

// ���W.
typedef struct _Vector2
{
	float x;
	float y;
} Vector2;