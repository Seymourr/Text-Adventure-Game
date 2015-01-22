#include"Human.h"
#include <stdlib.h>
#include <time.h>

namespace lab3{
	
	Human::Human(string n, string desc, vector<string> res, Env * start, string hR) {
		name = n;
		description = desc;
		responses = res;
		location = start;
		hitResponse = hR;
	}

	Human::~Human() {};
	/*
		if(weapon) {
			location->add(weapon);
			drop(weapon);
		}

		for(int i = 0; i < inventory.size(); ++i) {
			location->add(inventory[i]);
			drop(inventory[i]);
		}
		

	}
*/
	string Human::ownStats() const{
	cout << "Entered ownstats" << endl;
		string stat = "You have the following stats: \n";
		stat += "HP: " + to_string(egenStats.HP) + " \n";
		stat += "STR " + to_string(egenStats.STR) + " \n";
		stat += "LUCK " + to_string(egenStats.LUCK);
	cout << "Got past stats" << endl;
		if(weapon) {
	cout << "Has weapon" << endl;
			stat+= "\n";
			stat += "You wield: " + weapon->getName() + " which has " + std::to_string(weapon->dmgAmnt()) + " dmg";
		} 
		stat += ".";
		return stat;
	}

	string Human::meditate() {
		string response = "You sit down in the lotus position, breathing calmly..thinking about nothing...\n";

		auto func = [] (unsigned int luck) -> int {
				int randomNumber;
				srand(time(NULL));
				randomNumber = rand() % (luck) + 1;
				return randomNumber;
			};

			int randomNumber = func(egenStats.LUCK);
				if(randomNumber >= 8) {
					response += "Suddenly, you hear Buddha and gain 5 strength!";
					egenStats.STR += 5;
				} else {
					response += "With a joyous smile you feel ready to continue your journey";
				}
				return response;
	}
/*

	bool Human::give(Item* sak, Actor * actr) {
		bool check = false;
		if(check_inventory(sak)) {

			check = actr.pick_up(sak);
			if(check) {
	 			drop(sak);
			}
		}
		return check;
	}
	*/
	
	//string Human::action() {}
	/*
	string Human::talk_to(Actor & otherGuy){
		string response = otherGuy.response();
		return response;
	}
	
	*/

	bool Human::hasWon(string victoryitem) const{
		for(int i = 0; i < inventory.size(); ++i) {
			if(inventory[i]->getName() == victoryitem) {
				return true;
			}
		}
		return false;
	}
}
