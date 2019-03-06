// Joseph Brown
// Program 3
// Monster Implementation

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "monster.h"

using namespace std;
using namespace GameSpace;

Monster::Monster(string name, const int abilAdj[], const int hitDie[]): PlayerClass::PlayerClass(name, abilAdj, rollAbil) {
    
   PlayerClass::InitHP(hitDie);
    
}

int Monster::RollAttack(const int baseAttkBonus[]) const {
    
    int attkBonus = AttackBonus(baseAttkBonus);

    int attkRoll = 0;
    
    if (IsActive()) {
        
        attkRoll = Roll(GameSpace::ATT) + attkBonus;
    }
    
    return attkRoll;
}

int Monster::RollSavingThrow (SavingThrowType kindofThrow, const int savingThrows[]) const {
    
    int mod = 0;
    int saveThrow = 0;
    int saveThrowBonus = 0;

    if (kindofThrow < FORT || kindofThrow > WILL) {
        throw INVALID_SAVINGTHROW;
    }

    if (kindofThrow == GameSpace::FORT) {
        
        saveThrowBonus = savingThrows[GameSpace::FORT-1];
        mod = PlayerClass::AbilityMod(CON);
        
    } else if (kindofThrow == GameSpace::REFLEX) {
        
        saveThrowBonus = savingThrows[GameSpace::REFLEX-1];
        mod = AbilityMod(DEX);
        
    } else if (kindofThrow == GameSpace::WILL) {
        
        saveThrowBonus = savingThrows[GameSpace::WILL-1];
        mod = AbilityMod(WIS);
    }
    
    if (IsActive()){
        saveThrow = Roll(GameSpace::SVTH);
        saveThrow = saveThrow + saveThrowBonus + mod;
    }
    
    
    if (saveThrow < 0) {
   
       saveThrow = 0;
       
   }
    
    return saveThrow;
}

int Monster::AttackBonus(const int baseAttkBonus[]) const {
    
    int modifier = 0;
    int attkBonus = 0;
    
  
    if (Weapon::IsRange(PlayerClass::WeaponName())) {
      
        attkBonus = baseAttkBonus[0];
        modifier = PlayerClass::AbilityMod(DEX);

        attkBonus += modifier;
    }
    else {

        attkBonus = baseAttkBonus[1];
        modifier = PlayerClass::AbilityMod(STR);

        attkBonus += modifier;

    }
    
    return attkBonus;
}

void Monster::Write(ostream& out) const {
    
    PlayerClass::Write(out);
    
    return;
}
