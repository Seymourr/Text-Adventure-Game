#include "Outside.h"



namespace lab3{
using namespace std;

	Outside::Outside(string n, string des, vector<Item*> it){
		for(int i = 0; i<it.size(); ++i){
			items.push_back(it[i]);
		}
		description = des;
		name = n;
		
	}
	
	
	string Outside::areaDescription(string eventualActors){
		string desc = "You are in " + getName() + "\n";
		desc+= getDescription() + "\n";


		string neighbours = "There are doors to the: ";
		for(int i = 0; i < neigh.size(); ++i) {
			neighbours += neigh[i].direction + " ";
		}
		desc += neighbours + "\n";
		if(!items.empty()){
		desc = desc + "You spot the following items: ";
		for(int i = 0; i < items.size(); ++i) {
			desc = desc + items[i]->getName() + " , ";
		}
		desc = desc + "\n";
		} else {
			desc = desc + "You dont spot any items in this room \n";
		}
		
		if(eventualActors == "") {
			desc = desc + "There are no other persons in this room";
		} else {
		desc = desc + "The persons in this room are: " + eventualActors;
	}
		return desc;
	}



}

