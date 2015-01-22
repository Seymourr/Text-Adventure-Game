#ifndef ENV_H
#define ENV_H

#include <string>
#include <vector>
#include "Item.h"

namespace lab3 {
using namespace std;
	class Env {
	protected:
	
		struct neighbour {
		public:
			string direction;
			bool canEnter;
			Env* otherNeighbour;
		};
		
		
		string description;
		string name;
		
	public:
		string getDescription() const;
		vector<neighbour> neigh;
		bool add_neighbour(string direct, bool valid, Env* neig);
		
		vector<Item*> items;
		void pick_up(Item * item);
		void add(Item * item);
		vector<string> directions();
		string getName() const;
		virtual string areaDescription(string areaDesc) = 0;
	};



}
#endif 
