//Joseph Brown
//Fall 2018 (191)
//Handle class

#ifndef _PLAYER
# define _PLAYER

#include "human.h"
#include "elf.h"
#include "orc.h"
#include "halfelf.h"
#include "troll.h"
#include "ogre.h"

using namespace std;

class Player {
  public:

    // CONSTRUCTORS
    Player();

  Player(const Player & c);

  Player(PlayerClass * ptr);

  // DESTRUCTOR	
  ~Player();

  // ASSIGNMENT OP		
  Player & operator = (const Player & p);

  // PUBLIC METHODS

  string Name() const;
  // Returns the name of the character
  // pre: none  
  // post: returns name 

  string VocStr() const;
  // returns the vocation
  // pre:  none.
  // post: returns the vocation as a string

  string RaceStr() const;
  // returns the race
  // pre:  none.
  // post: returns the race as a string

  int HP() const;
  // Returns the HP (hit points)
  // pre:  none
  // post: returns the HP 

  int MaxHP() const;

  long XP() const;
  // returns the xp (experience points)
  // pre:  none.
  // post: returns the xp

  int Level() const;
  // returns the level
  // pre:  none.
  // post: returns the level

  int Row() const;
  // returns the row
  // pre: none
  // post: returns the row

  int Col() const;
  // returns the column
  // pre: none
  // post: returns the column

  int Ability(PlayerClass::AbilityType ability) const;
  // Returns the ability requested
  // pre:  none.
  // post: returns the ability value

  //    	int AbilityMod(PlayerClass::AbilityType ability ) const;
  // Returns the abilityMod requested
  // pre:  none.
  // post: returns the abilityMod value

  vector < int > Abilities() const;
  // Returns the abilities
  // pre:  none.
  // post: returns the abilities

  string WeaponName() const;
  // Returns the current wpn name, empty string if non exists
  // pre:  none.
  // post: returns the current weapon being used

  string WeaponNameAndNum() const;
  // Returns the current wpn name and number, empty string if non exists
  // pre:  none.
  // post: returns the current weapon being used

  bool HasWeapon() const;
  // returns true if player has a weapon
  // pre: none
  // post: returns true if player has a weapon

  vector < string > Pack() const;
  // returns the list of equipment in the pack
  // pre:  array of strings must be large enough
  // post: returns the list of equipment in pack

  vector < string > InitialWeaponList() const;
  // returns the list of initial equipment
  // pre:  array of strings must be large enough
  // post: returns the list of equipment 

  vector < string > Skills() const;
  //Returns the vector of skills
  //Pre :
  //Post: Skill vector is returned

  bool IsDead() const;
  //Returns true if player is dead, false otherwise.
  //Pre :
  //Post: True is returned if hp <= DEAD, false otherwise

  bool IsDying() const;
  //Returns true if player is dying, false otherwise.
  //Pre :
  //Post: True is returned if DEAD<hp<DISABLED, false otherwis

  bool IsDisabled() const;
  //Returns true if player is disabled, false otherwise.
  //Pre :
  //Post: True is returned if hp <= DISABLED, false otherwise

  bool IsActive() const;
  // Returns true if player is active (not disabled)
  // Pre :
  //Post: True if hp >DISABLED

  bool IsHumanoid() const;
  // returns true if player is Humanoid

  bool IsMonster() const;
  // returns true if player is Monster

  int UpdateHP(int val);
  // Updates the HP given val

  long UpdateXP(long val);
  // Updates the xp (experience points) with the val
  //  (XP will always be >=0)
  // pre: val has a value
  // post: xp is updated xp = xp + val

  bool SetCell(int newRow, int newCol);
  //Set the current coordinates regardless of other fields.
  //coordinates are set (returns true) under following conditi
  //  newRow and newCol not negative
  //  newRow and newCol are both -1  (ex: -1,-1)
  //all other cases the function returns false.
  //Pre: It is up to the user to send valid moves based on the
  //Post: The players coordinates are modified and true is r
  //          otherwise false is returned

  Weapon * LoseWeapon();
  // The player loses the current wpn
  // pre: none
  // post: players current wpn is returned and the current wpn
  //           player is carrying is none.

  Weapon * FindWeapon(Weapon * weapon);
  //Changes the current weapon and returns current weapon

  Weapon * ChangeWeapon(string wName);
  // Player should change the current weapon with wName
  // pre: none
  // post: if player is active and player has the wName
  //  in inventory then current weapon is put in pack
  //  and current weapon is wName.

  bool AddSkill(string skill);
  // Player aquires a new skill
  // pre: none
  // post: If player is active then new skill is added to the
  //  skill list and true is returned

  int SkillCheck(string skill) const;
  // Returns the skill check value for the skill
  // pre: none
  // post: if player not dead then skill check value returned

  void Amnesia();
  // Player hit head and lost all knowledge of skills
  // pre: none
  // post: player has no skill list

  int RollInitiative() const;
  //Calculates the initiative check for a player

  int RollAttack() const;
  //Determines the AttackRoll value

  int RollSavingThrow(SavingThrowType kind) const;
  //Determines the savingthrow value

  int RollDefense() const;
  //Determines the Defensive value

  int RollDamage() const;
  //Determines the value for damages     

  void Write(ostream & stream) const;
  // Writes the player data to an output stream
  // pre:  stream must be open, headers already printed
  //       if necessary.
  // post: all member data in player object has been inserted
  //       into output stream.

  VocRules::VocType Voc() const;
  // returns the enum value for vocation

  // Relational Operators	  
  bool operator == (const Player & c) const;
  bool operator != (const Player & c) const;
  bool operator < (const Player & c) const;
  bool operator <= (const Player & c) const;
  bool operator > (const Player & c) const;
  bool operator >= (const Player & c) const;

  private:

    void CopyIntoMe(const Player & p);
  // Copies player into self
  // used for copy constructor and op=

  // DATA	
  PlayerClass * p;
};

#
endif
