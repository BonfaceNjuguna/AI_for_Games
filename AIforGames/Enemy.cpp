#include "Enemy.h"
#include "KeyboardBehaviour.h"
#include <raymath.h>

Enemy::Enemy(){}

Enemy::~Enemy(){}

void Enemy::Update(float deltatime) {

	//Zero the current force out
	m_force = { 0,0 };

	//Go through each Behaviour, they will add to this enemy's m_force variable
	for (auto c : behaviours) {
		c->Update(this, deltatime);
	}
	//Apply m_force to our velocity and update position
	m_velocity = (Vector2Add(m_velocity, Vector2Scale(m_force, deltatime)));
	m_position = (Vector2Add(m_position, Vector2Scale(m_velocity, deltatime)));
}

void Enemy::Draw() {
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

void Enemy::AddBehaviour(Behaviour* c) {
	behaviours.push_back(c);
}

void Enemy::AddForce(Vector2 force)
{
	m_force = Vector2Add(m_force, force);
}
