#pragma once
#include <Windows.h>
#include "Global.h"		
#include "CPlayer.h"

#pragma comment( lib, "msimg32.lib" )	// �w��F�𓧉߂��ĕ`��Ŏg�p����.
										// �������̕`��ł��g�p����.

/**************************************************
*	�Q�[���N���X.
**/
class CGame
{
public:
	CGame();	// �R���X�g���N�^.
	CGame( GameWindow* pGameWnd );// �R���X�g���N�^(��������).
	~CGame();	// �f�X�g���N�^.

	// �\�z�֐�.
	bool Create();
	// �j���֐�.
	void Destroy();
	// �X�V�֐�(�L�[���͂⓮�쏈�����s��).
	void Update();
	// �`��֐�(�摜�̕\���������s��).
	void Draw();

	//�E�B���h�E����Ă��邩�m�F.
	BOOL IsWindowClosed() const { return m_pGameWnd->isWndClose; }
	//FPS���擾.
	DWORD GetFPS() const { return m_pGameWnd->dwFPS; }
	//�o�b�N�o�b�t�@���擾.
	HDC GetScreenDC() const { return m_pGameWnd->hScreenDC; }
	//�E�B���h�E�n���h�����擾.
	HWND GetWnd() const { return m_pGameWnd->hWnd; }

private:
	// �摜�̓ǂݍ���.
	bool LoadBmp(HBITMAP* phBmp, const char* fileName);

	// �摜�𓧉߂��ĕ\��.
	bool TransBlt(
		float xDest, float yDest, float wDest, float hDest,
		HDC hdcSrc, float xSrc, float ySrc);
	
private:
	GameWindow*	m_pGameWnd;		// �Q�[���E�B���h�E�\����.
	HDC			m_hMemDC;		// �������f�o�C�X�R���e�L�X�g.
	HDC			m_hWorkMemDC;	// ��ƗpDC.
	HBITMAP		m_hWorkBmp;		// ��ƗpBMP.
	HFONT		m_hFont;		// �t�H���g�n���h��.

	HBITMAP		m_BackImage;	// �w�i�̉摜.
	HBITMAP		m_PlayerImage;	// �v���C���[�̉摜.

	CPlayer*	m_pPlayer;		// �v���C���[.
};
