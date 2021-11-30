#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Defs.h"

struct SDL_Texture;

class Scene1 : public Module
{
public:

	Scene1(bool startEnabled);

	// Destructor
	virtual ~Scene1();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	
	//Collider* playerWall[100] = { nullptr };

private:

	SDL_Texture* map;

	SDL_Texture* img;

	//uint jump_fx;
	uint water_fx;
	uint fall_fx;
	uint win_fx;
	//uint bonus_fx;

	SDL_Rect end_rect;


	List<PhysBody*> static_chains;
	//p2List<PhysBody*> mapStaticBodies;

	PhysBody* sensor_fall01 =nullptr;
	PhysBody* sensor_fall02 = nullptr;
	PhysBody* sensor_fall03 = nullptr;
	PhysBody* sensor_water01 = nullptr;
	PhysBody* sensor_water02 = nullptr;
	PhysBody* sensor_water03 = nullptr;
	PhysBody* sensor_win = nullptr;
};

#endif // __SCENE1_H__