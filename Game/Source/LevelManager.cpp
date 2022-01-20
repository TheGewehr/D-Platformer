#include "App.h"
#include "LevelManager.h"
#include "Module.h"

#include "Defs.h"
#include "Log.h"


LevelManager::LevelManager(bool state) : Module()
{
	name.Create("renderer");
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
	return true;
}

bool LevelManager::Update(float dt)
{
	return true;
}

bool LevelManager::PostUpdate()
{
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
	return true;
}

void LevelManager::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}