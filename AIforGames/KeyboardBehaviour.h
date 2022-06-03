#pragma once

#include "Behaviour.h"

class KeyboardBehaviour : public Behaviour
{
public:
	KeyboardBehaviour() {}
	virtual ~KeyboardBehaviour() {}

	virtual bool Update(Agent* agent, float deltatime);
private:
	float m_speed = 10.0f;
};