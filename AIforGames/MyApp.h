#ifndef MYAPP_HEADER
#define MYAPP_HEADER

#include "Application.h"
#include "Animation.h"
#include "Agent.h"
#include "KeyboardBehaviour.h"
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
        auto keyboard = new KeyboardBehaviour();
        FiniteStateMachine* agentFiniteStateMachine = new FiniteStateMachine();
        //myagent->AddBehaviour(keyboard);
        myagent->AddBehaviour(agentFiniteStateMachine);
        myagent->SetPosition({ screenWidth * 0.5f, screenHeight * 0.5f });
        myagent->anim = myanim;

        auto fleeState = new FleeState(myenemy, 150);
        auto agentIdleState = new IdleState();
        /*auto wanderState = new WanderState();*/

        auto enemyWithinRangeCondition = new WithinRangeCondition(myenemy, 150);
        auto toFleeTransition = new Transition(fleeState, enemyWithinRangeCondition);
        agentIdleState->addTransition(toFleeTransition);
        agentFiniteStateMachine->addState(fleeState);
        agentFiniteStateMachine->addState(agentIdleState);
        /*finiteStateMachine->addState(wanderState);*/
        agentFiniteStateMachine->addCondition(enemyWithinRangeCondition);
        agentFiniteStateMachine->addTransition(toFleeTransition);
        agentFiniteStateMachine->setCurrentState(agentIdleState); //throws an exception position error, not sure why??

        //enemy
        FiniteStateMachine* enemyFiniteStateMachine = new FiniteStateMachine();
        myenemy->AddBehaviour(enemyFiniteStateMachine);
        myenemy->anim = enemyanim;
        myenemy->SetPosition({ screenWidth * 0.7f, screenHeight * 0.35f });

        auto attackState = new AttackState(myagent, 150);
        /*auto wanderState = new WanderState();*/
        auto idleState = new IdleState();
        
        // create the condition, setting the player as the target
        auto agentWithinRangeCondition = new WithinRangeCondition(myagent, 150);

        // create the transition, this will transition to the attack state when the
        // withinRange condition is met
        auto toAttackTransition = new Transition(attackState, agentWithinRangeCondition);

        // add the transition to the idle state
        idleState->addTransition(toAttackTransition);
        // add all the states, conditions and transitions to the FSM (the enemy
        // behaviour)
        enemyFiniteStateMachine->addState(attackState);
        enemyFiniteStateMachine->addState(idleState);
        /*enemyFiniteStateMachine->addState(wanderState);*/
        enemyFiniteStateMachine->addCondition(agentWithinRangeCondition);
        enemyFiniteStateMachine->addTransition(toAttackTransition);
        // set the current state of the FSM
        enemyFiniteStateMachine->setCurrentState(idleState);


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
        //Vector2 enemyPos = myenemy->GetPosition();
        if (agentPos.y < 0)
            agentPos.y = screenHeight;
        if (agentPos.y > screenHeight)
            agentPos.y = 0;
        if (agentPos.x < 0)
            agentPos.x = screenWidth;
        if (agentPos.x > screenWidth)
            agentPos.x = 0;
        myagent->SetPosition(agentPos);

        /*if (enemyPos.y < 0)
            enemyPos.y = screenHeight;
        if (enemyPos.y > screenHeight)
            enemyPos.y = 0;
        if (enemyPos.x < 0)
            enemyPos.x = screenWidth;
        if (enemyPos.x > screenWidth)
            enemyPos.x = 0;*/
        
        //myenemy->SetPosition(enemyPos);

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