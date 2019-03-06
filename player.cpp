// Joseph Brown
// Program 3
// PlayerClass Implementation

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "player3.h"

using namespace std;
using namespace GameSpace;

PlayerClass::MapType PlayerClass::skillsMap;

const int PlayerClass::NUM_ABILITY;
const int PlayerClass::DEAD = -10;
const int PlayerClass::DISABLED = 0;
const int PlayerClass::DYING = -1;
const int PlayerClass::START_ROW = -1;
const int PlayerClass::START_COL = -1;
const int PlayerClass::MAX_NAME_SIZE = 10;
const int PlayerClass::NUM_ROLLTYPE;
const int PlayerClass::NUM_DICE_DATA;

const int PlayerClass::DICE[NUM_ROLLTYPE][NUM_DICE_DATA] = {
    
    
         // NUM FACES MOD
    /*DEX*/ {3,   6,   0},
    /*CON*/ {3,   6,   0},
    /*INT*/ {3,   6,   0},
    /*CHA*/ {3,   6,   0},
    /*STR*/ {3,   6,   0},
    /*WIS*/ {3,   6,   0},
    /*GP*/  {0,   0,   0},  
    /*HP*/  {1,   0,   0},
    /*INIT*/{1,  20,   0},
    /*ATT*/ {1,  20,   0},
    /*SVTH*/{1,  20,   0}, 
    /*SKCK*/{1,  20,   0},
    /*DMG*/ {0,   0,   0}
    
};

PlayerClass::PlayerClass() {

}

PlayerClass::PlayerClass(string InName, const int abilAdj[], bool rollAbil): NAME(InitName(InName)), activeWpnPtr(NULL) {
    
    static bool isLoaded = false;
    
    if (!isLoaded) {
        skillsMap = LoadSkillsMap();
        isLoaded = true;
    }
    
    InitAbilities(abilAdj,rollAbil);
    InitVar();
    
    
}

PlayerClass::~PlayerClass() {
    
    delete activeWpnPtr;
    activeWpnPtr = NULL;
}

PlayerClass::PlayerClass(const PlayerClass& p): activeWpnPtr(NULL), NAME(p.NAME) {
  
    CopyPlayer(p);
    
}

PlayerClass::PlayerClass& PlayerClass::CopyPlayer(const PlayerClass& p) {
    
    delete activeWpnPtr;
    activeWpnPtr = NULL;
    
    if (p.HasWeapon()) {
   
        activeWpnPtr = new Weapon(*p.activeWpnPtr);
    
    }
    else {
        
        activeWpnPtr = NULL;
    }
    
    
    *const_cast<string *>(&NAME) = p.NAME;
    
    row = p.row;
    col = p.col;
    currentHP = p.currentHP;
    maxHP = p.maxHP;

    for (int i = 0; i < NUM_ABILITY; i++) {
        abilityScores[i] = p.abilityScores[i];
    }
    
    skills = p.skills;
    
    return *this;
}

PlayerClass& PlayerClass::operator=(const PlayerClass& p) {
    
    if (this != &p) {
        CopyPlayer(p);
    }
    
    return *this;
}

string PlayerClass::Name() const {

    return NAME;

}

int PlayerClass::Row() const {

    return row;

}

int PlayerClass::Col() const {

    return col;

}

int PlayerClass::HP() const {

    return currentHP;

}

int PlayerClass::MaxHP() const {

    return maxHP;

}

int PlayerClass::Ability(PlayerClass::AbilityType ability) const {

    return abilityScores[ability];
    
}

vector<int> PlayerClass::Abilities() const {
    
    vector<int> rv;
    
    for (int i = 0; i < NUM_ABILITY; i++) {
        rv.push_back(abilityScores[i]);
    }
    
    return rv;
}

int PlayerClass::AbilityMod(PlayerClass::AbilityType ability) const {
    
    int rv;
    
    rv = (abilityScores[ability] / 2) - 5;
    
    return rv;
    
}

string PlayerClass::WeaponName() const {
    
    string rv = "";
    
    if (HasWeapon()) {
        
        rv = activeWpnPtr->Name();
        
    }
    
    return rv;
}

string PlayerClass::WeaponNameAndNum() const {
    
    string rv = "";
    
    if (HasWeapon()) {
        
        rv = activeWpnPtr->NameAndNum();
    }
    
    return rv;
}

vector<string> PlayerClass::Skills() const {
    
    return skills;
}

bool PlayerClass::IsActive() const {
    return (!IsDead() && !IsDying() && !IsDisabled());
}

bool PlayerClass::IsDead() const {
    return (currentHP <= DEAD);
}

bool PlayerClass::IsDying() const {
    return (currentHP <= DYING && currentHP > DEAD);
}

