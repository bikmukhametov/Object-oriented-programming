#ifndef OOPPROG3_PIRATE_SHIP_HPP
#define OOPPROG3_PIRATE_SHIP_HPP

#include <string>
#include <iostream>
#include <compare>

#include "../../Ship/ship.hpp"
#include "../../Military_Facility/military_facility.hpp"

namespace Prog3 {

	class PirateShip : public Ship, public MilitaryFacility {

	public:
		PirateShip(): Ship(), MilitaryFacility() {} 

		//конструктор с вооружением
		PirateShip(std::string nameShip, double currentSpeed, unsigned int currentSurvivability,
			Characteristics chars, std::array<WeaponsPlace, 4> weapons):
			Ship(nameShip, currentSpeed, currentSurvivability, chars), MilitaryFacility(weapons){}

		//конструктор без вооружения
		PirateShip(std::string nameShip, double currentSpeed,
			unsigned int currentSurvivability, Characteristics chars) :
			Ship(nameShip, currentSpeed, currentSurvivability, chars), MilitaryFacility() {}

		void Move(Point& start, const Point& end) override;
		unsigned int Shoot(double p1_x, double p1_y, double p2_x, double p2_y) override;
		void TakeDamage(unsigned int damage) override;
		void CurrentSpeedRange(double from, double to) override;
		double MaxSpeed(unsigned int weight) override;

		virtual ~PirateShip() = default;
	};
}

#endif //PIRATE_SHIP_HPP