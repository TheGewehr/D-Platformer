#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"
#include "Defs.h"

#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

	GuiButton(uint id, SDL_Rect bounds, const char* text);
	virtual ~GuiButton();

	bool Update(float dt);
	bool Draw(Render* render);

	void SetPos(int x, int y);
	int mouseX, mouseY;
	unsigned int click;

	bool drawBasic = false;
	SDL_Rect btn_01;
	SDL_Rect btn_02;
	SDL_Rect btn_03;
	SDL_Rect gui_close;
	
};

class GuiBox : public GuiControl
{
public:

	GuiBox(uint id, SDL_Rect bounds);
	virtual ~GuiBox();

	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool drawBasic = false;
	bool box_info;
	
	SDL_Rect gui_case;
	SDL_Rect gui_check;

};

class GuiSlider : public GuiControl
{
public:

	GuiSlider(uint id, SDL_Rect bounds);
	virtual ~GuiSlider();

	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool drawBasic = false;
	bool box_info;

	SDL_Rect gui_slider;
	SDL_Rect gui_btn;

	bool focused;
	int pos_x;

};
#endif // __GUIBUTTON_H__