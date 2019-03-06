// Joseph Brown
// Program 3
// Orc header

#ifndef ORC_CLASS
#define ORC_CLASS

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "humanoid.h"

using namespace std;

class Orc: public Humanoid {

    public:
        
        Orc(string name, VocRules::VocType inVoc=DEFAULT_VOC);

        string RaceStr() const;

        virtual vector<string> InitialWeaponList() const;

        virtual void Write(ostream& out) const;
        
        virtual Orc::Orc* Clone() const;

    private:

        static const string RACE;

        static const int ABILITY_ADJ[6];

        static const VocRules::VocType DEFAULT_VOC = VocRules::BBN;

        static const string INIT_WPN[VocRules::NUM_VOC];

        Orc();


};

#endif
