// Joseph Brown
// Program 3
// Human header

#ifndef HUMAN_CLASS
#define HUMAN_CLASS

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "humanoid.h"

using namespace std;

class Human: public Humanoid {

    public:
        
        Human(string name, VocRules::VocType inVoc = DEFAULT_VOC);

        string RaceStr() const;

        virtual vector<string> InitialWeaponList() const;

        virtual void Write(ostream& out) const;
        
        virtual Human::Human* Clone() const;

    private:

        static const string RACE;

        static const int ABILITY_ADJ[6];

        static const VocRules::VocType DEFAULT_VOC = VocRules::FTR;

        static const string INIT_WPN[VocRules::NUM_VOC];

        Human();


};

#endif
