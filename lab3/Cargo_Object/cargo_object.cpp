#include "cargo_object.hpp"

namespace Prog3 {

	bool CargoObject::Load(unsigned int weight) {
		if ((this->currentWeight + weight > this->maxWeight) || (weight < 0)) {
			return false;
		} else {
			this->currentWeight += weight;
			return true;
		}
	}

	bool CargoObject::LoadRange(unsigned int from, unsigned int to){
		if (from > this->maxWeight || to < 0) {
			return false;
		}
		if (to > this->maxWeight) {
			currentWeight = maxWeight;
		}
		else {
			currentWeight = to;
		}
		return true;
	}
	
	unsigned int CargoObject::Unload(){
		unsigned int weight = currentWeight;
		currentWeight = 0;
		return weight;
	}
}