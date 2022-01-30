#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Window.h"
#include "Defs.h"

GuiButton::GuiButton(uint id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	btn_01 = { 950, 441, 122, 37 };
	btn_02 = { 950, 487, 122, 37 };
	btn_03 = { 950, 541, 122, 37 };
	gui_close = { 1139, 324, 25, 25 };
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)) &&
			canClick)
		{
			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiButton::Draw(Render* render)
{

	// Draw the right button depending on state
	if (id != 4)
	{
		switch (state)
		{

		case GuiControlState::DISABLED:
		{
			render->DrawTexture(texture, bounds.x, bounds.y, &btn_01);
		} break;

		case GuiControlState::NORMAL:
		{
			render->DrawTexture(texture, bounds.x, bounds.y, &btn_01);

		} break;

		//L14: TODO 4: Draw the button according the GuiControl State
		case GuiControlState::FOCUSED:
		{
			render->DrawTexture(texture, bounds.x, bounds.y, &btn_02);
		} break;
		case GuiControlState::PRESSED:
		{
			render->DrawTexture(texture, bounds.x, bounds.y, &btn_03);
		} break;

		/******/

		case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
			break;

		default:
			break;
		}

		if (id == 9)
		{
			section = { 0,0,50,50 };
			app->render->DrawTexture(texture, bounds.x, bounds.y, &section);
		}
	}
	else if (id == 4)	app->render->DrawTexture(texture, bounds.x, bounds.y, &gui_close);
	return false;
}

void GuiButton::SetPos(int x, int y)
{
	bounds.x = x;
	bounds.y = y;
}

GuiBox::GuiBox(uint id, SDL_Rect bounds) : GuiControl(GuiControlType::CHECKBOX, id)
{
	this->bounds = bounds;

	gui_case = { 1251, 203, 20, 20 };
	gui_check = { 1251, 246, 16, 16 };
	canClick = true;
	//drawBasic = false;
	
	if (id == 5) box_info = app->vSyncBool;
	else if (id == 6) box_info = app->win->fullscreen;
	
}

GuiBox::~GuiBox()
{

}

bool GuiBox::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)) &&
			canClick)
		{	
			
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;
	}

	if (id == 5)
	{
		box_info = app->vSyncBool;
	}
	else if (id == 6)
	{
		box_info = app->win->fullscreen;
	}
	
	return false;
}

bool GuiBox::Draw(Render* render)
{

	app->render->DrawTexture(texture, bounds.x, bounds.y, &gui_case);

	if (box_info) app->render->DrawTexture(texture, bounds.x + 2, bounds.y + 2, &gui_check);
	return true;
}

GuiSlider::GuiSlider(uint id, SDL_Rect bounds) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	pos_x = bounds.x;

	gui_slider = { 1251, 274, 131, 8 };
	gui_btn = { 1204, 203, 25, 25 };

	canClick = true;
	//drawBasic = false;
	focused = false;
	//box_info = false;
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)) &&
			canClick)
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
			{
				focused = true;
			}


			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT && focused)
			{
				state = GuiControlState::PRESSED;
			}

			if (state == GuiControlState::PRESSED)
			{
				if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)))
				{
					pos_x = mouseX;
				}
			}
			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				if (id == 7)
				{
					//app->audio->audio_mult = 5;
					app->audio->audio_mult = ((float)pos_x - (float)bounds.x) / 125.0f;
				}
				else if (id == 8)
				{
					app->audio->fx_mult = ((float)pos_x - (float)bounds.x) / 125.0f;
				}
				NotifyObserver();
				focused = false;
			}
		}
		else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiSlider::Draw(Render* render)
{
	app->render->DrawTexture(texture, bounds.x, bounds.y, &gui_slider);

	app->render->DrawTexture(texture, pos_x, bounds.y - 9, &gui_btn);

	return false;
}

