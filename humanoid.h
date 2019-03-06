// Joseph Brown
// Program 3
// Humanoid header

#ifndef HUMANOID_CLASS
#define HUMANOID_CLASS

#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "player3.h"
#include "pack.h"

using namespace std;

class Humanoid: public PlayerClass {

    public:
        
        virtual ~Humanoid();

        VocRules::VocType Voc() const;

        string VocStr() const;

        int Level() const;

        long XP() const;

        vector<string> Pack() const;

        virtual vector<string> InitialWeaponList() const = 0;

        virtual Weapon::Weapon* FindWeapon(Weapon* wpn);

        Weapon::Weapon* ChangeWeapon(string wName);

        virtual int RollAttack() const;

        virtual int RollSavingThrow(SavingThrowType kind) const;

        long UpdateXP(long modification);

        Humanoid& operator= (const Humanoid& h);
        
        virtual void Write(ostream& out) const;
        
        virtual Humanoid::Humanoid* Clone() const = 0;

    protected:

        static const bool rollAbil = true;

        Humanoid(string name, VocRules::VocType inVoc, const int abilAdj[]);

        Humanoid(const Humanoid& h);
        
        int RollHitDice() const;
        
        Humanoid& CopyHumanoid(const Humanoid& h);

    private:

        static const int START_LEVEL;
        static const int MAX_LEVEL;
        static const int START_XP;
        static const int NUM_INIT_SKILLS = 3;
        static const string INIT_SKILLS[VocRules::NUM_VOC][NUM_INIT_SKILLS];

        VocRules::VocType voc;
        int level;
        long xp;
        PackClass* pack;
        vector<string> skills;
        
        Humanoid();

        VocRules::VocType InitVoc(VocRules::VocType inVoc);

        void InitLevel();

        void InitXP();

        void InitSkills();

        void InitPack();
        
        void LevelUp();
        
        void HitDice(int hitDice[]) const;
        
        int WhatMod(SavingThrowType kindofThrow) const;
        
        int InitPackWt() const;
        
        void DiceArr();
        
        
        
};

#endif
