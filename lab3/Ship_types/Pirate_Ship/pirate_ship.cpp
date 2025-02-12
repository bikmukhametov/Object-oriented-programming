#include "pirate_ship.hpp"

namespace Prog3 {

	unsigned int PirateShip::Shoot(double p1_x, double p1_y, double p2_x, double p2_y){
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

	void PirateShip::TakeDamage(unsigned int damage) {
		unsigned int currentSurvivability = GetCurrentSurvivability();
		if (currentSurvivability < damage) {
			currentSurvivability = 0;
		}else {
			currentSurvivability -= damage;
		}
		SetCurrentSurvivability(currentSurvivability);
	}

	double PirateShip::MaxSpeed(unsigned int weight) {
		return GetMaxSpeed();
	}

	void PirateShip::Move(Point& start, const Point& end) {}
	void PirateShip::CurrentSpeedRange(double from, double to) {}
}