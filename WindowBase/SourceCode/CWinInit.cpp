#include "CWinInit.h"
#include "CGame.h"			// �Q�[���N���X.
#pragma comment(lib, "winmm.lib")

//----------------------------------
// �萔�錾.
//----------------------------------
const char APP_NAME[] = "Window";					// �A�v����.
const char WND_TITLE[] = "WindowTitle";				// �E�B���h�E�^�C�g��.

// �X���b�h�֐�.
DWORD WINAPI ThreadFunc( LPVOID vdParam )
{
	// �ϐ��錾
	CGame* pGame = nullptr;	// �|�C���^�̏�������nullptr���g��.
	// �Q�[���N���X�̃C���X�^���X(����)�𐶐�.
	pGame = new CGame( (GameWindow*)vdParam  );// �擪�A�h���X���L���X�g���Ĉڂ�.

	DWORD frames = 0;		// �t���[����.
	DWORD beforeTime = 0;	// �O�̎���.
	char MsgFPS[128] = "";

	// ���Ԃ̎擾.
	beforeTime = timeGetTime();	// ���݂̎��Ԃ��擾.

//----------------------------------------------------------
//	�N������[WM_CREATE].
//----------------------------------------------------------
	if( pGame->Create() == false )	return 0;

	//�E�B���h�E��������܂Ŗ������[�v.
	while( pGame->IsWindowClosed() == FALSE )
	{
		DWORD nowTime = 0;		//���݂̎���.
		DWORD progress = 0;		//�o�ߎ���.
		DWORD idealTime = 0;	//���z����.

		nowTime = timeGetTime();//���݂̎��Ԃ��擾.

		progress = nowTime - beforeTime;	//�o�ߎ���.

		//���z���Ԃ̎Z�o.
		// ( ���݂̃t���[���� �~ ( 1000 �� FPS�l ) ).
		idealTime = (DWORD)( frames * ( 1000.0F / pGame->GetFPS() ) );

		//----------------------------------------------------------
		//  �Q�[������[WM_TIMER].
		//----------------------------------------------------------
		pGame->Update();

		//----------------------------------------------------------
		//	�`�揈��[WM_PAINT].
		//----------------------------------------------------------
		pGame->Draw();

		//�`��̎��ԑ҂�.
		if( idealTime > progress ){
			Sleep( idealTime - progress );	//���ԑ҂�.
		}


		if( progress >= 1000 )	//1�b�o��.
		{
			wsprintf( MsgFPS, "FPS[%03d]", frames );
			beforeTime = nowTime;	//���݂̎��ԂɍX�V.
			frames = 0;
		}
		frames++;	//�t���[����UP.

		//�ĕ`��.
		InvalidateRect( pGame->GetWnd(), nullptr, FALSE );

		Sleep(1);//��ʂ��������̂��ߏ����҂�����
	}

	//----------------------------------------------------------
	//	�������[WM_DESTROY].
	//----------------------------------------------------------
	pGame->Destroy();

	//�s�v�ɂȂ����̂ō폜.
	if( pGame != nullptr ) {
		delete pGame;
		pGame = nullptr;
	}

	//�X���b�h�I���ʒm.
	ExitThread( 0 );

	return TRUE;
}

