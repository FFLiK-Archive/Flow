#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include <Color.h>
using namespace std;

enum Font { STD_FONT };

static class TextureManager {
public:
	SDL_Texture* LoadImage(const char* filename, SDL_Renderer* renderer);
	SDL_Texture* LoadText(const char* str, SDL_Renderer* renderer, int size, Font fontfile_name, Color::RGB color);
	SDL_Texture* LoadText(const wstring str, SDL_Renderer* renderer, int size, Font fontfile_name, Color::RGB color);

	void InitLoadTextureLibrary(SDL_Renderer* renderer);
	void QuitLoadTextureLibrary();
};