#pragma once
#include "Behaviour.h"
#include <raymath.h>
#include <vector>

class FleeBehaviour :
	public Behaviour
{
public:
	FleeBehaviour() {};
	virtual ~FleeBehaviour() {};

	virtual bool Update(Agent* agent, float deltaTime);

	virtual bool Update(Enemy* enemy, float deltatime);

	void SetDestination(Vector2 destination) { m_destination = destination; }

private:
	Vector2 m_destination;
	float m_fleeRadius = 100;
};