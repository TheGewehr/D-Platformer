#include "App.h"
#include "Log.h"
#include "Player.h"
#include "Input.h"
#include "p2List.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include"Render.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "SDL/include/SDL.h"

Player::Player() : Module()
{
	name.Create("player");

	float animSpeed = 0.01f;

	// IDLE animation right
	rightIdleAnim.PushBack({ 6, 15, 19, 33 });
	rightIdleAnim.PushBack({ 54, 15, 19, 33 });
	rightIdleAnim.PushBack({ 101, 15, 20, 33 });
	rightIdleAnim.PushBack({ 149, 15, 19, 33 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = animSpeed;

	// Walking animation right
	walkingRigthAnim.PushBack({ 9, 63, 23, 33 });
	walkingRigthAnim.PushBack({ 58, 62, 20, 34 });
	walkingRigthAnim.PushBack({ 105, 61, 17, 35 });
	walkingRigthAnim.PushBack({ 151, 63, 19, 33 });
	walkingRigthAnim.PushBack({ 201, 62, 17, 34 });
	walkingRigthAnim.PushBack({ 250, 61, 21, 35 });
	walkingRigthAnim.loop = true;
	walkingRigthAnim.speed = animSpeed;

	// Running animation right
	runningRigthAnim.PushBack({ 4, 111, 25, 33 });
	runningRigthAnim.PushBack({ 56, 113, 25, 31 });
	runningRigthAnim.PushBack({ 100, 113, 25, 31 });
	runningRigthAnim.PushBack({ 148, 112, 26, 32 });
	runningRigthAnim.PushBack({ 200, 113, 26, 31 });
	runningRigthAnim.PushBack({ 244, 113, 26, 31 });
	runningRigthAnim.loop = true;
	runningRigthAnim.speed = animSpeed;

	// Jumping animation right
	jumpingRigthAnim.PushBack({ 9, 209, 16, 31 });
	jumpingRigthAnim.PushBack({ 54, 208, 18, 32 });
	jumpingRigthAnim.PushBack({ 100, 206, 20, 34 });
	jumpingRigthAnim.PushBack({ 148, 201, 19, 34 });
	jumpingRigthAnim.PushBack({ 195, 198, 19, 39 });
	jumpingRigthAnim.PushBack({ 243, 200, 20, 34 });
	jumpingRigthAnim.loop = true;
	jumpingRigthAnim.speed = animSpeed;

	// Getting hit right
	hitFromRightAnim.PushBack({ 6, 255, 19, 33 });
	hitFromRightAnim.PushBack({ 55, 255, 19, 33 });
	hitFromRightAnim.PushBack({ 103, 255, 18, 33 });
	hitFromRightAnim.loop = false;
	hitFromRightAnim.speed = animSpeed;

	// Death animation right
	deathFromRightAnim.PushBack({ 6, 303, 19, 33 });
	deathFromRightAnim.PushBack({ 52, 308, 23, 28 });
	deathFromRightAnim.PushBack({ 99, 312, 32, 24 });
	deathFromRightAnim.PushBack({ 147, 318, 35, 18 });
	deathFromRightAnim.PushBack({ 195, 321, 34, 15 });
	deathFromRightAnim.PushBack({ 243, 324, 35, 12 });
	deathFromRightAnim.loop = false;
	deathFromRightAnim.speed = animSpeed;
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
	speed = { 2,0 };
	jumpForce = { 0,-3.0f };

	ColHitbox = app->physics->CreateCircle(startPosX, startPosY,15);
	
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

	b2Vec2 pos = { x,y };

	bool goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
	bool goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);

	//LOG("v: %f", ColHitbox->body->GetLinearVelocity().x);
	//ColHitbox->body->ApplyLinearImpulse(goRight * speed, ColHitbox->body->GetPosition(), true);

	if (ColHitbox->body->GetLinearVelocity().x < 5.f)
		ColHitbox->body->ApplyLinearImpulse(goRight * speed, ColHitbox->body->GetPosition(), true);
	
	if (ColHitbox->body->GetLinearVelocity().x > -5.f)
		ColHitbox->body->ApplyLinearImpulse(-goLeft* speed, ColHitbox->body->GetPosition(), true);

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
	
	if (direction == 0)
	{
		currentAnimation = &rightIdleAnim;
	}
	else if (direction == 1)
	{
		currentAnimation = &walkingRigthAnim;
	}
	else if (direction == 2)
	{
		currentAnimation = &jumpingRigthAnim;
	}
	else if (direction == 3)
	{
		currentAnimation = &deathFromRightAnim;
	}

	currentAnimation->Update();

	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{

	//Drawing player
	app->render->DrawTexture(texture, x, y, &currentAnimation->GetCurrentFrame());

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

