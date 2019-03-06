// Joseph Brown
// Program 3
// PlayerClass header

#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"

using namespace std;

class PlayerClass {
    
    public:
        
        static const int NUM_ABILITY = 6;
        // Total number of abilities

        enum AbilityType {DEX, CON, INT, CHA, STR, WIS};
        /*Player's abilities: DEX - Dexterity
         *                    CON - Constitution
         *                    INT - Intelligence
         *                    CHA - Charisma
         *                    STR - Strength
         *                    WIS - Wisdom */
        
        virtual ~PlayerClass();
        
        string Name() const;
        
        virtual string RaceStr() const = 0;
        
        int Row() const;
        
        int Col() const;
        
        int HP() const;
        
        int MaxHP() const;
        
        int Ability(AbilityType ability) const;
        
        vector<int> Abilities() const;
        
        bool IsActive() const;
        
        bool IsDead() const;
        
        bool IsDying() const;
        
        bool IsDisabled() const;
        
        
        int UpdateHP(int modification);
        
        bool SetCell(int newRow, int newCol);
        
        
        vector<string> Skills() const;
        
        int SkillCheck(string skill);
        
        bool AddSkill(string inSkill);
        
        void Amnesia();
        
        
        string WeaponNameAndNum() const;
        
        string WeaponName() const;
        
        bool HasWeapon() const;
        
        virtual vector<string> InitialWeaponList() const = 0;
        
        Weapon::Weapon* LoseWeapon();
        
        virtual Weapon::Weapon* FindWeapon(Weapon* wpn);
        
        
        int RollInitiative() const;
        
        virtual int RollAttack() const = 0;
        
        virtual int RollSavingThrow(SavingThrowType kindofThrow) const = 0;
        
        int RollDefense() const;
        
        int RollDamage() const;
        
        bool FindSkill(string skillToFind);
        
        bool ValidSkill(string skill);
        
        
        
        bool operator==(const PlayerClass& p) const;
        
        bool operator!=(const PlayerClass& p) const;
        
        bool operator<(const PlayerClass& p) const;
        
        bool operator<=(const PlayerClass& p) const;
        
        bool operator>(const PlayerClass& p) const;
        
        bool operator>=(const PlayerClass& p) const;
        
        virtual void Write(ostream& out) const;
        
        virtual PlayerClass::PlayerClass* Clone() const = 0;
        
    protected:
        
        static const int NUM_DICE_DATA = 3;
        
        enum DiceType {num, faces, mod};

        PlayerClass(string InName, const int abilAdj[], bool rollAbil);

        PlayerClass(const PlayerClass& p);
        
        void InitHP(const int hitDice[]);

        int Roll(const int Dice[], RollType roll) const;
        
        int Roll(RollType roll) const;

        int AbilityMod(AbilityType ability) const;
    
        PlayerClass& operator=(const PlayerClass& p);
        
        int UpdateMaxHP(int modification);
        
        PlayerClass& CopyPlayer(const PlayerClass& p); 
        
        
    private:
        
        static const int DEAD;
        // Number to determine if a player a player dead. Set to HP.
        
        static const int DISABLED;
        // Number to determine if a player is disabled. Set to HP.
        
        static const int DYING;
        // Number to determine if a player is dying.

        static const int START_ROW;

        static const int START_COL;
        
        static const int MAX_NAME_SIZE;
        
        static const int NUM_ROLLTYPE = 13;
        
        static const int DICE[NUM_ROLLTYPE][NUM_DICE_DATA];

        typedef map<string,AbilityType> MapType;
        
        static MapType skillsMap;
        vector<string> skills;
        
        int row;
        int col;
        int currentHP;
        int maxHP;
        int abilityScores [NUM_ABILITY];
        
        Weapon::Weapon* activeWpnPtr;
        const string NAME;
        
        PlayerClass();
        
        string InitName(string n);
        // Initializes and strips player name
        // Pre: name
        // Post: Initialized player name

        void InitAbilities(const int abilAdj[], bool rollAbil);
        
        void InitVar();
        
        MapType LoadSkillsMap();
        
        AbilityType StrToAbility(string s);
        
        void WriteMap();
        
};

ostream& operator << (ostream& out, const PlayerClass* p);

#endif
