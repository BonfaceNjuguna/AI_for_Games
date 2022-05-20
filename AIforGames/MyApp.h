#ifndef MYAPP_HEADER
#define MYAPP_HEADER

#include "Application.h"
#include "Animation.h"
#include "Agent.h"
#include "Enemy.h"
#include "KeyboardBehaviour.h"
#include "MakeNodeGrid.h"
#include "MapObject.h"
#include "DijkstraSearch.h"

class MyApp : public Application
{
private:
    Animation* myanim;

    Agent* myagent;

    MapObject* map;

    Enemy* myenemy;

    void OnStart() override {
        try
        {
            map = new MapObject("bin/level1.map");
        }
        catch (const std::exception& e)
        {

        }

        //map = new MapObject("bin/level1.map");
        myanim = new Animation(Rectangle{ 0,0,32,32 }, "bin/yellowbug.txt");

        myagent = new Agent();
        auto keyboard = new KeyboardBehaviour();

        myagent->AddBehaviour(keyboard);

        myagent->anim = myanim;
    }
    void OnDraw() override {
        map->Draw();
        //DrawCircle(200, 200, 20, RED);
        myanim->Draw(Vector2{ 300, 300 }, 0);
        myagent->Draw();
    }

    void OnUpdate(float delta) override {
        myagent->Update(delta);
    }
public:
    MyApp(int x, int y, const char* p) : Application{ x,y,p } {}


};

//MapObject m("bin/level1.map");
//float terrain[] = { impassable, 1, 1, 6 };
//auto nodegraph = MakeNodeGrid(m, 32, terrain);
//auto path = dijkstraSearch(nodegraph[3], nodegraph[290]);

#endif