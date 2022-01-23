#pragma once
#include "Module.h"
#include "Point.h"
#include "App.h"
#include "Physics.h"
#include "Input.h"
#include "Module.h"
#include "Animation.h"
#include "Entity.h"

struct SDL_Texture;
enum class ENTITY_TYPE;

struct Vect2 {
	int x, y;
};

class Player : public Entity
{

private:
	//float startPosX;
	//float startPosY;

	float x, y;
	b2Vec2 speed;
	float maxXspeed;
	b2Vec2 jumpForce;

	//PhysBody* ColHitbox;
	PhysBody* ShieldSensor;

	//SDL_Texture* texture;
	SDL_Texture* shieldTex;

	int lifes;
	
	bool win;

	bool slowMoHability;	
	float angularSpeed;

	b2GearJointDef jointDef;

public:
	Player(bool startEnabled);
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
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	int GetPlayerLifes();
	void SetPlayerLifes(int l);
	bool GetPlayerWin();
	void SetPlayerWin(bool b);
	bool GetPlayerSlowMo();
	void SetPlayerSlowMo(bool b);
	b2Vec2 GetPosition();

	


	PhysBody* GetColHitbox() const
	{
		return EntityCollider;
	}

	PhysBody* GetShieldSensor() const
	{
		return ShieldSensor;
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
	

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;
	Animation* currentShieldAnimation = nullptr;

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
	Animation leftIdleAnim;

	// Walking Animations
	Animation walkingRigthAnim;
	Animation walkingLeftAnim;

	// Running Animations
	Animation runningRigthAnim;
	Animation runningLeftAnim;

	// Jumping Animations
	Animation jumpingRigthAnim;
	Animation jumpingLeftAnim;

	// Damage Animatios
	Animation hitFromRightAnim;
	Animation hitFromLeftAnim;

	// Death Animation
	Animation deathFromRightAnim;
	Animation deathFromLeftAnim;

	// Shield Animation
	Animation shieldRightAnim;
	

	bool deathAnimAllowed;
	bool isAlive;
};