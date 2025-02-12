#ifndef OOPPROG3_SECURITY_SHIP_HPP
#define OOPPROG3_SECURITY_SHIP_HPP

#include <string>
#include <iostream>
#include <compare>

#include "../../Ship/ship.hpp"
#include "../../Military_Facility/military_facility.hpp"

namespace Prog3 {
	class SecurityShip : public Ship, public MilitaryFacility {
	private:
		unsigned int costShip;
	public:
		SecurityShip() : Ship(), MilitaryFacility(), costShip(100000) {}

		//конструктор с вооружением
		SecurityShip(std::string nameShip, double currentSpeed, unsigned int currentSurvivability, 
			Characteristics chars, unsigned int costShip, std::array<WeaponsPlace, 4> weapons) :
			Ship(nameShip, currentSpeed, currentSurvivability, chars), MilitaryFacility(weapons), costShip(costShip){}

		//конструктор без вооружения
		SecurityShip(std::string nameShip, double currentSpeed, unsigned int currentSurvivability, 
			Characteristics chars,unsigned int costShip) :
			Ship(nameShip, currentSpeed, currentSurvivability, chars), MilitaryFacility(), costShip(costShip) {}

		unsigned int GetCostShip() const override { return costShip; }
		Ship& SetCostShip(unsigned int costShip) { this->costShip = costShip; return *this; }

		void Move(Point& start, const Point& end) override;
		unsigned int Shoot(double p1_x, double p1_y, double p2_x, double p2_y) override;
		void TakeDamage(unsigned int damage) override;
		void CurrentSpeedRange(double from, double to) override;
		double MaxSpeed(unsigned int weight) override;

		virtual ~SecurityShip() = default;
	};
}

#endif //SECURITY_SHIP_HPP