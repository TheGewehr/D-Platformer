#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Physics.h"
#include "Window.h"
#include "Intro.h"
#include "Player.h"
#include "Physics.h"
#include "Map.h"
#include "EntityManager.h"
#include "SDL_mixer/include/SDL_mixer.h"

#include <iostream>

#include "Defs.h"


Intro::Intro(bool startEnabled) : Module()
{
	active = startEnabled;
	name.Create("scene");
}

// Destructor
Intro::~Intro()
{}

// Called before render is available
bool Intro::Awake()
{
	//LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Intro::Start()
{

	return true;
}

// Called each loop iteration
bool Intro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Intro::Update(float dt)
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
	//SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
	//	app->map->mapData.width, app->map->mapData.height,
	//	app->map->mapData.tileWidth, app->map->mapData.tileHeight,
	//	app->map->mapData.tilesets.count());
	//
	//app->win->SetTitle(title.GetString());


	//app->collisions->AddCollider();

	return true;
}

// Called each loop iteration
bool Intro::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;



	return ret;
}



// Called before quitting
bool Intro::CleanUp()
{
	//LOG("Freeing scene");
	while (app->physics->GetWorld()->GetBodyList()->GetNext() != nullptr)
	{
		app->physics->world->DestroyBody(app->physics->GetWorld()->GetBodyList());
	}

	return true;
}

void Intro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	

	if (bodyB == nullptr)
	{

	}
	else
	{
		if ((bodyA->id == 1) && (bodyB->id == 2))
		{

			if (app->entitymanager->player->GetPlayerLifes() > 0)
			{
				// fall in water loose one life
				app->audio->PlayFx(water_fx);
				//app->player->life
				app->entitymanager->player->SetPlayerLifes(app->entitymanager->player->GetPlayerLifes() - 1);

				bodyA->body->ApplyLinearImpulse({ 0, -3.5f }, app->entitymanager->player->EntityCollider->GetPosition_(), true);

			}
			else
			{
				//app->player->currentAnimation = &app->player->deathFromLeftAnim;


				//app->player->SetPlayerLifes(3);
			}
		}
		else if ((bodyA->id == 1) && (bodyB->id == 3))
		{
			// fall and loose

			if (app->entitymanager->player->GetPlayerLifes() > 0)
			{
				app->audio->PlayFx(fall_fx);

				app->entitymanager->player->SetPlayerLifes(app->entitymanager->player->GetPlayerLifes() - 1);

				bodyA->body->ApplyLinearImpulse({ 0, -5.5f }, app->entitymanager->player->EntityCollider->GetPosition_(), true);

			}
			else
			{

				//app->player->currentAnimation=&app->player->deathFromRightAnim;


				//app->player->SetPlayerLifes(3);
			}

		}
		else if ((bodyA->id == 1) && (bodyB->id == 0))
		{

			if (app->entitymanager->player->GetPlayerLifes() > 0)
			{


			}
			else
			{

				//app->player->currentAnimation=&app->player->deathFromRightAnim;
				app->entitymanager->player->deathAnimAllowed = true;

				//app->player->SetPlayerLifes(3);
			}

		}
		else if ((bodyA->id == 1) && (bodyB->id == 4))
		{

			if (app->entitymanager->player->GetPlayerLifes() > 0)
			{
				Mix_HaltMusic();
				app->audio->PlayFx(win_fx);
				app->entitymanager->player->SetPlayerWin(true);

			}
			else
			{
			}

		}

	}

}