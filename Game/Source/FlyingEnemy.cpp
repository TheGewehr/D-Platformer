#include "FlyingEnemy.h"
#include "App.h"
#include "Map.h"
#include "PathFinding.h"
#include "Log.h"
#include "Player.h"
#include "p2List.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include"Render.h"
#include"Window.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "SDL/include/SDL.h"

FlyingEnemy::FlyingEnemy()
{
	texture = nullptr;

}



FlyingEnemy::~FlyingEnemy()
{

}

bool FlyingEnemy::Awake()
{
	float idleSpeed = 0.1f;
	float movement1Speed = 0.1f;
	float movement2Speed = 0.2f;
	float deathSpeed = 0.1f;

	// IDLE animation right
	rightIdleAnim.PushBack({ 3, 15, 19, 33 });
	rightIdleAnim.PushBack({ 4, 15, 19, 33 });
	rightIdleAnim.PushBack({ 5, 15, 20, 33 });
	rightIdleAnim.PushBack({ 6, 15, 19, 33 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	return true;
}


// Called before the first frame
bool FlyingEnemy::Start()
{
	//textures
	texture = app->tex->Load("Assets/sprites/Enemies.png");

	//enemy stats
	//startPosX = 10;
	//startPosY = 1;
	// speed = { 1.3,0 };
	
	// id's :
	// 0 nothing
	// 1 player
	// 2 water
	// 3 holes
	// 4 win
	// 5 Flying Enemy
	// 6 Walking Enemy

	//ColHitbox = app->physics->CreateCircle(startPosX, startPosY, 6);
	//ColHitbox->id = 5;
	//ColHitbox->listener = app->flyingenemy;


	// int x_ = (int)x;
	// int y_ = (int)y;
	// ColHitbox->GetPosition(x_, y_);
	// actualState = PATROLLING;

	LOG("Loading Flying Enemy");

	return true;
}

bool FlyingEnemy::Update(float dt)
{
	/*
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->map->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (originSelected == true)
		{
			app->pathfinding->CreatePath(origin, p);
			originSelected = false;
		}
		else
		{
			origin = p;
			originSelected = true;
		}
	}
	*/

	iPoint pos;
	ColHitbox->GetPosition(pos.x, pos.y);

	iPoint listMapPosition = app->map->WorldToMap(pos.x, pos.y);
	iPoint pixMapPosition = app->map->MapToWorld(listMapPosition.x, listMapPosition.y);

	DetectionRange = app->player->GetColHitbox()->body->GetPosition();

	ColHitbox->body->ApplyLinearImpulse({ 0.0f, -30.0f }, ColHitbox->body->GetPosition(), true);
	
	if (isAlive == true)
	{
		// if (((DetectionRange.x < 3000) && (DetectionRange.x > -3000)) && ((DetectionRange.y < 3000) && (DetectionRange.y > -3000)))
		// {
		// 	actualState = CHASING_PLAYER;
		// }
		// else
		// {
		// 	actualState = PATROLLING;
		// }

		actualState = PATROLLING;
	}
	else
	{
		actualState = PATROLLING;
	}

	switch (actualState)
	{
	case CHASING_PLAYER:
	{
		// chase the player

		// Make the pathfinding

		// advance one tile

	}break;
	case PATROLLING:
	{
		//  Maintain the position
		

		
		

		if (pos.x > pixMapPosition.x)
		{
			if (ColHitbox->body->GetLinearVelocity().x < -1.0f)
			{
				ColHitbox->body->ApplyLinearImpulse({ -1.0f,0.0f }, ColHitbox->body->GetPosition(), true);
			}			
		}

		if (pos.x < pixMapPosition.x)
		{
			if (ColHitbox->body->GetLinearVelocity().x > 1.0f)
			{
				ColHitbox->body->ApplyLinearImpulse({ 1.0f,0.0f }, ColHitbox->body->GetPosition(), true);
			}
		}


		if (pos.y > pixMapPosition.y)
		{
			if (ColHitbox->body->GetLinearVelocity().y < -1.0f)
			{
				ColHitbox->body->ApplyLinearImpulse({ 0.0f,-1.0f }, ColHitbox->body->GetPosition(), true);
			}
		}

		if (pos.y < pixMapPosition.y)
		{
			if (ColHitbox->body->GetLinearVelocity().x > 1.0f)
			{
				ColHitbox->body->ApplyLinearImpulse({ 0.0f, 1.0f }, ColHitbox->body->GetPosition(), true);
			}
		}
		

		

	}break;
	case DEATH:
	{
		deathAnimAllowed = true;
		// dies and become a kinematic object
	}break;
	}

	currentAnimation = &rightIdleAnim;

	

	return true;
}

bool FlyingEnemy::PostUpdate()
{

	app->render->DrawTexture(texture, METERS_TO_PIXELS(ColHitbox->body->GetPosition().x) , METERS_TO_PIXELS(ColHitbox->body->GetPosition().y) , &currentAnimation->GetCurrentFrame());
	return true;
}

bool FlyingEnemy::CleanUp()
{
	LOG("Unloading Enemy");

	return true;
}

int FlyingEnemy::GetEnemyLifes()
{
	return lifes;
}

void FlyingEnemy::SetEnemyLifes(int l)
{
	lifes = l;
}



void FlyingEnemy::SetEnemyState(FLYING_ENEMY_STATE state)
{
	actualState = state;
}

bool FlyingEnemy::LoadState(pugi::xml_node&)
{


	return true;
}

bool FlyingEnemy::SaveState(pugi::xml_node&) const
{


	return true;
}

void FlyingEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
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
