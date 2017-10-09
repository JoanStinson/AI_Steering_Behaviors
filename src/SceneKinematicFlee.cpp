#include "SceneKinematicFlee.h"

using namespace std;

SceneKinematicFlee::SceneKinematicFlee()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/cat.png", 3);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	Agent *bg = new Agent;
	bg->setPosition(Vector2D(0, 383));
	bg->loadSpriteTexture("../res/bg.jpg", 2);
	agents.push_back(bg);

	Agent *text = new Agent;
	text->setPosition(Vector2D(635, -80));
	text->loadSpriteTexture("../res/flee.png", 2);
	agents.push_back(text);
}

SceneKinematicFlee::~SceneKinematicFlee()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneKinematicFlee::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->Flee(agents[0],agents[0]->getTarget(),dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneKinematicFlee::draw()
{
	agents[1]->draw();
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[2]->draw();
}

const char* SceneKinematicFlee::getTitle()
{
	return "SDL Steering Behaviors :: KinematicFlee Demo";
}