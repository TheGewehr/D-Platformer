#include "EntityManager.h"
#include "Player.h"
#include "FlyingEnemy.h"
#include "WalkingEnemy.h"
//#include "LifeItem.h"
//#include "Coin.h"
#include "App.h"
#include "Entity.h"

EntityManager::EntityManager(bool state) : Module()
{

	name.Create("entities");

	
	player = (Player*)CreateEntity(ENTITY_TYPE::PLAYER);

}



EntityManager::~EntityManager()
{
}

bool EntityManager::Awake(pugi::xml_node& config)
{
	active = false;

	bool ret = true;

	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{
		ret = item->data->Awake(config);
		if (!ret)
			break;
	}


	return ret;

}

bool EntityManager::Start()
{


	bool ret = true;
	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{

		//if (item->data->type != ENTITY_TYPE::WALKING_ENEMY && item->data->type != ENTITY_TYPE::FLYING_ENEMY) {

			ret = item->data->Start();
		//	if (!ret)
		//		break;
		//}
		

	}
	return ret;
}

bool EntityManager::PreUpdate()
{
	
	bool ret = true;
	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{
		//if (item->data->EntitiesEnable == true) {

			ret = item->data->PreUpdate();
			if (!ret)
				break;
		//}
	}
	return ret;
}

bool EntityManager::Update(float dt)
{
	
	bool ret = true;

	

	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{

		//if (item->data->EntitiesEnable == true) {

			ret = item->data->Update(dt, do_logic);
			//if (!ret)
			//	break;

		//}
	}


	return ret;
}

bool EntityManager::PostUpdate()
{
	
	bool ret = true;
	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{

		//if (item->data->EntitiesEnable == true) {

			ret = item->data->PostUpdate();
			//if (!ret)
			//	break;

		//}
	}
	return ret;
}

bool EntityManager::CleanUp()
{
	bool ret = true;
	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{

		ret = item->data->CleanUp();

		//if (!ret)
		//	break;

	}
	return ret;
}

bool EntityManager::Load(pugi::xml_node& save_game_manager)
{
	bool ret = true;

	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{
		ret = item->data->Load(save_game_manager);
		//if (!ret)
		//	break;
	}
	return ret;
}

bool EntityManager::Save(pugi::xml_node& save_game_manager) const
{
	bool ret = true;

	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{
		ret = item->data->Save(save_game_manager);
		//if (!ret)
		//	break;
	}
	return ret;
}

void EntityManager::OnCollision(PhysBody* c1, PhysBody* c2)
{
	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{
		if (item->data->EntitiesEnable == true) {
			//Some Entities manage/have more than 1 collider
			


					item->data->OnCollision(c1, c2);

			
		}
	}


	player->OnCollision(c1, c2);

}

Entity* EntityManager::CreateEntity(ENTITY_TYPE type)
{
	static_assert(ENTITY_TYPE::UNKNOWN == ENTITY_TYPE(5), "code needs update");
	Entity* ret = nullptr;
	switch (type) {

	case ENTITY_TYPE::FLYING_ENEMY: ret = new FlyingEnemy(); break;
	case ENTITY_TYPE::WALKING_ENEMY: ret = new WalkingEnemy(); break;
	case ENTITY_TYPE::PLAYER: ret = new Player(); break;
	//case ENTITY_TYPE::LIFE_ITEM: ret = new j2LifeItem(); break;
	//case ENTITY_TYPE::COIN: ret = new j2Coin(); break;
	}
	if (ret != nullptr)
		entities.add(ret);
	return ret;
}

void EntityManager::DestroyEntity(Entity* entity_to_destroy)
{
	for (p2List_item<Entity*>* item = entities.getFirst(); item; item = item->next)
	{
		if (item->data == entity_to_destroy)
		{
			entities.del(item);
			RELEASE(item->data);
			break;
		}
	}
}
