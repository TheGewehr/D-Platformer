#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "LevelManager.h"

#include "GuiButton.h"
#include "Audio.h"

GuiManager::GuiManager(bool state) :Module()
{
	active = state;
	name.Create("guiManager");
	controls.clear();
	
}

GuiManager::~GuiManager() {}

bool GuiManager::Start()
{
	texture = app->tex->Load("Assets/sprites/gui.png");
	heartTexture = app->tex->Load("Assets/sprites/Heart.png");
	return true;
}

GuiControl* GuiManager::CreateGuiControl(GuiControlType type, int id, const char* text, SDL_Rect bounds, Module* observer, SDL_Rect sliderBounds)
{
	// L14: TODO1: Create a GUI control and add it to the list of controls

	GuiControl* control = nullptr;

	//Call the constructor according to the GuiControlType
	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(id, bounds, text);
		break;
	case GuiControlType::CHECKBOX:
		control = new GuiBox(id, bounds);
		break;
	case GuiControlType::SLIDER:
		control = new GuiSlider(id, bounds);
		break;
	case GuiControlType::DISPLAY:
		control = new GuiButton(id, bounds,text);
		break;

	default:
		break;
	}

	//Set the observer
	control->SetObserver(observer);
	//control->SetTexture(texture);

	if ((id == 9)|| (id == 10) || (id == 11) || (id == 12 ) )
	{
		control->SetTexture(heartTexture);
		control->section = {0,0,50,50};
	}
	else
	{
		control->SetTexture(texture);
	}

	// Created GuiControls are added to the list of controls
	if (control != nullptr) controls.add(control);

	return control;
}

void GuiManager::DestroyGuiControl(GuiControl* entity)
{
	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		if (entity->id == control->data->id)
		{
			controls.del(control);
		}
		control = control->next;
	}
}

void GuiManager::AbleGuiControl(GuiControl* entity, bool able)
{
	

	for (ListItem<GuiControl*>* control = controls.start; control != nullptr; control = control->next)
	{
		if (entity->id == control->data->id)
		{
			control->data->canClick = able;
		}
		
	}
}

bool GuiManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}

bool GuiManager::UpdateAll(float dt, bool doLogic) {

	if (doLogic) {

		ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			control->data->Update(dt);//
			control = control->next;
		}

	}
	return true;

}

bool GuiManager::Draw() {

	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->Draw(app->render);
		control = control->next;
	}

	
	return true;

}

bool GuiManager::CleanUp()
{
	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		RELEASE(control);
	}

	return true;

	
}



