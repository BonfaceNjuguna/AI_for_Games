#include "../AIforGames/DijkstraSearch.h"
#include "../AIforGames/MapObject.h"
#include "../AIforGames/MakeNodeGrid.h"
#include "../AIforGames/Agent.h"
#include "../AIforGames/Animation.h"
#include <vector>

int main() 
{
    InitWindow(800, 600, "Hooking in Raylib in a new project");

    //Agent h;


    Animation a(Rectangle{ 0,0,32,32 }, "bin/yellowbug.txt");

    MapObject map("bin/level1.map");
    float terrain[] = { 20, 1, 1, 6 };

    auto nodegraph = MakeNodeGrid(map, 32, terrain);//grid

    ResetNodes(nodegraph);

    auto list = dijkstraSearch(nodegraph[20], nodegraph[90]); //find this path

    std::vector<Node*> path(list.begin(), list.end());

    while (!WindowShouldClose())
    {
        BeginDrawing();
        map.Draw();
        for (int i = 1; i < path.size(); i++)
        {
            DrawLine(path[i - 1]->position.x, path[i - 1]->position.y, path[i]->position.x, path[i]->position.y, { 255,0,0,255 });
        }
        //h.Draw();
        a.Draw(Vector2{ 300, 300 }, 0);
        EndDrawing();
    }


    return 0;
}