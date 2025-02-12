#include "security_ship.hpp"
#include <cmath>

namespace Prog3 {

	unsigned int SecurityShip::Shoot(double p1_x, double p1_y, double p2_x, double p2_y) {
		unsigned int damage = 0;
		std::array<WeaponsPlace, 4> weaponsPlace = GetWeapons();
		for (int location = 0; location < 4; location++) {
			std::vector<Armament> armaments = weaponsPlace[location].GetArmaments();
			for (auto it = armaments.begin(); it != armaments.end(); ++it) {
				damage += it->Shoot(p1_x, p1_y, p2_x, p2_y);
			}
			weaponsPlace[location].SetArmaments(armaments);
		}
		SetWeapons(weaponsPlace);
		return damage;
	}

	void SecurityShip::TakeDamage(unsigned int damage) {
		unsigned int currentSurvivability = GetCurrentSurvivability();
		if (currentSurvivability < damage) {
			currentSurvivability = 0;
		}else {
			currentSurvivability -= damage;
		}
		SetCurrentSurvivability(currentSurvivability);
	}

	 void SecurityShip::Move(Point& start, const Point& end) { //перемещение за 1 секунду
		double distance = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2)); //весь путь
		double currentDistance = GetCurrentSpeed(); //расстояние за одну секунду
		start.x = start.x + ((end.x - start.x) * (currentDistance / distance));
		start.y = start.y + ((end.y - start.y) * (currentDistance / distance));
	}

	void SecurityShip::CurrentSpeedRange(double from, double to) {
		if (from > GetMaxSpeed() || to < 0) {
			throw std::invalid_argument("invalid argument!");
		}
		if (to > GetMaxSpeed()) {
			SetCurrentSpeed(GetMaxSpeed());
		}else {
			SetCurrentSpeed(to);
		}
	}
	double SecurityShip::MaxSpeed(unsigned int weight) {
		return GetMaxSpeed();
	}
}