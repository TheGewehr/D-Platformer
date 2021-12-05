#pragma once
#include "Module.h"
#include "Point.h"
#include "App.h"
#include "Physics.h"
#include "Input.h"
#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

//enum class FLYING_ENEMY_STATE
//{
//	PATROLLING,
//	CHASING_PLAYER,
//	DEATH
//};

class FlyingEnemy : public Module
{

private:
	float startPosX;
	float startPosY;

	float x, y;
	b2Vec2 speed;
	float maxXspeed;

	PhysBody* ColHitbox;
	b2Vec2 DetectionRange;

	SDL_Texture* texture;
	

	int lifes;
	bool isAlive;

	enum FLYING_ENEMY_STATE
	{
		PATROLLING,
		CHASING_PLAYER,
		DEATH
	};

	FLYING_ENEMY_STATE actualState;

public:
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
	FLYING_ENEMY_STATE GetEnemyState();
	void SetEnemyState(FLYING_ENEMY_STATE state);
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Make a Function to Create an enemy that returns a FlyingEnemy to store in the Flying ennemy List
	



	PhysBody* GetColHitbox() const
	{
		return ColHitbox;
	}


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

	//// Set of animations
	//// IDLE animations
	//Animation rightIdleAnim;
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