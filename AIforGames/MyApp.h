#ifndef MYAPP_HEADER
#define MYAPP_HEADER

#include "Application.h"
#include "Animation.h"
#include "Agent.h"
#include "KeyboardBehaviour.h"
#include "MakeNodeGrid.h"
#include "MapObject.h"
#include "DijkstraSearch.h"
#include "WanderBehaviour.h"
#include "FleeBehaviour.h"
#include "SeekBehaviour.h"
#include <vector>

class MyApp : public Application
{
private:
    Animation* myanim;

    Animation* enemyanim;

    //Agent* myagent;

    std::vector <Agent*> agentList;

    MapObject* map;

    void OnStart() override {
        try
        {
            map = new MapObject("bin/level1.map");
        }
        catch (const std::exception& e)
        {

        }

        float deltaTime = 1;

        map = new MapObject("bin/level1.map");
        myanim = new Animation(Rectangle{ 0,0,32,32 }, "bin/yellowbug.txt");
        enemyanim = new Animation(Rectangle{ 0,0,32,32 }, "bin/enemybug.txt");

        //behaviours
        KeyboardBehaviour* keyboard = new KeyboardBehaviour();
        WanderBehaviour* wander = new WanderBehaviour();
        SeekBehaviour* seek = new SeekBehaviour();
        FleeBehaviour* flee = new FleeBehaviour();

        //agent
        /*myagent = new Agent();
        myagent->AddBehaviour(wander);
        myagent->SetPosition({ (float)(screenWidth >> 1), (float)(screenHeight >> 1) });
        myagent->SetMaxSpeed(50);
        myagent->anim = myanim;*/

        //Make a heap of agents
        for (int i = 0; i < 2; ++i)
        {
            auto newAgent = new Agent();
            if (i < 1)
            { //Make Flee-ing agents
                newAgent->AddBehaviour(wander);
                newAgent->SetPosition({ 150, 150 });
                newAgent->SetMaxSpeed(50);
                newAgent->anim = myanim;
            }
            else
            { //Make Attacking agents.
                newAgent->AddBehaviour(wander);
                newAgent->SetPosition({ 250, 250 });
                newAgent->SetMaxSpeed(50);
                newAgent->anim = enemyanim;
            }
            agentList.push_back(newAgent);
        }
    }
    void OnDraw() override {
        map->Draw();
        //DrawCircle(200, 200, 20, RED);
        //myanim->Draw(Vector2{ 300, 300 }, 0);
        /*myagent->Draw();

        Vector2 pos = myagent->GetPosition();
        if (pos.y < 0)
            pos.y = screenHeight;
        if (pos.y > screenHeight)
            pos.y = 0;
        if (pos.x < 0)
            pos.x = screenWidth;
        if (pos.x > screenWidth)
            pos.x = 0;
        myagent->SetPosition(pos);*/

        for (auto a : agentList) {
            a->Draw();
        }
        
    }

    void OnUpdate(float delta) override {
        //myagent->Update(delta);
        for (auto a : agentList) {
            a->Update(delta);
        }
    }
public:
    MyApp(int x, int y, const char* p) : Application{ x,y,p } {}


};
#endif