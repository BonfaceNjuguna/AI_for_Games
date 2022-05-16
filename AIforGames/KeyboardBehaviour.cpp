#include "KeyboardBehaviour.h"
#include <raymath.h>
#include "Agent.h"

bool KeyboardBehaviour::Update(Agent* agent, float deltatime) {
	Vector2 force = { 0, 0 };
	if (IsKeyDown(KEY_UP))
		force.y = -m_speed;

	if (IsKeyDown(KEY_DOWN))
		force.y = m_speed;

	if (IsKeyDown(KEY_LEFT))
		force.x = -m_speed;

	if (IsKeyDown(KEY_RIGHT))
		force.x = m_speed;

	agent->AddForce(force);
	return true;
 }