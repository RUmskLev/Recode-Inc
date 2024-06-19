#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>


/**
*\file
*Описание вспомогательных классов
*/

/**
*Представляет совокупность параметров страны игры 
*и методов взаимодействия с этими параметрами
*/
class Country{
        int population;///< Популяция страны
        int infected;///< Количество заражённых в стране
        double probabilityVirus;///< Вероятность попадания вируса в страну
        double speedVirus;///< Скорость вируса в стране
        int noc;///< Номер страны
        //roads
        std::vector<int> rv;///< Вектор смежности сухопутных путей
        //air_roads
        std::vector<int> av;///< Вектор смежности воздушных путей
        //water_roads
        std::vector<int> wv;///< Вектор смежности водных путей
public:
        /**
        *Конструктор класса страны
        *\param[in] pop популяция страны
	*\param[in] n количество стран
	*\param[in] numb номер страны
        */
        Country(int pop, int n, int numb);

        /**
        *Создание сухопутного пути
        *\param[in] i номер страны, куда ведёт сухопутный путь
        */
        void makeRoad(int i);
        /**
        *Создание воздушного пути
        *\param[in] i номер страны, куда ведёт воздушный путь
        */
        void makeAirRoad(int i);
        /**
        *Создание водного пути
        *\param[in] i номер страны, куда ведёт водный путь
        */
        void makeWaterRoad(int i);

        /**
        *Закрытие сухопутного пути
        *\param[in] i номер страны, куда ведёт сухопутный путь
        */
        void closeRoad(int i);
        /**
        *Закрытие воздушного пути
        *\param[in] i номер страны, куда ведёт воздушный путь
        */
        void closeAirRoad(int i);
        /**
        *Закрытие водного пути
        *\param[in] i номер страны, куда ведёт водный путь
        */
        void closeWaterRoad(int i);

        /**
         * Возвращает популяцию страны
         * \return популяция страны 
         */
        int getPopulation();
        /**
         * Возвращает количество заражённых в стране
         * \return количество заражённых в стране
         */
        int getInfected();
        /**
         * Возвращает вероятность попадания вируса в страну
         * \return вероятность попадания вируса в страну
         */
        double getProbVir();
        /**
         * Возвращает скорость вируса в стране
         * \return скорость вируса в стране
         */
        double getSpeedVir();
        /**
         * Возвращает номер страны
         * \return номер страны 
         */
        int getNOC();
        /**
         * Возвращает вектор смежности сухопутных путей
         * \return вектор смежности сухопутных путей
         */
        std::vector<int> getRV();
        /**
         * Возвращает вектор смежности воздушных путей
         * \return вектор смежности воздушных путей
         */
        std::vector<int> getAV();
        /**
         * Возвращает вектор смежности водных путей
         * \return вектор смежности водных путей
         */
        std::vector<int> getWV();

        /**
        *Увеличение числа заражённых
        *\param[in] inf число новых заражённых
        */
        void upInfected(int inf);
        /**
        *Изменение вероятности попадания вируса в страну
        *\param[in] newProbVir новая вероятность попадания вируса в страну
        */
        void updateProbVir(double newProbVir);
        /**
        *Изменение скорости вируса в стране
        *\param[in] newSpeed новая скорость вируса в стране
        */
        void updateSpeedVir(double newSpeed);
};      


/**
*Представляет собой мир, 
*то есть совокупность стран и методы налаживания связей между ними 
*и методов взаимодействия с этими параметрами
*/
class World{
        std::vector<Country*> countries;///< Список указателей на объекты стран
public:
        /**
        *Конструктор класса мира по умолчанию
        */
        World() = default;

        /**
        *Возвращает указательна страну по номеру в списке мира
        *\param[in] i номер страны в списке мира
        * \return указатель на страну с указанным номером в списке (i)
        */
        Country* getCountry(int i);

        /**
        *Прокладывает сухопутный путь между стран
        *\param[in] country1 первая страна, соединяемая путём
        *\param[in] country2 вторая страна, соединяемая путём
        */
        void makeRoad(int country1, int country2);
        /**
        *Прокладывает воздушный путь между стран
        *\param[in] country1 первая страна, соединяемая путём
        *\param[in] country2 вторая страна, соединяемая путём
        */
        void makeAirRoad(int country1, int country2);
        /**
        *Прокладывает водный путь между стран
        *\param[in] country1 первая страна, соединяемая путём
        *\param[in] country2 вторая страна, соединяемая путём
        */
        void makeWaterRoad(int country1, int country2);

        /**
        *Закрывает сухопутный путь между стран
        *\param[in] country1 первая страна, соединяемая путём
        *\param[in] country2 вторая страна, соединяемая путём
        */
        void closeRoad(int country1, int country2);
        /**
        *Закрывает воздушный путь между стран
        *\param[in] country1 первая страна, соединяемая путём
        *\param[in] country2 вторая страна, соединяемая путём
        */
        void closeAirRoad(int country1, int country2);
        /**
        *Закрывает водный путь между стран
        *\param[in] country1 первая страна, соединяемая путём
        *\param[in] country2 вторая страна, соединяемая путём
        */
        void closeWaterRoad(int country1, int country2);

        /**
        *Закрывает все внешние сухопутные пути из указанной страны
        *\param[in] i номер "закрываемой" страны
        */
        void closeCountry(int i);
        /**
        *Закрывает все внешние воздушные пути из указанной страны
        *\param[in] i номер "закрываемой" страны
        */
        void closeAirCountry(int i);
        /**
        *Закрывает все внешние водные пути из указанной страны
        *\param[in] i номер "закрываемой" страны
        */
        void closeWaterCountry(int i);

        /**
        *Прокладывает все внешние сухопутные пути из указанной страны
        *\param[in] i номер рассматриваемой страны
        */
        void makeAllRoads(int i);
        /**
        *Прокладывает все внешние воздушные пути из указанной страны
        *\param[in] i номер рассматриваемой страны
        */
        void makeAllAirRoads(int i);
        /**
        *Прокладывает все внешние водные пути из указанной страны
        *\param[in] i номер рассматриваемой страны
        */
        void makeAllWaterRoads(int i);

        /**
        *Закрывает все внешние пути
        */
        void closeAllAllCountries();

        /**
        *Прокладывает все внешние пути
        */
        void makeAllAllRoads();

        /**
        *Добавление новой страны в мир
        *\param[in] country страна (экземпляр класса страны)
        */
        void addCountry(Country &country);

        /**
        *Возвращение мира к начальному состоянию
        */
        void initStartWorld();
};

#endif