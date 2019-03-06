/* Joseph Brown
 * CSCI 330 section1
 * Fall 2018
 * lab 5
 **/

#include <vector>
#include <string>
#include <iostream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn.h"
#include "pack.h"

using namespace std;
using namespace GameSpace;


PackClass::PackClass():MAX_WT(0) {
}

PackClass::PackClass(int wt):MAX_WT(wt) {
   
    if (MAX_WT < 0) {
        throw INVALID_MISC;
    }
}

PackClass::PackClass(const PackClass& p):MAX_WT(p.MAX_WT) {
    CopyPack(p);
}

PackClass::~PackClass() {
    EmptyPack();
}

PackClass& PackClass::operator=(const PackClass& p) {

    if (this != &p) {
        CopyPack(p);
    }
    
    return *this;
}


bool PackClass::AddWeapon(Weapon::Weapon* w) {

    bool rv = false;
    
   if (w != NULL) {
       
    if (w->Wt() + Wt() <= MAX_WT) {
        pack.push_back(w);
        rv = true;
        
    }
    
   }
   
    return rv;
}

Weapon* PackClass::RemoveWeapon(string wName) {

    Weapon::Weapon* wpn = NULL;
    vector<Weapon*>:: iterator iter = FindWeapon(wName);
	
	if (iter != pack.end()) {
        wpn = *iter;
        pack.erase(iter);
    }
    
    return wpn;
}

void PackClass::EmptyPack() {
    
    vector<Weapon::Weapon*>::iterator iter;
    
    for (iter = pack.begin(); iter != pack.end(); iter++) {
        delete (*iter);
        *iter = NULL;
    }
    pack.clear();
    return;
}


bool PackClass::InPack(string wName) const {
    
    bool found = false;
	
	for (int i = 0; i < pack.size(); i++) {
		
		if (wName == pack[i]->Name()) {
			found = true;
		}
	}
	
	return found;
}

int PackClass::Size() const {
    return pack.size();
}

int PackClass::Wt() const {

    int temp = 0;
    
    for (int i = 0; i < pack.size(); i++) {
        temp += pack[i]->Wt();
    }
    
    return temp;
    
}

int PackClass::MaxWt() const {
    return MAX_WT;
}

bool PackClass::IsEmpty() const {
    return (Size() <= 0);
}

bool PackClass::IsFull() const {
    return (Wt() == MAX_WT);
}


void PackClass::Write(ostream& out) const {

	for (int i = 0; i < pack.size(); i++) {

		out << pack[i]->Name() << endl;
	}

	return;
}


void PackClass::CopyPack(const PackClass& p) {
    
    EmptyPack();

    *const_cast<int*>(&MAX_WT) = p.MAX_WT;
    
    for (int i = 0; i < p.pack.size(); i++) {
        if (p.pack[i] != NULL) {
            pack.push_back(new Weapon(*p.pack[i]));
        }
    }

    return;
}

vector<Weapon::Weapon*>::iterator PackClass::FindWeapon(string wName) {

    bool found = false;
	vector<Weapon::Weapon*>::iterator iter;
    vector<Weapon::Weapon*>::iterator rv;
	
    for (iter = pack.begin(); iter != pack.end() && !found; iter++) {
        
        if (Ucase(wName) == Ucase((*iter)->Name())) {
            found = true;
            rv = iter;
        }
        
    }
	
	return rv;
}

vector<string> PackClass::Pack() const {
    
    vector<string> rv;
    
    for (int i = 0; i < pack.size(); i++) {
        rv.push_back(pack[i]->NameAndNum());
    }
    
    Sort(rv);
    
    return rv;
}
