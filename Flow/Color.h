#pragma once
#include <SDL.h>

namespace Color {
	class RGB;
	class HSV;

	class RGB {
	public:
		RGB(int r, int g, int b);
		RGB(const RGB &rgb);
		RGB(HSV &hsv);
		RGB(SDL_Color &sdl);
		SDL_Color to_SDL();
		HSV to_HSV();

		int r;
		int g;
		int b;
	};

	class HSV {
	public:
		HSV(int h, int s, int v);
		HSV(const HSV& hsv);
		HSV(RGB& rgb);
		HSV(SDL_Color& sdl);
		SDL_Color to_SDL();
		RGB to_RGB();

		int h;
		int s;
		int v;
	};
}

