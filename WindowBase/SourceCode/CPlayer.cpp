#include "CPlayer.h"

CPlayer::CPlayer()
	: m_Position	()
	, m_Speed		( 0.5f )
{	
}

CPlayer::~CPlayer()
{
}

// 描画関数.
void CPlayer::Update()
{
	// Wキー.
	if( GetAsyncKeyState('W') & 0x8000) {
		m_Position.y -= m_Speed;
	}
	// Aキー.
	if( GetAsyncKeyState('A') & 0x8000) {
		m_Position.x -= m_Speed;
	}
	// Sキー.
	if( GetAsyncKeyState('S') & 0x8000) {
		m_Position.y += m_Speed;
	}
	// Dキー.
	if( GetAsyncKeyState('D') & 0x8000) {
		m_Position.x += m_Speed;
	}
}

// 動作関数.
void CPlayer::Draw()
{
}

// 位置情報を取得する.
const Vector2& CPlayer::GetPosition() const 
{
	return m_Position;
}