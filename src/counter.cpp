#include "counter.h"

void updateCounter(int losses, int winnnings){
        std::ofstream out("counter.txt");
        out << losses << " " << winnnings;
        out.close();
}