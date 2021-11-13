#pragma once
#include "Module.h"
#include "p2Point.h"
#include "App.h"
#include "Physics.h"
#include "Input.h"
#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

struct Vect2 {
	int x, y;
};

class Player : public Module
{
public:
	Player();
	virtual ~Player();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();

	PhysBody* GetColHitbox() const
	{
		return ColHitbox;
	}

	PhysBody* GetColSensor() const
	{
		return ColSensor;
	}

	const float getX()
	{
		return x;
	}

	const float getY()
	{
		return y;
	}

	//The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;
	int direction;

	void Player::SetAnimation(Animation& toChange)
	{
		if (currentAnimation != &toChange) {

			toChange.Reset();
			currentAnimation = &toChange;
		}
	}

	// Set of animations
	// IDLE animations
	Animation rightIdleAnim;

	// Walking Animations
	Animation walkingRigthAnim;

	// Running Animations
	Animation runningRigthAnim;

	// Jumping Animations
	Animation jumpingRigthAnim;

	// Damage Animatios
	Animation hitFromRightAnim;

	// Death Animation
	Animation deathFromRightAnim;

private:
	float startPosX;
	float startPosY;

	float x, y;
	b2Vec2 speed;
	float maxXspeed;
	b2Vec2 jumpForce;

	PhysBody* ColHitbox;
	PhysBody* ColSensor;
};