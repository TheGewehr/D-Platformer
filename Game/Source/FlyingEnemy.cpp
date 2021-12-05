#include "FlyingEnemy.h"
#include "App.h"
#include "Map.h"
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

	// define animations
}

FlyingEnemy::~FlyingEnemy()
{

}

bool FlyingEnemy::Awake()
{
	return true;
}


// Called before the first frame
bool FlyingEnemy::Start()
{
	//textures
	texture = app->tex->Load("Assets/sprites/Enemies.png");

	//player stats
	startPosX = 10;
	startPosY = 1;
	speed = { 1.3,0 };
	
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

	lifes = 2;
	isAlive = true;
	deathAnimAllowed = false;

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

	DetectionRange = app->player->GetColHitbox()->body->GetPosition();
	
	if (isAlive == true)
	{
		if (((DetectionRange.x < 3000) && (DetectionRange.x > -3000)) && ((DetectionRange.y < 3000) && (DetectionRange.y > -3000)))
		{
			actualState = CHASING_PLAYER;
		}
		else
		{
			actualState = PATROLLING;
		}
	}
	else
	{
		actualState = DEATH;
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

	}break;
	case DEATH:
	{
		deathAnimAllowed = true;
		// dies and become a kinematic object
	}break;
	}

	

	

	return true;
}

bool FlyingEnemy::PostUpdate()
{

	app->render->DrawTexture(texture, METERS_TO_PIXELS(ColHitbox->body->GetPosition().x) - 10, METERS_TO_PIXELS(ColHitbox->body->GetPosition().y) - 17, &currentAnimation->GetCurrentFrame());
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
