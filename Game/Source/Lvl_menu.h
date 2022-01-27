#pragma once
#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Defs.h"
#include "GuiButton.h"

struct SDL_Texture;

class Menu : public Module
{
public:

	Menu(bool startEnabled);

	// Destructor
	virtual ~Menu();

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

	// Called before quitting
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	//Collider* playerWall[100] = { nullptr };

	bool drawOptions;

private:
	SDL_Texture* image;

	
	GuiButton* btn1;
	GuiButton* btn2;
	GuiButton* btn3;
};

#endif // __SCENE2_H__