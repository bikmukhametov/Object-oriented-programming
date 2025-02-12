#ifndef OOPPROG3_TRANSPORT_SHIP_HPP
#define OOPPROG3_TRANSPORT_SHIP_HPP

#include <string>
#include <iostream>
#include <compare>

#include "../../Ship/ship.hpp"
#include "../../Cargo_Object/cargo_object.hpp"

namespace Prog3 {
	class TransportShip : public Ship, public CargoObject {
	private:
		unsigned int costShip;
		unsigned int reductionRatio;
	public:
		TransportShip():Ship(), CargoObject(), costShip(100000), reductionRatio(1) {}

		TransportShip(std::string nameShip, unsigned int costShip, double reductionRatio, Characteristics chars, 
			double currentSpeed, unsigned int currentSurvivability, unsigned int maxWeight, unsigned int currentWeight) :
			Ship(nameShip, currentSpeed, currentSurvivability, chars),
			CargoObject(maxWeight, currentWeight),
			costShip(costShip), reductionRatio(reductionRatio) {}

		unsigned int GetCostShip() const override { return costShip; }
		unsigned int GetReductionRatio() const override { return reductionRatio; }

		Ship& SetCostShip(unsigned int costShip)  override { this->costShip = costShip; return *this; }
		Ship& SetReductionRatio(unsigned int reductionRatio)  override { this->reductionRatio = reductionRatio; return *this; }

		void TakeDamage(unsigned int damage) override;
		void Move(Point& start, const Point& end) override;
		void CurrentSpeedRange(double from, double to) override;
		double MaxSpeed(unsigned int weight) override;

		virtual ~TransportShip() = default;
	};
} 

#endif //TRANSPORT_SHIP_HPP