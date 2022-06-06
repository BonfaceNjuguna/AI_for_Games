#pragma once
#include "Behaviour.h" 

class Condition : public Behaviour {
public:

	Condition() {}
	virtual ~Condition() {}

	virtual bool test(Agent* agent) const = 0;

	virtual bool Update(Agent* agent, float deltaTime) {
		if (test(agent))
			return true;
		return false;
	}
};