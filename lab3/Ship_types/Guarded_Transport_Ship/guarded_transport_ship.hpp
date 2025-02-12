#ifndef OOPPROG3_GUARDED_TRANSPORT_SHIP_HPP
#define OOPPROG3_GUARDED_TRANSPORT_SHIP_HPP
#include <string>
#include <iostream>
#include <compare>

#include "../../Cargo_Object/cargo_object.hpp"
#include "../../Military_Facility/military_facility.hpp"
#include "../../Ship/ship.hpp"

namespace Prog3 {
	class GuardedTransportShip : public Ship, public CargoObject, public MilitaryFacility {
	private:
		unsigned int costShip;
		unsigned int reductionRatio;
	public:
		GuardedTransportShip() : Ship(), MilitaryFacility(), costShip(100000), reductionRatio(50) {}

		//конструктор с вооружением
		GuardedTransportShip(std::string nameShip, double currentSpeed, unsigned int currentSurvivability, Characteristics chars, 
			unsigned int maxWeight, unsigned int currentWeight, std::array<WeaponsPlace, 4> weapons, unsigned int costShip, unsigned int reductionRatio) :
			Ship(nameShip, currentSpeed, currentSurvivability, chars),
			CargoObject(maxWeight, currentWeight), MilitaryFacility(weapons), 
			costShip(costShip), reductionRatio(reductionRatio) {}

		//конструктор без вооружения
		GuardedTransportShip(std::string nameShip, double currentSpeed, unsigned int currentSurvivability, Characteristics chars,
			unsigned int maxWeight, unsigned int currentWeight, unsigned int costShip, unsigned int reductionRatio) :
			Ship(nameShip, currentSpeed, currentSurvivability, chars),
			CargoObject(maxWeight, currentWeight),
			MilitaryFacility(),
			costShip(costShip), reductionRatio(reductionRatio){}


		unsigned int GetCostShip() const override{ return costShip; }
		unsigned int GetReductionRatio() const override { return reductionRatio; }

		Ship& SetCostShip(unsigned int costShip) override { this->costShip = costShip; return *this; }
		Ship& SetReductionRatio(unsigned int reductionRatio) override { this->reductionRatio = reductionRatio; return *this; }

		void Move(Point& start, const Point& end) override;
		unsigned int Shoot(double p1_x, double p1_y, double p2_x, double p2_y) override;
		void TakeDamage(unsigned int damage) override;
		void CurrentSpeedRange(double from, double to) override;
		double MaxSpeed(unsigned int weight) override;

		virtual ~GuardedTransportShip() = default;
	};
}

#endif //GUARDED_TRANSPORT_SHIP_HPP