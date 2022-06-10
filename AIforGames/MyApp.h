#ifndef MYAPP_HEADER
#define MYAPP_HEADER

#include "Application.h"
#include "Animation.h"
#include "Agent.h"
#include "MakeNodeGrid.h"
#include "MapObject.h"
#include "DijkstraSearch.h"
#include "Behaviour.h"
#include "Condition.h"
#include "FSM.h"
#include "State.h"
#include "WithinRangeCondition.h"
#include "EnemyStates.h"
#include <vector>

class MyApp : public Application
{
private:
    Animation* myanim;
    Animation* enemyanim;

    Agent* myagent;
    Agent* myenemy;

    //std::vector <Agent*> agentList;

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

        //agent
        myagent = new Agent();   
        myenemy = new Agent();
        FiniteStateMachine* agentFiniteStateMachine = new FiniteStateMachine();
        myagent->AddBehaviour(agentFiniteStateMachine);
        myagent->SetPosition({ screenWidth * 0.5f, screenHeight * 0.5f });
        myagent->anim = myanim;

        auto fleeState = new FleeState(myenemy, 90);
        auto agentKeyboardState = new KeyboardState(80);

        //enemy target
        auto enemyWithinRangeCondition = new WithinRangeCondition(myenemy, 150);
        auto enemyRange = new WithinRangeCondition(myenemy, 250);
        auto enemyOutOfRangeCondition = new InvertCondition(enemyRange);
        agentFiniteStateMachine->addCondition(enemyRange);
        agentFiniteStateMachine->addCondition(enemyOutOfRangeCondition); 
        auto fleeToKeyboard = new Transition(agentKeyboardState, enemyOutOfRangeCondition);
        fleeState->addTransition(fleeToKeyboard);

        auto keyboardToFlee = new Transition(fleeState, enemyWithinRangeCondition);
        agentKeyboardState->addTransition(keyboardToFlee);
        agentFiniteStateMachine->addState(fleeState);
        agentFiniteStateMachine->addState(agentKeyboardState);
        agentFiniteStateMachine->addCondition(enemyWithinRangeCondition);
        agentFiniteStateMachine->addTransition(keyboardToFlee);
        agentFiniteStateMachine->setCurrentState(agentKeyboardState);

        //enemy
        FiniteStateMachine* enemyFiniteStateMachine = new FiniteStateMachine();
        myenemy->AddBehaviour(enemyFiniteStateMachine);
        myenemy->anim = enemyanim;
        myenemy->SetPosition({ screenWidth * 0.7f, screenHeight * 0.35f });

        auto attackState = new AttackState(myagent, 80);
        auto wanderState = new WanderState();
        
        // create the condition, setting the agent as the target
        auto agentWithinRangeCondition = new WithinRangeCondition(myagent, 150);
        auto agentOutOfRangeCondition = new WithinRangeCondition(myagent, 200);
        auto agentOutOfRange = new InvertCondition(agentOutOfRangeCondition);
        //stop chasing if away
        auto attackToWander = new Transition(wanderState, agentOutOfRange);
        attackState->addTransition(attackToWander);
        //enemyFiniteStateMachine->addTransition(attackToWander);
        enemyFiniteStateMachine->addCondition(agentOutOfRange);
        enemyFiniteStateMachine->addCondition(agentOutOfRangeCondition);

        // create the transition, this will transition to the attack state when the
        // withinRange condition is met
        auto toAttackTransition = new Transition(attackState, agentWithinRangeCondition);

        // add the transition to the idle state
        wanderState->addTransition(toAttackTransition);
        // add all the states, conditions and transitions to the FSM (the enemy
        // behaviour)
        enemyFiniteStateMachine->addState(attackState);
        enemyFiniteStateMachine->addState(wanderState);
        enemyFiniteStateMachine->addCondition(agentWithinRangeCondition);
        enemyFiniteStateMachine->addTransition(toAttackTransition);
        // set the current state of the FSM
        enemyFiniteStateMachine->setCurrentState(wanderState);


        //behaviours
        /*KeyboardBehaviour* keyboard = new KeyboardBehaviour();
        WanderBehaviour* wander = new WanderBehaviour();
        SeekBehaviour* seek = new SeekBehaviour();
        FleeBehaviour* flee = new FleeBehaviour();*/

        //agent
        /*myagent = new Agent();
        myagent->AddBehaviour(wander);
        myagent->SetPosition({ (float)(screenWidth >> 1), (float)(screenHeight >> 1) });
        myagent->SetMaxSpeed(50);
        myagent->anim = myanim;*/

        //Make a heap of agents
        //for (int i = 0; i < 2; ++i)
        //{
        //    auto newAgent = new Agent();
        //    if (i < 1)
        //    { //Make Flee-ing agents
        //        newAgent->AddBehaviour(wander);
        //        newAgent->SetPosition({ 150, 150 });
        //        newAgent->SetMaxSpeed(50);
        //        newAgent->anim = myanim;
        //    }
        //    else
        //    { //Make Attacking agents.
        //        newAgent->AddBehaviour(wander);
        //        newAgent->SetPosition({ 250, 250 });
        //        newAgent->SetMaxSpeed(50);
        //        newAgent->anim = enemyanim;
        //    }
        //    agentList.push_back(newAgent);
        //}
    }
    void OnDraw() override {
        map->Draw();
        //DrawCircle(200, 200, 20, RED);
        //myanim->Draw(Vector2{ 300, 300 }, 0);
        myagent->Draw();
        myenemy->Draw();

        Vector2 agentPos = myagent->GetPosition();
        if (agentPos.y < 0)
            agentPos.y = screenHeight;
        if (agentPos.y > screenHeight)
            agentPos.y = 0;
        if (agentPos.x < 0)
            agentPos.x = screenWidth;
        if (agentPos.x > screenWidth)
            agentPos.x = 0;
        myagent->SetPosition(agentPos);

        /*Vector2 enemyPos = myenemy->GetPosition();
        if (enemyPos.y < 0)
            enemyPos.y = screenHeight;
        if (enemyPos.y > screenHeight)
            enemyPos.y = 0;
        if (enemyPos.x < 0)
            enemyPos.x = screenWidth;
        if (enemyPos.x > screenWidth)
            enemyPos.x = 0;
        myenemy->SetPosition(enemyPos);*/

        /*for (auto a : agentList) {
            a->Draw();
        }*/
        
    }

    void OnUpdate(float delta) override {
        myagent->Update(delta);
        myenemy->Update(delta);
        /*for (auto a : agentList) {
            a->Update(delta);
        }*/
    }
public:
    MyApp(int x, int y, const char* p) : Application{ x,y,p } {}

};
#endif