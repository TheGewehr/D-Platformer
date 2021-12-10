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
	rightIdleAnim.PushBack({ 6, 171, 21, 12 });
	rightIdleAnim.PushBack({ 39, 171, 21, 12 });
	rightIdleAnim.PushBack({73, 171, 21, 12 });
	rightIdleAnim.PushBack({ 104, 171, 21, 12 });
	rightIdleAnim.PushBack({ 134, 171, 21, 12 });
	rightIdleAnim.PushBack({ 165, 171, 21, 12 });
	rightIdleAnim.PushBack({ 198, 171, 21, 12 });
	rightIdleAnim.PushBack({ 231, 171, 21, 12 });
	rightIdleAnim.PushBack( {263, 171, 21, 12 });
	rightIdleAnim.PushBack({ 294, 171, 21, 12 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	//// IDLE animation left
	//leftIdleAnim.PushBack({ 263, 15, 19, 33 });
	//leftIdleAnim.PushBack({ 215, 15, 19, 33 });
	//leftIdleAnim.PushBack({ 167, 15, 20, 33 });
	//leftIdleAnim.PushBack({ 119, 15, 19, 33 });
	//leftIdleAnim.loop = true;
	//leftIdleAnim.speed = idleSpeed;
	//
	//// Walking animation right
	//walkingRigthAnim.PushBack({ 297, 63, 23, 33 });
	//walkingRigthAnim.PushBack({ 346, 62, 20, 34 });
	//walkingRigthAnim.PushBack({ 393, 61, 17, 35 });
	//walkingRigthAnim.PushBack({ 439, 63, 19, 33 });
	//walkingRigthAnim.PushBack({ 489, 62, 17, 34 });
	//walkingRigthAnim.PushBack({ 538, 61, 21, 35 });
	//walkingRigthAnim.loop = true;
	//walkingRigthAnim.speed = movement1Speed;
	//
	//// Walking animation left
	//walkingLeftAnim.PushBack({ 256, 63, 23, 33 });
	//walkingLeftAnim.PushBack({ 210, 62, 20, 34 });
	//walkingLeftAnim.PushBack({ 166, 61, 17, 35 });
	//walkingLeftAnim.PushBack({ 118, 63, 19, 33 });
	//walkingLeftAnim.PushBack({ 70, 62, 17, 34 });
	//walkingLeftAnim.PushBack({ 17, 61, 21, 35 });
	//walkingLeftAnim.loop = true;
	//walkingLeftAnim.speed = movement1Speed;
	//
	//// Running animation right
	//runningRigthAnim.PushBack({ 292, 111, 25, 33 });
	//runningRigthAnim.PushBack({ 344, 113, 25, 31 });
	//runningRigthAnim.PushBack({ 388, 113, 25, 31 });
	//runningRigthAnim.PushBack({ 436, 112, 26, 32 });
	//runningRigthAnim.PushBack({ 488, 113, 26, 31 });
	//runningRigthAnim.PushBack({ 532, 113, 26, 31 });
	//runningRigthAnim.loop = true;
	//runningRigthAnim.speed = movement2Speed;
	//
	//// Running animation left
	//runningLeftAnim.PushBack({ 259, 111, 25, 33 });
	//runningLeftAnim.PushBack({ 207, 113, 25, 31 });
	//runningLeftAnim.PushBack({ 163, 113, 25, 31 });
	//runningLeftAnim.PushBack({ 114, 112, 26, 32 });
	//runningLeftAnim.PushBack({ 62, 113, 26, 31 });
	//runningLeftAnim.PushBack({ 18, 113, 26, 31 });
	//runningLeftAnim.loop = true;
	//runningLeftAnim.speed = movement2Speed;
	//
	//// Jumping animation right
	//jumpingRigthAnim.PushBack({ 297, 209, 16, 31 });
	//jumpingRigthAnim.PushBack({ 342, 208, 18, 32 });
	//jumpingRigthAnim.PushBack({ 388, 206, 20, 34 });
	//jumpingRigthAnim.PushBack({ 436, 201, 19, 34 });
	//jumpingRigthAnim.PushBack({ 483, 198, 19, 39 });
	//jumpingRigthAnim.PushBack({ 531, 206, 20, 34 });
	//jumpingRigthAnim.loop = true;
	//jumpingRigthAnim.speed = movement1Speed;
	//
	//// Jumping animation left
	//jumpingLeftAnim.PushBack({ 263, 209, 16, 31 });
	//jumpingLeftAnim.PushBack({ 216, 208, 18, 32 });
	//jumpingLeftAnim.PushBack({ 168, 206, 20, 34 });
	//jumpingLeftAnim.PushBack({ 121, 201, 19, 34 });
	//jumpingLeftAnim.PushBack({ 74, 198, 19, 39 });
	//jumpingLeftAnim.PushBack({ 25, 206, 20, 34 });
	//jumpingLeftAnim.loop = true;
	//jumpingLeftAnim.speed = movement1Speed;
	//
	//// Getting hit right
	//hitFromRightAnim.PushBack({ 294, 255, 19, 33 });
	//hitFromRightAnim.PushBack({ 343, 255, 19, 33 });
	//hitFromRightAnim.PushBack({ 391, 255, 18, 33 });
	//hitFromRightAnim.loop = false;
	//hitFromRightAnim.speed = movement1Speed;
	//
	//// Getting hit left
	//hitFromLeftAnim.PushBack({ 263, 255, 19, 33 });
	//hitFromLeftAnim.PushBack({ 214, 255, 19, 33 });
	//hitFromLeftAnim.PushBack({ 167, 255, 18, 33 });
	//hitFromLeftAnim.loop = false;
	//hitFromLeftAnim.speed = movement1Speed;
	//
	//// Death animation right
	//deathFromRightAnim.PushBack({ 294, 303, 19, 33 });
	//deathFromRightAnim.PushBack({ 340, 303, 23, 33 });
	//deathFromRightAnim.PushBack({ 387, 303, 32, 33 });
	//deathFromRightAnim.PushBack({ 435, 303, 35, 33 });
	//deathFromRightAnim.PushBack({ 483, 303, 34, 33 });
	//deathFromRightAnim.PushBack({ 531, 303, 35, 33 });
	//deathFromRightAnim.loop = false;
	//deathFromRightAnim.speed = deathSpeed;
	//
	//// Death animation left
	//deathFromLeftAnim.PushBack({ 263, 303, 19, 33 });
	//deathFromLeftAnim.PushBack({ 213, 303, 23, 33 });
	//deathFromLeftAnim.PushBack({ 157, 303, 32, 33 });
	//deathFromLeftAnim.PushBack({ 106, 303, 35, 33 });
	//deathFromLeftAnim.PushBack({ 59, 303, 34, 33 });
	//deathFromLeftAnim.PushBack({ 10, 303, 35, 33 });
	//deathFromLeftAnim.loop = false;
	//deathFromLeftAnim.speed = deathSpeed;

	return true;
}


// Called before the first frame
bool FlyingEnemy::Start()
{
	//textures
	texture = app->tex->Load("Assets/sprites/Enemies.png");

	//enemy stats
	startPosX = 100;
	startPosY = 200;
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
	ColHitbox->listener = app->flyingenemy;


	 int x_ = (int)x;
	 int y_ = (int)y;
	 ColHitbox->GetPosition(x_, y_);
	 actualState = PATROLLING;
	 isAlive = true;

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

		ColHitbox->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		directionPoint = app->map->WorldToMap( positionOfTheObject.x, positionOfTheObject.y );
		
	
	}break;
	case DEATH:
	{
		isAlive = false;
		deathAnimAllowed = true;
		ColHitbox->id = 0;
		
	}break;
	}
	
	
	
	

