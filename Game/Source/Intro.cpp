#include "App.h"
#include "Animation.h"
#include "Render.h"
#include "Intro.h"
#include "Scene.h"
#include "Textures.h"

#include "Defs.h"
#include "Log.h"
#include "Point.h"


Intro::Intro()
{

}

// Destructor
Intro:: ~Intro() {}

// Called before render is available	
bool Intro::Awake()
{
	return true;
}


bool Intro::Start()
{
	switch (app->currentScene)
	{
		case (INTRO):
		{
			LOG("Loading Intro Scene");

			introimg = app->tex->Load("Assets/sprites/gamescreens/IntroScreen.png");
			winimg = app->tex->Load("Assets/sprites/gamescreens/WinningScreen.png");
			loseimg = app->tex->Load("Assets/sprites/gamescreens/GameOverScreen.png");
			return true;
		}
		break;

		case (WIN):
		{
			LOG("Loading Winning Scene");

			winimg = app->tex->Load("Assets/sprites/gamescreens/WinningScreen.png");
			app->render->camera.x = 0;
			return true;
		}
		break;

		case (GAMEOVER):
		{
			LOG("Loading Losing Scene");

			loseimg = app->tex->Load("Assets/sprites/gamescreens/GameOverScreen.png");
			app->render->camera.x = 0;
			return true;
		}
	}
}


bool Intro::PreUpdate()
{
	return true;
}


bool Intro::Update(float dt)
{
	app->render->DrawTexture(introimg, 0, 0);

	if (app->currentScene == WIN)
	{
		app->render->DrawTexture(winimg, 0, 0);
	}
	else if (app->currentScene == GAMEOVER)
	{
		app->render->DrawTexture(loseimg, 0, 0);
	}

	return true;
}


bool Intro::PostUpdate()
{
	return true;
}


bool Intro::CleanUp()
{
	switch (app->currentScene)
	{
		case (LEVEL1):
		{
			app->tex->UnLoad(introimg);
			return true;
		}
		break;
		case (LEVEL2):
		{
			app->tex->UnLoad(introimg);
			return true;
		}
		break;
	}

	return true;
}