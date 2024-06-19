#pragma once
#include "DxLib.h"

class Player;
class Camera
{
public:
	Camera();
	~Camera();

	void Update(const Player& player);

	const VECTOR& Getpos() const { return m_pos; }

private:
	VECTOR m_pos;
};