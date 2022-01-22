#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "p2List.h"
#include "PugiXml\src\pugixml.hpp"

class Entity;
class Player;
enum class ENTITY_TYPE;



class EntityManager : public Module
{
public:

	//Constructor
	EntityManager();
	//Destructor
	virtual ~EntityManager();

	// Awake: Called before render is available
	bool Awake(pugi::xml_node& config);

	//Start
	bool Start();
	//PreUpdate
	bool PreUpdate();
	//Update
	bool Update(float dt);

	//PostUpdate
	bool PostUpdate();

	bool CleanUp();

	//Load
	bool Load(pugi::xml_node&);
	//Save
	bool Save(pugi::xml_node&) const;

	//OnCollision Callback
	void OnCollision(PhysBody* c1, PhysBody* c2);



public:
	Entity* CreateEntity(ENTITY_TYPE type);
	void DestroyEntity(Entity* entity_to_destroy);

	p2List<Entity*> entities;

	Player* player;





};





#endif

