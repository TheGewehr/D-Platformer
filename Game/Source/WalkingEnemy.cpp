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
#include "Audio.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "SDL/include/SDL.h"

WalkingEnemy::WalkingEnemy()
{
	name.Create("walkingenemy");

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
	startPosX = app->map->MapToWorld(30,6).x;
	startPosY = app->map->MapToWorld(30, 6).y;
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
	ColHitbox->id = 6;
	ColHitbox->listener = app->walkingenemy;


	int x_ = (int)x;
	int y_ = (int)y;
	ColHitbox->GetPosition(x_, y_);
	actualStates = WALK;
	isAlive = true;
	lifes = 2;
	canJump = true;

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

		if (METERS_TO_PIXELS(app->player->GetColHitbox()->body->GetPosition().x) > 832)
		{
			actualStates = ATTACK;

			if (app->player->isAlive == false)
			{
				actualStates = WALK;
			}
		}
		else
		{
			actualStates = WALK;
		}

	}

	if (app->player->GetPlayerWin() == true)
	{
		actualStates = WALK;
	}


	switch (actualStates)
	{
	case WALK:
	{
		
		ColHitbox->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		directionPoint = app->map->WorldToMap(positionOfTheObject.x, positionOfTheObject.y);


		//iPoint playerPos;

		//ColHitbox->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		//directionPoint = app->map->WorldToMap(positionOfTheObject.x, positionOfTheObject.y);

		//playerPos = app->map->WorldToMap(playerPos.x + 15, playerPos.y + 15);

		app->pathfinding->CreatePath(directionPoint, { 29,6 });

		iPoint NextPos;

		const DynArray<iPoint>* lastPath = app->pathfinding->GetLastPath();

		if (lastPath->Count() > 1)
		{
			iPoint path(lastPath->At(1)->x, lastPath->At(1)->y);
			NextPos = path;
		}

		directionPoint = NextPos;

		if (app->physics->debug == true)
		{
			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint i = 0; i < path->Count(); ++i)
			{
				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				app->render->DrawTexture(app->scene->pathTex, pos.x, pos.y);
			}
		}

	}break;
	case ATTACK:
	{
		ColHitbox->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		directionPoint = app->map->WorldToMap(positionOfTheObject.x, positionOfTheObject.y);


		iPoint playerPos;
		app->player->GetColHitbox()->GetPosition(playerPos.x, playerPos.y);

		ColHitbox->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		directionPoint = app->map->WorldToMap(positionOfTheObject.x, positionOfTheObject.y);

		playerPos = app->map->WorldToMap(playerPos.x + 15, playerPos.y + 15);

		app->pathfinding->CreatePath(directionPoint, playerPos);

		iPoint NextPos;

		const DynArray<iPoint>* lastPath = app->pathfinding->GetLastPath();

		if (lastPath->Count() > 1)
		{
			iPoint path(lastPath->At(1)->x, lastPath->At(1)->y);
			NextPos = path;
		}

		directionPoint = NextPos;

		if (app->physics->debug == true)
		{
			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint i = 0; i < path->Count(); ++i)
			{
				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				app->render->DrawTexture(app->scene->pathTex, pos.x, pos.y);
			}
		}

	}break;
	case DIE:
	{
		ColHitbox->GetPosition(positionOfTheObject.x, positionOfTheObject.y);
		directionPoint = app->map->WorldToMap(positionOfTheObject.x, positionOfTheObject.y);

	}break;
	}


	// Enemy movement 

	if (isAlive == true)
	{
		switch (actualStates)
		{
		case WALK:
		{
			directionPoint = app->map->MapToWorld(directionPoint.x, directionPoint.y ); // pixels
			//directionPoint = app->map->MapToWorld(4, 4); // pixels	

			directionPoint = { directionPoint.x + 13, directionPoint.y + 16 };

			ColHitbox->GetPosition(positionOfTheObject.x, positionOfTheObject.y); // pixels



			if (directionPoint.x + 32 < positionOfTheObject.x)
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

		}break;
		case ATTACK:
		{
			
			directionPoint = app->map->MapToWorld(directionPoint.x, directionPoint.y); // pixels
			//directionPoint = app->map->MapToWorld(4, 4); // pixels	

			directionPoint = { directionPoint.x + 13, directionPoint.y + 16 };

			ColHitbox->GetPosition(positionOfTheObject.x, positionOfTheObject.y); // pixels



			if (directionPoint.x + 32 < positionOfTheObject.x)
			{
				if (ColHitbox->body->GetLinearVelocity().x > -0.1f)
				{
					ColHitbox->body->ApplyLinearImpulse({ -0.2f,0.0f }, ColHitbox->body->GetPosition(), true);
				}
			
			}

			if (directionPoint.x > positionOfTheObject.x)
			{
				if (ColHitbox->body->GetLinearVelocity().x < 0.9f)
				{
					ColHitbox->body->ApplyLinearImpulse({ 0.2f,0.0f }, ColHitbox->body->GetPosition(), true);
				}
			}

			if ((directionPoint.y   < positionOfTheObject.y)&& (canJump == true))
			{
				
					ColHitbox->body->ApplyLinearImpulse({ 0.0f,-0.1f }, ColHitbox->body->GetPosition(), true);
					canJump = false;
				
			}

		}break;
		case DIE:
		{
			

		}break;
		}
	}

	switch (actualStates)
	{
	case WALK:
	{
		statesInt = 0;
	}break;
	case ATTACK:
	{
		statesInt = 1;
	}break;
	case DIE:
	{
		statesInt = 2;
	}
	}

	direction = 0;

	if (direction == 0)
	{
		currentAnimation = &rightIdleAnim;
	}

	currentAnimation->Update();

	LOG("%i", lifes);

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

