#pragma once
#include "Graph.h"
#include <list>
#include <stdexcept>
#include <unordered_set>
#include <algorithm>
#include <queue>

void ResetNodes(std::vector<Node*>& nodes) {
	for (auto n : nodes)
	{
		n->gscore = std::numeric_limits<float>::max();
	}
}

using Path = std::list<Node*>;

//procedure dijkstraSearch
Path dijkstraSearch(Node* startNode, Node* endNode)
{
	//validate input
	if (!startNode || !endNode)
	{
		throw std::runtime_error("Null nodes supplied");
	}

	//if startNode == endNode
	if (startNode == endNode)
	{
		return Path();
	}

	//initialise the starting node
	startNode->gscore = 0;
	//set startNode parent to null
	startNode->parent = nullptr;

	//create temporary list for storing nodes
	std::vector<Node*> openList;
	std::unordered_set<Node*> closedList;

	//add startNode to openList
	openList.push_back(startNode);

	//while openList is not empty
	while (!openList.empty())
	{
		auto sortByGScore = [](const Node* l, const Node* r) {
			return l->gscore < r->gscore;
		};
		std::sort(openList.begin(), openList.end(), sortByGScore);

		//currentNode = first item in openList
		auto currentNode = openList.front();

		//if end node exit
		if (currentNode == endNode)
		{
			break;
		}

		//remove currentNode from openList
		openList.erase(openList.begin());

		//add currentNode to closedList
		closedList.insert(currentNode);

		//for all connection c in currentNode
		for (auto& e : currentNode->outgoing_edges)
		{
			if (std::find(closedList.begin(), closedList.end(), e.target) == closedList.end())
			{
				// let gScore = currentNode.gscore + e.cost
				float gscore = currentNode->gscore + e.cost;

				//if not yet visited
				if (std::find(openList.begin(), openList.end(), e.target) == openList.end())
				{
					//calculate the sore and update its parent
					e.target->gscore = gscore;


					//add to the openlist for processing
					openList.push_back(e.target);

					//if target not in the openList
					e.target->parent = currentNode;
				}
				else if (gscore < e.target->gscore)
				{
					e.target->gscore = gscore;
					e.target->parent = currentNode;
				}
			}
		}
	}

	//build the path and return
	Path path;
	Node* current_node = endNode;
	if (!endNode->parent)
	{
		return path;
	}

	while (current_node)
	{
		path.push_front(current_node);
		current_node = current_node->parent;
	}
	return path;
}