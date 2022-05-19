#pragma once
#include <raymath.h>
#include <vector>

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update(float deltatime);

	virtual void Draw();

protected:

};
