#ifndef NPC_H
#define NPC_H

#include "Actor.h"
#include "Item.h"
#include <string>


namespace lab3{
	using namespace std;
	class NPC:public Actor{
		protected:
			bool isEnemy = true;
			bool hasSeenPlayer = false;
			string discoveryLine;
			Actor * player;
		public:

		
		NPC(string n, string desc, vector<string> res, Env * start, string hitResponse, string dL, Actor * player, int HP, int STR, bool enemy, Item * it = nullptr);
		~NPC();
		string action();
		bool seeIfEnemy();
		string getDiscLine();
	};



}

#endif	
