// Joseph Brown
// Program 3
// Troll implementation

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "troll.h"

using namespace std;
using namespace GameSpace;

const string Troll::RACE = "TROLL";
const int Troll::ABILITY_ADJ[6] = {14, 23, 6, 6, 23, 9};
const int Troll::HIT_DIE[3] = {6, 8, 36};
const int Troll::SAVE_THROW[3] = {11,4,3};
const int Troll::BASE_ATT_BONUS[2] = {1,9};
const string Troll::INIT_WPN = "CLUB";
const int Troll::NUM_INIT_SKILLS;
const string Troll::INIT_SKILLS[NUM_INIT_SKILLS] = {"LISTEN", "SPOT"};

Troll::Troll(string name): Monster(name, ABILITY_ADJ, HIT_DIE) {

  for (int i = 0; i < NUM_INIT_SKILLS; i++) {

    PlayerClass::AddSkill(INIT_SKILLS[i]);
  }

}

Troll::Troll * Troll::Clone() const {
  return new Troll( * this);
}

vector < string > Troll::InitialWeaponList() const {

  vector < string > weaponList;

  weaponList.push_back(INIT_WPN);

  return weaponList;
}

string Troll::RaceStr() const {
  return RACE;
}

int Troll::RollAttack() const {

  int rollAttk = 0;

  rollAttk = Monster::RollAttack(BASE_ATT_BONUS);

  return rollAttk;
}

int Troll::RollSavingThrow(SavingThrowType kindofThrow) const {

  int saveThrow = 0;

  saveThrow = Monster::RollSavingThrow(kindofThrow, SAVE_THROW);

  return saveThrow;
}

void Troll::Write(ostream & out) const {
  out << RACE << "#";
  Monster::Write(out);

  return;
}

