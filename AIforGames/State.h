#pragma once
#include "Transition.h"
#include <vector> 

class Agent;
class Transition;

class State
{
public:
	State() {};
	virtual ~State() {};

	virtual void update(Agent* agent, float deltaTime) = 0;
	virtual void init(Agent* agent) {};
	virtual void exit(Agent* agent) {};

	void addTransition(Transition* transition) {
		m_transitions.push_back(transition);
	}

	Transition* getTriggeredTransition(Agent* agent);

protected:
	std::vector<Transition*>  m_transitions;
};

Transition* State::getTriggeredTransition(Agent* agent) {
	for (auto transition : m_transitions) {
		if (transition->hasTriggered(agent))
			return transition;
	}
	return nullptr;
}