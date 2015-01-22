#include "Actor.h"
namespace lab3{

Actor::~Actor() {
		if(weapon) {
			location->add(weapon);
			drop(weapon);
		}

		for(int i = 0; i < inventory.size(); ++i) {
			location->add(inventory[i]);
			drop(inventory[i]);
		}
		

	}
	
string Actor::characterType() const{
	return type;
}

string Actor::characterName() const{
	return name;
}


bool Actor::pick_up(Item* obj) {
	return inventory.add_item(obj);
}

bool Actor::drop(Item * obj) {
	return inventory.remove_from_backpack(obj);
}

void Actor::hit(int dmg) {
	egenStats.HP = egenStats.HP - dmg;
 }
 
 bool Actor::leave(string direction) {
	bool couldEnter = false;

	for(int i = 0; i < location->neigh.size(); ++i) {
		if(location->neigh[i].direction == direction) {
			if(location->neigh[i].canEnter) {
				couldEnter = true;
				enter(location->neigh[i].otherNeighbour);
			} 
			break;
		}
	}

	return couldEnter;
	}

void Actor::enter(Env * place) {
	location = place;
}

bool Actor::equip(Item * obj) {
	if(check_inventory(obj)) {
		weapon = obj;
		return true;
	}
	return false;
}	

bool Actor::isAlive() const{
	if(egenStats.HP > 0) {
		return true;
	}
	return false;
}
		
string Actor::response(){
	string response = responses[responseIndex];
	responseIndex = responseIndex + 1;
	if(responseIndex >= responses.size()) {
		responseIndex = 0;
	}
	return response;
}

string Actor::getDescription() const{
		return description;
	}
string Actor::getName() const{
	return name;
}

string Actor::getHitResponse() const {
	return hitResponse;
}

bool Actor::eat(Item* sak){
	bool valid = check_inventory(sak);
	if(sak->regain()==0){
		valid = false;
	}
	if(valid){
		this->egenStats.HP += sak->regain();
	}
	return valid;
		
	}

bool Actor::check_inventory(Item* sak) const{
		bool valid = false;
		for(int i = 0; i < inventory.size(); ++i) {
			if(inventory[i]->getName() == sak->getName()) {
			valid = true;
			break;
			}
		}
		return valid;
	}

string Actor::action() {} //Dont do anything in actor...

}


