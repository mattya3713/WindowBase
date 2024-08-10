#include "CPlayer.h"

CPlayer::CPlayer()
	: m_Position	()
	, m_Speed		( 0.5f )
{	
}

CPlayer::~CPlayer()
{
}

// �`��֐�.
void CPlayer::Update()
{
	// W�L�[.
	if( GetAsyncKeyState('W') & 0x8000) {
		m_Position.y -= m_Speed;
	}
	// A�L�[.
	if( GetAsyncKeyState('A') & 0x8000) {
		m_Position.x -= m_Speed;
	}
	// S�L�[.
	if( GetAsyncKeyState('S') & 0x8000) {
		m_Position.y += m_Speed;
	}
	// D�L�[.
	if( GetAsyncKeyState('D') & 0x8000) {
		m_Position.x += m_Speed;
	}
}

// ����֐�.
void CPlayer::Draw()
{
}

// �ʒu�����擾����.
const Vector2& CPlayer::GetPosition() const 
{
	return m_Position;
}