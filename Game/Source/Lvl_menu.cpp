#include "Lvl_menu.h"
#include "Render.h"
#include "Textures.h"
#include "App.h"

Menu::Menu(bool startEnabled)
{
	app->render->camera.x = 0;
	app->render->camera.y = 0;
	image = app->tex->Load("Assets/sprites/gameScreens/introScreen.png");

	Start();
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
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	return true;
}

bool Menu::PreUpdate()
{
	return true;
}

bool Menu::Update(float dt)
{
	app->render->camera.x = 0;
	app->render->camera.y = 0;
	return true;
}

bool Menu::PostUpdate()
{
	app->render->DrawTexture(image, 0, 0);
	
	return true;
}

bool Menu::CleanUp()
{
	return true;
}

void Menu::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
