#ifndef DEFINITIONS_H
#define DEFINITIONS_H


#include "logger.h"


#define MENU_BUTTONS_COLOR SDL_Color{43, 4, 4, 255}
#define MENU_BUTTONS_TEXT_COLOR SDL_Color{240, 230, 230, 255}
#define CLOSE_BUTTON_COLOR SDL_Color{244, 122, 74, 255}
#define WORLD_BUTTON_COLOR SDL_Color{251, 212, 251, 255}

#define SELECTED_COUNTRY_COLOR_1 SDL_Color{240, 240, 240, 255}
#define SELECTED_COUNTRY_COLOR_2 SDL_Color{230, 230, 230, 255}

#define COLOR_TRANSPARENT SDL_Color{0, 0, 0, 0}


#define logger Logger::getInstance(LMode_Console)


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define GAME_FRAME_RATE 60


#define EURASIA_VERTICES std::vector<SDL_Point>{{580, 147}, {746, 197}, {584, 344}, {370, 255}}
#define AUSTRALIA_VERTICES std::vector<SDL_Point>{{640, 389}, {679, 418}, {665, 457}, {607, 441}, {600, 411}, {640, 389}}
#define AFRICA_VERTICES std::vector<SDL_Point>{{382, 284}, {491, 328}, {432, 448}, {396, 355}, {357, 347}}
#define SOUTH_AMERICA_VERTICES std::vector<SDL_Point>{{248, 336}, {321, 377}, {249, 496}, {252, 404}, {230, 371}}
#define NORTH_AMERICA_GREENLAND_VERTICES std::vector<SDL_Point>{{195, 123}, {361, 125}, {304, 222}, {267, 155}, {235, 166}, {286, 243}, {204, 338}, {119, 231}, {73, 235}, {72, 179}, {127, 182}}
#define HEXAGON_VERTICES std::vector<SDL_Point>{{410, 230}, {437, 230}, {450, 253}, {437, 276}, {410, 276}, {397, 253}}

#endif