// Joseph Brown
// Program 3
// Humanoid header

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "humanoid.h"

using namespace std;
using namespace GameSpace;

const int Humanoid::START_LEVEL = 1;
const int Humanoid::MAX_LEVEL = 20;
const int Humanoid::START_XP = 0;
const int Humanoid::NUM_INIT_SKILLS;
const string Humanoid::INIT_SKILLS[VocRules::NUM_VOC][NUM_INIT_SKILLS] = {
 
                /* Skill 1 */ /* Skill 2 */ /* Skill 3 */ 
                
    /* NNE */   { "", "", "" },
     
    /* BBN */   { "CLIMB", "LISTEN", "SWIM" },
    
    /* CLR */   { "HEAL", "USE MAGIC DEVICES", "" },
    
    /* FTR */   { "INTIMIDATE", "SWIM", "" },
    
    /* ROG */   { "BLUFF", "CLIMB", "HIDE" },
    
    /* WIZ */   { "CONCENTRATION", "HIDE", "USE MAGIC DEVICES" }
    
};


Humanoid::Humanoid(string name, VocRules::VocType inVoc, const int abilAdj[]):pack(NULL), voc(inVoc) , PlayerClass::PlayerClass(name, abilAdj, rollAbil) {
    
    InitVoc(inVoc);
    
    InitPack();
    InitLevel();
    InitXP();
    DiceArr();
    InitSkills();
    
}

Humanoid::Humanoid(const Humanoid& h):PlayerClass::PlayerClass(h), pack(NULL) {
   
   CopyHumanoid(h);
    
}

Humanoid::~Humanoid() {
    delete pack;
    pack = NULL;
}

Humanoid& Humanoid::operator=(const Humanoid& h){
    
    if (this != &h) {       
       CopyHumanoid(h);
    }
   
   return *this; 
}

VocRules::VocType Humanoid::InitVoc(VocRules::VocType inVoc) {
    
    if (inVoc > 0 && inVoc < VocRules::NUM_VOC) {
        voc = inVoc;
    }
    else {
        throw INVALID_VOC;
    }
    
    return voc;
}

void Humanoid::InitLevel() {
    level = START_LEVEL;
    return;
}

void Humanoid::InitXP() {
    xp = START_XP;
    return;
}

void Humanoid::InitSkills() {
    
    for (int i = 0; i < NUM_INIT_SKILLS; i++) {
        
        if (INIT_SKILLS[voc][i] != "") {

            PlayerClass::AddSkill(INIT_SKILLS[voc][i]);
        }
    }

    return;
}

void Humanoid::InitPack() {
    
    pack = new PackClass(InitPackWt());
    
    return;
}

vector<string> Humanoid::Pack() const {
    return pack->Pack();
}

VocRules::VocType Humanoid::Voc() const {
    
    return voc;
}

string Humanoid::VocStr() const {
    
    VocRules *vocPointer;
    vocPointer = VocRules::GetVocRules();

    string rv = VocRules::VocToStr(voc);

    return rv;
}

int Humanoid::Level() const {
    
    return level;
}

long Humanoid::XP() const {
    
    return xp;
}

Weapon::Weapon* Humanoid::FindWeapon(Weapon::Weapon* wpn) {
 
     Weapon::Weapon* rv = NULL;
     Weapon::Weapon* temp = NULL;
   
    if (PlayerClass::IsActive()) {
    
        if (wpn != NULL) {
        
           temp = PlayerClass::LoseWeapon();
           pack->PackClass::AddWeapon(temp);
           rv = PlayerClass::FindWeapon(wpn);
        }
    }
    else {
        
        rv = wpn;
    }
    
    return rv;

}

Weapon::Weapon* Humanoid::ChangeWeapon(string wName) {
  
    Weapon::Weapon* rv = NULL;
    Weapon::Weapon* temp = NULL;
    
    if (PlayerClass::IsActive()) {
        
        if (pack->PackClass::InPack(wName) && PlayerClass::HasWeapon()) {
            
            temp = pack->PackClass::RemoveWeapon(wName);
            pack->AddWeapon(PlayerClass::LoseWeapon());
            rv = PlayerClass::FindWeapon(temp);
        }
    }
    else {
        
        rv = NULL;
    }
    
    return rv;
}

