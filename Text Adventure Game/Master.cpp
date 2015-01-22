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
#include "Commands.h"
#include "NPC.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace lab3;

vector<Actor *> persons;
vector<Env *> areas;
vector<Item *> allItems;
vector<vector<Item *>> roomItems;
bool running = true;
Human * Player;

Commands *c;
typedef string(Commands::*somethingFancy)(string);
typedef bool(*readStuff)(string);
unordered_map<string, somethingFancy> ourMap;

unordered_map<string, readStuff> readMap;
vector<string> legitCommands = {"info", "take", "inventory", "drop", "eat", "equip", "fight", "unlock", "go", "commands", "talk", "stats", "meditate", "save", "load"};

string parse(string indata);
void fillMaps();
bool addItem(string s);
bool addKey(string s);
bool addVictoryItem(string s);
bool addArea(string s);
bool addExit(string s);
bool addPlayer(string s);
bool addPlayerItems(string s);
bool addPlayerWeapon(string s);
bool addNPC(string s);
bool loadgame(string f);
int findIndex(Item * obj);
int findAreaIndex(Env * obj);
bool savegame(string f);
void cleanUp();
bool checkConsistency(string n);




string victoryitem = "C++BookOfTruth";
Item * vicItem;
string maingame = "MainGame";
string currentgame = "";

int main() {

	fillMaps();
	if(!loadgame(maingame)) {
		cout << "Something went wrong with loading the game!" << endl;
		exit(1);
	}
	
	//PARSER INIT
	
	cout << "The nigth is dark, you blood is pumping. The last programmer of C++ lives in the castle before you. \nWith determined steps, enter the beasts nest and claim your right to learn C++!" << endl;

	while(running) {
		char nextCommand[256];
		cout<<"type 'commands' for help"<<endl;
		cin.getline(nextCommand, 256);
		cout << "----------------------------------------" << endl;
		cout << parse(nextCommand) << endl;
		
		if(Player->hasWon(victoryitem)) {
			cout << "CONGRATULATIONS, you beat the game!" << endl;
			break;
		}
		
		for(int i = 0; i < persons.size(); ++i) {
			if(persons[i] != Player) {
				string timeForAction  = persons[i]->action();
				if(timeForAction == "ACTION_FIGHT") {
					cout << c->fight(persons[i], Player->getName()) << endl;
				} else if(timeForAction == "ACTION_FOLLOW") {
						cout << c->follow(persons[i]) << endl;
					} else if(timeForAction != "NO_ACTION") {
							cout << persons[i]->getName() + " : " + timeForAction << endl;
						}  else {

							// do nothing
							}
			} 
		}
		cout << "----------------------------------------" << endl;
		//Eventuell bugg: Måste rerouta Player pekare vid defeat?)
		bool alive = false;;
		for(int i = 0; i < persons.size(); ++i) {
			if(Player == persons[i]) {
				alive = true;
				break;
			}
		}
		if(!alive) {
			cout << "After fighting for your life, you transcend into luminous light.. Passing away slowly.. \nDeep down in the final remnants of your soul you hear a faint whisper: 'Play me again...'" << endl;
			running = false;
		}

	}

	cleanUp();
	

	cout << "Thank you for playin!" << endl;
}


void cleanUp() {
	delete c;
	c = nullptr;
	int i = 0;
	for(auto it = persons.begin(); it != persons.end(); ++it) {
		++i;
		delete *it;
	}
	
	persons.clear();
	Player = nullptr;
	
	for(int i = 0; i < allItems.size(); ++i) {
		delete allItems[i];
	}
	allItems.clear();

	for(int i = 0; i < areas.size(); ++i) {
		delete areas[i];
	}
	areas.clear();
	


}

