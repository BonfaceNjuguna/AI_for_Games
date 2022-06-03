#pragma once

class Agent;
class Enemy;

class Behaviour
{
public:
	Behaviour() {}
	~Behaviour() {}

	virtual bool Update(Agent* agent, float deltatime) = 0;
};