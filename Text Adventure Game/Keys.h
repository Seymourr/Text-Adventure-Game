#ifndef KEYS_H
#define KEYS_H

#include <string>
#include "Env.h"
#include "Item.h"


namespace lab3 {
using namespace std;
class Keys : public Item {
	public:
	Keys();
	
	bool unlock(Env * from, Env * to);
	

};
}
#endif 

