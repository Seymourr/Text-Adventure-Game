#ifndef COMMANDS_H
#define COMMANDS_H
#include <vector>
#include <string>
#include "Actor.h"
#include "Container.h"
#include "Env.h"
#include "Human.h"
#include "Item.h"
#include "Keys.h"
#include "Outside.h"
#include <iostream>
#include <unordered_map>
#include <functional>




namespace lab3{
using namespace std;



	class Commands{
	protected:
	vector<Actor *> * persons;
	Human * Player;
	
	public:
	Commands(vector<Actor *> * , Human *);
	string getAreaDescription(string);

	string take(string);
	string showInventory(string);
	string drop(Actor *, string item);
	string drop(string);
	string eat(string);
	string equip(string);
	string fight(Actor *, string);
	string fight(string);
	string unlock(string);
	string go(string);
	string getCommands(string);
	string follow(Actor * enemy);
	string talkTo(string target);
	string checkStats(string dummy);
	string meditate(string dummy);
};



}
#endif
