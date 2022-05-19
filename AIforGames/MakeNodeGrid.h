#pragma once
#include "Graph.h"
#include "MapObject.h"
#include <vector>
#include <glm.hpp>

const float impassable = -1;

std::vector<Node*> MakeNodeGrid(const MapObject& mo, int tilesize, float* terrain) {
	std::vector<Node*> graph;
	graph.reserve(mo.info.size());

	for (int i = 0; i < mo.info.size(); ++i)
	{
		graph.push_back(new Node());
	}

	for (int id = 0; id < mo.info.size(); ++id) {
		const int x = id % mo.x;
		const int y = id / mo.x;

		bool addLeft = x > 0;
		bool addRight = x < mo.x - 1;
		bool addUp = y < mo.y - 1;
		bool addDown = y > 0;

		int goLeft = -1;
		int goRight = 1;
		int goUp = mo.x;
		int goDown = -mo.x;

		bool addUpLeft = addLeft && addUp;
		bool addUpRight = addRight && addUp;
		bool addDownLeft = addDown && addLeft;
		bool addDownRight = addDown && addRight;

		int goUpLeft = goLeft + goUp;
		int goDownLeft = goLeft + goDown;
		int goUpRight = goRight + goUp;
		int goDownRight = goRight + goDown;

		graph[id]->id = id;
		graph[id]->position = glm::vec2{ x * tilesize + tilesize / 2, y * tilesize + tilesize / 2 };


		auto AddConnection = [&](bool canDirection, int offset, float distance = 1.0f) {
			if (canDirection) {
				float weight = terrain[mo.info[id + offset]];
				if (weight != impassable)
				{
					graph[id]->outgoing_edges.push_back(Edge{ graph[id + offset], distance * weight });
				}
			}
		};

		AddConnection(addLeft, goLeft);
		AddConnection(addRight, goRight);
		AddConnection(addUp, goUp);
		AddConnection(addDown, goDown);
	}

	return graph;
}