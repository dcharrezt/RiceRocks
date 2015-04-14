/*
 * SDLsetup.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: ddc
 */

#include "SDLsetup.h"

SDLsetup::SDLsetup(bool *quit,int screenWidth ,int screenHeigh){
	//TTF_Init();
	window = SDL_CreateWindow("Ricerocks v1.0",250,250,screenWidth,screenHeigh,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	mainEvent = new SDL_Event();
	//TTF_CloseFont(font);

}
SDLsetup::~SDLsetup() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete (mainEvent);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_Quit();

}
SDL_Renderer * SDLsetup::getRenderer(){
	return renderer;
}
SDL_Event * SDLsetup::getMainEvent(){
	return mainEvent;
}
void SDLsetup::writeText(string text, int x, int y){

	TTF_Init();

	font = TTF_OpenFont("data/FreeMono.ttf", 25);
	SDL_Color color = { 255, 255, 255 };

	surface = TTF_RenderText_Solid(font,text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer,surface);

	int texW = 10;
	int texH = 30;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dstrect = { x, y, texW, texH };

	TTF_CloseFont(font);
}
void SDLsetup::drawText(){
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	//SDL_RenderPresent(renderer);
}
void  SDLsetup::begin(){
	SDL_PollEvent(getMainEvent());
	SDL_RenderClear(getRenderer());
}
void  SDLsetup::end(){

	SDL_RenderPresent(getRenderer());
}

