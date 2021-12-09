#pragma once
#include "Module.h"
#include "Point.h"
#include "App.h"
#include "Physics.h"
#include "Input.h"
#include "Module.h"
#include "Textures.h"
#include "Animation.h"

struct SDL_Texture;

//enum class FLYING_ENEMY_STATE
//{
//	PATROLLING,
//	CHASING_PLAYER,
//	DEATH
//};


enum FLYING_ENEMY_STATE
{
	PATROLLING,
	CHASING_PLAYER,
	DEATH
};

class FlyingEnemy : public Module
{

private:
	

	float x, y;
	b2Vec2 speed = { 1.3,0 };
	float maxXspeed;

	
	b2Vec2 DetectionRange;

	SDL_Texture* texture;
	
	

	//enemy stats
	//startPosX = 10;
	//startPosY = 1;
	

	

	

public:

	iPoint directionPoint; // pixels
	iPoint positionOfTheObject;

	int lifes;
	bool isAlive;

	float startPosX;
	float startPosY;

	FLYING_ENEMY_STATE actualState;

	PhysBody* ColHitbox;

	FlyingEnemy();
	virtual ~FlyingEnemy();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();
	int GetEnemyLifes();
	void SetEnemyLifes(int l);
	void SetEnemyState(FLYING_ENEMY_STATE state);
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// FlyingEnemy* CreateFlyingEnemy(int xPosition, int yPosition);


	// Make a Function to Create an enemy that returns a FlyingEnemy to store in the Flying ennemy List
	



	//The player spritesheet loaded into an SDL_Texture


	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;
	int direction;

	void FlyingEnemy::SetAnimation(Animation& toChange)
	{
		if (currentAnimation != &toChange) {

			toChange.Reset();
			currentAnimation = &toChange;
		}
	}



	FlyingEnemy* CreateFlyingEnemy(int xPosition, int yPosition)
	{
		FlyingEnemy enemy;

		enemy.startPosX = xPosition;
		enemy.startPosY = yPosition;

		enemy.ColHitbox = app->physics->CreateCircle(enemy.startPosX, enemy.startPosY, 6);
		enemy.ColHitbox->id = 5;
		enemy.ColHitbox->listener = app->flyingenemy;

		enemy.actualState = PATROLLING;

		enemy.lifes = 2;
		enemy.isAlive = true;
		enemy.deathAnimAllowed = false;



		return &enemy;
	}

	//// Set of animations
	//// IDLE animations
	Animation rightIdleAnim;
	//Animation leftIdleAnim;
	//
	//// Walking Animations
	//Animation walkingRigthAnim;
	//Animation walkingLeftAnim;
	//
	//// Running Animations
	//Animation runningRigthAnim;
	//Animation runningLeftAnim;
	//
	//// Jumping Animations
	//Animation jumpingRigthAnim;
	//Animation jumpingLeftAnim;
	//
	//// Damage Animatios
	//Animation hitFromRightAnim;
	//Animation hitFromLeftAnim;
	//
	//// Death Animation
	//Animation deathFromRightAnim;
	//Animation deathFromLeftAnim;

	bool deathAnimAllowed;
};