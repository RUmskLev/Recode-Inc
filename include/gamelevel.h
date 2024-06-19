#ifndef GAME_H
#define GAME_H

#include "base.h"
#include <string>
#include "SDL2_gfxPrimitives.h"
#include "world.h"
#include <memory>


/**
 * @brief Class, that describes country object.
 * 
 */
class DrawCountry : public Drawable
{
public:
    std::string name; // DrawCountry name
    int population = 0; // Total country population
    int infected = 0; // Infected in country
    std::vector<SDL_Point> boundariesPoints; // Points of country boundaries
    int colorOffset = 0; // Defines change in color, when mouse is over the country

    DrawCountry(std::vector<SDL_Point> countryBoundaries, std::string name, int poplation, int infected);

    DrawCountry() {}

    ~DrawCountry();

    void draw(SDL_Renderer *renderer);

    bool isMouseOver(int mouseX, int mouseY);

    void updateValues(int newInfected);

    void onMouseOver();

    int onClick();
};


/**
 * @brief Class, that describes node object.
 * 
 */
class VirusNode : public Drawable
{
public:
    std::string name; // Virus upgrade name
    std::string description; // virus upgrade description
    int colorOffset = 0; // Defines change in color, when mouse is over the node
    std::vector<std::string> requires; // required upgrades to able upgrade this
    SDL_Point position; // cords of hexagon in grid
    int price; // points price
    std::vector<SDL_Point> coords;
    SDL_Color nodeColor;

    VirusNode(int price, std::string name, std::string description, std::vector<std::string> requiredNodes, SDL_Point position, SDL_Color nodeColor);

    VirusNode() {}

    ~VirusNode();

    void draw(SDL_Renderer *renderer);

    bool isMouseOver(int mouseX, int mouseY);

    void onMouseOver();

    int onClick();
};


/**
 * @brief Class, that describes game scene.
 * 
 */
class Game : public Scene
{
public:
    std::vector<DrawCountry> objects; // All countries
    std::vector<VirusNode> nodes; // All nodes
    std::vector<DrawCountry> bobjects;
    SDL_Texture *bgTexture; // World map texture
    SDL_Texture *upgradeMenuTexture; // virus upgrade menu texture
    DrawCountry* selectedCountry = nullptr; // Currently selected country
    Country* startCountry;
    VirusNode* selectedNode = nullptr;
    bool menuOpened = false;
    Button* exitButton; // Exit button
    Button* closeUpgradeMenuButton; // Close upgrade menu button
    Button* upgradesButton;
    Button* infoWorldButton;
    Button* infoCountryButton;
    Button* infoVirusLeftButton;
    Button* infoVirusRightButton;
    Button* buyUpgradeButton;
    Button* newsButton;
    SDL_Texture* countryLabel;
    SDL_Renderer* levelRendererForTests; // Test variations of functions visually display info, so renderer is needed in checks
    bool* gamepause;
    World* gameWorld;
    Label* countryName;
    Label* countryPopulation;
    Label* countryInfected;
    Label* newsLabel;
    Label* dnaLabel;
    TTF_Font* commonFont;
    int bought_green;
    int DNA = 5;

    Game(SDL_Renderer *renderer, bool* gamePause, World* world);

    ~Game();

    int draw(SDL_Renderer *renderer) override;

    int onClick(int mouseX, int mouseY) override;

    void onMouseOver(int mouseX, int mouseY);
};

#endif