//�E�B���h�E�֐�.
LRESULT CALLBACK WindowProc(
	HWND hWnd,		//�E�B���h�E�n���h��.
	UINT uMsg,		//���b�Z�[�W.
	WPARAM wParam,	//���b�Z�[�W�ɑΉ�������.
	LPARAM lParam )	//���b�Z�[�W�ɑΉ�������.
{
	HDC hDC;			//�f�o�C�X�R���e�L�X�g.
	PAINTSTRUCT ps;		//�`��\����.

	//----------------------------------------------------------
	//	�X���b�h�֘A.
	//----------------------------------------------------------
	static GameWindow gameWnd;	//�Q�[���E�B���h�E�\����.
	static HANDLE hThread;		//�X���b�h�n���h��.
	DWORD dwID;		//�X���b�hID.
	HBITMAP hBmp;	//�r�b�g�}�b�v�n���h��.

	//���b�Z�[�W�ʂ̏���.
	switch( uMsg ){
	case WM_DESTROY:	//�E�B���h�E���j�����ꂽ��.

		//�A�v���P�[�V�����̏I����Windows�ɒʒm����.
		PostQuitMessage( 0 );
		return 0;

	case WM_CREATE:		//�E�B���h�E����������鎞.
		//----------------------------------------------------------
		//	�X���b�h�̐ݒ�.
		//----------------------------------------------------------
		//�X���b�h�ɓn���l��ݒ�.
		gameWnd.hWnd = hWnd;		//�E�B���h�E�n���h��.
		gameWnd.size.cx = WND_W;	//�E�B���h�E��.
		gameWnd.size.cy = WND_H;	//�E�B���h�E����.
		gameWnd.dwFPS = FPS;		//FPS�l(�).

		//HDC�̍쐬.
		hDC = GetDC( hWnd );	// DC(�f�o�C�X�R���e�L�X�g)���擾.

		//�r�b�g�}�b�v�n���h�����쐬.
		hBmp = CreateCompatibleBitmap(
			hDC,
			gameWnd.size.cx,
			gameWnd.size.cy );

		//DC�ƌ݊����̂���DC���쐬.
		gameWnd.hScreenDC = CreateCompatibleDC( hDC );

		//hScreenDC���r�b�g�}�b�v�p�Ƃ��Ē�`.
		SelectObject( gameWnd.hScreenDC, hBmp );

		//�s�v�ɂȂ���DC�����.
		ReleaseDC( hWnd, hDC );

		//�X���b�h�̍쐬�Ǝ��s.
		hThread = CreateThread(
			nullptr,			//�n���h���𑼂̃v���Z�X�Ƌ��L����ꍇ�͎w��.
			0,					//�X�^�b�N�T�C�Y(�f�t�H���g:0).
			ThreadFunc,			//�X���b�h�֐���.
			(LPVOID)&gameWnd,	//�X���b�h�ɓn���\����.
			0,					//0:�쐬�Ɠ����Ɏ��s.
			&dwID );			//(out)�X���b�hID.

		return 0;
	case WM_KEYDOWN:
		//�L�[�ʂ̏���.
		switch( wParam ){
		case VK_ESCAPE:	//ESC�L�[.
			if( MessageBox( nullptr,
				"�Q�[�����I�����܂���", "�x��", MB_YESNO ) == IDYES )
			{
				//�E�B���h�E����邱�Ƃ�Windows�ɒm�点��.
				PostMessage( gameWnd.hWnd, WM_CLOSE, 0, 0 );
			}
			break;
		}
		return 0;

	case WM_CLOSE:
		//�E�B���h�E����t���O�L��.
		//���X���b�h���Ŋm�F���邽�߂̃t���O.
		gameWnd.isWndClose = TRUE;

		DWORD result;
		while( 1 ) {
			//�X���b�h���I��������`�F�b�N.
			GetExitCodeThread( hThread, &result );
			//�I�������n���h�������.
			if( STILL_ACTIVE != result ) {
				//closehandle�ŕ���.
				CloseHandle( hThread );
				//���[�v�𔲂���.
				break;
			}
		}
		//�E�B���h�E��j������.
		DestroyWindow( hWnd );
		return 0;

	case WM_PAINT:		//�E�B���h�E���X�V���ꂽ��.
		//�`��J�n.
		hDC = BeginPaint( hWnd, &ps );

		BitBlt(
			hDC,				//�\��DC.
			0, 0,				//�\����x,y���W.
			gameWnd.size.cx,	//�\�����镝.
			gameWnd.size.cy,	//�\�����鍂��.
			gameWnd.hScreenDC,	//�o�b�N�o�b�t�@(�X���b�h���ō쐬).
			0, 0,				//���摜��x,y.
			SRCCOPY );			//�R�s�[����.

		//�`��I��.
		EndPaint( hWnd, &ps );
		return 0;
	}

	//���C���ɕԂ����.
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//�R���X�g���N�^
CWinInit::CWinInit()
{
}
//�f�X�g���N�^
CWinInit::~CWinInit()
{
}

HRESULT CWinInit::MakeWindow(HWND* phWnd, HINSTANCE hInstance)
{
	//�g�p����CPU���w�肷��
	if ( FAILED( SelectUseCPU( 1 ) ) ) 	 //CPU1���w��
	{
		return E_FAIL;
	}
	//�E�B���h�E�N���X��o�^����
	if ( FAILED ( RegisterMyWindowClass( hInstance,APP_NAME ) ) )	//CPU1���w��
	{
		return E_FAIL;
	}
	//�E�B���h�E�̈�̒���
	int WindowWidth		= 0;
	int WindowHeight	= 0;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;	//�E�B���h�E�X�^�C��
	if (FAILED
	(AdjustMyWindowRect(
		&WindowWidth, &WindowHeight, dwStyle, WND_W, WND_H)))
	{
		return E_FAIL;
	}
		//�E�B���h�E�̍쐬
	if (FAILED(
		CreateMyWindow(
			phWnd, hInstance, APP_NAME, dwStyle, WindowWidth, WindowHeight)))
	{
		return E_FAIL;
	}
	

	//�E�B���h�E�̕\��.
	// SW_SHOW : �\������.
	// SW_HIDE : �B��(��\��).
	ShowWindow(*phWnd, SW_SHOW);

	return S_OK;
}

HRESULT CWinInit::SelectUseCPU(
	DWORD ProcessAffinitMask)	//CPU�w��(2�i���Ŏw��)
{
	HANDLE hProcess;			//�v���Z�X�n���h��.
	DWORD errnum;				//�G���[No.
	BOOL ret;					//�֐����A�l.

	//���g�̃v���Z�X�̃n���h�����擾.
	hProcess = GetCurrentProcess();

	ret = SetProcessAffinityMask(
		hProcess,
		ProcessAffinitMask);
	if (ret == FALSE)
	{
		errnum = GetLastError();	//�G���[�����擾.
		return E_FAIL;
	}

	return S_OK;
}
//�E�B���h�E�N���X��o�^
HRESULT CWinInit::RegisterMyWindowClass(HINSTANCE hInstance, 
	const char* pApplicationName)
{
	WNDCLASS wc;	//�E�B���h�E�N���X�\����.

	//--------------------------------------
	//  �E�B���h�E�N���X�̓o�^.
	//--------------------------------------
	//�X�^�C���̓o�^.
	// CS_HREDRAW : ���������̍ĕ`��.
	// CS_VREDRAW : ���������̍ĕ`��.
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//�E�B���h�E�֐��̓o�^.
	// DefWindowProc : �f�t�H���g�E�B���h�E�֐�(��Ŏ����ō��).
	wc.lpfnWndProc = WindowProc;
	//�g��Ȃ�(0�Œ�).
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//�C���X�^���X�ԍ��̓o�^.
	wc.hInstance = hInstance;
	//�A�C�R���̓o�^.
	// nullptr : �f�t�H���g.
	wc.hIcon = (HICON)LoadImage(
		nullptr,			//�C���X�^���X.
		"Data\\Image\\icon\\favicon.ico",			//�t�@�C����(�p�X�܂�).
		IMAGE_ICON,		//�r�b�g�}�b�v.
		0, 0,				//�ǂݍ��ލ��W.
		LR_LOADFROMFILE);	//�t�@�C������ǂݍ���.
	//�J�[�\���̓o�^.
	// nullptr : �f�t�H���g.
	wc.hCursor = nullptr;
	//�E�B���h�E�̔w�i�F.
	// LTGRAY_BRUSH : ���邢�D�F.
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	//���j���[�̓o�^.
	// nullptr : �f�t�H���g.
	wc.lpszMenuName = nullptr;
	//�A�v���P�[�V������.
	wc.lpszClassName = APP_NAME;

	//�E�B���h�E��Windows�ɓo�^.
	if (RegisterClass(&wc) == 0) {
		//�G���[���b�Z�[�W�̕\��.
		// MB_OK : OK���݂̂�.
		// MB_YESNO : �͂��E������.
		// MB_OKCANCEL : OK�E�L�����Z��.
		// MB_YESNOCANCEL : �͂��E�������E�L�����Z��.
		MessageBox(nullptr,
			"�E�B���h�E�N���X�o�^���s",
			"�G���[���b�Z�[�W",
			MB_YESNOCANCEL);
		return E_FAIL;
	}

	return S_OK;
}
//�E�B���h�E�̈撲��
HRESULT CWinInit::AdjustMyWindowRect(
	int* pOutWidth, int* pOutHeight,	//(out)�v�Z����
	DWORD WindowStyle, //�E�B���h�E��ʁ@�E�B���h�E�̌`��,���ׂ�WS_OVERLAPPEDWINDOW
	int WindowWidth,   //�E�B���h�E��
	int WindowHeight)  //�E�B���h�E����
{
	RECT rect;			//��`�\����.
	rect.top = 0;			//��.
	rect.left = 0;			//��.
	rect.right = WindowWidth;		//�E.
	rect.bottom = WindowHeight;	//��.

	if (AdjustWindowRect(
		&rect,			//(in)��ʃT�C�Y����������`�\����.(out)�v�Z����.
		WindowStyle,		//�E�B���h�E�X�^�C��.
		FALSE) == 0)	//���j���[�������ǂ����̎w��.
	{
		MessageBox(nullptr, "�E�B���h�E�̈�̒����Ɏ��s", "�G���[���b�Z�[�W", MB_OK);
		return E_NOTIMPL;
	}

	//�E�B���h�E��,�������Z�o
	*pOutWidth = rect.right - rect.left;
	*pOutHeight = rect.bottom - rect.top;

	return S_OK;
}
//�E�B���h�E�̍쐬
HRESULT CWinInit::CreateMyWindow(
	HWND* phWnd, HINSTANCE hInstance, 
	const char* pApplicationName,		//�A�v���P�[�V������
	DWORD WindowStyle,					//�E�B���h�E���
	int WindowWidth, int WindowHeight)	//�E�B���h�E������
{
	*phWnd = CreateWindow(
		pApplicationName,				//�A�v���P�[�V������.
		WND_TITLE,				//�E�B���h�E�^�C�g��.
		WindowStyle,				//�E�B���h�E���.
		100, 100,				//�E�B���h�E�̕\���ʒu(x,y).
		WindowWidth,	//�E�B���h�E�̕�.
		WindowHeight,	//�E�B���h�E�̍���.
		nullptr,				//�e�E�B���h�E�̃n���h��.
		nullptr,				//���j���[�̐ݒ�.
		hInstance,				//�C���X�^���X�ԍ�.
		nullptr);				//�E�B���h�E�쐬���ɔ�������C�x���g�ɓn���f�[�^.

	if (*phWnd == nullptr) {
		MessageBox(nullptr,
			"�E�B���h�E�쐬���s",
			"�G���[���b�Z�[�W", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
