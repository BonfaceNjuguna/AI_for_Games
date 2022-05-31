#include "KeyboardBehaviour.h"
#include "Enemy.h"
#include "Agent.h"
#include <raymath.h>

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

bool KeyboardBehaviour::Update(Enemy* enemy, float deltatime)
{
	Vector2 force = { 0, 0 };
	if (IsKeyDown(KEY_UP))
		force.y = -m_speed;

	if (IsKeyDown(KEY_DOWN))
		force.y = m_speed;

	if (IsKeyDown(KEY_LEFT))
		force.x = -m_speed;

	if (IsKeyDown(KEY_RIGHT))
		force.x = m_speed;

	enemy->AddForce(force);
	return true;
}
