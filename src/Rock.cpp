/*
 * Rock.cpp
 *
 *  Created on: Oct 24, 2014
 *      Author: ddc
 */

#include "Rock.h"
#include <cstdlib>
#include <time.h>

Rock::Rock(SDLsetup * setup , int width , int height) {

	angle = 0;

	randomW = rand() % (width);
	randomH = rand() % (height/20);

	this->setup=setup;
	rock = new Sprite(setup->getRenderer(),"data/asteroid.png",randomW,randomH,50,50);
	timeCheck = SDL_GetTicks();
}

Rock::~Rock() {
	delete rock;
}
void Rock::draw(){
	rock->draw();
}

void Rock::randomMotionLeftO(){
	if ( unsigned (timeCheck + 20) < SDL_GetTicks()){
			rock->setX(rock->getX()-2);
			rock->setY(rock->getY()+2);
			timeCheck = SDL_GetTicks();
	}
}
void Rock::randomMotionRightO(){
	if ( unsigned (timeCheck + 60) < SDL_GetTicks()){
		rock->setX(rock->getX()+2);
		rock->setY(rock->getY()+2);
		timeCheck = SDL_GetTicks();
	}
}
void Rock::randomMotionDown() {

	//int motion = rand() % 3;
	if ( unsigned (timeCheck + 60) < SDL_GetTicks()){

						rock->setX(rock->getX()+0);
						rock->setY(rock->getY()+2);

				timeCheck = SDL_GetTicks();
		}
}

