void fillMaps() {
	ourMap["info"] = &Commands::getAreaDescription;
	ourMap["take"] = &Commands::take;
	ourMap["inventory"] = &Commands::showInventory;
	ourMap["drop"] = &Commands::drop;
	ourMap["eat"] = &Commands::eat;
	ourMap["equip"] = &Commands::equip;
	ourMap["fight"] = &Commands::fight;
	ourMap["unlock"] = &Commands::unlock;
	ourMap["go"] = &Commands::go;
	ourMap["commands"] = &Commands::getCommands;
	ourMap["talk"] = &Commands::talkTo;
	ourMap["stats"] = &Commands::checkStats;
	ourMap["meditate"] = &Commands::meditate;

	readMap["OBJ"] = &addItem;
	readMap["KEY"] = &addKey;
	readMap["VIC"] = &addVictoryItem;
	readMap["OUT"] = &addArea;
	readMap["EXI"] = &addExit;
	readMap["PLA"] = &addPlayer;
	readMap["PLI"] = &addPlayerItems;
	readMap["PLW"] = &addPlayerWeapon;
	readMap["NPC"] = &addNPC;

}


bool addItem(string line) {
	string delimiter = ":";
	string name = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	string desc = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	int weight = stoi(line.substr(0, line.find(delimiter)));
	line.erase(0, line.find(delimiter) + delimiter.length());

	int reg = stoi(line.substr(0, line.find(delimiter)));
	line.erase(0, line.find(delimiter) + delimiter.length());

	int dmg = stoi(line.substr(0, line.find(delimiter)));
	line.erase(0, line.find(delimiter) + delimiter.length());

	allItems.push_back(new Item(name, desc, weight, reg, dmg));
	return true;
}

bool addKey(string dummy) {
	allItems.push_back(new Keys());
	return true;
}

bool addVictoryItem(string line) {

	string delimiter = ":";
	string name = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	victoryitem = name;

	string desc = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	int weight = stoi(line.substr(0, line.find(delimiter)));
	line.erase(0, line.find(delimiter) + delimiter.length());

	int reg = stoi(line.substr(0, line.find(delimiter)));
	line.erase(0, line.find(delimiter) + delimiter.length());

	int dmg = stoi(line.substr(0, line.find(delimiter)));
	line.erase(0, line.find(delimiter) + delimiter.length());

	vicItem = new Item(name, desc, weight, reg, dmg);
	allItems.push_back(vicItem);
	
	return true;
}

bool addArea(string line) {
	string delimiter = ":";

	string name = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	string desc = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	vector<Item *> items;
	if(line != "NULL:") {

	while(line.length() > 0) {
		string it = line.substr(0, line.find(delimiter));
		if(it == "VICTORYITEM") {
			items.push_back(vicItem);
		} else {
		it.erase(0,3);
		int numberOfItem = stoi(it);
		items.push_back(allItems[numberOfItem - 1]);
		
		}
		line.erase(0, line.find(delimiter) + delimiter.length());
	}
	}

	areas.push_back(new Outside(name, desc, items));
	return true;
}

bool addExit(string line) {
	string delimiter = ":";

	string direction = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	bool locked = false;
	string boolean= line.substr(0, line.find(delimiter));
	if(boolean == "true") {
		locked = true;
	}
	line.erase(0, line.find(delimiter) + delimiter.length());
	string from = line.substr(0, line.find(delimiter));
	from.erase(0,3);
	int numberOfFrom = stoi(from);
	line.erase(0, line.find(delimiter) + delimiter.length());
	string to = line.substr(0, line.find(delimiter));
	to.erase(0,3);
	int numberOfTo = stoi(to);
	line.erase(0, line.find(delimiter) + delimiter.length());
	areas[numberOfFrom - 1]->add_neighbour(direction,locked, areas[numberOfTo - 1]);
	return true;
}

