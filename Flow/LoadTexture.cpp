#include <LoadTexture.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <Log.h>
#include <FileManager.h>
#include <han2unicode.h>

SDL_Texture *circle, *star;

void TextureManager::InitLoadTextureLibrary(SDL_Renderer *renderer) {
	circle = LoadImage(FileManager::Location(RES, "circle.img").c_str(), renderer);
	star = LoadImage(FileManager::Location(RES, "star.img").c_str(), renderer);
	SDL_SetTextureBlendMode(circle, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(star, SDL_BLENDMODE_BLEND);
}

void TextureManager::QuitLoadTextureLibrary() {
	SDL_DestroyTexture(circle);
	SDL_DestroyTexture(star);
}

/*
void TextureManager::DrawCircle(SDL_Point point, SDL_Renderer * renderer, int circle_size, int r, int g, int b, int a) {
	SDL_SetTextureColorMod(star, r, g, b);
	SDL_Rect dst;
	dst.w = circle_size;
	dst.h = circle_size;
	dst.x = point.x - circle_size / 2;
	dst.y = point.y - circle_size / 2;
	SDL_SetTextureBlendMode(star, SDL_BLENDMODE_ADD);
	SDL_SetTextureAlphaMod(star, a / 2);
	SDL_RenderCopy(renderer, star, NULL, &dst);
	SDL_SetTextureBlendMode(star, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(star, a);
	SDL_RenderCopy(renderer, star, NULL, &dst);
}

void TextureManager::DrawPoint(SDL_Point point, SDL_Renderer * renderer, int circle_size, int r, int g, int b, int a) {
	SDL_SetTextureColorMod(circle, r, g, b);
	SDL_Rect dst;
	dst.w = circle_size;
	dst.h = circle_size;
	dst.x = point.x - circle_size / 2;
	dst.y = point.y - circle_size / 2;
	SDL_SetTextureBlendMode(circle, SDL_BLENDMODE_ADD);
	SDL_SetTextureAlphaMod(circle, a / 2);
	SDL_RenderCopy(renderer, circle, NULL, &dst);
	SDL_SetTextureBlendMode(circle, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(circle, a);
	SDL_RenderCopy(renderer, circle, NULL, &dst);
}

void TextureManager::DrawLine(SDL_Point begin, SDL_Point end, SDL_Renderer * renderer, int circle_size, int r, int g, int b, int a) {
	SDL_SetTextureColorMod(circle, r, g, b);
	int addX, addY;
	int counter = 0;
	int dx = end.x - begin.x;
	int dy = end.y - begin.y;
	if (dx < 0) {
		addX = -1;
		dx = -dx;
	}
	else {
		addX = 1;
	}
	if (dy < 0) {
		addY = -1;
		dy = -dy;
	}
	else {
		addY = 1;
	}

	int x = begin.x;
	int y = begin.y;

	double n = sqrt(circle_size) / 2 + 1;
	addX *= n;
	addY *= n;

	if (dx >= dy) {
		for (int i = 0; i < dx; i += n) {
			x += addX;
			counter += dy;
			if (counter >= dx) {
				y += addY;
				counter -= dx;
			}
			SDL_Rect dst;
			dst.w = circle_size;
			dst.h = circle_size;
			dst.x = x - circle_size / 2;
			dst.y = y - circle_size / 2;
			SDL_SetTextureBlendMode(circle, SDL_BLENDMODE_ADD);
			SDL_SetTextureAlphaMod(circle, a / 2);
			SDL_RenderCopy(renderer, circle, NULL, &dst);
			SDL_SetTextureBlendMode(circle, SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(circle, a);
			SDL_RenderCopy(renderer, circle, NULL, &dst);
		}
	}
	else {
		for (int i = 0; i < dy; i += n) {
			y += addY;
			counter += dx;
			if (counter >= dy) {
				x += addX;
				counter -= dy;
			}
			SDL_Rect dst;
			dst.w = circle_size;
			dst.h = circle_size;
			dst.x = x - circle_size / 2;
			dst.y = y - circle_size / 2;
			SDL_SetTextureBlendMode(circle, SDL_BLENDMODE_ADD);
			SDL_SetTextureAlphaMod(circle, a / 2);
			SDL_RenderCopy(renderer, circle, NULL, &dst);
			SDL_SetTextureBlendMode(circle, SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(circle, a);
			SDL_RenderCopy(renderer, circle, NULL, &dst);
		}
	}
}
*/

SDL_Texture * TextureManager::LoadImage(const char * filename, SDL_Renderer * renderer) {
	SDL_Surface *surface;
	SDL_Texture *texture;
	surface = IMG_Load(filename);
	Log::PrintLog("TextureManager", "LoadImage", IMG_GetError());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture * TextureManager::LoadText(const char* str, SDL_Renderer* renderer, int size, Font fontfile_name, Color::RGB color) {
	TTF_Font* font;
	SDL_Surface *surface;
	SDL_Texture *texture;
	string adr;
	switch (fontfile_name) {
	case STD_FONT:
		adr = "";

	}
	adr += ".font";
	adr = FileManager::Location(RES, adr);
	font = TTF_OpenFont(adr.c_str(), size);

	Uint16 unicode[32768];
	han2unicode(str, unicode);

	surface = TTF_RenderUNICODE_Blended(font, unicode, color.to_SDL());

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	//delete font;
	TTF_CloseFont(font);
	return texture;
}

SDL_Texture * TextureManager::LoadText(const wstring str, SDL_Renderer* renderer, int size, Font fontfile_name, Color::RGB color)
{
	TTF_Font* font;
	SDL_Surface *surface;
	SDL_Texture *texture;
	string adr;
	adr = fontfile_name;
	adr += ".font";
	adr = FileManager::Location(RES, adr);
	font = TTF_OpenFont(adr.c_str(), size);

	SDL_Color clr;
	clr.r = color.r;
	clr.g = color.g;
	clr.b = color.b;
	clr.a = 255;

	surface = TTF_RenderUNICODE_Blended(font, (Uint16*)str.c_str(), color.to_SDL());

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	//delete font;
	TTF_CloseFont(font);
	return texture;
}