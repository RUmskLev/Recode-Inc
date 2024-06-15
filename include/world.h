#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>


class Country{
        int population;
        int infected;
        double probabilityVirus;
        double speedVirus;
        int noc; //number of country
        //roads
        std::vector<int> rv;
        //air_roads
        std::vector<int> av;
        //water_roads
        std::vector<int> wv;
public:
        Country(int pop, int n, int numb);

        void makeRoad(int i);
        void makeAirRoad(int i);
        void makeWaterRoad(int i);

        void closeRoad(int i);
        void closeAirRoad(int i);
        void closeWaterRoad(int i);

        int getPopulation();
        int getInfected();
        double getProbVir();
        double getSpeedVir();
        int getNOC();
        std::vector<int> getRV();
        std::vector<int> getAV();
        std::vector<int> getWV();

        void upInfected(int inf);
        void updateProbVir(double newProbVir);
        void updateSpeedVir(double newSpeed);
};      


class World{
        std::vector<Country*> countries;
public:
        World() = default;


        Country* getCountry(int i);

        void makeRoad(int country1, int country2);
        void makeAirRoad(int country1, int country2);
        void makeWaterRoad(int country1, int country2);

        void closeRoad(int country1, int country2);
        void closeAirRoad(int country1, int country2);
        void closeWaterRoad(int country1, int country2);

        void closeCountry(int i);
        void closeAirCountry(int i);
        void closeWaterCountry(int i);

        void makeAllRoads(int i);
        void makeAllAirRoads(int i);
        void makeAllWaterRoads(int i);

        void closeAllAllCountries();

        void makeAllAllRoads();

        void addCountry(Country &country);

};

#endif