#pragma once
#include "Agent.h"
#include "State.h"
#include "Condition.h"
#include <vector>

class IdleState : public State {
public:
	IdleState(){}
	virtual ~IdleState(){}
	virtual void update(Agent* agent, float deltaTime) { agent->SetVelocity({ 0,0 }); }
};

class KeyboardState : public State {
private:
	float m_speed;
public:
	KeyboardState(float sp) : m_speed{ sp } {}
	virtual ~KeyboardState() {}
	virtual void update(Agent* agent, float deltaTime) { 
		Vector2 force = { 0, 0 };
		if (IsKeyDown(KEY_UP))
			force.y = -m_speed;

		if (IsKeyDown(KEY_DOWN))
			force.y = m_speed;

		if (IsKeyDown(KEY_LEFT))
			force.x = -m_speed;

		if (IsKeyDown(KEY_RIGHT))
			force.x = m_speed;

		agent->SetVelocity(force);
	}
};


class AttackState : public State {
public:
	AttackState(Agent* target, float speed) : m_target(target), m_speed(speed) {}
	virtual ~AttackState() {}
	virtual void update(Agent* agent, float deltaTime) {
		Vector2 direction = Vector2Subtract(m_target->GetPosition(), agent->GetPosition());
		direction = Vector2Normalize(direction);
		direction = Vector2Scale(direction, m_speed);

		agent->AddForce(Vector2Subtract(direction, agent->GetVelocity()));
		agent->SetVelocity(direction);
	}
private:
	float m_speed;
	Agent* m_target;
};


class FleeState : public State{
public:
	FleeState(Agent* target, float speed) : a_target(target), a_speed(speed) {}
	virtual ~FleeState() {};
	virtual void update(Agent* agent, float deltaTime) {
		Vector2 direction = Vector2Subtract(a_target->GetPosition(), agent->GetPosition());
		direction = Vector2Normalize(direction);
		direction = Vector2Scale(direction, -a_speed);

		agent->AddForce(Vector2Subtract(direction, agent->GetVelocity()));
		agent->SetVelocity(direction);
	}
private:
	float a_speed;
	Agent* a_target;
};

class WanderState : public State
{
public:
	WanderState() { srand(time(nullptr)); };
	virtual ~WanderState() {};

	virtual void update(Agent* agent, float deltaTime) {
		Vector2 velocity = agent->GetVelocity();
		if (Vector2Length(velocity) == 0)
		{
			velocity = { 0, -1 };

		}
		// The code to calculate the circle center:
		// m_circleDistance from the current agent position, in the same direction as the current velocity
		Vector2 circleCenter = Vector2Scale(Vector2Normalize(velocity), m_circleDistance);

		Vector2 displacement = { 0, -1 };
		displacement = Vector2Scale(displacement, m_circleRadius);
		//
		// Randomly change the vector direction
		// by making it change its current angle
		displacement = SetAngle(displacement, m_wanderAngle);

		//
		// Change wanderAngle just a bit, so it
		// won't have the same value in the
		// next game frame.	
		m_wanderAngle += ((rand() % (int)m_angleChange) - m_angleChange * .5) * 0.01;

		Vector2 wanderForce = Vector2Add(circleCenter, displacement);

		agent->SetVelocity(Vector2Scale(wanderForce, 0.2f));
	}

private:
	Vector2 SetAngle(Vector2 vector, float value) {
		float length = Vector2Length(vector);
		return { cosf(value) * length, sinf(value) * length };
	}

	float m_circleDistance = 60;
	float m_circleRadius = 50;
	float m_wanderAngle = 0;

	const float m_angleChange = 50;
};