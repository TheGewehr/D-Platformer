#include "FlyingEnemy.h"
#include "App.h"
#include "Log.h"
#include "Player.h"
#include "p2List.h"
#include "Scene1.h"
#include "Scene2.h"
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
	texture = app->tex->Load("Assets/sprites/GraveRobber.png");

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

	lifes = 2;
	isAlive = true;
	deathAnimAllowed = false;

	LOG("Loading Flying Enemy");

	return true;
}

bool FlyingEnemy::Update(float dt)
{


	return true;
}

bool FlyingEnemy::PostUpdate()
{


	return true;
}

bool FlyingEnemy::CleanUp()
{
	LOG("Unloading player");

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

FLYING_ENEMY_STATE FlyingEnemy::GetEnemyState()
{
	return actualState;
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