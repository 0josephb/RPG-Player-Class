// Joseph Brown
// Program 3
// Monster header

#ifndef MONSTER
#define MONSTER

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "player3.h"

using namespace std;

class Monster: public PlayerClass {

    public:
       
        virtual vector<string> InitialWeaponList() const = 0;
        
        virtual void Write(ostream& out) const;
        
        virtual Monster::Monster* Clone() const = 0;

    protected:
        
        static const bool rollAbil = false;
         
        Monster(string name, const int abilAdj[], const int hitDie[]);
        
        int RollHitDice() const;

        virtual int RollAttack(const int baseAttkBonus[]) const;

        virtual int RollSavingThrow(SavingThrowType kindofThrow, const int savingThrows[]) const;
        
        

    private:
             
        Monster();

        int AttackBonus(const int baseAttkBonus[]) const;


};

#endif
