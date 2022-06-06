#pragma once
#include "Behaviour.h" 
#include "Condition.h"
#include "Agent.h"


class WithinRangeCondition : public Condition {
public:

	WithinRangeCondition(Agent* target, float range)
		: m_target(target), m_range(range) {}
	virtual ~WithinRangeCondition() {}

	virtual bool test(Agent* agent) const {
		// get target position 
		Vector2 targetPos = m_target->GetPosition();

		// get my position 
		Vector2 agentPos = agent->GetPosition();

		// compare the two and get the distance between them 
		float xDiff = targetPos.x - agentPos.x;
		float yDiff = targetPos.y - agentPos.y;
		float distance = sqrtf(xDiff * xDiff + yDiff * yDiff);

		return distance <= m_range;
	}

private:
	Agent* m_target;
	float m_range;
};