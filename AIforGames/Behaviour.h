#pragma once

class Agent;

class Behaviour
{
public:
	Behaviour() {}
	~Behaviour() {}

	virtual bool Update(Agent* agent, float deltatime) = 0;
};