#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
//#include <iostream>
constexpr int WIN_WIDTH = 800;
constexpr int WIN_HEIGHT = 600;

//SDL_Window* window = nullptr;
//SDL_Renderer* renderer = nullptr;
class Screen {
public:
	Screen() :window(nullptr), renderer(nullptr) {
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, 0, &window, &renderer);
		TTF_Init();
		SDL_RenderPresent(renderer);
	}
	void update() {
		SDL_RenderPresent(renderer);
	}
	void drawString(const char* s, int x, int y , KDColor c = KDColorBlack, int length = -1 ,bool largeFont = false) {
		TTF_Font* font = TTF_OpenFont((largeFont ? "LargeFont.ttf" :"SmallFont.ttf"), (largeFont ? 15:11));
		char* linkCopy = (char*) malloc( length == -1 ? (strlen(s) + 1) : length + 1 );
		memcpy(linkCopy, s , length == -1 ? (strlen(s)) : length);
		linkCopy[length == -1 ? (strlen(s)) : length] = 0;
		auto text_surface = TTF_RenderText_Solid(font, linkCopy, { c.red(), c.green() ,c.blue(), 255 });
		auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		
		SDL_Rect text_rect;
		SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
		//std::cout <<s;
		text_rect.x = x;
		text_rect.y = y;
		SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);
		SDL_FreeSurface(text_surface);
		free(linkCopy);
		update();
	}
	void delay(int ms) {
		SDL_Delay(ms);
	}
	void setPixel(int x, int y, KDColor c, int a = SDL_ALPHA_OPAQUE) {
		SDL_SetRenderDrawColor(renderer, c.red(), c.green(), c.blue(), a);
		SDL_RenderDrawPoint(renderer, x, y);
	}
	void drawLine(int x1, int y1, int x2, int y2, KDColor c, int a = SDL_ALPHA_OPAQUE) {
		SDL_SetRenderDrawColor(renderer, c.red(), c.green(), c.blue(), a);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}
	void strokeRect(int x, int y, int w, int h, KDColor c, int a = SDL_ALPHA_OPAQUE) {
		SDL_SetRenderDrawColor(renderer, c.red(), c.green(), c.blue(), a);
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		SDL_RenderDrawRect(renderer, &rect);
		update();
	}
	void fillRect(int x, int y, int w, int h, KDColor c, int a = SDL_ALPHA_OPAQUE) {
	/*	int r = c.red();
		int g = c.green();
		int b = c.blue();*/
		//cout << "color : ( " << c.red() << " , " << c.green() << " , " << c.blue() << " )" << endl;
		SDL_SetRenderDrawColor(renderer, c.red(), c.green(), c.blue(), a);
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		SDL_RenderFillRect(renderer, &rect);
		update();
	}
	~Screen() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		SDL_Quit();
	}

	SDL_Window* window;
	SDL_Renderer* renderer;
};