#ifndef CONTAINER_H
#define CONTAINER_H

#include<iostream>
#include<vector>
#include<string>

namespace lab3{
using namespace std;
template <class T>
class container{
	protected:
		int backpackSpace = 10; //Default
		vector<T> backpack;
	public:

	int size() const{
		backpack.size();
	}
	int space() const {
		return backpackSpace;
	}
	
	bool add_item(T NewItem){
		bool valid =  false;
		int sum = 0;
		for(int i = 0; i < backpack.size(); ++i) {
			sum += backpack[i]->size();
		}
		if(sum + NewItem->size() <= backpackSpace){
		
			valid = true;
		} 
		if(valid){
			backpack.push_back(NewItem);
		}
		
		return valid;
	}

	std::vector<T> search_backpack(){
		return backpack;
	}

	bool remove_from_backpack(T Item){
		bool valid = false;
		for(int it = 0; it < backpack.size(); ++it){
			if(backpack[it]->description().compare(Item->description()) == 0){
				valid=true;
				backpack.erase(backpack.begin()+it);
				break;
			}
		}
		return valid;
	}
	
	T operator[](unsigned int i) const{
	return backpack[i];
	}

};
}
	
#endif
