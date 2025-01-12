#pragma once
#include "Global.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	// 動作関数.
	void Update();	

	// 描画関数.
	void Draw();

	// 位置情報を取得する.
	const Vector2& GetPosition() const;

private:
	Vector2 m_Position;	// 座標.
	float   m_Speed;	// 移動速度.
};
