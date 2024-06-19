#include "gamelevel.h"
#include <algorithm>
#include "cmath"

// Checking if a point is inside a polygon
bool point_in_polygon(SDL_Point point, std::vector<SDL_Point> polygon)
{
    int num_vertices = polygon.size();
    double x = point.x, y = point.y;
    bool inside = false;
 
    // Store the first point in the polygon and initialize
    // the second point
    SDL_Point p1 = polygon[0], p2;
 
    // Loop through each edge in the polygon
    for (int i = 1; i <= num_vertices; i++) {
        // Get the next point in the polygon
        p2 = polygon[i % num_vertices];
 
        // Check if the point is above the minimum y
        // coordinate of the edge
        if (y > std::min(p1.y, p2.y)) {
            // Check if the point is below the maximum y
            // coordinate of the edge
            if (y <= std::max(p1.y, p2.y)) {
                // Check if the point is to the left of the
                // maximum x coordinate of the edge
                if (x <= std::max(p1.x, p2.x)) {
                    // Calculate the x-intersection of the
                    // line connecting the point to the edge
                    double x_intersection
                        = (y - p1.y) * (p2.x - p1.x)
                              / (p2.y - p1.y)
                          + p1.x;
 
                    // Check if the point is on the same
                    // line as the edge or to the left of
                    // the x-intersection
                    if (p1.x == p2.x
                        || x <= x_intersection) {
                        // Flip the inside flag
                        inside = !inside;
                    }
                }
            }
        }
 
        // Store the current point as the first point for
        // the next iteration
        p1 = p2;
    }
 
    // Return the value of the inside flag
    return inside;
}

DrawCountry::DrawCountry(std::vector<SDL_Point> countryBoundaries, std::string name, int population, int infected) : boundariesPoints(countryBoundaries), name(name), population(population), infected(infected)
{
    is_selected = false;
}

DrawCountry::~DrawCountry()
{

}


void DrawCountry::draw(SDL_Renderer *renderer)
{
    if (boundariesPoints.size() < 3)
    {
        return;
    }

    Sint16* vx = new Sint16[boundariesPoints.size()];
    Sint16* vy = new Sint16[boundariesPoints.size()];

    for (int i = 0; i < boundariesPoints.size(); i++)
    {
        vx[i] = boundariesPoints[i].x;
        vy[i] = boundariesPoints[i].y;
    }

    int result = 0;

    if (is_selected)
    {
        result = filledPolygonColor(renderer, vx, vy, boundariesPoints.size(), 0x0F0FF0FF);
    } else {
        result = filledPolygonColor(renderer, vx, vy, boundariesPoints.size(), 0xFF0000FF);
    }

    delete[] vx;
    delete[] vy;

    if (result!= 0)
    {
        return;
    }
}


bool DrawCountry::isMouseOver(int mouseX, int mouseY)
{
    return point_in_polygon(SDL_Point{mouseX, mouseY}, boundariesPoints);
}

void DrawCountry::updateValues(int newInfected)
{
    infected = newInfected;
}

void DrawCountry::onMouseOver()
{
    colorOffset = 20;
}


int DrawCountry::onClick()
{
    is_selected = true;
    return 0;
}


