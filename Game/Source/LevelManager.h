#pragma once
#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

#include "SString.h"
#include "Module.h"
#include "PugiXml/src/pugixml.hpp"

#include "SDL/include/SDL.h"

enum class SCENE_TYPE
{
	MENU = 0,
	LVL_01,
	WIN,
	LOSE
};

class LevelManager : public Module
{	
public:
	//LevelManager();
	LevelManager(bool state);
	LevelManager() : Module() {};
	virtual ~LevelManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	
	void ChangeScene(SCENE_TYPE scene);
	Module* Levels = NULL;
	SString	name;
	SCENE_TYPE scene_;

	SDL_Texture * pathTex;

	uint water_fx;
	uint fall_fx;
	uint win_fx;

	uint hit_fx;

	uint ehit_fx;
	uint edeath_fx;
	uint pdeath_fx;

	uint shield_fx;
};

#endif // __MODULE_H__