#pragma once
#include "Behaviour.h"
#include <raymath.h>
#include <vector>

class SeekBehaviour : public Behaviour
{
public:
	SeekBehaviour() {};
	virtual ~SeekBehaviour() {};

	virtual bool Update(Agent* agent, float deltaTime);

	void SetDestination(Vector2 destination) { m_destination = destination; }

private:
	Vector2 m_destination;
};