bool WalkingEnemy::LoadState(pugi::xml_node& data)
{

	b2Vec2 v = { PIXEL_TO_METERS(data.child("Pos").attribute("x").as_float()), PIXEL_TO_METERS(data.child("Pos").attribute("y").as_float()) };
	
	 lifes = data.child("lifes").attribute("value").as_int();
	 isAlive = data.child("isAlive").attribute("value").as_bool();
	 deathAnimAllowed = data.child("deathAnimation").attribute("value").as_bool();
	 statesInt = data.child("deathAnimation").attribute("value").as_int();

	 switch (statesInt)
	 {
	 case 0:
	 {
		 actualStates = WALK;
	 }break;
	 case 1:
	 {
		 actualStates =ATTACK;
	 }break;
	 case 2:
	 {
		 actualStates = DIE;
	 }
	 }
	
	 ColHitbox->body->SetTransform(v, 0);

	return true;
}

bool WalkingEnemy::SaveState(pugi::xml_node& data) const
{
	LOG("saving enemy ");

	data.child("Pos").attribute("x").set_value(positionOfTheObject.x);
	data.child("Pos").attribute("y").set_value(positionOfTheObject.y);
	data.child("lifes").attribute("value").set_value(lifes);
	data.child("isAlive").attribute("value").set_value(isAlive);
	data.child("deathAnimation").attribute("value").set_value(deathAnimAllowed);
	data.child("state").attribute("value").set_value(statesInt);

	

	return true;
}

void WalkingEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	// id's :
	// 0 nothing
	// 1 player
	// 2 water
	// 3 holes
	// 4 win
	// 5 Flying Enemy
	// 6 Walking Enemy

	if (bodyB == nullptr)
	{

	}
	else
	{
		if ((bodyA->id == 6) && (bodyB->id == 0))
		{

			
			canJump = true;
			

		}
		if ((bodyA->id == 6) && (bodyB->id == 2))
		{

			if (lifes > 0)
			{
				app->audio->PlayFx(app->scene->water_fx);
				
				lifes--;

				bodyA->body->ApplyLinearImpulse({ 0, -0.5f }, ColHitbox->body->GetPosition(), true);
			}
			else
			{

			}

		}

		if ((bodyA->id == 6) && (bodyB->id == 3))
		{

			if (lifes > 0)
			{
				//app->audio->PlayFx(app->scene->fall_fx);
				
				lifes--;

				bodyA->body->ApplyLinearImpulse({ 0, -0.5f }, ColHitbox->body->GetPosition(), true);
			}
			else
			{

			}

		}
	}
}
