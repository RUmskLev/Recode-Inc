#include "definitions.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "base.h"
#include "menu.h"
#include "gamelevel.h"
#include "logger.h"
#include <memory>
#include "SDL2_framerate.h"
#include "virus.h"
#include "world.h"
#include "game_neural_net.hpp"
#include <random>


void saveStats(const std::string &filename, int wins, int loses)
{
    std::ofstream file(filename);

    if (file.is_open())
    {
        file << wins << std::endl;
        file << loses << std::endl;
        file.close();
    } else {
        logger.error(101, "No file to save stats!");
    }
}


void loadStats(const std::string &filename, int& wins, int& loses)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        file >> wins;
        file >> loses;
        file.close();
    } else {
        logger.error(101, "No file to load stats!");
    }
}


int main(int argc, char *argv[])
{
    logger.debug("PROGRAMM START");

    bool QUIT = false;
    bool UPGRADE_MENU_OPEN = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::string ErrorMessage{"Couldn't initialize sdl subsystem: "};
        logger.error(100, ErrorMessage.append(SDL_GetError()));
        QUIT = true;
    }

    if (TTF_Init() < 0)
    {
        std::string ErrorMessage{"Couldn't initialize sdl ttf subsystem: "};
        logger.error(100, ErrorMessage.append(SDL_GetError()));
        QUIT = true;
    }

    FPSmanager GameFPSManager = FPSmanager();

    SDL_initFramerate(&GameFPSManager);

    if (SDL_setFramerate(&GameFPSManager, 60))
    {
        logger.error(100, "Can't set FPS to 60, retrying with 30 FPS");
        SDL_Delay(1000);
        if (SDL_setFramerate(&GameFPSManager, 30))
        {
            logger.error(100, "Can't set FPS to 30, terminating!");
            SDL_Delay(1000);
            QUIT = true;
        }
    }

    int fps_counter = 0;
    bool gamepause = false;

    int wins = 0;
    int loses = 0;
    bool show_score = true;

    loadStats("stats.txt", wins, loses);

    Virus covid19;
    Country country1(1000000, 5, 1);
    Country country2(5000000, 5, 2);
    Country country3(500000, 5, 3);
    Country country4(3200000, 5, 4);
    Country country5(1500000, 5, 5);
    World world;
    world.addCountry(country1);
    world.addCountry(country2);
    world.addCountry(country3);
    world.addCountry(country4);
    world.addCountry(country5);
    for(int i{1}; i <= 5; ++i){
        world.makeRoad(i, i);
        world.makeAirRoad(i, i);
        world.makeWaterRoad(i, i);
        world.makeAllAirRoads(i);
        world.makeAllWaterRoads(i);
    }
    //

    //
    std::vector<std::vector<double>> data;
    std::vector<std::vector<double>> targets;
    NeuralNetwork nn = NeuralNetwork(
        generate_target, data, targets,33, 105,
        0.15, {104, 78, 52, 38}, 0.99);
    std::vector<double> input(100, 0.0);
    input[0] = 5.0;
    std::vector<double> output;
    // Вход
    // 1-количество стран 
    // 25 - аэропорты, 25 - порты, 25 - дороги/жд, итого 75
    // 14 -вирус
    // 10 - популяции и заражённые в стране
    // 100
    // Выход
    // 1 - ставить метку балла или нет
    // 1 - куда ставить (по 0,2 на страну)
    // 10 - вероятности поппадания в страны и скорость вируса
    // 5 - внешнее закрытие аэропортов
    // 5 - внешнее закрытие портов
    // 5 - внутреннее закрытие жд
    // 5 - внутреннее закрытие аэропортов
    // 5 - внутреннее закрытие портов 
    // 1 - скорость лекарства
    // 38
    //
    //
    // Переменная победы или поражения
    int wl = 0;
    // Переменная  замарозки игры
    //
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> dist(0, 100000);
    int rand_value{0};
    int rand_of_inf{0};

    SDL_Window *window = SDL_CreateWindow("RE CODE INC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    std::unique_ptr<Scene> currentScene; // Holds current scene. Smart pointer needed for automatic destruction of old scene.
    currentScene = std::make_unique<Menu>(renderer, &gamepause);

    while (!QUIT)
    {
        SDL_framerateDelay(&GameFPSManager);

        fps_counter++;

        // std::cout << "FPS Counter: " << fps_counter << "\n";

        {
            // Scope for dimochka
            if (!gamepause & fps_counter % 180 == 0 & fps_counter != 0) {

                fps_counter = 0;

                std::cout << "Entered dima's sycle\n";


                for(int i{0}; i < 5; ++i){
                    Country country{*world.getCountry(i + 1)};
                    std::vector<int> rv = country.getRV();
                    std::vector<int> av = country.getAV();
                    std::vector<int> wv = country.getWV();
                    int infected = country.getInfected();
                    int population = country.getPopulation();
                    input[90 + i * 2] = population;
                    input[90 + i * 2 + 1] = infected;
                    for(int j{0}; j < 5; ++j){
                        input[1 + i * 5 + j] = rv[j] * static_cast<double>(infected) / population;
                        input[26 + i * 5 + j] = av[j] * static_cast<double>(infected) / population;
                        input[51 + i * 5 + j] = wv[j] * static_cast<double>(infected) / population;
                    }
                    input[76] = covid19.getMedRes();
                    input[77] = covid19.getAirTr();
                    input[78] = covid19.getWaterTr();
                    input[79] = covid19.getBirdTr();
                    input[80] = covid19.getBloodTr();
                    input[81] = covid19.getInsectTr();
                    input[82] = covid19.getRodentTr();
                    input[83] = covid19.getLivestockTr();
                    input[84] = covid19.getIntestines();
                    input[85] = covid19.getLungs();
                    input[86] = covid19.getBlood();
                    input[87] = covid19.getSkin();
                    input[88] = covid19.getImmune();
                    input[89] = covid19.getCns();
                }
                //
                output = nn.feedforward(input);
                if(output[37] == 1.0){
                    break;
                }
                //
                // Update values
                for(int i{0}; i < 5; ++i){
                    Country* country = world.getCountry(i + 1);
                    country->updateProbVir(output[2 + i * 2]);
                    country->updateSpeedVir(0.1);// output[3 + i * 2]);
                    // std::cout << "JUst after speed vir: " << world.getCountry(i + 1)->getSpeedVir() << "\n";
                    if(output[12 + i] >= 0.5){
                        world.closeAirCountry(i + 1);
                    }
                    if(output[17 + i] >= 0.5){
                        world.closeWaterCountry(i + 1);
                    }
                    if(output[22 + i] >= 0.5){
                        world.closeRoad(i + 1, i + 1);
                    }
                    if(output[27 + i] >= 0.5){
                        world.closeAirRoad(i + 1, i + 1);
                    }
                    if(output[32 + i] >= 0.5){
                        world.closeWaterRoad(i + 1, i + 1);
                    }
                }
                //
                if(output[0] >= 0.5){
                    int i{(static_cast<int>(output[1] / 0.2)) % 5};

                }
                //
                int sumInfected{0};
                for(int i{1}; i < 6; ++i){

                    int population = world.getCountry(i)->getPopulation();
                    int infected = world.getCountry(i)->getInfected();
                    int speedVirus = static_cast<int>(world.getCountry(i)->getSpeedVir() * population);
                    //std::cout << "Speed virus: " << speedVirus << "\n";
                    double probability = world.getCountry(i)->getProbVir();
                    std::uniform_int_distribution<int> distInf(0, speedVirus);

                    if(infected == 0){

                        rand_value = dist(gen);
                        rand_of_inf = distInf(gen);

                        if(rand_value / 100000.0 <= probability){
                            world.getCountry(i)->upInfected(rand_of_inf);
                        }
                    }else if(infected != population){
                        rand_of_inf = distInf(gen);
                        world.getCountry(i)->upInfected(std::min(rand_of_inf, population - infected) + 123);
                    }
                    sumInfected += world.getCountry(i)->getInfected();
                } 
                if(sumInfected == 11200000){
                    wl = 1;
                    break;
                }
            }
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                QUIT = true;
                break;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    std::cout << "User entered q which means he wants exit the program. terminating...\n";
                    QUIT = true;
                    break;
                case SDLK_SPACE:
                    UPGRADE_MENU_OPEN = !UPGRADE_MENU_OPEN;
                default:
                    break;
                }
            }
            
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int result = currentScene->onClick(event.button.x, event.button.y);
                if (result)
                {
                    if (result == -1)
                    {
                        QUIT = true;
                    } else if (result == 1)
                    {
                        currentScene = std::make_unique<Game>(renderer, &gamepause, &world);
                        show_score = false;
                    } else if (result == -2)
                    {
                        currentScene = std::make_unique<Menu>(renderer, &gamepause);
                        show_score = true;
                    } else if (result == 2)
                    {
                        logger.debug("YOU WON!");
                    }
                }
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                currentScene->onMouseOver(event.button.x, event.button.y);
                // std::cout << event.button.x << " " << event.button.y << "\n";
            }
        }

        SDL_RenderClear(renderer);

        TTF_Font* scoreFont = TTF_OpenFont("assets/fonts/Elounda-Regular.otf", 20);

        Label winsLabel{renderer, std::string{"Wins: "}.append(std::to_string(wins)), 40, 300, 100, 40, scoreFont};
        Label losesLabel{renderer, std::string{"Loses: "}.append(std::to_string(loses)), 40, 350, 100, 40, scoreFont};

        currentScene->draw(renderer);

        if (show_score)
        {
            winsLabel.draw(renderer);
            losesLabel.draw(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    saveStats("stats.txt", wins, loses);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    logger.debug("PROGRAMM END");

    // dimochka code

    return 0;
}