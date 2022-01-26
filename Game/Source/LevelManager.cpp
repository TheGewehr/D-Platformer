#include "App.h"
#include "LevelManager.h"
#include "Module.h"
#include "Lvl_menu.h"
#include "Scene.h"
#include "EntityManager.h"
#include "Defs.h"
#include "Log.h"
#include "Input.h"
#include "Audio.h"
#include "SDL/include/SDL.h"

LevelManager::LevelManager(bool state) : Module()
{
	active = state;
	name.Create("levelmanager");
}

LevelManager::~LevelManager()
{

}

bool LevelManager::Awake()
{
	
	
	return true;
}

bool LevelManager::Start()
{
	pathTex = app->tex->Load("Assets/sprites/PathTexture.png");

	water_fx = app->audio->LoadFx("Assets/audio/fx/Fall_in_water.wav");
	fall_fx = app->audio->LoadFx("Assets/audio/fx/mixkit-lose-life-falling-2029.wav");
	win_fx = app->audio->LoadFx("Assets/audio/fx/uno.wav");


	hit_fx = app->audio->LoadFx("Assets/audio/fx/player_hitted.wav");

	edeath_fx = app->audio->LoadFx("Assets/audio/fx/enemy_death.wav");
	ehit_fx = app->audio->LoadFx("Assets/audio/fx/b.wav");
	shield_fx = app->audio->LoadFx("Assets/audio/fx/no.wav");
	pdeath_fx = app->audio->LoadFx("Assets/audio/fx/death_player.wav");

	Levels = new Menu(true);
	return true;
}

bool LevelManager::PreUpdate()
{

	if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		ChangeScene(SCENE_TYPE::LVL_01);
	}
	else if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
	{
		ChangeScene(SCENE_TYPE::MENU);
	}
	Levels->PreUpdate();
	return true;
}

bool LevelManager::Update(float dt)
{
	Levels->Update(dt);
	return true;
}

bool LevelManager::PostUpdate()
{
	Levels->PostUpdate();
	return true;
}

bool LevelManager::LoadState(pugi::xml_node&)
{
	return true;
}

bool LevelManager::SaveState(pugi::xml_node&) const
{
	return true;
}

bool LevelManager::CleanUp()
{
	delete(Levels);
	return true;
}

void LevelManager::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

void LevelManager::ChangeScene(SCENE_TYPE scene)
{
	if (scene == SCENE_TYPE::MENU) 
	{
		Levels->CleanUp();
		
		Levels = new Menu(true);
	}
	else if (scene == SCENE_TYPE::LVL_01)
	{
		Levels->CleanUp();
		
		Levels = new Scene(true);
		// initiate necessary things for gameplay
	}
	scene_ = scene;
}

