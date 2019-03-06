// Joseph Brown
// Program 3
// Ogre implementation

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "ogre.h"

using namespace std;
using namespace GameSpace;

const string Ogre::RACE = "OGRE";
const int Ogre::ABILITY_ADJ[6] = {8, 15, 6, 7, 21, 10};
const int Ogre::HIT_DIE[NUM_DICE_DATA] = {4, 8, 8};
const int Ogre::SAVE_THROW[3] = {6, 0, 1};
const int Ogre::BASE_ATT_BONUS[2] = {1,8};
const string Ogre::INIT_WPN = "SPEAR";
const int Ogre::NUM_INIT_SKILLS;
const string Ogre::INIT_SKILLS[NUM_INIT_SKILLS] = {"INTIMIDATE", "LISTEN", "SPOT"};

Ogre::Ogre(string name):Monster(name, ABILITY_ADJ, HIT_DIE) {
    
    for (int i = 0; i < NUM_INIT_SKILLS; i++) {
        
        PlayerClass::AddSkill(INIT_SKILLS[i]);
    }
    
}

Ogre::Ogre* Ogre::Clone() const {
    return new Ogre(*this);
}

vector<string> Ogre::InitialWeaponList() const {
    
    vector<string> weaponList;
    
    weaponList.push_back(INIT_WPN);
    
    return weaponList; 
}

string Ogre::RaceStr() const {
    return RACE;
}

int Ogre::RollAttack() const {

    int rollAttk = 0;
    
    rollAttk = Monster::RollAttack(BASE_ATT_BONUS);
    
    return rollAttk;
}

int Ogre::RollSavingThrow(SavingThrowType kindofThrow) const {

    int saveThrow = 0;
    
    saveThrow = Monster::RollSavingThrow(kindofThrow, SAVE_THROW);

    return saveThrow;
}

void Ogre::Write(ostream& out) const {
    
    out << RACE << "#";
    Monster::Write(out);
    
    return;
}






