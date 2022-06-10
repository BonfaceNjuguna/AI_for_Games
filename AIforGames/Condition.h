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

class InvertCondition : public Condition {
	Condition* condition;
public:

	InvertCondition(Condition* c) : condition{ c } {}
	virtual ~InvertCondition() {}

	virtual bool test(Agent* agent) const {
		return !condition->test(agent);
	}

	virtual bool Update(Agent* agent, float deltaTime) {
		if (test(agent))
			return true;
		return false;
	}
};