#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "gamelevel.h"
#include "menu.h"


TEST_CASE("INITIALISING SUBSYSTEMS CORRECTLY ON WINDOWS")
{
    CHECK(!SDL_Init(SDL_INIT_VIDEO));
    CHECK(!SDL_Init(SDL_INIT_EVENTS));
    CHECK(!SDL_Init(SDL_INIT_TIMER));

    CHECK(!SDL_Init(SDL_INIT_EVERYTHING));
    
    CHECK(!TTF_Init());
}