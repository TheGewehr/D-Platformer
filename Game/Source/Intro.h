#include "Module.h"
#include "Point.h"
#include "Animation.h"
#include "Render.h"


class Intro : public Module
{
public:

	Intro();

	// Destructor
	virtual ~Intro();

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

private:
	bool introScene;

	//Intro Background image
	SDL_Texture* introimg;

	//Winning Screen image
	SDL_Texture* winimg;

	//Losing Screen image
	SDL_Texture* loseimg;
};