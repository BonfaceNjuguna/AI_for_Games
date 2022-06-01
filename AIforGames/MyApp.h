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
#include "WanderBehaviour.h"
#include "FleeBehaviour.h"
#include "SeekBehaviour.h"

class MyApp : public Application
{
private:
    Animation* myanim;

    Animation* enemyanim;

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

        float deltaTime = 0;

        map = new MapObject("bin/level1.map");
        myanim = new Animation(Rectangle{ 0,0,32,32 }, "bin/yellowbug.txt");
        enemyanim = new Animation(Rectangle{ 6,6,32,32 }, "bin/enemybug.txt");

        //behaviours
        KeyboardBehaviour* keyboard = new KeyboardBehaviour();
        WanderBehaviour* wander = new WanderBehaviour();
        SeekBehaviour* seek = new SeekBehaviour();
        FleeBehaviour* flee = new FleeBehaviour();

        //agent
        myagent = new Agent();
        myagent->AddBehaviour(wander);
        myagent->SetPosition({ (float)(screenWidth >> 1), (float)(screenHeight >> 1) });
        myagent->SetMaxSpeed(50);
        myagent->anim = myanim;

        //enemy
        myenemy = new Enemy();
        myenemy->anim = enemyanim;
        myenemy->SetPosition({ 150,150 });
    }
    void OnDraw() override {
        map->Draw();
        //DrawCircle(200, 200, 20, RED);
        //myanim->Draw(Vector2{ 300, 300 }, 0);
        //enemyanim->Draw(Vector2{ 300, 300 }, 0);
        myagent->Draw();
        myenemy->Draw();

        Vector2 pos = myagent->GetPosition();
        if (pos.y < 0)
            pos.y = screenHeight;
        if (pos.y > screenHeight)
            pos.y = 0;
        if (pos.x < 0)
            pos.x = screenWidth;
        if (pos.x > screenWidth)
            pos.x = 0;
        myagent->SetPosition(pos);
        
    }

    void OnUpdate(float delta) override {
        myagent->Update(delta);
        myenemy->Update(delta);
    }
public:
    MyApp(int x, int y, const char* p) : Application{ x,y,p } {}


};
#endif