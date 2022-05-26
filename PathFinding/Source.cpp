#include "../AIforGames/DijkstraSearch.h"
#include "../AIforGames/MapObject.h"
#include "../AIforGames/MakeNodeGrid.h"
#include "../AIforGames/Agent.h"
#include "../AIforGames/Animation.h"
#include <vector>
#include <iostream>

int main() 
{
    InitWindow(800, 600, "Hooking in Raylib in a new project");

    Agent h;

    Animation a(Rectangle{ 0,0,32,32 }, "bin/yellowbug.txt");

    MapObject map("bin/level1.map");
    float terrain[] = { 60, 1, 1, 6 };

    auto nodegraph = MakeNodeGrid(map, 32, terrain); //grid

    //ResetNodes(nodegraph);
    //Node* start;
    //Node* end;
    //auto list = dijkstraSearch(start, end); //find this path

    //std::vector<Node*> path(list.begin(), list.end());

    while (!WindowShouldClose())
    {
        BeginDrawing();

        map.Draw(); // draw map

        h.Draw(); // draw agent
        h.anim = &a; //agent animation

        a.Draw(Vector2{ 300, 300 }, 0); // draw anim

        /*for (int i = 1; i < path.size(); i++)
        {
            DrawLine(path[i - 1]->position.x, path[i - 1]->position.y, path[i]->position.x, path[i]->position.y, { 255,0,0,255 });
        }*/
        
        auto p = GetMousePosition();

        int tileid = map.GetIDAtPosition(p.x, p.y);

        Vector2 mouse_int{ ((int)(p.x / 32)) * 32,((int)p.y / 32) * 32 };


        if (IsMouseButtonPressed(0)) {
            auto end = tileid;

            ResetNodes(nodegraph);//reset the graph

            auto agent_tile = map.GetIDAtPosition(h.GetPosition().x, h.GetPosition().y);

            auto list = dijkstraSearch(nodegraph[agent_tile], nodegraph[end]);
            // in the draw function loop through the path variable and draw from point to point.
        }

        EndDrawing();
    }


    return 0;
}