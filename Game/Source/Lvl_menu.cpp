#include "Lvl_menu.h"
#include "Render.h"
#include "Textures.h"
#include "App.h"
#include "GuiManager.h"
#include "LevelManager.h"

#include "Defs.h"
#include "Log.h"
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


	btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { app->render->camera.w / 2, 240, 160, 40 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { app->render->camera.w / 2, 320, 160, 40 }, this);
	btn3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Test2", { app->render->camera.w / 2, 400, 160, 40 }, this);

	drawOptions = false;

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
	app->guiManager->DestroyGuiControl(btn1);
	app->guiManager->DestroyGuiControl(btn2);
	app->guiManager->DestroyGuiControl(btn3);

	return true;
}

bool Menu::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 1)
		{
			app->lvlmanager->ChangeScene(SCENE_TYPE::LVL_01);
		}
		else if (control->id == 2) // Options!!!
		{
			//disables buttons 1, 2, 3
			app->guiManager->AbleGuiControl(btn1, false);
			app->guiManager->AbleGuiControl(btn2, false);
			app->guiManager->AbleGuiControl(btn3, false);

			drawOptions = true;

			// create options buttons
		}
		else if (control->id == 3)
		{
			app->end_app = true;
		}

	}
	//Other cases here

	default: break;
	}

	return true;
}

void Menu::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
