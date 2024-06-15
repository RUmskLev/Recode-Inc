#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "gamelevel.h"
#include "menu.h"


TEST_CASE("INITIALISING SUBSYSTEMS")
{
    CHECK(!SDL_Init(SDL_INIT_VIDEO));
    CHECK(!SDL_Init(SDL_INIT_EVENTS));
    CHECK(!SDL_Init(SDL_INIT_TIMER));

    CHECK(!SDL_Init(SDL_INIT_EVERYTHING));
    
    CHECK(!TTF_Init());
}

// TEST_CASE("LOAD GAME OBJECTS FROM FILES")
// {
//     CHECK();
// }

// void test_loading_menu() {
//     std::string output;
//     std::cout << "Hello, World!" << std::endl;
// }
// TEST_CASE("Test cout output") {
//     std::getline(std::cin, output);
//     CHECK(output == "Hello, World!\n");
// }