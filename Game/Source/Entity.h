#ifndef __ENTITIES_H__
#define __ENTITIES_H__

#include "SString.h"
#include "p2List.h"
#include "Point.h"
#include "Physics.h"
#include "SDL_image/include/SDL_image.h"
#include "PugiXml/src/pugixml.hpp"
#include "SDL_image/include/SDL_image.h"

class EntityManager;

enum class ENTITY_TYPE
{
	FLYING_ENEMY,
	WALKING_ENEMY,
	PLAYER,
	LIFE_ITEM,
	COIN,
	UNKNOWN
};



class Entity
{
public:

	//Constructor

	Entity(ENTITY_TYPE type) : name("Unknown"), manager(NULL), type(type), id(-1), active(true), EntityCollider(nullptr)
	{

	}

	//Destructor
	virtual ~Entity() {}

	virtual bool Awake(pugi::xml_node& config) { return true; }
	//Start
	virtual bool Start() { return true; }
	//PreUpdate		Called each loop iteration
	virtual bool PreUpdate() { return true; }
	//Update		Called each loop iteration
	virtual bool Update(float dt) { return true; }
	//PostUpdate	Called each loop iteration
	virtual bool PostUpdate() { return true; }
	//CleanUp
	virtual bool CleanUp() { return true; }


	//Load
	virtual bool Load(pugi::xml_node&) { return true; }
	//Save
	virtual bool Save(pugi::xml_node&) const { return true; }

	//OnCollision Callback
	virtual void OnCollision(PhysBody* c1, PhysBody* c2) {}

public:
	//iPoint positionOrigin;
	iPoint position;
	SString name;
	PhysBody* EntityCollider;
	
	
	bool active;
	//bool EntitiesEnable;

	SDL_Texture* EntityText = nullptr;
	
	p2List<PhysBody*> colliders;
	


	ENTITY_TYPE type;
	

	int id;


private:
	EntityManager* manager;
};

#endif
