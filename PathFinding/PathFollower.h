#pragma once
#include "../AIforGames/Behaviour.h"
#include "../AIforGames/DijkstraSearch.h"
#include "../AIforGames/Agent.h"

class PathFollower : public Behaviour
{
public:
	Path path;
	float speed = 20;
	Path::iterator current;

	void SetPath(Path p) {
		path = p;
		current = path.begin();
		current++;
	}

	virtual bool Update(Agent* agent, float deltatime) {
		if (path.empty())
		{
			return true;
		}

		if (current!=path.end())
		{
			glm::vec2 ap{ agent->GetPosition().x, agent->GetPosition().y };
			auto direction = (*current)->position - ap;
			direction = glm::normalize(direction) * speed;
			agent->SetVelocity({ direction.x , direction.y });
			if (glm::distance(ap, (*current)->position) < deltatime * speed)
			{
				current++;
			}
		}
		else {
			agent->SetVelocity({ 0, 0 });
		}
		return true; 
	}
};