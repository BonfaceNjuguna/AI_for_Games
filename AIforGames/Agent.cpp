#include "Agent.h"
#include "KeyboardBehaviour.h"
#include <raymath.h>

Agent::Agent() {}
Agent::~Agent() {}

void Agent::Update(float deltatime) {

	//Zero the current force out
	m_force = { 0,0 };

	//Go through each Behaviour, they will add to this agent's m_force variable
	for (auto b : behaviours) {
		b->Update(this, deltatime);
	}

	//Apply m_force to our velocity and update position
	m_velocity = (Vector2Add(m_velocity, Vector2Scale(m_force, deltatime)));
	m_position = (Vector2Add(m_position, Vector2Scale(m_velocity, deltatime)));
}

void Agent::Draw() {
	float angel = 0;
	auto v = GetVelocity();
	auto l = Vector2Length(v);
	if (l != 0)
	{
		v = Vector2Normalize(v);
		angel = std::atan2(v.y, v.x) * RAD2DEG + 90;
	}
	anim->Draw({ m_position.x,m_position.y }, angel);
	//DrawCircle(m_position.x, m_position.y, 50, Color{ 255,0,0,255 });
}

void Agent::AddBehaviour(Behaviour* b) {
	behaviours.push_back(b);
}


void Agent::AddForce(Vector2 force) {
	m_force = Vector2Add(m_force, force);
}