Game::Game(SDL_Renderer *renderer, bool* gamePause, World* world)
{
    gamepause = gamePause;
    *gamepause = false;

    gameWorld = world;

    TTF_Font* usedFont = TTF_OpenFont("assets/fonts/Elounda-Regular.otf", 20);
    if(!usedFont) {
        logger.error(101, "Font for exit button in level was not found!\n");
    }

    commonFont = usedFont;

    exitButton = new Button{renderer, "X", 760, 10, 30, 30, CLOSE_BUTTON_COLOR, usedFont};
    closeUpgradeMenuButton = new Button{renderer, "X", 10, 10, 30, 30, CLOSE_BUTTON_COLOR, usedFont};
    upgradesButton = new Button{renderer, "Virus", -35, 525, 175, 110, WORLD_BUTTON_COLOR, usedFont};
    infoWorldButton = new Button{renderer, "World", 660, 525, 175, 110, WORLD_BUTTON_COLOR, usedFont};
    infoCountryButton = new Button{renderer, " ", 200, 510, 400, 200, WORLD_BUTTON_COLOR, usedFont};
    newsButton = new Button{renderer, " ", -30, -30, 230, 80, WORLD_BUTTON_COLOR, usedFont};

    infoVirusLeftButton = new Button{renderer, " ", -50, 475, 350, 225, WORLD_BUTTON_COLOR, usedFont};
    infoVirusRightButton = new Button{renderer, " ", 500, 475, 350, 225, WORLD_BUTTON_COLOR, usedFont};
    buyUpgradeButton = new Button{renderer, "Buy for ? DNA", 25, 500, 225, 50, CLOSE_BUTTON_COLOR, usedFont};

    countryName = new Label{renderer, "Country", 260, 500, 300, 50, commonFont};
    countryPopulation = new Label{renderer, "0", 280, 520, 300, 50, commonFont};
    countryInfected = new Label{renderer, "0", 280, 540, 300, 50, commonFont};
    newsLabel = new Label{renderer, "News:", 2, 2, 50, 50, usedFont};
    dnaLabel = new Label{renderer, "0", 50, 520, 50, 50, usedFont};

    bgTexture = IMG_LoadTexture(renderer, "assets/Game_background.jpg");
    if(!bgTexture) {
        logger.error(101, "Image for level background not found!\n");
    }

    upgradeMenuTexture = IMG_LoadTexture(renderer, "assets/uhhhm.png");
    if(!upgradeMenuTexture) {
        logger.error(101, "Image for upgrade menu background not found!\n");
    }

    objects.push_back(DrawCountry(EURASIA_VERTICES, "EURASIA", gameWorld->getCountry(1)->getPopulation(), gameWorld->getCountry(1)->getInfected()));
    objects.push_back(DrawCountry(AUSTRALIA_VERTICES, "AUSTRALIA", gameWorld->getCountry(2)->getPopulation(), gameWorld->getCountry(2)->getInfected()));
    objects.push_back(DrawCountry(AFRICA_VERTICES, "AFRICA", gameWorld->getCountry(3)->getPopulation(), gameWorld->getCountry(3)->getInfected()));
    objects.push_back(DrawCountry(SOUTH_AMERICA_VERTICES, "SOUTH AMERICA", gameWorld->getCountry(4)->getPopulation(), gameWorld->getCountry(4)->getInfected()));
    objects.push_back(DrawCountry(NORTH_AMERICA_GREENLAND_VERTICES, "NORTH AMERICA & GRENLAND", gameWorld->getCountry(5)->getPopulation(), gameWorld->getCountry(5)->getInfected()));

    // bobjects.push_back(DrawCountry(HEXAGON_VERTICES));

    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{0, 6}, SDL_Color{119, 151, 51, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{-4, -1}, SDL_Color{241, 241, 234, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{4, -1}, SDL_Color{105, 173, 224, 255}));
    
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{-4, 8}, SDL_Color{119, 151, 51, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{-2, 9}, SDL_Color{119, 151, 51, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{1, 9}, SDL_Color{119, 151, 51, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{3, 8}, SDL_Color{119, 151, 51, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{5, 7}, SDL_Color{119, 151, 51, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{6, 6}, SDL_Color{119, 151, 51, 255}));

    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{-6, -3}, SDL_Color{241, 241, 234, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{-8, -1}, SDL_Color{241, 241, 234, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{-6, 2}, SDL_Color{241, 241, 234, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{-3, 2}, SDL_Color{241, 241, 234, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{-4, -1}, SDL_Color{241, 241, 234, 255}));

    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{-4, 5}, SDL_Color{119, 151, 51, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{4, 5}, SDL_Color{119, 151, 51, 255}));
    nodes.push_back(VirusNode(3, "Beda s boshkoy", "You know what it does", {"requrement"}, SDL_Point{1, 6}, SDL_Color{119, 151, 51, 255}));

}

Game::~Game()
{
    delete countryName;
    delete countryPopulation;
    delete countryInfected;
    delete exitButton;
    delete closeUpgradeMenuButton;
    delete upgradesButton;
    delete infoWorldButton;
    delete infoVirusLeftButton;
    delete infoVirusRightButton;
    delete buyUpgradeButton;
    delete infoCountryButton;
    delete newsButton;
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(upgradeMenuTexture);
}


int Game::draw(SDL_Renderer *renderer)
{
    if(!bgTexture)
        logger.error(101, "No game bg texture!\n");
    
    if(!upgradeMenuTexture)
        logger.error(101, "No upgrade menu bg texture!\n");

    if(!menuOpened)
    {
        SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr);

        for (int i = 0; i < 5; i++)
        {
            DrawCountry country = objects[i];
            country.updateValues(gameWorld->getCountry(i+1)->getInfected());
            if(&country != selectedCountry) {
                country.draw(renderer);
            }
        }

        if (selectedCountry)
        {
            // std::cout << "CUrrent infection rate: " << startCountry->getSpeedVir() << "\n";
            selectedCountry->draw(renderer);
            countryName->change_text(selectedCountry->name);
            countryPopulation->change_text(std::string{"Population: "}.append(std::to_string(startCountry->getPopulation())));
            countryInfected->change_text(std::string{"Infected: "}.append(std::to_string(startCountry->getInfected())));
        }

        dnaLabel->change_text(std::to_string(DNA));

        exitButton->draw(renderer);
        upgradesButton->draw(renderer);
        infoWorldButton->draw(renderer);
        infoCountryButton->draw(renderer);
        newsButton->draw(renderer);

        countryName->draw(renderer);
        countryPopulation->draw(renderer);
        countryInfected->draw(renderer);
        newsLabel->draw(renderer);
        dnaLabel->draw(renderer);

        return 0;
    } else {
        SDL_RenderCopy(renderer, upgradeMenuTexture, nullptr, nullptr);

        for (auto &node : nodes)
        {
            node.draw(renderer);
        }

        for (auto &bob : bobjects)
        {
            bob.draw(renderer);
        }

        closeUpgradeMenuButton->draw(renderer);
        infoVirusLeftButton->draw(renderer);
        infoVirusRightButton->draw(renderer);
        buyUpgradeButton->draw(renderer);

        return 0;
    }
}


int Game::onClick(int mouseX, int mouseY)
{
    if (exitButton->isMouseOver(mouseX, mouseY) & !menuOpened)
    {
        return -2;
    } else if (closeUpgradeMenuButton->isMouseOver(mouseX, mouseY) & menuOpened)
    {
        menuOpened = false;
        *gamepause = true;
    } else if (upgradesButton->isMouseOver(mouseX, mouseY))
    {
        menuOpened = true;
        *gamepause = false;
    }

    for (auto &country : objects)
    {
        if (country.isMouseOver(mouseX, mouseY))
        {
            for (int i{0}; i < 5; i++)
            {
                if (!selectedCountry)
                {
                    if (&country == &objects[i])
                    {
                        gameWorld->getCountry(i+1)->upInfected(10000);
                        startCountry = gameWorld->getCountry(i+1);
                    }
                } else {
                    if (&country == &objects[i])
                    {
                        startCountry = gameWorld->getCountry(i+1);
                    }
                }
            }
            selectedCountry = &country;
            country.is_selected = true;
            for (auto &ccountry : objects)
            {
                ccountry.is_selected = false;
            }
            break;
        }
    }

    return 0;
}


void Game::onMouseOver(int mouseX, int mouseY)
{
    for (auto &country : objects)
    {
        if (country.isMouseOver(mouseX, mouseY))
        {
            country.onMouseOver();
        } else {
            if (country.colorOffset)
            {
                country.colorOffset = 0;
            }
        }
    }

    for (auto &node : nodes)
    {
        if (node.isMouseOver(mouseX, mouseY))
        {
            node.onMouseOver();
        } else {
            if (node.colorOffset)
            {
                node.colorOffset = 0;
            }
        }
    }
}


VirusNode::VirusNode(int price, std::string name, std::string description, std::vector<std::string> requiredNodes, SDL_Point coords, SDL_Color nodeColor) : price(price), name(name), description(description), requires(requiredNodes), position(coords), nodeColor(nodeColor)
{
    is_selected = false;
}

VirusNode::~VirusNode()
{
}

void VirusNode::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, nodeColor.r, nodeColor.g, nodeColor.b, nodeColor.a);
    colorOffset = 0;
    bool requrementsSatisfied = true;
    if (requrementsSatisfied)
    {
        // Sint16* nx = new Sint16[coords.size()];
        // Sint16* ny = new Sint16[coords.size()];

        // for (int i = 0; i < 6; i++)
        // {
        //     nx[i] = coords[i].x;
        //     ny[i] = coords[i].y;
        // }

        // int result = filledPolygonColor(renderer, nx, ny, coords.size(), 0x00FF00FF);

        // delete[] nx;
        // delete[] ny;
    }
    SDL_RenderFillCircle(renderer, 420 + 40*position.x, 253 + 23 * position.y, 19);
}

bool VirusNode::isMouseOver(int mouseX, int mouseY)
{
    return false;
}

void VirusNode::onMouseOver()
{
}

int VirusNode::onClick()
{
    is_selected = true;
    return 0;
}