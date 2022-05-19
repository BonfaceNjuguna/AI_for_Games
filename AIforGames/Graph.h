#pragma once
#include <raylib.h>
#include <vector>
#include <list>
#include <glm.hpp>

class Node;
class Edge;

struct Edge {
	Node* target;
	float cost;
};

struct Node {

	char id;

	glm::vec2 position;
	std::vector<Edge> outgoing_edges;
	
	float gscore;
	Node* parent;
};

using Path = std::list<Node*>;