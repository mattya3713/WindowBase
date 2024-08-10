#pragma once
#include "Global.h"

/*********************************************
*	�E�B���h�E�쐬�N���X
* */

class CWinInit
{
public://�O������A�N�Z�X�\
	CWinInit();		//�R���X�g���N�^
	~CWinInit();	//�f�X�g���N�^

	//�E�B���h�E�쐬�֐�
	HRESULT MakeWindow(HWND* phWnd, HINSTANCE hInstance);

private://private:�O������A�N�Z�X�s�\ �������您������
	//�g�p����CPU���w�肷��
	HRESULT SelectUseCPU(DWORD ProcessAffinitMask);
	//�E�B���h�E�N���X��o�^
	HRESULT RegisterMyWindowClass
	(HINSTANCE hInstance, const char* pApplicationName);
	//�E�B���h�E�̈撲��
	HRESULT AdjustMyWindowRect(
		int* pOutWidth, int* pOutHeight,
		DWORD WindowStyle, int WindowWidth, int WindowHeight);
	//�E�B���h�E�̍쐬
	HRESULT CreateMyWindow(HWND* phWnd, HINSTANCE hInstance,
		const char* pApplicationName, DWORD WindowStyle,
		int WindowWidth, int WindowHeight);

};