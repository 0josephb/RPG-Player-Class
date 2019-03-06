// Joseph Brown
// Program 3
// Elf implementation

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "elf.h"

using namespace std;
using namespace GameSpace;

const string Elf::RACE = "ELF";
const int Elf::ABILITY_ADJ[6] = {2, -2, 0, 0, 0, 0};
const VocRules::VocType Elf::DEFAULT_VOC;
const string Elf::INIT_WPN[VocRules::NUM_VOC] = { "","DAGGER","LONGSWORD","SWORD","RAPIER","SHORT BOW" };

Elf::Elf(string name, VocRules::VocType inVoc):Humanoid::Humanoid(name, inVoc, ABILITY_ADJ) {

}

Elf::Elf* Elf::Clone() const {
    return new Elf(*this);
}

string Elf::RaceStr() const {
   return RACE; 
}

vector<string> Elf::InitialWeaponList() const {
    
    vector<string> weaponList;

    weaponList.push_back(INIT_WPN[Humanoid::Voc()]);
    
    return weaponList;
}

void Elf::Write(ostream& out) const {

    out << RACE << "#";

    Humanoid::Write(out);

    return;
}
