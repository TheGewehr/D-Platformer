#include "App.h"
#include "Log.h"
#include "Player.h"
#include "Input.h"
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

Player::Player() : Module()
{
	name.Create("player");

	texture = nullptr;

	float idleSpeed = 0.1f;
	float movement1Speed = 0.1f;
	float movement2Speed = 0.2f;
	float deathSpeed = 0.1f;

	// IDLE animation right
	rightIdleAnim.PushBack({ 294, 15, 19, 33 });
	rightIdleAnim.PushBack({ 342, 15, 19, 33 });
	rightIdleAnim.PushBack({ 389, 15, 20, 33 });
	rightIdleAnim.PushBack({ 437, 15, 19, 33 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	// IDLE animation left
	leftIdleAnim.PushBack({ 263, 15, 19, 33 });
	leftIdleAnim.PushBack({ 215, 15, 19, 33 });
	leftIdleAnim.PushBack({ 167, 15, 20, 33 });
	leftIdleAnim.PushBack({ 119, 15, 19, 33 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = idleSpeed;

	// Walking animation right
	walkingRigthAnim.PushBack({ 297, 63, 23, 33 });
	walkingRigthAnim.PushBack({ 346, 62, 20, 34 });
	walkingRigthAnim.PushBack({ 393, 61, 17, 35 });
	walkingRigthAnim.PushBack({ 439, 63, 19, 33 });
	walkingRigthAnim.PushBack({ 489, 62, 17, 34 });
	walkingRigthAnim.PushBack({ 538, 61, 21, 35 });
	walkingRigthAnim.loop = true;
	walkingRigthAnim.speed = movement1Speed;

	// Walking animation left
	walkingLeftAnim.PushBack({ 256, 63, 23, 33 });
	walkingLeftAnim.PushBack({ 210, 62, 20, 34 });
	walkingLeftAnim.PushBack({ 166, 61, 17, 35 });
	walkingLeftAnim.PushBack({ 118, 63, 19, 33 });
	walkingLeftAnim.PushBack({ 70, 62, 17, 34 });
	walkingLeftAnim.PushBack({ 17, 61, 21, 35 });
	walkingLeftAnim.loop = true;
	walkingLeftAnim.speed = movement1Speed;

	// Running animation right
	runningRigthAnim.PushBack({ 292, 111, 25, 33 });
	runningRigthAnim.PushBack({ 344, 113, 25, 31 });
	runningRigthAnim.PushBack({ 388, 113, 25, 31 });
	runningRigthAnim.PushBack({ 436, 112, 26, 32 });
	runningRigthAnim.PushBack({ 488, 113, 26, 31 });
	runningRigthAnim.PushBack({ 532, 113, 26, 31 });
	runningRigthAnim.loop = true;
	runningRigthAnim.speed = movement2Speed;

	// Running animation left
	runningLeftAnim.PushBack({ 259, 111, 25, 33 });
	runningLeftAnim.PushBack({ 207, 113, 25, 31 });
	runningLeftAnim.PushBack({ 163, 113, 25, 31 });
	runningLeftAnim.PushBack({ 114, 112, 26, 32 });
	runningLeftAnim.PushBack({ 62, 113, 26, 31 });
	runningLeftAnim.PushBack({ 18, 113, 26, 31 });
	runningLeftAnim.loop = true;
	runningLeftAnim.speed = movement2Speed;

	// Jumping animation right
	jumpingRigthAnim.PushBack({ 297, 209, 16, 31 });
	jumpingRigthAnim.PushBack({ 342, 208, 18, 32 });
	jumpingRigthAnim.PushBack({ 388, 206, 20, 34 });
	jumpingRigthAnim.PushBack({ 436, 201, 19, 34 });
	jumpingRigthAnim.PushBack({ 483, 198, 19, 39 });
	jumpingRigthAnim.PushBack({ 531, 206, 20, 34 });
	jumpingRigthAnim.loop = true;
	jumpingRigthAnim.speed = movement1Speed;

	// Jumping animation left
	jumpingLeftAnim.PushBack({ 263, 209, 16, 31 });
	jumpingLeftAnim.PushBack({ 216, 208, 18, 32 });
	jumpingLeftAnim.PushBack({ 168, 206, 20, 34 });
	jumpingLeftAnim.PushBack({ 121, 201, 19, 34 });
	jumpingLeftAnim.PushBack({ 74, 198, 19, 39 });
	jumpingLeftAnim.PushBack({ 25, 206, 20, 34 });
	jumpingLeftAnim.loop = true;
	jumpingLeftAnim.speed = movement1Speed;

	// Getting hit right
	hitFromRightAnim.PushBack({ 294, 255, 19, 33 });
	hitFromRightAnim.PushBack({ 343, 255, 19, 33 });
	hitFromRightAnim.PushBack({ 391, 255, 18, 33 });
	hitFromRightAnim.loop = false;
	hitFromRightAnim.speed = movement1Speed;

	// Getting hit left
	hitFromLeftAnim.PushBack({ 263, 255, 19, 33 });
	hitFromLeftAnim.PushBack({ 214, 255, 19, 33 });
	hitFromLeftAnim.PushBack({ 167, 255, 18, 33 });
	hitFromLeftAnim.loop = false;
	hitFromLeftAnim.speed = movement1Speed;

	// Death animation right
	deathFromRightAnim.PushBack({ 294, 303, 19, 33 });
	deathFromRightAnim.PushBack({ 340, 308, 23, 28 });
	deathFromRightAnim.PushBack({ 387, 312, 32, 24 });
	deathFromRightAnim.PushBack({ 435, 318, 35, 18 });
	deathFromRightAnim.PushBack({ 483, 321, 34, 15 });
	deathFromRightAnim.PushBack({ 531, 324, 35, 12 });
	deathFromRightAnim.loop = false;
	deathFromRightAnim.speed = deathSpeed;

	// Death animation left
	deathFromLeftAnim.PushBack({ 263, 303, 19, 33 });
	deathFromLeftAnim.PushBack({ 213, 308, 23, 28 });
	deathFromLeftAnim.PushBack({ 157, 312, 32, 24 });
	deathFromLeftAnim.PushBack({ 106, 318, 35, 18 });
	deathFromLeftAnim.PushBack({ 59, 321, 34, 15 });
	deathFromLeftAnim.PushBack({ 10, 324, 35, 12 });
	deathFromLeftAnim.loop = false;
	deathFromLeftAnim.speed = deathSpeed;
}

Player::~Player()
{}

bool Player::Awake()
{
	return true;
}

// Load assets
bool Player::Start()
{
	//textures
	texture = app->tex->Load("Assets/sprites/GraveRobber.png");

	//player stats
	startPosX = 10;
	startPosY = 1;
	speed = { 1.3,0 };
	jumpForce = { 0,-2.6f };

	ColHitbox = app->physics->CreateCircle(startPosX, startPosY,15);
	ColHitbox->id = 1;
	ColHitbox->listener = app->scene;
	
	int x_ = (int)x;
	int y_ = (int)y;
	ColHitbox->GetPosition(x_, y_);

	//ColSensor = app->physics->CreateRectangle(x, y, 46, 50);
	//ColSensor->body->GetFixtureList()->SetSensor(true);
	//ColSensor->body->SetType(b2_kinematicBody);

	LOG("Loading player");
	return true;
}

// Unload assets
bool Player::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
bool Player::Update(float dt)
{
	//ColSensor->body->SetTransform(ColHitbox->body->GetPosition(), 0);
	//app->render->viewport.x = METERS_TO_PIXELS(ColHitbox->body->GetPosition().x);
	//app->render->camera.x = METERS_TO_PIXELS(ColHitbox->body->GetPosition().x);

	b2Vec2 pos = { x,y };
	b2Vec2 stopping = {0.0f,0.0f};

	bool goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
	bool goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);

	//LOG("v: %f", ColHitbox->body->GetLinearVelocity().x);
	//ColHitbox->body->ApplyLinearImpulse(goRight * speed, ColHitbox->body->GetPosition(), true);

	// x movement on ground

	if (goRight == true)
	{
		if (ColHitbox->body->GetLinearVelocity().x < 5.f)
			ColHitbox->body->ApplyLinearImpulse(speed, ColHitbox->body->GetPosition(), true);

	}

	if (goLeft == true)
	{
		if (ColHitbox->body->GetLinearVelocity().x > -5.f) 
			ColHitbox->body->ApplyLinearImpulse(-speed, ColHitbox->body->GetPosition(), true);

	}

	// x movement on air

	if (ColHitbox->body->GetLinearVelocity().x < -3)
	{
		stopping = { speed.x * 0.2f,0 };

		ColHitbox->body->ApplyLinearImpulse(stopping, ColHitbox->body->GetPosition(), true);
	}
	
	if (ColHitbox->body->GetLinearVelocity().x > 3 )
	{
		stopping = { speed.x * 0.2f,0 };

		ColHitbox->body->ApplyLinearImpulse(-stopping, ColHitbox->body->GetPosition(), true);
	}
	

	


	//if (ColHitbox->body->GetLinearVelocity().x > -5.f) 
	//	ColHitbox->body->ApplyLinearImpulse(speed, ColHitbox->body->GetPosition(), true);
	
		
	b2Body* ground;

	if (ColHitbox->body->GetContactList() != nullptr)
	{
		ground = ColHitbox->body->GetContactList()->contact->GetFixtureA()->GetBody();

		if (ground != nullptr)
		{

			b2Vec2 xVel = { 0,ColHitbox->body->GetLinearVelocity().y };
			if (!goLeft && !goRight) ColHitbox->body->SetLinearVelocity(xVel);

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				b2Vec2 yVel = { ColHitbox->body->GetLinearVelocity().y,0 };
				ColHitbox->body->SetLinearVelocity(yVel);
				ColHitbox->body->ApplyLinearImpulse(jumpForce, ColHitbox->body->GetPosition(), true);
				ColHitbox->body->SetLinearDamping(0);
			}
		}
	}

	// app->render->DrawTexture(texture, METERS_TO_PIXELS(ColHitbox->body->GetPosition().x) - 20, METERS_TO_PIXELS(ColHitbox->body->GetPosition().y) - 33 , NULL);
	
	if (ColHitbox->body->GetLinearVelocity().x < 0)
	{
		direction = 3;
	}
	else if (ColHitbox->body->GetLinearVelocity().x > 0)
	{
		direction = 2;
	}
	/*
	else if ((ColHitbox->body->GetLinearVelocity().x != 0) || (ColHitbox->body->GetLinearVelocity().y != 0))
	{
		if (direction == 2) {
			direction = 4;
		}
		if (direction == 3) {
			direction = 5;
		}
	}
	*/
	else if (ColHitbox->body->GetLinearVelocity().x == 0)
	{
		if (direction == 2) {
			direction = 0;
		}
		if (direction == 3) {
			direction = 1;
		}
	}

	/*
	if (???)
	{
		direction = 2;
	}
	*/

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
		currentAnimation = &runningRigthAnim;
	}
	else if (direction == 3)
	{
		currentAnimation = &runningLeftAnim;
	}
	else if (direction == 4)
	{
		currentAnimation = &jumpingRigthAnim;
	}
	else if (direction == 5)
	{
		currentAnimation = &jumpingLeftAnim;
	}
	else if (direction == 6)
	{
		currentAnimation = &deathFromRightAnim;
	}
	else if (direction == 7)
	{
		currentAnimation = &deathFromLeftAnim;
	}

	currentAnimation->Update();

	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{

	//Drawing player
	app->render->DrawTexture(texture, METERS_TO_PIXELS(ColHitbox->body->GetPosition().x)-10, METERS_TO_PIXELS(ColHitbox->body->GetPosition().y)-17, &currentAnimation->GetCurrentFrame());

	return true;
}

bool Player::LoadState(pugi::xml_node& data)
{
	startPosX = data.child("startPos").attribute("x").as_float(0);
	startPosY = data.child("startPos").attribute("y").as_float(0);

	b2Vec2 v = { PIXEL_TO_METERS( startPosX), PIXEL_TO_METERS(startPosY )};
	ColHitbox->body->SetTransform(v, 0);

	return true;
}


bool Player::SaveState(pugi::xml_node& data) const
{

	LOG("saving camera pos");
	data.child("startPos").attribute("x").set_value(METERS_TO_PIXELS(ColHitbox->body->GetPosition().x));
	data.child("startPos").attribute("y").set_value(METERS_TO_PIXELS(ColHitbox->body->GetPosition().y));
	return true;
}

