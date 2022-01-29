#include "Lvl_menu.h"
#include "Render.h"
#include "Textures.h"
#include "App.h"
#include "GuiManager.h"
#include "LevelManager.h"
#include "Window.h"
#include "Defs.h"
#include "Log.h"
Menu::Menu(bool startEnabled)
{
	app->render->camera.x = 0;
	app->render->camera.y = 0;
	image = app->tex->Load("Assets/sprites/gameScreens/introScreen.png");
	options = app->tex->Load("Assets/sprites/gui.png");
	options_ = { 376, 2, 389, 185 };
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


	btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->render->camera.w - 122) / 2, 240, 122, 37 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->render->camera.w - 122) / 2, 320, 122, 37 }, this);
	btn3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Test2", { (app->render->camera.w -122 ) / 2, 400, 122, 37 }, this);

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
	if (drawOptions) app->render->DrawTexture(options, (app->render->camera.w - options_.w) / 2, 225, &options_);
	
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
			app->guiManager->DestroyGuiControl(btn1);
			app->guiManager->DestroyGuiControl(btn2);
			app->guiManager->DestroyGuiControl(btn3);

			drawOptions = true;

			// create options buttons
			gui_close = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Checkbox01", { (app->render->camera.w + options_.w - 40) / 2, 220, 25, 25 }, this);
			gui_vsync = (GuiBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 5, "checkbox01", { (app->render->camera.w - 90) / 2, 280, 25, 25 }, this);
			gui_fullscreen = (GuiBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 6, "checkbox02", { (app->render->camera.w + 50) / 2, 280, 25, 25 }, this);
			gui_music = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 7, "Slider01", { (app->render->camera.w - 130) / 2, 330, 131, 12 }, this);
			gui_fx = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 7, "Slider02", { (app->render->camera.w - 130) / 2, 360, 131, 12 }, this);
		}
		else if (control->id == 3)
		{
			app->end_app = true;
		}
		else if (control->id == 4)
		{
			drawOptions = false;
			app->guiManager->DestroyGuiControl(gui_close);
			app->guiManager->DestroyGuiControl(gui_vsync);
			app->guiManager->DestroyGuiControl(gui_fullscreen);
			app->guiManager->DestroyGuiControl(gui_music);
			app->guiManager->DestroyGuiControl(gui_fx);
			btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->render->camera.w - 122) / 2, 240, 122, 37 }, this);
			btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->render->camera.w - 122) / 2, 320, 122, 37 }, this);
			btn3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Test2", { (app->render->camera.w - 122) / 2, 400, 122, 37 }, this);
			
		}
		

	}
	case GuiControlType::CHECKBOX:
	{
		if (control->id == 5)
		{
			app->vSyncBool = !app->vSyncBool;
			app->render->ChangeVsync(app->vSyncBool);
		}
		else if (control->id == 6)
		{
			app->win->fullscreen = !app->win->fullscreen;
		}
		
	}

	default: break;
	}

	return true;
}

void Menu::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
