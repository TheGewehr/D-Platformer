#include "WalkingEnemy.h"
#include "App.h"
#include "Map.h"
#include "PathFinding.h"
#include "Log.h"
#include "Player.h"
#include "p2List.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "SDL/include/SDL.h"

WalkingEnemy::WalkingEnemy()
{
	texture = nullptr;

	float idleSpeed = 0.4f;
	float movement1Speed = 0.1f;
	float movement2Speed = 0.2f;
	float deathSpeed = 0.1f;

	// IDLE animation right
	rightIdleAnim.PushBack({ 6, 171, 21, 12 });
	rightIdleAnim.PushBack({ 39, 171, 21, 12 });
	rightIdleAnim.PushBack({ 73, 171, 21, 12 });
	rightIdleAnim.PushBack({ 104, 171, 21, 12 });
	rightIdleAnim.PushBack({ 134, 171, 21, 12 });
	rightIdleAnim.PushBack({ 165, 171, 21, 12 });
	rightIdleAnim.PushBack({ 198, 171, 21, 12 });
	rightIdleAnim.PushBack({ 231, 171, 21, 12 });
	rightIdleAnim.PushBack({ 263, 171, 21, 12 });
	rightIdleAnim.PushBack({ 294, 171, 21, 12 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	// IDLE animation left
	leftIdleAnim.PushBack({ 325, 171, 21, 12 });
	leftIdleAnim.PushBack({ 357, 171, 21, 12 });
	leftIdleAnim.PushBack({ 389, 171, 21, 12 });
	leftIdleAnim.PushBack({ 421, 171, 21, 12 });
	leftIdleAnim.PushBack({ 453, 171, 21, 12 });
	leftIdleAnim.PushBack({ 485, 173, 21, 12 });
	leftIdleAnim.PushBack({ 518, 172, 21, 12 });
	leftIdleAnim.PushBack({ 550, 172, 21, 12 });
	leftIdleAnim.PushBack({ 582, 171, 21, 12 });
	leftIdleAnim.PushBack({ 614, 171, 21, 12 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = idleSpeed;

	// WALKING animation right
	runRigthAnim.PushBack({ 295, 236, 21, 12 });
	runRigthAnim.PushBack({ 262, 235, 21, 12 });
	runRigthAnim.PushBack({ 230, 236, 21, 12 });
	runRigthAnim.PushBack({ 197, 237, 21, 12 });
	runRigthAnim.PushBack({ 164, 236, 21, 12 });
	runRigthAnim.PushBack({ 134, 237, 21, 12 });
	runRigthAnim.PushBack({ 102, 236, 21, 12 });
	runRigthAnim.PushBack({ 71, 235, 21, 12 });
	runRigthAnim.PushBack({ 39, 235, 21, 12 });
	runRigthAnim.PushBack({ 6, 235, 21, 12 });
	runRigthAnim.loop = true;
	runRigthAnim.speed = idleSpeed;

	// WALKING animation left
	runLeftAnim.PushBack({ 325, 235, 21, 12 });
	runLeftAnim.PushBack({ 357, 235, 21, 12 });
	runLeftAnim.PushBack({ 389, 237, 21, 12 });
	runLeftAnim.PushBack({ 422, 237, 21, 12 });
	runLeftAnim.PushBack({ 455, 236, 21, 12 });
	runLeftAnim.PushBack({ 485, 237, 21, 12 });
	runLeftAnim.PushBack({ 517, 236, 21, 12 });
	runLeftAnim.PushBack({ 548, 235, 21, 12 });
	runLeftAnim.PushBack({ 580, 235, 21, 12 });
	runLeftAnim.PushBack({ 613, 235, 21, 12 });
	runLeftAnim.loop = true;
	runLeftAnim.speed = idleSpeed;

	// DEATH animation right
	deathFromRightAnim.PushBack({ 324, 308, 21, 12 });
	deathFromRightAnim.PushBack({ 356, 308, 21, 12 });
	deathFromRightAnim.PushBack({ 388, 308, 21, 12 });
	deathFromRightAnim.PushBack({ 421, 237, 21, 12 });
	deathFromRightAnim.PushBack({ 455, 236, 21, 12 });
	deathFromRightAnim.PushBack({ 486, 306, 21, 12 });
	deathFromRightAnim.PushBack({ 519, 302, 21, 12 });
	deathFromRightAnim.PushBack({ 551, 300, 21, 12 });
	deathFromRightAnim.PushBack({ 584, 300, 21, 12 });
	deathFromRightAnim.PushBack({ 614, 299, 21, 12 });
	deathFromRightAnim.loop = true;
	deathFromRightAnim.speed = idleSpeed;

	// DEATH animation left
	deathFromLeftAnim.PushBack({ 295, 308, 21, 12 });
	deathFromLeftAnim.PushBack({ 263, 308, 21, 12 });
	deathFromLeftAnim.PushBack({ 231, 308, 21, 12 });
	deathFromLeftAnim.PushBack({ 198, 308, 21, 12 });
	deathFromLeftAnim.PushBack({ 165, 308, 21, 12 });
	deathFromLeftAnim.PushBack({ 134, 306, 21, 12 });
	deathFromLeftAnim.PushBack({ 101, 302, 21, 12 });
	deathFromLeftAnim.PushBack({ 67, 300, 21, 12 });
	deathFromLeftAnim.PushBack({ 36, 300, 21, 12 });
	deathFromLeftAnim.PushBack({ 5, 299, 21, 12 });
	deathFromLeftAnim.loop = true;
	deathFromLeftAnim.speed = idleSpeed;
}



WalkingEnemy::~WalkingEnemy()
{

}

bool WalkingEnemy::Awake()
{

	return true;
}


// Called before the first frame
bool WalkingEnemy::Start()
{
	//textures
	texture = app->tex->Load("Assets/sprites/Enemies.png");

	//enemy stats
	startPosX = 300;
	startPosY = 290;
	speed = { 1.3f,0 };

	// id's :
	// 0 nothing
	// 1 player
	// 2 water
	// 3 holes
	// 4 win
	// 5 Flying Enemy
	// 6 Walking Enemy

	ColHitbox = app->physics->CreateCircle(startPosX, startPosY, 6);
	ColHitbox->id = 5;
	ColHitbox->listener = app->walkingenemy;


	int x_ = (int)x;
	int y_ = (int)y;
	ColHitbox->GetPosition(x_, y_);
	actualStates = WALK;
	isAlive = true;
	lifes = 2;

	LOG("Loading Flying Enemy");

	return true;
}

bool WalkingEnemy::Update(float dt)
{
	if (lifes <= 0)
	{
		actualStates = DIE;
		isAlive = false;
	}

	if (isAlive == true)
	{
		

	}

	if (app->player->GetPlayerWin() == true)
	{
		actualStates = WALK;
	}


	switch (actualStates)
	{
	case WALK:
	{
		


	}break;
	case ATTACK:
	{
		

	}break;
	case DIE:
	{
		

	}break;
	}





	// Enemy movement 

	if (isAlive == true)
	{
		switch (actualStates)
		{
		case WALK:
		{
			

		}break;
		case ATTACK:
		{
			


		}break;
		case DIE:
		{


		}break;
		}
	}

	direction = 0;
	if (direction == 0)
	{
		currentAnimation = &rightIdleAnim;
	}

	currentAnimation->Update();

	return true;
}

bool WalkingEnemy::PostUpdate()
{
	app->render->DrawTexture(texture, positionOfTheObject.x - 5, positionOfTheObject.y, &currentAnimation->GetCurrentFrame());
	return true;
}

bool WalkingEnemy::CleanUp()
{
	LOG("Unloading Enemy");

	return true;
}

int WalkingEnemy::GetEnemyLifes()
{
	return lifes;
}

void WalkingEnemy::SetEnemyLifes(int l)
{
	lifes = l;
}



void WalkingEnemy::SetEnemyState(WALKING_ENEMY_STATE state)
{
	actualStates = state;
}

bool WalkingEnemy::LoadState(pugi::xml_node&)
{
	// startPosX = data.child("startPos").attribute("x").as_float(0);
	// startPosY = data.child("startPos").attribute("y").as_float(0);
	// lifes = data.child("lifes").attribute("value").as_int();
	// isAlive = data.child("isAlive").attribute("value").as_bool();
	// deathAnimAllowed = data.child("deathAnimation").attribute("value").as_bool();
	// 
	// b2Vec2 v = { PIXEL_TO_METERS(startPosX), PIXEL_TO_METERS(startPosY) };
	// ColHitbox->body->SetTransform(v, 0);

	return true;
}

bool WalkingEnemy::SaveState(pugi::xml_node&) const
{
	//LOG("saving player pos");
	//data.child("startPos").attribute("x").set_value(METERS_TO_PIXELS(ColHitbox->body->GetPosition().x));
	//data.child("startPos").attribute("y").set_value(METERS_TO_PIXELS(ColHitbox->body->GetPosition().y));
	//data.child("lifes").attribute("value").set_value(lifes);
	//data.child("isAlive").attribute("value").set_value(isAlive);
	//data.child("deathAnimation").attribute("value").set_value(deathAnimAllowed);

	return true;

	return true;
}

void WalkingEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
	{

	}
	else
	{
		if ((bodyA->id == 5) && (bodyB->id == 1))
		{

			// is hitted by the player

		}
	}
}