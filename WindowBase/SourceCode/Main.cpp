#include "CWinInit.h"

//���C���֐�.
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,	//�C���X�^���X�ԍ�(�E�B���h�E�̔ԍ�).
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR lpCmdLine,
	_In_ int nCmdShow )
{
	HWND hWnd;		//�E�B���h�E�n���h��.
	MSG msg;        //���b�Z�[�W.

	//�E�B���h�E�쐬�N���X�̃C���X�^���X�쐬.
	CWinInit* pWinInit = new CWinInit();

	//�E�B���h�E�̍쐬.
	pWinInit->MakeWindow( &hWnd, hInstance );

	//���b�Z�[�W���[�v.
	while( GetMessage( &msg, nullptr, 0, 0 ) > 0 ){
		//�E�B���h�E�֐��Ƀ��b�Z�[�W�𑗂�.
		DispatchMessage( &msg );
	}

	if (pWinInit != nullptr) {
		delete pWinInit;
		pWinInit = nullptr;
	}

	return 0;
}