int Humanoid::RollAttack() const {
  
   VocRules *vocPointer;
   vocPointer = VocRules::GetVocRules();
   int baseAttkBonus = 0; 
   int attkRoll = 0;
   int modifier = 0;
   
   if (IsActive()) {
       
       if (HasWeapon()) {
           
        if (Weapon::IsRange(WeaponName())) {
                
                baseAttkBonus = vocPointer->BaseAttackBonus(voc, level);
                modifier = PlayerClass::AbilityMod(DEX);
        }
       
        else if (Weapon::IsMelee(WeaponName())) {
            
            baseAttkBonus = vocPointer->BaseAttackBonus(voc, level);
            modifier = PlayerClass::AbilityMod(STR);
      }
      
    }
    else {
            
        baseAttkBonus = vocPointer->BaseAttackBonus(voc, level);
        modifier = PlayerClass::AbilityMod(STR);
    }
    
    attkRoll = Roll(GameSpace::ATT) + baseAttkBonus + modifier;
}

    if (attkRoll < 0) {
        attkRoll = 0;
    }
       
    return attkRoll;

}

int Humanoid::RollSavingThrow(SavingThrowType kindOfThrow) const {
    
   VocRules *vocPointer;
   vocPointer = VocRules::GetVocRules();
   int saveThrow = 0;
   int modifier = 0;
   int saveThrowBonus = 0;
    
    if (kindOfThrow < GameSpace::FORT || kindOfThrow > GameSpace::WILL) {
       
       throw INVALID_SAVINGTHROW;
   }
   
     if (PlayerClass::IsActive()) {
        
        saveThrowBonus = vocPointer->BaseSaveBonus(voc, level, kindOfThrow);
        modifier = WhatMod(kindOfThrow);
        saveThrow = Roll(GameSpace::SVTH);
    }
    
    saveThrow = saveThrow + saveThrowBonus + modifier;
    
    if (saveThrow < 0) {
   
       saveThrow = 0;
       
   }
   
   return saveThrow;
}

long Humanoid::UpdateXP(long modification) {
    
    VocRules *vocPointer;
    vocPointer = VocRules::GetVocRules();
    int xpForPromotion = vocPointer->XPforPromotion(level + 1);

    if (modification > 0) {
        
    if (IsActive()) { 
        
            while (xp + modification >= xpForPromotion && level <= Humanoid::MAX_LEVEL-1) {
        
                LevelUp();
                xpForPromotion = vocPointer->XPforPromotion(level + 1);
            }
            
            xp = xp + modification;
    
   }
   
}

    return xp;
    
}

void Humanoid::Write(ostream& out) const {
    
    vector<string> temp = Pack();
   
    out << VocStr() << "#" << level << "#" << xp << "#";
    
    PlayerClass::Write(out);
    
    out << "\t(";
    
    for (int i = 0; i < temp.size(); i++) {
            
        out << temp[i];
            if (i != temp.size()-1) {
                out << ",";
            }
    }
	        
    out << ")" << "#" << endl;

    return;
}

int Humanoid::WhatMod(SavingThrowType kindOfThrow) const {
    
    int rv;
    
    if (kindOfThrow == FORT) {
        rv = PlayerClass::AbilityMod(CON);
    } else if (kindOfThrow == REFLEX) {
        rv = PlayerClass::AbilityMod(DEX);
    } else if (kindOfThrow == WILL) {
        rv = PlayerClass::AbilityMod(WIS);
    }
    
    return rv;
    
}

int Humanoid::InitPackWt() const {
    
    int weight = 0;
    
    weight = 25 + (AbilityMod(STR) * 5);
    
    return weight;
}

Humanoid::Humanoid& Humanoid::CopyHumanoid(const Humanoid& h) {
    
    delete pack;
    pack = NULL;
    
    if (h.pack != NULL) {
        pack = new PackClass::PackClass(*h.pack);
    }
    
    voc = h.voc;
    level = h.level;
    xp = h.xp;
    
    PlayerClass::CopyPlayer(h);
    
    
    return *this;
}

void Humanoid::LevelUp() {

    VocRules *vocPointer;
    vocPointer = VocRules::GetVocRules();
    int hitDie = vocPointer->HitDie(voc);
	
	int hpToAdd;
    hpToAdd = Dice::Roll(Name(), GameSpace::HP, 1, hitDie) + PlayerClass::AbilityMod(PlayerClass::CON);
    
    if (hpToAdd <= 0) {
        hpToAdd = 1;
    }
	
    PlayerClass::UpdateMaxHP(hpToAdd);
	
    level++;
    
    return;
}

void Humanoid::DiceArr() {
    
    VocRules *vocPointer;
    vocPointer = VocRules::GetVocRules();
    int value = vocPointer->HitDie(voc);
  
    int hitDie[3];
    
    hitDie[0] = 1;
    hitDie[1] = value;
    hitDie[2] = AbilityMod(CON);
    
    PlayerClass::InitHP(hitDie);
    
    return;
}





















