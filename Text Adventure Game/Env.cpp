#include "Env.h"

namespace lab3{

string Env::getDescription() const {
		return description;
	}
vector<string> Env::directions() {
	vector<string> dir;
	for(int i = 0; i < neigh.size(); ++i) {
		dir.push_back(neigh[i].direction);
	}
	return dir;
}



void Env::pick_up(Item* item) {
	for(int i = 0; i < items.size();++i) {
		if(items[i]->description() == item->description()) {
			items.erase(items.begin()+i);
			break;
		}
	}
}

void Env::add(Item * item) {
	items.push_back(item);
}

bool Env::add_neighbour(string direct, bool valid, Env* neig){
	neighbour granne;
	granne.direction = direct;
	granne.canEnter = valid;
	granne.otherNeighbour = neig;
	
	neigh.push_back(granne);
	
	}
	
string Env::getName() const{
	return name;
}

}

