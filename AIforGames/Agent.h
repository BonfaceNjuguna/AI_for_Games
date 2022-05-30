#pragma once
#include "Animation.h"
#include <raymath.h>
#include <vector>


class Behaviour;

class Agent
{
public:
	Animation* anim;
	Agent();
	virtual ~Agent();

	virtual void Update(float deltatime);

	virtual void Draw();

	void AddBehaviour(Behaviour* b);

	// Movement functions
	void SetPosition(Vector2 position) { m_position = position; }
	Vector2 GetPosition() { return m_position; }
	void SetVelocity(Vector2 velocity) { m_velocity = velocity; }
	Vector2 GetVelocity() { return m_velocity; }
	void SetMaxSpeed(float speed) { m_maxSpeed = speed; }
	float GetMaxSpeed() { return m_maxSpeed; }

	void AddForce(Vector2 force);

protected:
	std::vector<Behaviour*> behaviours;

	Vector2 m_position = { 0, 0 };
	Vector2 m_velocity = { 0, 0 };
	Vector2 m_force = { 0, 0 };
	float m_maxSpeed = 0;
};