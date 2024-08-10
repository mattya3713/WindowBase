#include "CGame.h"
#include <time.h>		// time関数を使用するために必要.

#include "MyMacro.h"	// マクロ.

// コンストラクタ.
CGame::CGame()
	: CGame( nullptr )
{
}

// コンストラクタ(引数あり).
CGame::CGame( GameWindow* pGameWnd )
	: m_pGameWnd	( pGameWnd )
	, m_hMemDC		( nullptr )
	, m_hWorkMemDC	( nullptr )
	, m_hWorkBmp	( nullptr )
	, m_hFont		( nullptr )

	, m_BackImage   ( nullptr )
	, m_PlayerImage	( nullptr )
	, m_pPlayer		( nullptr )
{
}

// デストラクタ.
CGame::~CGame()
{
	SAFE_DELETE(m_pPlayer);
}

// 構築関数.
bool CGame::Create()
{
	// 乱数の初期化.
	srand( (unsigned int)time( nullptr ) );

	// メモリDCの作成.
	m_hMemDC = CreateCompatibleDC( nullptr );

	// 作業用DCの作成.
	m_hWorkMemDC = CreateCompatibleDC( nullptr );

	// 作業用BITMPの作成.
	m_hWorkBmp = CreateCompatibleBitmap(m_pGameWnd->hScreenDC, WND_W, WND_H);

	// DCとBITMAPを紐づけ.
	SelectObject(m_hWorkMemDC, m_hWorkBmp);

	// フォントの作成.
	m_hFont = CreateFont(
		60,					// 文字高さ.
		20,					// 文字幅.
		0,					// 角度.
		0,					// ベースライン角度.
		FW_REGULAR,			// 太さ(太字:FW_BOLD,通常:FW_REGULAR).
		FALSE,				// 斜体(TRUE:有効).
		FALSE,				// 下線(TRUE:有効).
		FALSE,				// 打ち消し線(TRUE:有効).
		SHIFTJIS_CHARSET,	// 文字セット.
		OUT_DEFAULT_PRECIS,	// 出力精度.
		CLIP_DEFAULT_PRECIS,// クリッピング精度.
		DEFAULT_QUALITY,	// 出力品質.
		VARIABLE_PITCH | FF_ROMAN,	// 可変ピッチとフォントファミリ.
		"" );				// 書体(nullptr:現在使われている書体).

	if (LoadBmp(&m_BackImage,   "Data\\BMP\\Back.bmp"  ) == false) { return false; };
	if (LoadBmp(&m_PlayerImage, "Data\\BMP\\Player.bmp") == false) { return false; };

	// プレイヤーのインスタンス生成
	m_pPlayer = new CPlayer();

	return true;
}

//破棄関数.
void CGame::Destroy()
{
	SAFE_DELETE(m_pPlayer);

	// フォントの解放.
	DeleteObject( m_hFont );

	// メモリDCの解放.
	DeleteDC( m_hMemDC );
}

// 更新関数(キー入力や動作処理を行う).
void CGame::Update()
{
	// F1キー.
	if( GetAsyncKeyState( VK_F1 ) & 0x0001 ) {
		// ウィンドウを閉じる通知を送る.
		PostMessage( m_pGameWnd->hWnd, WM_CLOSE, 0, 0 );
	}

	// プレイヤーの処理.
	m_pPlayer->Update();
}

// 描画関数.
void CGame::Draw()
{
	// 画像を選択.
	SelectObject(m_hMemDC, m_BackImage);

	// プレイヤー座標に画像をセット.
	TransBlt(
		0, 0,
		WND_Wf, WND_Hf,
		m_hMemDC,
		0, 0);

	// 画像を選択.
	SelectObject(m_hMemDC, m_PlayerImage);

	// プレイヤー座標に画像をセット.
	TransBlt(
		m_pPlayer->GetPosition().x,
		m_pPlayer->GetPosition().y,
		64, 64,
		m_hMemDC,
		0, 0);
}

// 画像の読み込み.
bool CGame::LoadBmp(HBITMAP* phBmp, const char* fileName)
{
	*phBmp = (HBITMAP)LoadImage(
		nullptr,					// ｲﾝｽﾀﾝｽ.
		fileName,					// ﾌｧｲﾙ名(ﾊﾟｽ含む).
		IMAGE_BITMAP,				// ﾋﾞｯﾄﾏｯﾌﾟ.
		0, 0,						// 読み込む座標.
		LR_LOADFROMFILE);			// ﾌｧｲﾙから読み込む.

	if (*phBmp == nullptr)
	{
		MessageBox(
			nullptr,
			fileName, "画像読み込みの失敗", MB_OK);
		return false;
	}
	return true;
}

// 透過表示.
bool CGame::TransBlt(float xDest, float yDest, float wDest, float hDest,
	HDC hdcSrc, float xSrc, float ySrc)
{
	if (TransparentBlt(
		m_pGameWnd->hScreenDC,	 // 表示先(実はﾃﾞｨｽﾌﾟﾚｲ).
		static_cast<int>(xDest), // 表示位置x座標.
		static_cast<int>(yDest), // 表示位置y座標.
		static_cast<int>(wDest), // 表示幅.
		static_cast<int>(hDest), // 表示高さ.
		hdcSrc,					 // 画像が設定されたﾒﾓﾘDC.
		static_cast<int>(xSrc),  // 元画像の切り出し開始x座標.
		static_cast<int>(ySrc),	 // 元画像の切り出し開始y座標.
		static_cast<int>(wDest), // 元画像の切り出し幅.
		static_cast<int>(hDest), // 元画像の切り出し高さ.
		RGB(0x00, 0xFF, 0x00)))  // 透明色(緑を設定).
	{
		return true;
	}

	return false;
}