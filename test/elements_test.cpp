#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "virus.h"
#include "world.h"

TEST_CASE("Virus"){
        Virus covid19;
        CHECK(covid19.getMedRes() == 0);
        CHECK(covid19.getAirTr() == 0);
        CHECK(covid19.getWaterTr() == 0);
        CHECK(covid19.getBirdTr() == 0);
        CHECK(covid19.getBloodTr() == 0);
        CHECK(covid19.getInsectTr() == 0);
        CHECK(covid19.getRodentTr() == 0);
        CHECK(covid19.getLivestockTr() == 0);
        CHECK(covid19.getIntestines() == 0);
        CHECK(covid19.getLungs() == 0);
        CHECK(covid19.getBlood() == 0);
        CHECK(covid19.getSkin() == 0);
        CHECK(covid19.getImmune() == 0);
        CHECK(covid19.getCns() == 0);
        for(int i{0}; i < 10; ++i){
                covid19.upMedRes();
                covid19.upAirTr();
                covid19.upWaterTr();
                covid19.upBirdTr();
                covid19.upBloodTr();
                covid19.upInsectTr();
                covid19.upRodentTr();
                covid19.upLivestockTr();
                covid19.upIntestines();
                covid19.upLungs();
                covid19.upBlood();
                covid19.upSkin();
                covid19.upImmune();
                covid19.upCns();
        }
        CHECK(covid19.getMedRes() == 10);
        CHECK(covid19.getAirTr() == 10);
        CHECK(covid19.getWaterTr() == 10);
        CHECK(covid19.getBirdTr() == 10);
        CHECK(covid19.getBloodTr() == 10);
        CHECK(covid19.getInsectTr() == 10);
        CHECK(covid19.getRodentTr() == 10);
        CHECK(covid19.getLivestockTr() == 10);
        CHECK(covid19.getIntestines() == 10);
        CHECK(covid19.getLungs() == 10);
        CHECK(covid19.getBlood() == 10);
        CHECK(covid19.getSkin() == 10);
        CHECK(covid19.getImmune() == 10);
        CHECK(covid19.getCns() == 10);

}

TEST_CASE("Country"){
        Country country(100, 2, 1);
        CHECK(country.getPopulation() == 100);
        CHECK(country.getInfected() == 0);
        CHECK(country.getProbVir() == 0.0);
        CHECK(country.getSpeedVir() == 0.0);
        CHECK(country.getNOC() == 1);

        CHECK(country.getRV() == std::vector<int>{0, 0});
        CHECK(country.getAV() == std::vector<int>{0, 0});
        CHECK(country.getWV() == std::vector<int>{0, 0});

        country.makeRoad(1);
        country.makeAirRoad(1);
        country.makeWaterRoad(1);

        country.makeRoad(2);
        country.makeAirRoad(2);
        country.makeWaterRoad(2);

        CHECK(country.getRV() == std::vector<int>{1, 1});
        CHECK(country.getAV() == std::vector<int>{1, 1});
        CHECK(country.getWV() == std::vector<int>{1, 1});

        // Повторное действие
        country.makeRoad(2);
        country.makeAirRoad(2);
        country.makeWaterRoad(2);

        CHECK(country.getRV() == std::vector<int>{1, 1});
        CHECK(country.getAV() == std::vector<int>{1, 1});
        CHECK(country.getWV() == std::vector<int>{1, 1});
        //

        country.closeRoad(1);
        country.closeAirRoad(1);
        country.closeWaterRoad(1);

        CHECK(country.getRV() == std::vector<int>{0, 1});
        CHECK(country.getAV() == std::vector<int>{0, 1});
        CHECK(country.getWV() == std::vector<int>{0, 1});

        // Повторное действие
        country.closeRoad(1);
        country.closeAirRoad(1);
        country.closeWaterRoad(1);

        CHECK(country.getRV() == std::vector<int>{0, 1});
        CHECK(country.getAV() == std::vector<int>{0, 1});
        CHECK(country.getWV() == std::vector<int>{0, 1});
        //

        country.upInfected(10);
        CHECK(country.getInfected() == 10);

        country.upInfected(100);
        CHECK(country.getInfected() == 110);

        country.upInfected(-110);
        CHECK(country.getInfected() == 0);

        country.updateProbVir(0.5);
        country.updateSpeedVir(0.5);
        CHECK(country.getProbVir() == 0.5);
        CHECK(country.getSpeedVir() == 0.5);

        country.updateProbVir(1.5);
        country.updateSpeedVir(1.5);
        CHECK(country.getProbVir() == 1.5);
        CHECK(country.getSpeedVir() == 1.5);
}


