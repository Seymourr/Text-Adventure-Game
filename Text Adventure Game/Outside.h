#ifndef OUTSIDE_H
#define OUTSIDE_H

#include "Env.h"
#include "Actor.h"

namespace lab3{
using namespace std;
	class Outside: public Env{
	protected:
	
	
	public:
	Outside(string name, string des, vector<Item*> it);
	
	string areaDescription(string eventualActors);
	
};

}
#endif
