#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Physics.h"
#include "Window.h"
#include "Intro.h"
#include "Scene.h"
#include "Player.h"
#include "Physics.h"
#include "Map.h"
#include "PathFinding.h"
#include "SDL_mixer/include/SDL_mixer.h"

#include <iostream>

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	//LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->physics->world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	app->physics->world->SetContactListener(app->physics);

	app->player->SetPlayerLifes(3);


	switch (app->currentScene)
	{
		case INTRO:
		{
			introimg = app->tex->Load("Assets/sprites/gamescreens/IntroScreen.png");
			winimg = app->tex->Load("Assets/sprites/gamescreens/WinningScreen.png");
			loseimg = app->tex->Load("Assets/sprites/gamescreens/GameOverScreen.png");
		}
		break;

		case LEVEL1:
		{
			LOG("CLEARING INTRODUCTION PAGE");
			app->intro->CleanUp();

			int map[142] = {
			-2, -3,
			-2, 417,
			127, 417,
			127, 444,
			352, 444,
			352, 417,
			383, 417,
			383, 571,
			455, 573,
			448, 480,
			511, 417,
			606, 417,
			606, 587,
			704, 593,
			705, 481,
			705, 353,
			832, 225,
			1310, 225,
			1310, 285,
			831, 286,
			831, 417,
			927, 417,
			929, 445,
			1028, 445,
			1031, 418,
			1047, 418,
			1050, 445,
			1159, 444,
			1159, 417,
			1176, 417,
			1179, 442,
			1278, 442,
			1280, 417,
			1312, 417,
			1439, 288,
			1504, 288,
			1600, 383,
			1600, 413,
			1855, 413,
			1855, 385,
			1951, 288,
			2015 ,288,
			2015, 600,
			2112, 600,
			2112, 319,
			2080, 319,
			2080, 288,
			2175, 288,
			2175, 319,
			2143, 319,
			2143, 600,
			2240, 600,
			2240, 319,
			2208, 319,
			2208, 288,
			2303, 288,
			2303, 319,
			2271, 319,
			2271, 600,
			2368, 600,
			2368, 319,
			2336, 319,
			2336, 288,
			2431, 288,
			2431, 319,
			2399, 319,
			2399, 600,
			2496, 600,
			2496, 288,
			2570, 288,
			2570, -3
			};

			int platform01[8] = {
			129, 289,
			383, 288,
			383, 317,
			129, 317
			};

			int platform02[8] = {
			448, 192,
			480, 192,
			480, 224,
			449, 224
			};

			int platform03[8] = {
			544, 256,
			607, 256,
			607, 286,
			545, 286
			};

			int platform04[8] = {
			1664, 288,
			1664, 319,
			1695, 319,
			1695, 288
			};

			int platform05[8] = {
			1760, 288,
			1760, 319,
			1791, 319,
			1791, 288
			};

			int platform06[8] = {
			2048, 128,
			2048, 159,
			2079, 159,
			2079, 128
			};

			int platform07[8] = {
			2176, 128,
			2176, 159,
			2207, 159,
			2207, 128
			};

			int platform08[8] = {
			2304, 128,
			2304, 159,
			2335, 159,
			2335, 128
			};

			int platform09[8] = {
			2432, 128,
			2432, 159,
			2463, 159,
			2463, 128
			};

			// id's :
			// 0 map
			// 1 player
			// 2 water
			// 3 holes
			// 4 win

			// map
			static_chains.add(app->physics->CreateStaticChain(0, 0, map, 142));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;
			static_chains.add(app->physics->CreateStaticChain(0, 0, platform01, 8));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;
			static_chains.add(app->physics->CreateStaticChain(0, 0, platform02, 8));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;
			static_chains.add(app->physics->CreateStaticChain(0, 0, platform03, 8));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;
			static_chains.add(app->physics->CreateStaticChain(0, 0, platform04, 8));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;
			static_chains.add(app->physics->CreateStaticChain(0, 0, platform05, 8));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;
			static_chains.add(app->physics->CreateStaticChain(0, 0, platform06, 8));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;
			static_chains.add(app->physics->CreateStaticChain(0, 0, platform07, 8));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;
			static_chains.add(app->physics->CreateStaticChain(0, 0, platform08, 8));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;
			static_chains.add(app->physics->CreateStaticChain(0, 0, platform09, 8));
			static_chains.getLast()->data->id = 0;
			static_chains.getLast()->data->listener = this;

			FlyingEnemiesList.add(app->flyingenemy->CreateFlyingEnemy(50, 50));

			// water
			sensor_water01 = app->physics->CreateRectangleSensor(240, 455, 250, 60);
			sensor_water01->id = 2;
			sensor_water01->listener = this;

			sensor_water02 = app->physics->CreateRectangleSensor(1060, 455, 500, 60);
			sensor_water02->id = 2;
			sensor_water02->listener = this;

			sensor_water03 = app->physics->CreateRectangleSensor(1727, 420, 265, 60);
			sensor_water03->id = 2;
			sensor_water03->listener = this;

			// holes
			sensor_fall01 = app->physics->CreateRectangleSensor(420, 550, 100, 60);
			sensor_fall01->id = 3;
			sensor_fall01->listener = this;

			sensor_fall02 = app->physics->CreateRectangleSensor(660, 550, 110, 85);
			sensor_fall02->id = 3;
			sensor_fall02->listener = this;

			sensor_fall03 = app->physics->CreateRectangleSensor(2255, 550, 523, 100);
			sensor_fall03->id = 3;
			sensor_fall03->listener = this;

			// win
			sensor_win = app->physics->CreateRectangleSensor(2580, 310, 20, 85);
			sensor_win->id = 4;
			sensor_win->listener = this;

			app->map->Load("level1.tmx");
			water_fx = app->audio->LoadFx("Assets/audio/fx/Fall_in_water.wav");
			fall_fx = app->audio->LoadFx("Assets/audio/fx/mixkit-lose-life-falling-2029.wav");
			backgroundimg = app->tex->Load("Assets/background/Background.png");
			app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
		}
		break;

		case LEVEL2:
		{
			LOG("CLEARING INTRODUCTION PAGE");
			app->intro->CleanUp();

		}
		break;
	}
	
	if (app->map->Load("level1_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data, 1/*random, need to change*/)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	pathTex = app->tex->Load("Assets/sprites/PathTexture.png");
	originTex = app->tex->Load("Assets/sprites/Cross.png");
	
	if (app->player->Awake() == 0)
	{
		app->player->Awake();
	}

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	switch (app->currentScene)
	{
		case INTRO:
		{
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				app->SceneSwap(LEVEL1);
				app->render->camera.x = 0;
				app->scene->Start();
				return true;
			}
		}
		break;

		case LEVEL1:
		{
			app->intro->CleanUp();
			app->render->DrawTexture(backgroundimg, 0, 0, NULL);
			app->map->Draw();
			return true;
		}
		break;

		case LEVEL2:
		{
			app->intro->CleanUp();
			app->render->DrawTexture(backgroundimg, 0, 0, NULL);
			app->map->Draw();
			return true;
		}
		break;

		case WIN:
		{
			if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
			{
				app->SceneSwap(INTRO);
				app->intro->Start();
				app->render->camera.x = 0;
				return true;
			}
		}
		break;

		case GAMEOVER:
		{
			if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
			{
				app->SceneSwap(INTRO);
				app->intro->Start();
				app->render->camera.x = 0;
				return true;
			}
		}
		break;
	}

	return true;

	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	// Debug keys
	// Level 1 start
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		app->currentScene = LEVEL1;
	}
	// Level 2 start
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		app->currentScene = LEVEL2;
	}
	// Insta win
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		app->currentScene = WIN;
	}
	// Insta lose
	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{
		app->currentScene = GAMEOVER;
	}

	return ret;
}


// Used to pass to the second level
bool Scene::PassLevelCondition()
{
	if (app->player->GetPlayerWin() == true)
	{
		if (app->player->GetPlayerLifes() > 0)
		{
			return true;
		}
	}
	else 
	{
		return false;
	}
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Cleaning all");

	switch (app->currentScene)
	{
		case LEVEL1:
		{
			LOG("Unloading Background Texture");
			app->tex->UnLoad(backgroundimg);
			return true;
		}
		break;

		case LEVEL2:
		{
			LOG("Unloading Background Texture");
			app->tex->UnLoad(backgroundimg);
			return true;
		}
		break;
	}

	return true;
}