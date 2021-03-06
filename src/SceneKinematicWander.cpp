#include "SceneKinematicWander.h"

using namespace std;

SceneKinematicWander::SceneKinematicWander()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/cat.png", 3);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	wanderRadius = 150;
	wanderOffset = 200;
	wanderMaxAngle = 60;
	randTarget = Vector2D(rand() % 1280, rand() % 768);
	angle = 0;

	Agent *bg = new Agent;
	bg->setPosition(Vector2D(0, 383));
	bg->loadSpriteTexture("../res/bg.jpg", 2);
	agents.push_back(bg);

	Agent *text = new Agent;
	text->setPosition(Vector2D(635, -80));
	text->loadSpriteTexture("../res/wander.png", 2);
	agents.push_back(text);
}

SceneKinematicWander::~SceneKinematicWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	//

}

void SceneKinematicWander::update(float dtime, SDL_Event *event)
{
	// Keyboard & Mouse events
switch (event->type) {
case SDL_MOUSEMOTION:
case SDL_MOUSEBUTTONDOWN:
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		
		agents[0]->setTarget(target);
	}
	break;
default:
	break;
}

Vector2D dist = target - agents[0]->getPosition();
angle = rand() % 360;

centre = agents[0]->getPosition() + agents[0]->getVelocity().Normalize() * wanderOffset;

target.x = centre.x + wanderRadius * sin(angle);
target.y = centre.y + wanderRadius * cos(angle);

agents[0]->setTarget(target);
Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], agents[0]->getTarget(), dtime);
agents[0]->update(steering_force, dtime, event);
}

void SceneKinematicWander::draw()
{
	agents[1]->draw();
	draw_circle(TheApp::Instance()->getRenderer(), centre.x, centre.y, wanderRadius,250, 0, 250, 1);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), centre.x, centre.y, target.x, target.y);
	draw_circle(TheApp::Instance()->getRenderer(), centre.x, centre.y, wanderRadius, 0, 255, 0, 1);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agents[0]->getPosition().x, agents[0]->getPosition().y, target.x, target.y);
	draw_circle(TheApp::Instance()->getRenderer(), centre.x, centre.y, wanderRadius, 250, 250, 250, 1);
	agents[0]->draw();
	agents[2]->draw();
}

const char* SceneKinematicWander::getTitle()
{
	return "SDL Steering Behaviors :: KinematicWander Demo";
}