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


class AttackState : public State {
public:
	AttackState(Agent* target, float speed) : m_target(target), m_speed(speed) {}
	virtual ~AttackState() {}
	virtual void update(Agent* agent, float deltaTime) {
		Vector2 direction = Vector2Subtract(m_target->GetPosition(), agent->GetPosition());
		direction = Vector2Normalize(direction);
		direction = Vector2Scale(direction, m_speed);

		agent->AddForce(Vector2Subtract(direction, agent->GetVelocity()));
		//agent->SetVelocity(direction);
	}
private:
	float m_speed;
	Agent* m_target;
};