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
#include "EntityManager.h"
#include "Audio.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "SDL/include/SDL.h"
#include "LevelManager.h"

WalkingEnemy::WalkingEnemy()
{
	name.Create("walkingenemy");

	EntityText = nullptr;

	float idleSpeed = 0.4f;
	float movement1Speed = 0.1f;
	float movement2Speed = 0.2f;
	float deathSpeed = 0.1f;


	// IDLE animation right
	rightIdleAnim.PushBack({ 326, 51, 20, 15 });
	rightIdleAnim.PushBack({ 357, 51, 20, 15 });
	rightIdleAnim.PushBack({ 387, 51, 20, 15 });
	rightIdleAnim.PushBack({ 420, 51, 20, 15 });
	rightIdleAnim.PushBack({ 452, 51, 20, 15 });
	rightIdleAnim.PushBack({ 484, 51, 20, 15 });
	rightIdleAnim.PushBack({ 517, 51, 20, 15 });
	rightIdleAnim.PushBack({ 549, 51, 20, 15 });
	rightIdleAnim.PushBack({ 582, 51, 20, 15 });
	rightIdleAnim.PushBack({ 614, 51, 20, 15 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	// IDLE animation left
	leftIdleAnim.PushBack({ 295, 51, 20, 15 });
	leftIdleAnim.PushBack({ 264, 51, 20, 15 });
	leftIdleAnim.PushBack({ 232, 51, 20, 15 });
	leftIdleAnim.PushBack({ 200, 51, 20, 15 });
	leftIdleAnim.PushBack({ 168, 51, 20, 15 });
	leftIdleAnim.PushBack({ 136, 51, 20, 15 });
	leftIdleAnim.PushBack({ 104, 51, 20, 15 });
	leftIdleAnim.PushBack({ 71, 51, 20, 15 });
	leftIdleAnim.PushBack({ 38, 51, 20, 15 });
	leftIdleAnim.PushBack({ 6, 51, 20, 15 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = idleSpeed;

	// WALKING animation right
	runRigthAnim.PushBack({ 327, 116, 20, 15 });
	runRigthAnim.PushBack({ 359, 116, 20, 15 });
	runRigthAnim.PushBack({ 393, 116, 20, 15 });
	runRigthAnim.PushBack({ 423, 116, 20, 15 });
	runRigthAnim.PushBack({ 452, 116, 20, 15 });
	runRigthAnim.PushBack({ 483, 116, 20, 15 });
	runRigthAnim.PushBack({ 514, 116, 20, 15 });
	runRigthAnim.PushBack({ 547, 116, 20, 15 });
	runRigthAnim.PushBack({ 581, 116, 20, 15 });
	runRigthAnim.PushBack({ 614, 116, 20, 15 });
	runRigthAnim.loop = true;
	runRigthAnim.speed = idleSpeed;

	// WALKING animation left
	runLeftAnim.PushBack({ 294, 116, 20, 15 });
	runLeftAnim.PushBack({ 262, 116, 20, 15 });
	runLeftAnim.PushBack({ 228, 116, 20, 15 });
	runLeftAnim.PushBack({ 197, 116, 20, 15 });
	runLeftAnim.PushBack({ 168, 116, 20, 15 });
	runLeftAnim.PushBack({ 136, 116, 20, 15 });
	runLeftAnim.PushBack({ 105, 116, 20, 15 });
	runLeftAnim.PushBack({ 73, 116, 20, 15 });
	runLeftAnim.PushBack({ 39, 116, 20, 15 });
	runLeftAnim.PushBack({ 6, 116, 20, 15 });
	runLeftAnim.loop = true;
	runLeftAnim.speed = idleSpeed;

	// DEATH animation right
	deathFromRightAnim.PushBack({ 614, 148, 20, 15 });
	deathFromRightAnim.PushBack({ 582, 148, 20, 15 });
	deathFromRightAnim.PushBack({ 550, 148, 20, 15 });
	deathFromRightAnim.PushBack({ 518, 148, 20, 15 });
	deathFromRightAnim.PushBack({ 485, 148, 20, 15 });
	deathFromRightAnim.PushBack({ 452, 148, 20, 15 });
	deathFromRightAnim.PushBack({ 421, 148, 20, 15 });
	deathFromRightAnim.PushBack({ 390, 148, 20, 15 });
	deathFromRightAnim.PushBack({ 357, 148, 20, 15 });
	deathFromRightAnim.PushBack({ 327, 148, 20, 15 });
	deathFromRightAnim.loop = false;
	deathFromRightAnim.speed = idleSpeed;

	// DEATH animation left
	deathFromLeftAnim.PushBack({ 6, 148, 20, 15 });
	deathFromLeftAnim.PushBack({ 39, 148, 20, 15 });
	deathFromLeftAnim.PushBack({ 71, 148, 20, 15 });
	deathFromLeftAnim.PushBack({ 103, 148, 20, 15 });
	deathFromLeftAnim.PushBack({ 135, 148, 20, 15 });
	deathFromLeftAnim.PushBack({ 167, 148, 20, 15 });
	deathFromLeftAnim.PushBack({ 198, 148, 20, 15 });
	deathFromLeftAnim.PushBack({ 231, 148, 20, 15 });
	deathFromLeftAnim.PushBack({ 262, 148, 20, 15 });
	deathFromLeftAnim.PushBack({ 294, 148, 20, 15 });
	deathFromLeftAnim.loop = false;
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
	EntityText = app->tex->Load("Assets/sprites/Enemies.png");

	//enemy stats
	position.x = app->map->MapToWorld(30,6).x;
	position.y = app->map->MapToWorld(30, 6).y;
	speed = { 1.3f,0 };

	// id's :
	// 0 nothing
	// 1 player
	// 2 water
	// 3 holes
	// 4 win
	// 5 Flying Enemy
	// 6 Walking Enemy

	EntityCollider = app->physics->CreateCircle(position.x, position.y, 6);
	EntityCollider->id = 6;
	EntityCollider->listener = app->entitymanager;

	currentAnimation = &rightIdleAnim;

	int x_ = (int)x;
	int y_ = (int)y;
	EntityCollider->GetPosition(x_, y_);
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

		if (METERS_TO_PIXELS(app->entitymanager->player->GetColHitbox()->body->GetPosition().x) > 832)
		{
			actualStates = ATTACK;

			if (app->entitymanager->player->isAlive == false)
			{
				actualStates = WALK;
			}
		}
		else
		{
			actualStates = WALK;
		}

	}

	if (app->entitymanager->player->GetPlayerWin() == true)
	{
		actualStates = WALK;
	}


	switch (actualStates)
	{
	case WALK:
	{
		
		EntityCollider->GetPosition(position.x, position.y);
		directionPoint = app->map->WorldToMap(position.x, position.y);


		//iPoint playerPos;

		//EntityCollider->GetPosition(position.x, position.y);
		//directionPoint = app->map->WorldToMap(position.x, position.y);

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
				app->render->DrawTexture(app->lvlmanager->pathTex, pos.x, pos.y);
			}
		}

	}break;
	case ATTACK:
	{
		EntityCollider->GetPosition(position.x, position.y);
		directionPoint = app->map->WorldToMap(position.x, position.y);


		iPoint playerPos;
		app->entitymanager->player->GetColHitbox()->GetPosition(playerPos.x, playerPos.y);

		EntityCollider->GetPosition(position.x, position.y);
		directionPoint = app->map->WorldToMap(position.x, position.y);

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
				app->render->DrawTexture(app->lvlmanager->pathTex, pos.x, pos.y);
			}
		}

	}break;
	case DIE:
	{
		EntityCollider->GetPosition(position.x, position.y);
		directionPoint = app->map->WorldToMap(position.x, position.y);

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

			EntityCollider->GetPosition(position.x, position.y); // pixels



			if (directionPoint.x + 16 < position.x)
			{
				if (EntityCollider->body->GetLinearVelocity().x > -0.1f)
				{
					EntityCollider->body->ApplyLinearImpulse({ -0.1f,0.0f }, EntityCollider->body->GetPosition(), true);
				}

			}

			if (directionPoint.x - 16 > position.x)
			{
				if (EntityCollider->body->GetLinearVelocity().x < 0.1f)
				{
					EntityCollider->body->ApplyLinearImpulse({ 0.1f,0.0f }, EntityCollider->body->GetPosition(), true);
				}
			}

		}break;
		case ATTACK:
		{
			
			directionPoint = app->map->MapToWorld(directionPoint.x, directionPoint.y); // pixels
			//directionPoint = app->map->MapToWorld(4, 4); // pixels	

			directionPoint = { directionPoint.x + 13, directionPoint.y + 16 };

			EntityCollider->GetPosition(position.x, position.y); // pixels

			iPoint playerPosition;
			app->entitymanager->player->GetColHitbox()->GetPosition(playerPosition.x, playerPosition.y);

			if (playerPosition.x >= position.x)
			{
				if (directionPoint.x + 32 < position.x)
				{
					if (EntityCollider->body->GetLinearVelocity().x > -0.1f)
					{
						EntityCollider->body->ApplyLinearImpulse({ -0.2f,0.0f }, EntityCollider->body->GetPosition(), true);
					}

				}

				if (directionPoint.x + 16 > position.x)
				{
					if (EntityCollider->body->GetLinearVelocity().x < 0.9f)
					{
						EntityCollider->body->ApplyLinearImpulse({ 0.2f,0.0f }, EntityCollider->body->GetPosition(), true);
					}
				}
			}
			else
			{
				if (directionPoint.x - 32 < position.x)
				{
					if (EntityCollider->body->GetLinearVelocity().x > -0.1f)
					{
						EntityCollider->body->ApplyLinearImpulse({ -0.2f,0.0f }, EntityCollider->body->GetPosition(), true);
					}

				}

				if (directionPoint.x - 16 > position.x)
				{
					if (EntityCollider->body->GetLinearVelocity().x < 0.9f)
					{
						EntityCollider->body->ApplyLinearImpulse({ 0.2f,0.0f }, EntityCollider->body->GetPosition(), true);
					}
				}
			}

			

			if ((directionPoint.y   < position.y)&& (canJump == true))
			{
				
					EntityCollider->body->ApplyLinearImpulse({ 0.0f,-0.12f }, EntityCollider->body->GetPosition(), true);
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

	if (isAlive == true)
	{
		if (EntityCollider->body->GetLinearVelocity().x < 0)
		{
			direction = 3;
		}
		else if (EntityCollider->body->GetLinearVelocity().x > 0)
		{
			direction = 2;
		}
		else if ((EntityCollider->body->GetLinearVelocity().x == 0))
		{
			if (direction == 2) {
				direction = 0;
			}
			if (direction == 3) {
				direction = 1;
			}
		}
	}
	else
	{
		if (deathAnimAllowed == true)
		{
			if (direction == 0) {
				direction = 4;
			}
			if (direction == 1) {
				direction = 5;
			}
			if (direction == 2) {
				direction = 4;
			}
			if (direction == 3) {
				direction = 5;
			}
		}

	}


	if (direction == 0)
	{
		currentAnimation = &rightIdleAnim;
	}
	else if (direction == 1)
	{
		currentAnimation = &leftIdleAnim;
	}
	else if (direction == 2)
	{
		currentAnimation = &runRigthAnim;
	}
	else if (direction == 3)
	{
		currentAnimation = &runLeftAnim;
	}
	else if (direction == 4)
	{
		currentAnimation = &deathFromRightAnim;
	}
	else if (direction == 5)
	{
		currentAnimation = &deathFromLeftAnim;
	}

	currentAnimation->Update();

	LOG("%i", lifes);

	return true;
}

bool WalkingEnemy::PostUpdate()
{
	app->render->DrawTexture(EntityText, position.x - 5, position.y, &currentAnimation->GetCurrentFrame());

	

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
	
	 EntityCollider->body->SetTransform(v, 0);

	return true;
}

bool WalkingEnemy::SaveState(pugi::xml_node& data) const
{
	LOG("saving enemy ");

	data.child("Pos").attribute("x").set_value(position.x);
	data.child("Pos").attribute("y").set_value(position.y);
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
				//app->audio->PlayFx(app->lvlmanager->water_fx);
				
				lifes--;

				bodyA->body->ApplyLinearImpulse({ 0, -0.5f }, EntityCollider->body->GetPosition(), true);
				app->audio->PlayFx(app->lvlmanager->ehit_fx);
			}
			else
			{
				deathAnimAllowed = true;
				app->audio->PlayFx(app->lvlmanager->edeath_fx);
			}

		}

		if ((bodyA->id == 6) && (bodyB->id == 3))
		{

			if (lifes > 0)
			{
				//app->audio->PlayFx(app->lvlmanager->fall_fx);
				
				lifes--;

				bodyA->body->ApplyLinearImpulse({ 0, -0.5f }, EntityCollider->body->GetPosition(), true);
				app->audio->PlayFx(app->lvlmanager->ehit_fx);
			}
			else
			{
				deathAnimAllowed = true;
				app->audio->PlayFx(app->lvlmanager->edeath_fx);
			}

		}

		if ((bodyA->id == 6) && (bodyB->id == 7))
		{

			if (lifes > 0)
			{
				//app->audio->PlayFx(app->lvlmanager->fall_fx);

				lifes--;

				//bodyA->body->ApplyLinearImpulse({ 0, -0.5f }, EntityCollider->body->GetPosition(), true);
				app->audio->PlayFx(app->lvlmanager->ehit_fx);
			}
			else
			{
				deathAnimAllowed = true;
				app->audio->PlayFx(app->lvlmanager->edeath_fx);
			}

		}
	}
}
