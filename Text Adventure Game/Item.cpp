#include "Item.h"
namespace lab3{
using namespace std;
Item::Item(string n, string desc, int s, int nu, int d){
	sak.desc = desc;
	sak.name = n;
	sak.storlek = s;
	sak.nutr = nu;
	sak.dmg = d;
}
string Item::description() const{
	return this->sak.desc;	
}

int Item::size() const{
	return this->sak.storlek;
}

int Item::regain() const{
	return this->sak.nutr;
}

int Item::dmgAmnt() const{
	return this->sak.dmg;
}

string Item::getName() const {
	return this->sak.name;
}

}
