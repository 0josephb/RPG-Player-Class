// Joseph Brown
// Program 3
// Elf header

#ifndef ELF_CLASS
#define ELF_CLASS

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "humanoid.h"

using namespace std;

class Elf: public Humanoid {

    public:
        
        Elf(string name, VocRules::VocType voc=DEFAULT_VOC);

        string RaceStr() const;

        virtual vector<string> InitialWeaponList() const;

        virtual void Write(ostream& out) const;
        
        virtual Elf::Elf* Clone() const;

    private:

        static const string RACE;

        static const int ABILITY_ADJ[6];

        static const VocRules::VocType DEFAULT_VOC = VocRules::WIZ;

        static const string INIT_WPN[VocRules::NUM_VOC];

        Elf();


};

#endif
