#include "App.h"
#include "LevelManager.h"
#include "Module.h"
#include "Lvl_menu.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"
#include "Input.h"

#include "SDL/include/SDL.h"

LevelManager::LevelManager(bool state) : Module()
{
	name.Create("renderer");
}

LevelManager::~LevelManager()
{

}

bool LevelManager::Awake()
{
	Levels = new Menu(true);
	
	return true;
}

bool LevelManager::Start()
{
	return true;
}

bool LevelManager::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		
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
		Levels = new Menu(true);
	}
	else if (scene == SCENE_TYPE::LVL_01)
	{
		Levels = new Scene(true);
	}
	
}
