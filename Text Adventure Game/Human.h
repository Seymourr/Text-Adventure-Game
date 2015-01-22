#ifndef HUMAN_H
#define HUMAN_H

#include "Actor.h"
#include "Item.h"
#include <string>


namespace lab3{
	using namespace std;
	class Human:public Actor{
		protected:

		public:
		
		Human(string n, string desc, vector<string> res, Env * start, string hitResponse = "Waagh!");
		~Human();
	//	bool give(Item* sak,Human& actr);
		string ownStats() const;
		string meditate();
		bool hasWon(string victoryitem) const;
	//	string action();
	//	virtual string talk_to(Actor & otherGuy);
	};



}

#endif	
