/* Joseph Brown
 * CSCI 330 section1
 * Fall 2018
 * lab 5
 **/

#ifndef PACK_CLASS
#define PACK_CLASS

#include <vector>
#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"

using namespace std;

class PackClass {

    public:

        PackClass(int wt);
        PackClass(const PackClass& p);
        ~PackClass();
        PackClass& operator=(const PackClass& p);

        bool AddWeapon(Weapon* w);
        Weapon* RemoveWeapon(string wName);
        void EmptyPack();

        bool InPack(string wName) const;
        int Size() const;
        int Wt() const;
        int MaxWt() const;
        bool IsEmpty() const;
        bool IsFull() const;
        vector<string> Pack() const;

        void Write(ostream& out) const;

    private:

        const int MAX_WT;
        vector<Weapon::Weapon*> pack;
        

        PackClass();
        void CopyPack(const PackClass& p);
        vector<Weapon::Weapon*>::iterator FindWeapon(string wName);

};

#endif
