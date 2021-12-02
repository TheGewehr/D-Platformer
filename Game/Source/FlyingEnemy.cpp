#include "FlyingEnemy.h"
#include "Log.h"

FlyingEnemy::FlyingEnemy()
{
	texture = nullptr;

	// define animations
}

FlyingEnemy::~FlyingEnemy()
{

}

bool Awake()
{
	return true;
}

// Called before the first frame
bool FlyingEnemy::Start()
{


	return true;
}

bool FlyingEnemy::Update(float dt)
{


	return true;
}

bool FlyingEnemy::PostUpdate()
{


	return true;
}

bool FlyingEnemy::CleanUp()
{
	LOG("Unloading player");

	return true;
}

int FlyingEnemy::GetEnemyLifes()
{
	return lifes;
}

void FlyingEnemy::SetEnemyLifes(int l)
{
	lifes = l;
}

FLYING_ENEMY_STATE FlyingEnemy::GetEnemyState()
{
	return actualState;
}

void FlyingEnemy::SetEnemyState(FLYING_ENEMY_STATE state)
{
	actualState = state;
}

bool FlyingEnemy::LoadState(pugi::xml_node&)
{


	return true;
}

bool FlyingEnemy::SaveState(pugi::xml_node&) const
{


	return true;
}