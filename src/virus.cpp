#include "virus.h"
//
int Virus::getMedRes() const{
        return medResist;
}
//
int Virus::getAirTr() const{
        return air;
}

int Virus::getWaterTr() const{
        return water;
}

int Virus::getBirdTr() const{
        return bird;
}

int Virus::getBloodTr() const{
        return bloodTr;
}

int Virus::getInsectTr() const{
        return insect;
}

int Virus::getRodentTr() const{
        return rodent;
}

int Virus::getLivestockTr() const{
        return livestock;
}
//
int Virus::getIntestines() const{
        return intestines;
}
        
int Virus::getLungs() const{
        return lungs;
}

int Virus::getBlood() const{
        return blood;
}

int Virus::getSkin() const{
        return skin;
}

int Virus::getImmune() const{
        return immune;
}

int Virus::getCns() const{
        return cns;
}
//
//
void Virus::upMedRes(){
        ++medResist;
}
//
void Virus::upAirTr(){
        ++air;
}
        
void Virus::upWaterTr(){
        ++water;
}
        
void Virus::upBirdTr(){
        ++bird;
}

void Virus::upBloodTr(){
        ++bloodTr;
}

void Virus::upInsectTr(){
        ++insect;
}

void Virus::upRodentTr(){
        ++rodent;
}

void Virus::upLivestockTr(){
        ++livestock;
}
//
void Virus::upIntestines(){
        ++intestines;
}

void Virus::upLungs(){
        ++lungs;
}
        
void Virus::upBlood(){
        ++blood;
}
        
void Virus::upSkin(){
        ++skin;
}
        
void Virus::upImmune(){
        ++immune;
}
        
void Virus::upCns(){
        ++cns;
}
