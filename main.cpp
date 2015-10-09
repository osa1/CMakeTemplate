#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <iostream>
#include <stdio.h>

int main()
{
    ///////////////////////
    // Make sure SDL2 inits
    ///////////////////////

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    ///////////////////////////
    // Make sure SDL2_ttf inits
    ///////////////////////////

    SDL_version compileVersion;
    SDL_TTF_VERSION(&compileVersion);
    const SDL_version* ttfLinkVersion = TTF_Linked_Version();

    printf("compiled with SDL_ttf version: %d.%d.%d\n",
            compileVersion.major,
            compileVersion.minor,
            compileVersion.patch);
    printf("running with SDL_ttf version: %d.%d.%d\n",
            ttfLinkVersion->major,
            ttfLinkVersion->minor,
            ttfLinkVersion->patch);

    if(TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        return 1;
    }

    /////////////////////////////
    // Make sure SDL2_image inits
    /////////////////////////////

    SDL_IMAGE_VERSION(&compileVersion);
    const SDL_version *imgLinkVersion = IMG_Linked_Version();

    printf("compiled with SDL_image version: %d.%d.%d\n",
            compileVersion.major,
            compileVersion.minor,
            compileVersion.patch);
    printf("running with SDL_image version: %d.%d.%d\n",
            imgLinkVersion->major,
            imgLinkVersion->minor,
            imgLinkVersion->patch);

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if(initted & flags != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        return 1;
    }

    ///////////////////////
    // Make sure GLEW works
    ///////////////////////

    SDL_Window* window = SDL_CreateWindow("test", 0, 0, 100, 100, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return 1;
    }

    SDL_Quit();

    ////////////////////////
    // Make sure we link glm
    ////////////////////////

    glm::vec3 v = glm::vec3(1.0f, 1.0f, 0.0f);
    std::cout << "vector length: " << glm::length(v) << std::endl;

    return 0;
}
