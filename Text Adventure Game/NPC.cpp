#include "NPC.h"


namespace lab3{
	
	NPC::NPC(string n, string desc, vector<string> res, Env * start, string hR, string dL, Actor * pl, int HP, int STR, bool enemy, Item * it) {
		name = n;
		description = desc;
		responses = res;
		location = start;
		hitResponse = hR;
		discoveryLine = dL;
		player = pl;
		egenStats.HP = HP;
		egenStats.STR = STR;
		isEnemy = enemy;
		if(it) {
		inventory.add_item(it);
		}
	}

	NPC::~NPC() {
		
	};
		/*
		std::cout << "DESTRUKTOR" << std::endl;
		for(int i = 0; i < inventory.size(); ++i) {
			location->add(inventory[i]);
			drop(inventory[i]);
		}
		
	}

*/	
	string NPC::action() {
		//Time to check what the bug should do:
		string response = "NO_ACTION";

		//Is player in the same room?
		
		if(player->location == location) {

			//Have we met the player yet?
			if(!hasSeenPlayer) {
				hasSeenPlayer = true;
				response = discoveryLine;
				return response;
			} 
			//We have seen the player, but are we friendly?
			if(isEnemy) {
				response = "ACTION_FIGHT";
				return response;
			}
		}
		//We are not in the same room as the player, should we follow?
		if(hasSeenPlayer && player->location != location) {
			response = "ACTION_FOLLOW";
			return response;
		}

		return response;
	}

		bool NPC::seeIfEnemy() {
			return isEnemy;
		}
		string NPC::getDiscLine() {
			return discoveryLine;
		}
	
}
