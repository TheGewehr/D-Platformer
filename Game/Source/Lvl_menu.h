#pragma once
#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Defs.h"

struct SDL_Texture;

class Menu : public Module
{
public:

	Menu(bool startEnabled);

	// Destructor
	virtual ~Menu();

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
	SDL_Texture* image;
	
};

#endif // __SCENE2_H__