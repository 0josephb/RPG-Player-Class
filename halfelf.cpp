// Joseph Brown
// Program 3
// Elf implementation

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "halfelf.h"

using namespace std;
using namespace GameSpace;

const int HalfElf::INIT_WPN_NUM;
const string HalfElf::RACE = "HALFELF";
const int HalfElf::ABILITY_ADJ[6] = {0, 0, 1, 2, 0, 1};
const VocRules::VocType HalfElf::DEFAULT_VOC;
const string HalfElf::INIT_WPN[VocRules::NUM_VOC][INIT_WPN_NUM] = {{"",""},{"DAGGER", "SHORT BOW"},{"LONG SWORD",""},{"SWORD",""},{"RAPIER","SHORT BOW"},{"CLUB","LIGHT CROSSBOW"}};

HalfElf::HalfElf(string name, VocRules::VocType inVoc):Humanoid::Humanoid(name, inVoc, ABILITY_ADJ) {

    Humanoid::AddSkill("MOVE SILENTLY");
}

HalfElf::HalfElf* HalfElf::Clone() const {
    return new HalfElf(*this);
}

string HalfElf::RaceStr() const {
   return RACE; 
}

Weapon::Weapon* HalfElf::FindWeapon(Weapon::Weapon* wpn) {
    
    Weapon::Weapon* rv = NULL;

    
    if (wpn != NULL) {
        
        if (wpn->Wt() <= 10) {
            rv = Humanoid::FindWeapon(wpn);
        }
        else {
            rv = wpn;
        }
    }
       
    
    return rv;
}

vector<string> HalfElf::InitialWeaponList() const {
    
    vector<string> weaponList;

    for (int i = 0; i < weaponList.size(); i++) {
        
        if (INIT_WPN[Humanoid::Voc()][i] != "") {
            weaponList.push_back(INIT_WPN[Humanoid::Voc()][i]);
        }
        
    }
    
    return weaponList;
}

int HalfElf::RollSavingThrow(SavingThrowType kindofThrow) const {
    
    int saveThrow = 0;
    
    saveThrow = Humanoid::RollSavingThrow(kindofThrow) * 1.5;

    return saveThrow;
}

void HalfElf::Write(ostream& out) const {

    out << RACE << "#";

    Humanoid::Write(out);

    return;
}