bool addPlayer(string line) {
	string delimiter = ":";

	string name = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	string desc = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	string startArea = line.substr(0, line.find(delimiter));
	startArea.erase(0,3);
	int numberOfArea = stoi(startArea);
	line.erase(0, line.find(delimiter) + delimiter.length());

	string hitResponse = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	vector<string> resp;
	while(line.length() > 0) {
		string name = line.substr(0, line.find(delimiter));
		resp.push_back(name);
		line.erase(0, line.find(delimiter) + delimiter.length());
	}
	Player = new Human(name, desc, resp, areas[numberOfArea - 1], hitResponse);
	persons.push_back(Player);
	return true;
}

bool addPlayerItems(string line) {
	string delimiter = ":";

	if(line == "NULL:") {
		return true;
	}

	vector<Item *> items;

	while(line.length() > 0) {
		string item = line.substr(0, line.find(delimiter));
		item.erase(0,3);
		int numberOfItem = stoi(item);
		items.push_back(allItems[numberOfItem - 1]);
		line.erase(0, line.find(delimiter) + delimiter.length());
	}

	for(int i = 0; i < items.size(); ++i) {
		Player->inventory.add_item(items[i]);
	}

	return true;
}

bool addPlayerWeapon(string line) {
	string delimiter = ":";
	
	if(line == "NULL:") {
		return true;
	}
	
	string item = line.substr(0, line.find(delimiter));
	item.erase(0,3);
	int numberOfItem = stoi(item);
	line.erase(0, line.find(delimiter) + delimiter.length());

	Player->equip(allItems[numberOfItem - 1]);

	return true;
}

bool addNPC(string line) {
	string delimiter = ":";

	string name = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	string desc = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	string startArea = line.substr(0, line.find(delimiter));
	startArea.erase(0,3);
	int numberOfArea = stoi(startArea);
	line.erase(0, line.find(delimiter) + delimiter.length());

	string hitResponse = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	string meetPhrase = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	string follow = line.substr(0, line.find(delimiter));
	line.erase(0, line.find(delimiter) + delimiter.length());

	Actor * toFollow;
	if(follow == "PLAYER") {
		toFollow = Player;
	} else {
		follow.erase(0,3);
		toFollow = persons[stoi(follow) - 1];
	}

	string health = line.substr(0, line.find(delimiter));
	int hp = stoi(health);
	line.erase(0, line.find(delimiter) + delimiter.length());

	string damage = line.substr(0, line.find(delimiter));
	int dmg = stoi(damage);
	line.erase(0, line.find(delimiter) + delimiter.length());

	bool friendly = false;
	string seeIfFriendly = line.substr(0, line.find(delimiter));
	if(seeIfFriendly == "true") {
		friendly = true;
	}
	line.erase(0, line.find(delimiter) + delimiter.length());

	string item = line.substr(0, line.find(delimiter));
	Item * npcItem;
	if(item == "NULL") {
		npcItem = nullptr;
	} else if(item == "VICTORYITEM") {
		npcItem = vicItem;
	} else {
		item.erase(0,3);
		int numberOfItem = stoi(item);
		npcItem = allItems[numberOfItem - 1];
	}
	line.erase(0, line.find(delimiter) + delimiter.length());

	vector<string> responses;

	while(line.length() > 0) {
		string phrase = line.substr(0, line.find(delimiter));
		responses.push_back(phrase);
		line.erase(0, line.find(delimiter) + delimiter.length());
	}
	NPC * npc = new NPC(name, desc, responses, areas[numberOfArea - 1], hitResponse, meetPhrase, toFollow, hp, dmg, friendly, npcItem);
	persons.push_back(npc);

	return true;
}


bool checkConsistency(string seeked) {
	ifstream file(currentgame);
	string line = "";
	bool found = false;
	while(getline(file, line)) {
		string first = line.substr(0, line.find("::"));
		if(first == seeked) {
			found = true;
			break;
		}
	}
	file.close();
	return found;
}
bool loadgame(string file) {
	bool loaded = true;
	string line = "";
	string fileComplete = file + ".txt";
	ifstream myfile (fileComplete);
	currentgame = fileComplete;
	string delimiter = "::";
	if(myfile.fail()){
       loaded = false;
       return loaded;
    } 
    
	if(myfile && myfile.is_open()) {
		cleanUp();
		while(getline(myfile, line)) {
		string first = line.substr(0, line.find(delimiter));
		first = first.substr(0,3);
		line.erase(0, line.find(delimiter) + delimiter.length());
		bool response = readMap[first](line);
		if(!response) {
			loaded = false;
			myfile.close();
			return loaded;
		}
		}
		c = new Commands(&persons, Player);
		myfile.close();
	} else {
		loaded = false;
	}
	
	return loaded;
}


