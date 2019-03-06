// Joseph Brown
// Program 3
// Troll header

#ifndef TROLL
#define TROLL

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "monster.h"

using namespace std;

class Troll:public Monster {

    public:

        Troll(string name);

        string RaceStr() const;

        virtual vector<string> InitialWeaponList() const;

        virtual int RollAttack() const;

        virtual int RollSavingThrow(SavingThrowType kindofThrow) const;

        virtual void Write(ostream& out) const;
        
        virtual Troll::Troll* Clone() const;
        
 
    private:

        static const string RACE;

        static const int ABILITY_ADJ[6];

        static const int HIT_DIE[3];

        static const int SAVE_THROW[3];

        static const int BASE_ATT_BONUS[2];

        static const string INIT_WPN;

        static const int NUM_INIT_SKILLS = 2;

        static const string INIT_SKILLS[NUM_INIT_SKILLS];

        Troll();

};

#endif
