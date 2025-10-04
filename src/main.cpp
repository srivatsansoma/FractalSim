#include <SDL2/SDL.h>

// #include "../glad_gl/include/glad/glad.h"
#include "../include/sdl_surface_func.hpp"

#include <SDL2/SDL_video.h>
#include <iostream>
#include <vector>
#include <cmath>

#define MAIN_WIN_WIDTH 640
#define MAIN_WIN_HIEGTH 480


int main(){

    std::vector<std::vector<int>> drawn_pix = {};

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "vedioInit failed " << SDL_GetError();
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("MAIN", 0, 0, MAIN_WIN_WIDTH, MAIN_WIN_HIEGTH, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    // SDL_GLContext context;

    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // context = SDL_GL_CreateContext(window);

    SDL_Surface* screen = SDL_GetWindowSurface(window);

    // sdl_blitt_retreived_surface(window, screen,
    //     convert_to_greyscale_Upixels(
    //         retriveDisplayLocal("hello", MAIN_WIN_WIDTH,MAIN_WIN_HIEGTH, 4),
    //         MAIN_WIN_WIDTH,MAIN_WIN_HIEGTH, 4)
    // );

    sdl_blitt_retreived_surface(window, screen, retriveDisplayLocal("hello", MAIN_WIN_WIDTH, MAIN_WIN_HIEGTH, 4));

    //direct memcpy to screen->pixels cause unexpected behaviour. So copy it to temp change and then bring back
    sdl_LoadAndDisplayImgFullScreenFullScaled(window, screen, "./testLoadImages/fractal1testimg.bmp");
    memcpy_greyscale_to_whole_surface(window, screen, MAIN_WIN_WIDTH, MAIN_WIN_HIEGTH, 4);
    SDL_UpdateWindowSurface(window);

    //gladLoadGL();

    bool runProg = true;

    bool rst_colour = 0;
    while(runProg){

        SDL_Event event;
        const Uint8* key_states = SDL_GetKeyboardState(NULL);
        if (SDL_PollEvent(&event)) {
            switch (event.type){
                case SDL_QUIT:
                    runProg = false;
                    for (std::vector<int> i : drawn_pix){
                        std::cout<< i[0] << " " << i[1] << std::endl;
                    }
                    saveDisplayLocal(screen, "hello");
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        //std::cout << "DRAWN";

                        if(rst_colour) {
                            //fullColourReset(200, screen);
                            rst_colour =0;
                        }
                        else {
                            //fullColourReset(50, screen);
                            rst_colour = 1;
                        }

                        SDL_UpdateWindowSurface(window);
                    }
                    break;

                case SDL_KEYDOWN:
                    if (event.type != SDL_MOUSEMOTION && event.type != SDL_MOUSEBUTTONDOWN){
                        //std::cout << event.key.keysym.sym << "\n";
                        std::cout << SDL_GetKeyName( event.key.keysym.sym);
                    }
                    break;
            }

            if (key_states[SDL_SCANCODE_W] && key_states[SDL_SCANCODE_DOWN])
                std::cout << "acheived screenshot\n";
            if (event.button.button == SDL_BUTTON_LEFT){
                int x,y;
                std::cout << x << " " << y << "\n";
                SDL_GetMouseState(&x, &y);
                sdl_changeSingularPixel(window, screen, 0, 0, 255, 255, x, y ,true);
            }
            else if (event.button.button == SDL_BUTTON_MIDDLE){
                int x,y;
                std::cout << x << " " << y << "\n";
                SDL_GetMouseState(&x, &y);
                sdl_changeSingularPixel(window, screen, 0, 255, 0, 255, x, y ,true);
            }
            else if (event.button.button == SDL_BUTTON_RIGHT){
                int x,y;
                std::cout << x << " " << y << "\n";
                SDL_GetMouseState(&x, &y);
                sdl_changeSingularPixel(window, screen, 255, 0, 0, 255, x, y ,true);
            }
        }

        // glClearColor(0.2f , 0.0f, 0.0f, 1.0f);
        // glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        // SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
