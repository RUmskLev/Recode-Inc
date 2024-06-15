#ifndef VIRUS_H
#define VIRUS_H
#include <iostream>

class Virus{
        //abilities
        int medResist{0};
        //transmission
        int air{0};
        int water{0};
        int bird{0};
        int bloodTr{0};
        int insect{0};
        int rodent{0};
        int livestock{0};
        //syptoms
        int intestines{0};
        int lungs{0};
        int blood{0};
        int skin{0};
        int immune{0};
        int cns{0};
public:
        //
        Virus() = default;
        //
        //
        int getMedRes() const;
        //
        int getAirTr() const;
        int getWaterTr() const;
        int getBirdTr() const;
        int getBloodTr() const;
        int getInsectTr() const;
        int getRodentTr() const;
        int getLivestockTr() const;
        //
        int getIntestines() const;
        int getLungs() const;
        int getBlood() const;
        int getSkin() const;
        int getImmune() const;
        int getCns() const;
        //
        //
        void upMedRes();
        //
        void upAirTr();
        void upWaterTr();
        void upBirdTr();
        void upBloodTr();
        void upInsectTr();
        void upRodentTr();
        void upLivestockTr();
        //
        void upIntestines();
        void upLungs();
        void upBlood();
        void upSkin();
        void upImmune();
        void upCns();
};

#endif