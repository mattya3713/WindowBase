#pragma once
#include "Global.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	// ����֐�.
	void Update();	

	// �`��֐�.
	void Draw();

	// �ʒu�����擾����.
	const Vector2& GetPosition() const;

private:
	Vector2 m_Position;	// ���W.
	float   m_Speed;	// �ړ����x.
};
