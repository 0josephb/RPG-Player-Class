// Joseph Brown
// Program 3
// Elf header

#ifndef HALFELF_CLASS
#define HALFELF_CLASS

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "humanoid.h"

using namespace std;

class HalfElf: public Humanoid {

    public:
        
        HalfElf(string name, VocRules::VocType voc=DEFAULT_VOC);

        string RaceStr() const;

        virtual vector<string> InitialWeaponList() const;
        
        virtual Weapon::Weapon* FindWeapon(Weapon::Weapon* wpn);
        
        virtual int RollSavingThrow(SavingThrowType kindofThrow) const;

        virtual void Write(ostream& out) const;
        
        virtual HalfElf::HalfElf* Clone() const;

    private:
        
        static const string RACE;
        
        static const int INIT_WPN_NUM = 2;

        static const int ABILITY_ADJ[6];

        static const VocRules::VocType DEFAULT_VOC = VocRules::ROG;

        static const string INIT_WPN[VocRules::NUM_VOC][INIT_WPN_NUM];

        HalfElf();


};

#endif
