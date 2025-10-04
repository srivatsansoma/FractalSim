#include <SDL2/SDL.h>
#include <iostream>

#include <fstream>
#include <filesystem>

#include "../include/sdl_surface_func.hpp"

void sdl_changeSingularPixel(SDL_Window* window, SDL_Surface* screen, uint8_t b, uint8_t g ,uint8_t r, uint8_t alpha, int x, int y, bool UpdateOnceComplete){
    int w,h;
    SDL_GetWindowSize(window, &w, &h);

    if(x>=0 && x<w && y>=0 && y<h){
        uint8_t* pixels = (uint8_t*)screen->pixels;
        pixels[y* screen->pitch + x* screen->pitch/w] = b;
        pixels[y* screen->pitch + x* screen->pitch/w +1] = g;
        pixels[y* screen->pitch + x* screen->pitch/w +2] = r;

        if(UpdateOnceComplete) SDL_UpdateWindowSurface(window);
    }
}

void sdl_LoadAndDisplayImgFullScreen (SDL_Window *window, SDL_Surface* screen, std::string fpath){
    SDL_Surface *test_img;

    test_img = SDL_LoadBMP(fpath.c_str());

    SDL_BlitSurface(test_img , NULL, screen ,NULL);

    SDL_UpdateWindowSurface(window);
    SDL_FreeSurface(test_img);//delete the temp image
}

void sdl_LoadAndDisplayImgFullScreenFullScaled (SDL_Window *window, SDL_Surface* screen, const char* fpath){
    SDL_Surface *test_img;
    test_img = SDL_LoadBMP(fpath);

    if (!test_img) {
        std::cerr << "Failed to load image: " << fpath << "\n";
        std::cerr << "SDL Error: " << SDL_GetError() << "\n";
        return;
    }

    int w,h;
    SDL_GetWindowSize(window, &w, &h);

    SDL_Rect scale_rect{0,0, w,h};
    SDL_BlitScaled(test_img , NULL, screen , &scale_rect);

    SDL_UpdateWindowSurface(window);
    SDL_FreeSurface(test_img);//delete the temp image
}

void fullColourReset(unsigned char* c, SDL_Surface* screen){
    Uint32 colour = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_ABGR8888), *c, *(c+1), *(c+2));

    SDL_LockSurface(screen);
    SDL_memset(screen->pixels , colour, screen->pitch * screen->h);
    SDL_UnlockSurface(screen);
}

void saveDisplayLocal(SDL_Surface* screen, std::string fpath){
    std::ofstream file(fpath, std::ios::binary);

    uint8_t* pixels = (uint8_t*) screen->pixels;
    file.write(reinterpret_cast<const char*>(pixels), screen->pitch * screen->h);
}

uint8_t* retriveDisplayLocal(std::string fpath, int w, int h, int channels){

    uint8_t* Upixels = new uint8_t[ w*h*channels];
    if (std::filesystem::exists(fpath)){
        char *pixels = new char[w*h*channels];


        std::ifstream file(fpath, std::ios::binary);
        file.read(pixels, w*h*channels);

        for (int i = 0; i <   w*h*channels; i++)
            Upixels[i] = static_cast<uint8_t>(pixels[i]);

        return Upixels;
    }

    for (int i = 0; i <   w*h*channels; i++)
        i%4 == 3 ? Upixels[i] = 1 : Upixels[i] = 0;

    return Upixels;
}

void sdl_blitt_retreived_surface(SDL_Window* window, SDL_Surface* screen, uint8_t* Upixels){
    int w,h;
    SDL_GetWindowSize(window, &w, &h);

    for (int i = 0; i< h; i++){
        for (int j=0; j<w; j++){
            sdl_changeSingularPixel(
                window, screen,
                Upixels[i* screen->pitch + j* screen->pitch/w],
                Upixels[i* screen->pitch + j* screen->pitch/w +1],
                Upixels[i* screen->pitch + j* screen->pitch/w +2],
                Upixels[i* screen->pitch + j* screen->pitch/w +3],
                j, i,
                false);
        }
    }

    SDL_UpdateWindowSurface(window);
}

uint8_t* convert_to_greyscale_Upixels(uint8_t* upix, uint16_t w, uint16_t h, uint8_t channels){
    uint8_t* retpix = new uint8_t[w*h*channels];
    for (int i = 0; i < w*h; i++){
        uint8_t grey = 0.1140*upix[i*channels] + 0.5870*upix[i*channels +1] + 0.2989*upix[i*channels +2]; //bgr
        retpix[i*channels] = retpix[i*channels +1] = retpix[i*channels +2] =  grey;
        retpix[i*channels +3] = upix[i*channels +3];
    }

    return retpix;
}

void memcpy_greyscale_to_whole_surface(SDL_Window* window, SDL_Surface* screen, int w, int h, int channels){
    uint8_t* temp_Upixs = new uint8_t[w*h*channels];
    memcpy(temp_Upixs , screen->pixels, w*h*channels);

    uint8_t* grey_Upixs = convert_to_greyscale_Upixels(temp_Upixs, w, h, channels);

    sdl_blitt_retreived_surface(window, screen, grey_Upixs);

    delete[] temp_Upixs;
    delete[] grey_Upixs;
}
