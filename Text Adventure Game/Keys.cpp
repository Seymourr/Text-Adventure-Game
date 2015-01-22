#include "Keys.h"

namespace lab3{

	Keys::Keys(){
	this->sak.desc = "A fine Key";
	this->sak.name = "Key";
	this->sak.storlek = 0;
	this->sak.nutr = 0;
	this->sak.dmg = 0;
	}
	
	bool Keys::unlock(Env * from, Env * to) {
		for(int i = 0; i < from->neigh.size(); ++i) {
			if(from->neigh[i].otherNeighbour == to) {
				if(from->neigh[i].canEnter) {
					return false; //it was already unlocked, no need to use item
				} else {
					from->neigh[i].canEnter = true;
					for(int j = 0; j < to->neigh.size(); ++j){
						if(to->neigh[j].otherNeighbour == from) {
							to->neigh[j].canEnter = true;
							break;
						}
					
					}
				break;
				}
			}
		}
		
		return true;
	}
}


