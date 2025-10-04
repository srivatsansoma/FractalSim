#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include <fstream>
#include <filesystem>

void sdl_changeSingularPixel(SDL_Window* window, SDL_Surface* screen, uint8_t b, uint8_t g ,uint8_t r, uint8_t alpha, int x, int y, bool UpdateOnceComplete);

void sdl_LoadAndDisplayImgFullScreen (SDL_Window *window, SDL_Surface* screen, std::string fpath);

void sdl_LoadAndDisplayImgFullScreenFullScaled (SDL_Window *window, SDL_Surface* screen, const char* fpath);

void fullColourReset(unsigned char* c, SDL_Surface* screen);

void saveDisplayLocal(SDL_Surface* screen, std::string fpath);

uint8_t* retriveDisplayLocal(std::string fpath, int w, int h, int channels);

void sdl_blitt_retreived_surface(SDL_Window* window, SDL_Surface* screen, uint8_t* Upixels);

uint8_t* convert_to_greyscale_Upixels(uint8_t* upix, uint16_t w, uint16_t h, uint8_t channels);

void memcpy_greyscale_to_whole_surface(SDL_Window* window, SDL_Surface* screen, int w, int h, int channels);