TEST_CASE("World for two countries"){
        Country c1(100, 2, 1);
        Country c2(200, 2, 2);
        
        World world;
        world.addCountry(c1);
        world.addCountry(c2);

        CHECK(world.getCountry(1) == &c1);
        CHECK(world.getCountry(2) == &c2);

        world.makeRoad(1, 2);
        world.makeAirRoad(1, 2);
        world.makeWaterRoad(1, 2);

        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 1});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{1, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 1});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{1, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 1});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{1, 0});

        // Повторный вызов
        world.makeRoad(1, 2);
        world.makeAirRoad(1, 2);
        world.makeWaterRoad(1, 2);

        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 1});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{1, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 1});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{1, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 1});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{1, 0});
        //

        world.closeRoad(1, 2);
        world.closeAirRoad(1, 2);
        world.closeWaterRoad(1, 2);

        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{0, 0});

        // Повторный вызов
        world.closeRoad(1, 2);
        world.closeAirRoad(1, 2);
        world.closeWaterRoad(1, 2);

        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 0});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{0, 0});
        //

        world.addCountry(c2);
        CHECK(world.getCountry(2) == world.getCountry(3));


}

TEST_CASE("World for three countries"){
        Country c1(100, 3, 1);
        Country c2(200, 3, 2);
        Country c3(200, 3, 3);

        World world;
        world.addCountry(c1);
        world.addCountry(c2);
        world.addCountry(c3);

        world.makeAllRoads(1);
        world.makeAllAirRoads(1);
        world.makeAllWaterRoads(1);
        
        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(3)->getRV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(3)->getAV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(3)->getWV() == std::vector<int>{1, 0, 0});

        // Повторный вызов
        world.makeAllRoads(1);
        world.makeAllAirRoads(1);
        world.makeAllWaterRoads(1);
        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(3)->getRV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(3)->getAV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(3)->getWV() == std::vector<int>{1, 0, 0});
        //

        world.closeCountry(1);
        world.closeAirCountry(1);
        world.closeWaterCountry(1);
        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getWV() == std::vector<int>{0, 0, 0});
        
        // Повторный вызов
        world.closeCountry(1);
        world.closeAirCountry(1);
        world.closeWaterCountry(1);
        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getWV() == std::vector<int>{0, 0, 0});
        //

        world.makeAllAllRoads();
        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{1, 0, 1});
        CHECK(world.getCountry(3)->getRV() == std::vector<int>{1, 1, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{1, 0, 1});
        CHECK(world.getCountry(3)->getAV() == std::vector<int>{1, 1, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{1, 0, 1});
        CHECK(world.getCountry(3)->getWV() == std::vector<int>{1, 1, 0});

        // Повторный вызов
        world.makeAllAllRoads();
        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{1, 0, 1});
        CHECK(world.getCountry(3)->getRV() == std::vector<int>{1, 1, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{1, 0, 1});
        CHECK(world.getCountry(3)->getAV() == std::vector<int>{1, 1, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 1, 1});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{1, 0, 1});
        CHECK(world.getCountry(3)->getWV() == std::vector<int>{1, 1, 0});
        //

        world.closeAllAllCountries();
        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getWV() == std::vector<int>{0, 0, 0});

        // Повторный вызов
        world.closeAllAllCountries();
        CHECK(world.getCountry(1)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getRV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getAV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{0, 0, 0});
        CHECK(world.getCountry(3)->getWV() == std::vector<int>{0, 0, 0});
        //

        world.makeAllAllRoads();
        for(int i{1}; i <= 3; ++i){
                Country* country = world.getCountry(i);
                country->updateProbVir(0.5);
                country->updateSpeedVir(0.5);
                country->upInfected(100);
        }
        world.initStartWorld();
        CHECK(world.getCountry(1)->getRV() == std::vector<int>{1, 0, 0});
        CHECK(world.getCountry(2)->getRV() == std::vector<int>{0, 1, 0});
        CHECK(world.getCountry(3)->getRV() == std::vector<int>{0, 0, 1});
        CHECK(world.getCountry(1)->getAV() == std::vector<int>{1, 1, 1});
        CHECK(world.getCountry(2)->getAV() == std::vector<int>{1, 1, 1});
        CHECK(world.getCountry(3)->getAV() == std::vector<int>{1, 1, 1});
        CHECK(world.getCountry(1)->getWV() == std::vector<int>{1, 1, 1});
        CHECK(world.getCountry(2)->getWV() == std::vector<int>{1, 1, 1});
        CHECK(world.getCountry(3)->getWV() == std::vector<int>{1, 1, 1});
        for(int i{1}; i <= 3; ++i){
                Country* country = world.getCountry(i);
                CHECK(country->getProbVir() == 0.0);
                CHECK(country->getSpeedVir() == 0.0);
                CHECK(country->getInfected() == 0);
        }

}

