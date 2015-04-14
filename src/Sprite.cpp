/*
 * Sprite.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: ddc
 */

#include "Sprite.h"


/*Sprite::Sprite(){
}*/
Sprite::Sprite(SDL_Renderer * passedRenderer ,string filePath,int x,int y,int w,int h) {
	renderer = passedRenderer;
	image = IMG_LoadTexture(renderer,filePath.c_str());

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}
Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(renderer);
}
void Sprite::draw()
{
	SDL_RenderCopy(renderer,image,0,&rect);
}
void Sprite::setX(int X)
{
	rect.x = X;
}
void Sprite::setY(int Y)
{
	rect.y = Y;
}
void Sprite::setPosition(int X,int Y)
{
	rect.x = X;
	rect.x = Y;
}


int Sprite::getX()
{
	return rect.x;
}
int Sprite::getY()
{
	return rect.y;
}
int Sprite::getW()
{
  return rect.w;
}
int Sprite::getH()
{
  return rect.h;
}



SDL_Rect Sprite::getRect()
{
	return rect;
}
SDL_Texture * Sprite::getTexture()
{
	return image;
}
SDL_Renderer * Sprite::getRenderer()
{
	return renderer;
}
void Sprite::setRect(SDL_Rect r)
{
	rect = r;
}
void Sprite::setTexture(SDL_Texture * img)
{
	image = img;
}
void Sprite::setRenderer(SDL_Renderer * render)
{
	renderer = render;
}


