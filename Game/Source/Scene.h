#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Defs.h"
#include "FlyingEnemy.h"
#include "GuiButton.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene(bool startEnabled);

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Used to pass to the second level
	bool PassLevelCondition();

	// Win and Loss screens and consequences
	bool WinLoseCondition();

	// Called before quitting
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void ResetLevel();
	
	

	
	


	int currentLevel;
	bool stop_phys;

private:
	SDL_Texture* map;

	SDL_Texture* img;

	
	SDL_Texture* originTex;

	SDL_Rect end_rect;

	List<PhysBody*> static_chains;
	//p2List<PhysBody*> mapStaticBodies;
	List<FlyingEnemy*> FlyingEnemiesList;

	PhysBody* sensor_fall01 =nullptr;
	PhysBody* sensor_fall02 = nullptr;
	PhysBody* sensor_fall03 = nullptr;
	PhysBody* sensor_water01 = nullptr;
	PhysBody* sensor_water02 = nullptr;
	PhysBody* sensor_water03 = nullptr;
	PhysBody* sensor_win = nullptr;

	GuiButton* gui_lifes01;
	GuiButton* gui_lifes02;
	GuiButton* gui_lifes03;
	GuiButton* gui_lifes04;
	GuiButton* gui_close;
	GuiButton* gui_goMenu;

	SDL_Texture* winTexture;


};

#endif // __SCENE1_H__