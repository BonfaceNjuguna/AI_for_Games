#ifndef MYAPP_HEADER
#define MYAPP_HEADER

#include "Application.h"
#include "Animation.h"
#include "Agent.h"
#include "KeyboardBehaviour.h"

class MyApp : public Application
{
private:
    Animation* myanim;

    Agent* myagent;

    void OnStart() override {
        myanim = new Animation(Rectangle{ 0,0,32,32 }, "bin/yellowbug.txt");



        myagent = new Agent();
        auto keyboard = new KeyboardBehaviour();

        myagent->AddBehaviour(keyboard);

        myagent->anim = myanim;
    }
    void OnDraw() override {
        DrawCircle(200, 200, 20, RED);
        myanim->Draw(Vector2{ 300, 300 }, 0);
        myagent->Draw();
    }

    void OnUpdate(float delta) override {
        myagent->Update(delta);
    }
public:
    MyApp(int x, int y, const char* p) : Application{ x,y,p } {}
};

#endif