bool PlayerClass::IsDisabled() const {
    return (currentHP == DISABLED);
}

bool PlayerClass::HasWeapon() const {
    return (activeWpnPtr != NULL);
}

int PlayerClass::UpdateHP(int modification) {

    if (!IsDead()) {
        if (modification > 0) {

            currentHP = currentHP + modification;

            if (currentHP > maxHP) {

                currentHP = maxHP;

            }

        } else if (modification < 0) {

            currentHP = currentHP + modification;

        }

    }
    
    return currentHP;
}

int PlayerClass::UpdateMaxHP(int modification) {
    
     if (!IsDead()) {
        if (modification > 0) {

            maxHP = maxHP + modification;

            if (currentHP < maxHP) {

                currentHP = maxHP;

            }

        } 

    }
    
    return 0; 
}

bool PlayerClass::SetCell(int newRow, int newCol) {
    
    bool rv = false;
    
    if ((newRow <= GameSpace::NUMROWS) && (newCol <= GameSpace::NUMCOLS)) {

        if ((newRow >= 0) && (newCol >= 0)) {

            row = newRow;
            col = newCol;
            rv = true;

        }
        else if ((newRow == -1) && (newCol == -1)) {

            row = START_ROW;
            col = START_COL;
            rv = true;

        }
    }
    return rv;
}

int PlayerClass::SkillCheck(string skill) {
    
    AbilityType abil;
    int modifier = 0;
    int skillCheckValue = 0;

    if (ValidSkill(skill)) {
        
        if (!IsDead()) {
        
            if (FindSkill(skill)) {
            
                abil = skillsMap.find(GameSpace::Ucase(skill))->second;
                modifier = AbilityMod(abil);
                skillCheckValue = Roll(GameSpace::SKCK) + modifier;
            }   
        }
    }
    else {
        
        throw INVALID_SKILL;
    }
    
    
    return skillCheckValue;
}

bool PlayerClass::AddSkill(string inSkill) {
 
   bool rv = false;
    
        if (ValidSkill(inSkill)) {
            
            if (!FindSkill(inSkill)) {
                
                if (IsActive()) {
                    inSkill = GameSpace::Ucase(inSkill);
                    skills.push_back(inSkill);
                    rv = true;
                    }
            }
            else if (FindSkill(inSkill)) {
                rv = true;
            }
        }
        else {
            throw INVALID_SKILL;
        }
    
    GameSpace::Sort(skills);
    
    return rv;
}

void PlayerClass::Amnesia() {

    if (IsActive()) {
        skills.clear();
    }
    
    return;
}

Weapon* PlayerClass::LoseWeapon() {
    
    Weapon::Weapon* temp = activeWpnPtr;
    
    activeWpnPtr = NULL;
    
    return temp;
}

Weapon* PlayerClass::FindWeapon(Weapon::Weapon* wpn) {
    
    Weapon::Weapon* temp = NULL;
    
    if (IsActive()) {
        
        if (wpn != NULL) {
            
            temp = activeWpnPtr;
            activeWpnPtr = wpn;
            wpn = temp;
            
        }
        
    }
    
    temp = NULL;
    
    return wpn;
}

int PlayerClass::RollInitiative() const {
    
    int initiative = 0;
    int modifier = AbilityMod(DEX);
    
    if (IsActive()) {
        
        initiative = Roll(GameSpace::INIT) + modifier;
        
    }
    
    return initiative;
}

int PlayerClass::RollDefense() const {
    
    int defense = 0;
    
    if (IsActive()) {
        
        defense = 10 + AbilityMod(DEX);
    }
    
    return defense;
}

int PlayerClass::RollDamage() const {
    
    int modifier = AbilityMod(STR);
    int damage = 0;

    if (IsActive()) {
        
        if (HasWeapon()) {
            
            damage = activeWpnPtr->RollWeaponDamage(NAME);
            
            if (activeWpnPtr->IsMelee()) {
                
                damage = damage + modifier;
                
            }
            
        } else {
            
            damage = modifier;
            
        }
    }
    
    if (damage < 0) {
        damage = 0;
    }
    
    return damage;
    
}


void PlayerClass::Write(ostream& out) const {


    out << NAME << "#(" << row << "," << col << ")#" 
    << currentHP << "#" << maxHP << "#[" << abilityScores[DEX] << "#" << abilityScores[CON] << "#" << abilityScores[INT] << "#" << abilityScores[CHA] << "#" << abilityScores[STR] << "#" << abilityScores[WIS]
            << "]#" << WeaponNameAndNum() << "#" <<"("; 
            
            for (int i = 0; i < skills.size(); i++) {
                
		        out << skills[i];
                if ( i != skills.size()-1) {
                    out << ",";
                }
	        }   
            
            out << ")" << "#" << endl;
            
    
    return;
}


