#ifndef OOPPROG3_CARGO_OBJECT_HPP
#define OOPPROG3_CARGO_OBJECT_HPP

#include <string>
#include <iostream>
#include <compare>

namespace Prog3 {
	class CargoObject{
	private:
		unsigned int maxWeight;
		unsigned int currentWeight;
	public:
		CargoObject(): maxWeight(10000), currentWeight(0){}

		CargoObject(unsigned int maxWeight, unsigned int currentWeight): 
			maxWeight(maxWeight), currentWeight(currentWeight){}

		unsigned int GetMaxWeight() const { return maxWeight; }
		unsigned int GetCurrentWeight() const { return currentWeight; }

		CargoObject& SetMaxWeight(unsigned int maxWeight) { this->maxWeight = maxWeight; return *this; }
		CargoObject& SetCurrentWeight(unsigned int currentWeight) { this->currentWeight = currentWeight; return *this; }

		virtual bool Load(unsigned int weight);
		virtual bool LoadRange(unsigned int from, unsigned int to);
		virtual unsigned int Unload();

		virtual ~CargoObject() = default;
	};
}


#endif //CARGO_OBJECT_HPP