int findIndex(Item * obj) {
	int index = -1;
	for(int i = 0; i < allItems.size(); ++i) {
		if(allItems[i] == obj) {
			index = i;
			break;
		}
	}
	return index;
}


int findAreaIndex(Env * obj) {
	int index = -1;
	for(int i = 0; i < areas.size(); ++i) {
		if(areas[i] == obj) {
			index = i;
			break;
		}
	}
	return index;
}
bool savegame(string file) {
	bool saved = true;
	string fileComplete = file + ".txt";
	ofstream myfile;
	myfile.open(fileComplete);
	if(myfile && myfile.is_open() ) {

		//Fillitems
		for(int i = 0; i < allItems.size(); ++i) {
			if(allItems[i]->getName() == "Key" && allItems[i]->description() == "A fine Key") {
				myfile << "KEY" << (i+1) << "::" << "KEY" << ":" << endl;
			} else if(allItems[i] == vicItem) {
				myfile << "VICTORYITEM" << "::" << allItems[i]->getName() << ":" << allItems[i]->description() << ":" << allItems[i]->size() << ":" << allItems[i]->regain() << ":" << allItems[i]->dmgAmnt() << ":" << endl;
			} else { //VICTORYITEM SHOULD BE LAST!!
			myfile << "OBJ" << (i+1) << "::" << allItems[i]->getName() << ":" << allItems[i]->description() << ":" << allItems[i]->size() << ":" << allItems[i]->regain() << ":" << allItems[i]->dmgAmnt() << ":" << endl;
			}
		}

		//FillOutsides
		for(int i = 0; i < areas.size(); ++i) {
			myfile << "OUT" << (i+1) << "::" << areas[i]->getName() << ":" << areas[i]->getDescription() << ":";
			if(areas[i]->items.size() == 0) {
				myfile << "NULL:" << endl;
			} else {
				for(int j = 0; j < areas[i]->items.size(); ++j) {
					if(areas[i]->items[j]->getName() == "Key" && areas[i]->items[j]->description() == "A fine Key") {
						myfile << "KEY" << (findIndex(areas[i]->items[j]) + 1) <<":";
					} else if(areas[i]->items[j] == vicItem) {
						myfile << "VICTORYITEM:";
					} else {
						myfile << "OBJ" << (findIndex(areas[i]->items[j]) + 1) << ":";
					}
				}
				myfile << endl;
			}
		}

		//FillExits
		int exitCnt = 0;
		for(int i = 0; i < areas.size(); ++i) {
			for(int j = 0; j < areas[i]->neigh.size(); ++j) {
				exitCnt = exitCnt + 1;
				string canEnter = "false";
				if(areas[i]->neigh[j].canEnter) {
					canEnter = "true";
				}
				myfile << "EXIT" << exitCnt << "::" << areas[i]->neigh[j].direction << ":" << canEnter << ":" << "OUT" << (i+1) << ":" << "OUT" << (findAreaIndex(areas[i]->neigh[j].otherNeighbour) + 1) << ":" << endl;
			}
		}


		//Fillplayer
		myfile << "PLAYER::" << Player->getName() << ":" << Player->getDescription() << ":" << "OUT" << (findAreaIndex(Player->location) + 1) << ":" << Player->hitResponse << ":";
		for(int i = 0; i < Player->responses.size(); ++i) {
			myfile << Player->responses[i] << ":";
		}
		myfile << endl;

		//Fillplayeritem
		if(Player->inventory.size() == 0) {
			myfile << "PLITEM::NULL:" << endl;
		} else {
			myfile << "PLITEM::";
			for(int i = 0; i < Player->inventory.size(); ++i) {
				if(Player->inventory[i]->getName() == "Key" && Player->inventory[i]->description() == "A fine Key") {
					myfile << "KEY" << (findIndex(Player->inventory[i]) + 1)<< ":";
				} else {
				myfile << "OBJ" << (findIndex(Player->inventory[i]) + 1)<< ":";
				}
			}
			myfile << endl;
		}

		//Fillplayerweapon
		if(Player->weapon) {
			myfile << "PLWEAPON::"<<"OBJ" << (findIndex(Player->weapon) + 1) << ":" << endl;
		} else {
			myfile << "PLWEAPON::NULL:" << endl;
		}

		//fillNPC
		int NPCcnter = 0;
		for(int i = 0; i < persons.size(); ++i) {
			if(persons[i] != Player) {
				NPC* someNpc = dynamic_cast<NPC *>(persons[i]);
				NPCcnter = NPCcnter + 1;
				myfile << "NPC" << NPCcnter << "::" << persons[i]->getName() << ":" << persons[i]->getDescription() << ":" << "OUT" << (findAreaIndex(persons[i]->location) + 1) << ":" << persons[i]->hitResponse << ":" << someNpc->getDiscLine()<< ":PLAYER:" << persons[i]->egenStats.HP << ":" << persons[i]->egenStats.STR << ":";
				string isEnemy = "false";
				if(someNpc->seeIfEnemy()) {
					isEnemy = "true";
				}

				myfile << isEnemy << ":";
				if(persons[i]->inventory.size() > 0) {
					for(int k = 0; k < persons[i]->inventory.size(); ++k) {
						if(persons[i]->inventory[k]->getName() == "Key" && persons[i]->inventory[k]->description() == "A fine Key") {
							myfile << "KEY" << (findIndex(persons[i]->inventory[k]) + 1) << ":";
						} else if(persons[i]->inventory[k] == vicItem) {
							myfile << "VICTORYITEM:";
						} else {
							myfile << "OBJ" << (findIndex(persons[i]->inventory[k]) + 1) << ":";
						}
					}
				} else {
					myfile << "NULL:";
				}

				for(int k = 0; k < persons[i]->responses.size(); ++k) {
					myfile << persons[i]->responses[k] << ":";
				}
				myfile << endl;
			}
		}


	myfile.close();
	} else {
		saved = false;
	}

	return saved;
}


