


#include "Commands.h"

namespace lab3{


Commands::Commands(vector<Actor *> * act, Human * play) {
	persons = act;
	Player = play;
}
string Commands::getAreaDescription(string place) {
	bool exists;
	Env * area;
	for(int i = 0; i < persons->size(); ++i) {
		if(persons->at(i)->location->getName() == place) {
			exists = true;
			area = persons->at(i)->location;
		}
	}
	
	string inRoom = "";
	if(exists) {
		for(int i = 0; i < persons->size(); ++i) {
	
			if(persons->at(i)->location == area) {
				inRoom = persons->at(i)->getName() + " ";
			}
		}
		
	} else {
		return "You are not in that room.";
	}
	
	
	if(inRoom == "") {
			inRoom = "No one is in this room.";
		}
	return area->areaDescription(inRoom);
	
}

string Commands::take(string item) {
	bool exists;
	Item * it;
	for(int i = 0; i < Player->location->items.size(); ++i) {
		if(Player->location->items[i]->getName() == item) {
			exists = true;
			it = Player->location->items[i];
			break;
		}
	}
	
	if(!exists) {
		return "There is no such item to pick up";
	}
	
	bool addedItem = Player->pick_up(it);
	if(addedItem) {
		Player->location->pick_up(it);
	} else {
		return "Your inventory dont have enough space";
	}
	
	return "You picked up a " + item;
}

string Commands::showInventory(string dummy) {
	string prnt = "";
	
	for(int i = 0; i < Player->inventory.size(); ++i) {
		prnt += Player->inventory[i]->getName() + " : " + Player->inventory[i]->description() + ", size: " + to_string(Player->inventory[i]->sak.storlek) + "\n";
	}
	if(prnt == "") {
		return "Your inventory is empty";
	}
	prnt = "Your inventory which can contain " + to_string(Player->inventory.space()) + " units of items contains the following: \n" + prnt;
	return prnt;
	
}
string Commands::drop(Actor * someOne, string item) {
	bool exists;
	Item *it;
	for(int i = 0; i < someOne->inventory.size(); ++i) {
		if(someOne->inventory[i]->getName() == item) {
			exists = true;
			it= someOne->inventory[i];
			
			break;
		}
	}
	
	if(!exists) {
		return "You dont have the item";
	}

	if(someOne->weapon == it) {
		someOne->weapon = nullptr;
	}
	someOne->drop(it);
	someOne->location->add(it);
	
	return (someOne->getName()) + " dropped " + item;
}


string Commands::drop(string item) {
	return drop(Player, item);
}
	

string Commands::eat(string item){
	bool exists;
	Item *it;
	int indexOfItem = 0;
	for(int i = 0; i < Player->inventory.size(); ++i) {
		if(Player->inventory[i]->getName() == item) {
			exists = true;
			indexOfItem = i;
			it= Player->inventory[i];
			
			break;
		}
	}

	if(!exists){
		return "You dont have the item.";
	}

	int nutr = it->regain();
	if(nutr <= 0) {
		return "You cant eat that!";
	}


	if(Player->eat(it)){
		if(Player->weapon == it) {
		Player->weapon = nullptr;
		}
		Player->inventory.remove_from_backpack(it);
		return "You ate and gained " + std::to_string(nutr) + " HP!";
	} else {
		std::cout << "SOMETHING WENT HORRIBLY WRONG IN EAT" << std::endl;
		return "chaos";
	}


}

string Commands::equip(string item) {

	bool exists;
	Item *it;
	int indexOfItem = 0;
	for(int i = 0; i < Player->inventory.size(); ++i) {
		if(Player->inventory[i]->getName()== item) {
			exists = true;
			indexOfItem = i;
			it= Player->inventory[i];
			break;
		}
	}



	if(!exists){
		return "You cant equip something you dont have!";
	}


	Player->equip(it);
	return "You equipped " + it->getName() + " which have " + std::to_string(it->dmgAmnt()) + " damage.";

}

string Commands::fight(Actor * someOne, string opp) {
	

	//Find opponent
	Actor * opponent;
	bool exists = false;
	for(int i = 0; i < persons->size(); ++i) {
		if(persons->at(i)->getName() == opp) {
			opponent = persons->at(i);
			exists = true;
			break;
		}
	}


	if(exists && someOne->location == opponent->location) {
		//Somebody is about to get hit
		string hitResponse = opponent->hitResponse;
		int playerDmg = someOne->egenStats.STR;
		if(someOne->weapon) {
			playerDmg += someOne->weapon->dmgAmnt(); 
		}
		string response = someOne->getName() + " hit " + opponent->getName() + " for " + std::to_string(playerDmg)+ " damage!";
		response = response + "\n" + "" + opponent->getName() + ": " + opponent -> getHitResponse();
		opponent->hit(playerDmg);
		if(!opponent->isAlive()) {
			//Opponent died, delete him!
			int index = 0;
			for(int i = 0; i < persons->size(); ++i) {
				if(persons->at(i)->getName() == opponent->getName()) {
					index = i;
					break;
				}
			}
			response = response + "\n" + someOne->getName() + " killed " + opponent->getName() + "!";
			persons->erase(persons->begin() + index);
			//opponent->~Actor();
			if(opponent->inventory.size() > 0) {
				response += "\n " + opponent->getName() + " dropped: ";
			}
			for(int i = 0; i < opponent->inventory.size(); ++i) {
				response+= opponent->inventory[i]->getName() + " ";
			}
			delete opponent; // TODOOOOO Calls destruktor of opponent (no humans should die..?)
			
		}
		return response;
	} else {
		return "The person you are trying to hit does not exist";
	}

}

string Commands::fight(string opp) {
	return fight(Player, opp);
}

string Commands::unlock(string direction) {

	bool hasKey = false;
	int keyIndex = 0;
	Item *it;
	//Kolla om spelaren har en nyckel
	
	for(int i = 0; i < Player->inventory.size(); ++i) {
		if(Player->inventory[i]->getName() == "Key") { //Standardsträng för nyckel
			hasKey = true;
			keyIndex = i;
			it= Player->inventory[i];
			break;
		}
	}

	if(!hasKey) {
		return "You dont have a key, go find one!";
	}


	//Kolla om det går att unlocka stället
	bool exists = false;
	int placeIndex = 0;
	for(int i = 0; i < Player->location->neigh.size(); ++i) {
		if(direction == Player->location->neigh[i].direction) {
			placeIndex = i;
			exists = true;
		}
	}

	if(!exists) {
		return "There is nothing there!";
	}
	
	Keys k;
	bool unlocked = k.unlock(Player->location, Player->location->neigh[placeIndex].otherNeighbour);
	if(unlocked) {
		Player->inventory.remove_from_backpack(it);
		return "You unlocked the door to the " + direction + ". Your key vanished";
	} 

	//unlocked is false, it is already open
	return "The door is already open!";
}

string Commands::go(string direction) {
	string response = "You walked " + direction + " and went away from " + Player->location->getName() + ".";

	if(Player->leave(direction)) {
		string personsInRoom = ""; 
		for(int i = 0; i < persons->size(); ++i) {
			if(persons->at(i)->location == Player->location) {
				if(persons->at(i) != Player) {
					personsInRoom += "" + persons->at(i)->getName() + " ";
				}
			}
		}
		response = response + "\n" + Player->location->areaDescription(personsInRoom);
		return response;
	}
	//Om koden kommer hit gick det inte att gå till det önskade rummet
	bool isLocked = false;
	vector<string> directions = Player->location->directions();

	for(int i = 0; i < directions.size(); ++i) {
		if(directions[i] == direction) {
			isLocked = true;
			break;
		}
	}
	string errResponse = "You cant go to the desired direction.";
	if(isLocked) {
		errResponse += " The door is locked!";
	}
	return errResponse;


}

string Commands::getCommands(string dummy) {
	string cmnds = "The available commands are in the following format: '<command><space><eventual thing>'. Choose from: \n";
	cmnds += "'info' - info about current area. \n";
	cmnds += "'save <filename>' - save your current progress with a special filename \n"; //Låt anv veta om fil finns
	cmnds += "'load <filename>' - load saved file, if any, and enter the state of that save \n"; //-==-
	cmnds += "'take <object>' - take item from area \n";
	cmnds += "'inventory' - show your inventory \n";
	cmnds += "'drop <object>' - drop selected object to the ground \n";
	cmnds += "'eat <object>' - attempt to eat selected object\n";
	cmnds += "'equip <object>' - equip selected object as a weapon\n";
	cmnds += "'fight <opponent>' - fight selected opponent\n";
	cmnds += "'unlock <direction>' - unlock the area in the given direction \n";
	cmnds += "'go <direction>' - go towards given direction \n";
	cmnds += "'talk <opponent>' - try to talk with target \n";
	cmnds += "'stats' - get a description of your base stats etcetera";

	return cmnds;
}

string Commands::follow(Actor * enemy) {
	enemy->location = Player->location;
	string response = enemy->getName() + " followed you into " + enemy->location->getName() + "!";
	return response;
}

string Commands::talkTo(string target) {
	Actor * opponent;
	bool exists = false;
	for(int i = 0; i < persons->size(); ++i) {
		if(persons->at(i)->getName() == target) {
			opponent = persons->at(i);
			exists = true;
			break;
		}
	}
	string response;
	if(exists) {
		response = opponent->getName() + " : " + opponent->response();
	} else {
		response = "Thats not someone you can talk to!";
	}

	return response;
}

string Commands::checkStats(string dummy) {
	return Player->ownStats();
}



string Commands::meditate(string dummy) {
	return Player->meditate();
}


}