// Enemy movement 

	if (isAlive == true)
	{
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

			directionPoint = app->map->MapToWorld(directionPoint.x, directionPoint.y-1); // pixels
			//directionPoint = app->map->MapToWorld(4, 4); // pixels	

			directionPoint = { directionPoint.x + 13, directionPoint.y + 16 };

			ColHitbox->GetPosition(positionOfTheObject.x, positionOfTheObject.y); // pixels



			if (directionPoint.x < positionOfTheObject.x)
			{
				if (ColHitbox->body->GetLinearVelocity().x > -0.1f)
				{
					ColHitbox->body->ApplyLinearImpulse({ -0.1f,0.0f }, ColHitbox->body->GetPosition(), true);
				}

			}

			if (directionPoint.x > positionOfTheObject.x)
			{
				if (ColHitbox->body->GetLinearVelocity().x < 0.1f)
				{
					ColHitbox->body->ApplyLinearImpulse({ 0.1f,0.0f }, ColHitbox->body->GetPosition(), true);
				}
			}

			if (directionPoint.y - 10 < positionOfTheObject.y)
			{
				if (ColHitbox->body->GetLinearVelocity().y > -0.2f)
				{
					ColHitbox->body->ApplyLinearImpulse({ 0.0f,-0.1f }, ColHitbox->body->GetPosition(), true);
				}
			}

			//if (directionPoint.y + 10 > positionOfTheObject.y)
			//{
			//	if (ColHitbox->body->GetLinearVelocity().x < 0.2f)
			//	{
			//		ColHitbox->body->ApplyLinearImpulse({ 0.0f, 0.1f }, ColHitbox->body->GetPosition(), true);
			//	}
			//}


		}break;
		case DEATH:
		{
			

		}break;
		}

		
	}
	
	
	

	currentAnimation = &rightIdleAnim;
	currentAnimation->Update();

	
	
	return true;
}

bool FlyingEnemy::PostUpdate()
{

	app->render->DrawTexture(texture, positionOfTheObject.x, positionOfTheObject.y , &currentAnimation->GetCurrentFrame());
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
