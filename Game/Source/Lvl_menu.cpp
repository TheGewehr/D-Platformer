#include "Lvl_menu.h"

Menu::Menu(bool startEnabled)
{
}

Menu::~Menu()
{
}

bool Menu::Awake()
{
	return true;
}

bool Menu::Start()
{
	return true;
}

bool Menu::PreUpdate()
{
	return true;
}

bool Menu::Update(float dt)
{
	return true;
}

bool Menu::PostUpdate()
{
	return true;
}

bool Menu::CleanUp()
{
	return true;
}

void Menu::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
