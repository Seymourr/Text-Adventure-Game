#ifndef ACTOR_H
#define ACTOR_H
#include <string>
#include <vector>
#include "Item.h"
#include "Container.h"
#include "Env.h"
namespace lab3 {
using namespace std;
	class Actor {
	protected: 
		struct stats {
			int HP = 100;
			unsigned int STR = 5;
			unsigned int LUCK = 10;
		};
	
		string description;
		string name;
		string type;
		

	public:
		virtual ~Actor();
		container<Item*>  inventory;
		Env * location;
		Item* weapon = nullptr;
		stats egenStats;
		
		string hitResponse; 
		vector<string> responses;
		int responseIndex;
		
		string characterType() const; 

		string characterName() const;

		bool pick_up(Item * obj);

		bool drop(Item * obj);
		
		void hit(int dmg);
		
		bool leave(string direction);
		void enter(Env * place);
		
		bool isAlive() const;
		bool equip(Item * obj);
		bool check_inventory(Item* sak) const;
		string response();
		string getDescription() const;
		string getName() const;
		string getHitResponse() const;
		bool eat(Item * sak);
		//virtual string talk_to(Actor & otherGuy) = 0;
	 	virtual string action(); 
		

	};



}
#endif 
