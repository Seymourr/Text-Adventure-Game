#ifndef ITEM_H
#define ITEM_H
#include <string>
namespace lab3{
using namespace std;
class Item{
	protected:
	struct info{
		int storlek;
		int nutr;
		int dmg;
		string desc;
		string name;

	};
	public:
	Item(){};
	Item(string name, string desc, int storlek, int nutr, int dmg);
	info sak;
	int size()const;
	int regain()const;
	int dmgAmnt()const;
	string description()const;
	string getName()const;
	
	};
	}
#endif
