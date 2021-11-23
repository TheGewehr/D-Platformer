#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Physics.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Physics.h"
#include "Map.h"

#include <iostream>

#include "Defs.h"


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

	// List of points of Box2D
	int map[78] = {
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
	1439, 289,
	1599, 289,
	1788, 100,
	1590, -97,
	245, -128
	};

	int platform01[8] = {
	129, 289,
	351, 289,
	351, 317,
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

	// id's :
	// 0 nothing
	// 1 player
	// 2 water
	// 3 holes


	static_chains.add(app->physics->CreateStaticChain(0, 0, map, 78));
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

	
	sensor_water01 = app->physics->CreateRectangleSensor(240, 455, 250, 60);
	sensor_water01->id = 2;
	sensor_water01->listener = this;

	sensor_water02 = app->physics->CreateRectangleSensor(1000, 455, 300, 60);
	sensor_water02->id = 2;
	sensor_water02->listener = this;

	sensor_fall01 = app->physics->CreateRectangleSensor(420, 550, 100, 60);
	sensor_fall01->id = 3;
	sensor_fall01->listener = this;

	sensor_fall02 = app->physics->CreateRectangleSensor(660, 550, 110, 85);
	sensor_fall02->id = 3;
	sensor_fall02->listener = this;

	// Uploading the assets
	app->map->Load("hello.tmx");
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	img = app->tex->Load("Assets/background/Background.png");
	water_fx = app->audio->LoadFx("Assets/audio/fx/Fall_in_water.wav");
	fall_fx = app->audio->LoadFx("Assets/audio/fx/mixkit-lose-life-falling-2029.wav");


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
	app->render->DrawTexture(img, 0, 0, NULL);

	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();


	//std::cout << "    " << app->player->xposition << "      " << app->player->yposition <<std::endl;

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());


	//app->collisions->AddCollider();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;



	return ret;
}



// Called before quitting
bool Scene::CleanUp()
{
	//LOG("Freeing scene");

	return true;
}

void Scene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
	{

	}
	else
	{
		if ((bodyA->id == 1) && (bodyB->id == 2))
		{
			// fall in water loose one life
			app->audio->PlayFx(water_fx);
			//app->player->life
		}
		else if ((bodyA->id == 1) && (bodyB->id == 3))
		{
			// fall and loose
			app->audio->PlayFx(fall_fx);
			
		}
		
	}

}