string parse(string indata) {

	int space = indata.find_first_of(" ");
	string first = indata.substr(0, space);
	string second = indata.substr(space+1);
	bool legitCommand = false;
	string toReturn;
	for(int i = 0; i < legitCommands.size(); ++i) {
		if(legitCommands[i] == first) {
			legitCommand = true;
			break;
		}
	}
	if(!legitCommand) {
		return "Thats not an action you can make!";
	}
	if(first == "info") {
		second = Player->location->getName();
	} 

	if(first == "save") {

		if(indata.length() == first.length() || second == "" || second == " ") {
				toReturn = "Too short title for save";
			} else {
			if(second == "MainGame" || second == "OtherGame") {
			toReturn = "Whoa dude..";
			} else {
			bool response = savegame(second);
			if(response) {
				toReturn = "Game saved in '" + second + "'";
			} else {
				toReturn = "Something went wrong with saving '" + second + "'";
			}
			}
		}
	} else if(first == "load") {
		
		bool response = loadgame(second);

		if(!response) {
			loadgame(maingame);
			toReturn = "The save file '" + second + "' do not exist!";
		} else {
			toReturn = (c->*ourMap["info"])(Player->location->getName());
		}
		
	} else {
	 toReturn = (c->*ourMap[first])(second);
	}
	return toReturn;

	
}