bool PlayerClass::operator == (const PlayerClass& p) const {
    return (GameSpace::Ucase(NAME) == GameSpace::Ucase(p.NAME));
}

bool PlayerClass::operator != (const PlayerClass& p) const {
    return (GameSpace::Ucase(NAME) != GameSpace::Ucase(p.NAME));
}

bool PlayerClass::operator < (const PlayerClass& p) const {
    return (GameSpace::Ucase(NAME) < GameSpace::Ucase(p.NAME));
}

bool PlayerClass::operator <= (const PlayerClass& p) const {
    return (GameSpace::Ucase(NAME) <= GameSpace::Ucase(p.NAME));
}

bool PlayerClass::operator > (const PlayerClass& p) const {
    return (GameSpace::Ucase(NAME) > GameSpace::Ucase(p.NAME));
}

bool PlayerClass::operator >= (const PlayerClass& p) const {
    
    return (GameSpace::Ucase(NAME) >= GameSpace::Ucase(p.NAME));
}

string PlayerClass::InitName(string n) {
    
    n = GameSpace::TrimStr(n);
    string tempName;
    
    if (n.length() > 0 && n.length() <= MAX_NAME_SIZE){

        tempName = n;
        
    }
    else if (n.length() > MAX_NAME_SIZE) {
        
        n.resize(MAX_NAME_SIZE);
        tempName = n;
    
    }
    else {
        
        throw INVALID_NAME;
        
    }
    
    return TrimStr(tempName);
}

void PlayerClass::InitAbilities(const int abilAdj[], bool rollAbil) {
    
    int roll = 0;
    
    for (int i = 0; i < NUM_ABILITY; i++) {
            
        if (rollAbil) {
            
            roll = Roll(static_cast <GameSpace::RollType>(i));
        }
        
        abilityScores[i] = abilAdj[i] + roll;
    }
    
   return;
}


void PlayerClass::InitHP(const int hitDie[]) {
   
    maxHP = Roll(hitDie, GameSpace::HP);
    currentHP = maxHP;
    
    if (maxHP <= 0) {
        maxHP = currentHP = 1;
    }

    return;
}

void PlayerClass::InitVar() {
    
    row = START_ROW;
    col = START_COL;
    
    maxHP = 1;
    currentHP = 1;
    
    return;
}

bool PlayerClass::FindSkill(string skillToFind) {
	
    bool found = false;
	vector<string>::iterator iter;
	
	skillToFind = Ucase(skillToFind);
	
	for (iter = skills.begin(); iter != skills.end(); iter++) {
		
		if (skillToFind == *iter) {
			found = true;
		}
	}
	
	return found;
}

bool PlayerClass::ValidSkill(string skill) {
    bool rv = false;
    
    int tempSkill = skillsMap.count(GameSpace::Ucase(skill));
    
    if (tempSkill > 0) {
        rv = true;
    }
    
    return rv;
}

PlayerClass::MapType PlayerClass::LoadSkillsMap() {
    
	bool found = false;
	string aSkill, ability;
	AbilityType abil;
	ifstream fin;

	fin.open(GameSpace::SKILLS_FILE.c_str());
	// asssume that is opens correctly
	
	getline(fin, aSkill, '#');
	getline(fin, ability);
	while (fin && !found)
	{
      abil = StrToAbility(ability);
      skillsMap.insert(make_pair(GameSpace::Ucase(aSkill),abil));
        
		getline(fin, aSkill, '#');
		getline(fin, ability);
	}
	fin.close();

    
    return skillsMap;
}

PlayerClass::AbilityType PlayerClass::StrToAbility(string s) {
    
    AbilityType abil;
    s = GameSpace::Ucase(s);
    
      if (s == "DEX")
        abil = DEX;
      else if (s == "CON")
        abil = CON;
      else if (s == "INT")
        abil = INT;
      else if (s == "CHA")
        abil = CHA;
      else if (s == "STR")
        abil = STR;
      else if (s == "WIS")
        abil = WIS;
      return abil;
    
    return abil;
}

int PlayerClass::Roll(const int Dice[], RollType rollInput) const {
    return (Dice::Roll(NAME, rollInput, Dice[num], Dice[faces]) + Dice[mod]);
}

int PlayerClass::Roll(RollType roll) const {
    return (Dice::Roll(NAME, roll, DICE[roll][num], DICE[roll][faces]));
}

void PlayerClass::WriteMap() {

	MapType::iterator iter;

	for (iter = skillsMap.begin(); iter != skillsMap.end(); iter++) {
		cout << iter->first << " " << iter->second << endl;
	}

    return;
}

ostream& operator << (ostream& out, const PlayerClass* p) {
        
    p->Write(out);

    return out;
}


