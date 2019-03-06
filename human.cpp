// Joseph Brown
// Program 3
// Human implementation

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "human.h"

using namespace std;
using namespace GameSpace;

const string Human::RACE = "HUMAN";
const int Human::ABILITY_ADJ[6] = {0, 0, 0, 0, 0, 0};
const VocRules::VocType Human::DEFAULT_VOC;
const string Human::INIT_WPN[VocRules::NUM_VOC] =  {"","DAGGER","CROSSBOW","SWORD","RAPIER","CLUB" };

Human::Human(string name, VocRules::VocType inVoc):Humanoid(name, inVoc, ABILITY_ADJ) {

}

Human::Human* Human::Clone() const {
    return new Human(*this);
}

string Human::RaceStr() const {
   return RACE; 
}

vector<string> Human::InitialWeaponList() const {
    
    vector<string> weaponList;

    weaponList.push_back(INIT_WPN[Humanoid::Voc()]);
    
    return weaponList; 
}


void Human::Write(ostream& out) const {

    out << RaceStr() << "#";

    Humanoid::Write(out);

    return;
}
