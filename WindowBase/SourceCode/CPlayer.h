#pragma once
#include "Global.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	// “®ìŠÖ”.
	void Update();	

	// •`‰æŠÖ”.
	void Draw();

	// ˆÊ’uî•ñ‚ğæ“¾‚·‚é.
	const Vector2& GetPosition() const;

private:
	Vector2 m_Position;	// À•W.
	float   m_Speed;	// ˆÚ“®‘¬“x.
};
