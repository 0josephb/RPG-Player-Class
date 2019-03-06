// Joseph Brown
// Program 3
// Orc implementation

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "orc.h"

using namespace std;
using namespace GameSpace;

const string Orc::RACE = "ORC";
const int Orc::ABILITY_ADJ[6] = {0, 0, -2, -2, 2, -1};
const VocRules::VocType Orc::DEFAULT_VOC;

const string Orc::INIT_WPN[VocRules::NUM_VOC] = { ""    ,  "DAGGER"   ,    "CROSSBOW"    ,     "SWORD"    ,    "SHORT BOW"    , "LIGHT CROSSBOW" };

Orc::Orc(string name, VocRules::VocType inVoc):Humanoid::Humanoid(name, inVoc, ABILITY_ADJ) {

}

Orc::Orc* Orc::Clone() const {
    return new Orc(*this);
}

string Orc::RaceStr() const {
   return RACE; 
}

vector<string> Orc::InitialWeaponList() const {
    
     vector<string> weaponList;

    weaponList.push_back(INIT_WPN[Humanoid::Voc()]);
    
    return weaponList;
}

void Orc::Write(ostream& out) const {

    out << RACE << "#";

    Humanoid::Write(out);

    return;
}
