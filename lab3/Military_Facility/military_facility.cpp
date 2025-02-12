#include "military_facility.hpp"

namespace Prog3 {

	unsigned int Armament::Shoot(double p1_x, double p1_y, double p2_x, double p2_y) { //выстрел за 1 сек
		double distance = std::sqrt(std::pow(p1_x - p2_x, 2) + std::pow(p1_y - p2_y, 2));
		int count = 0;
		if (distance > characteristics.firingRange) return 0;

		for (int i = 0; i < characteristics.fireRate; i++) {
			if (currentAmmunition > 0) {
				currentAmmunition -= 1;
				count++;
			}
		}
		int setDamage = characteristics.damage * count;
		return setDamage;
	}

	void WeaponsPlace::AddWeapon(Armament armament) {
		armaments.push_back(armament);
	}

	void WeaponsPlace::RemoveWeapon(std::string typeArmament) {
		for (auto it = armaments.begin(); it != armaments.end(); ++it) {
			if (it->GetTypeArmament() == typeArmament) {
				armaments.erase(it);
				return;
			}
		}
		throw std::invalid_argument("invalid argument!");
	}

	void MilitaryFacility::AddWeapons(int location, Armament armament){
		if (location > 3 || location < 0) {
			throw std::invalid_argument("invalid argument!");
		}
		weapons[location].AddWeapon(armament);
	}

	void MilitaryFacility::RemoveWeapons(int location, std::string typeArmament){
		if (location > 3 || location < 0) {
			throw std::invalid_argument("invalid argument!");
		}
		weapons[location].RemoveWeapon(typeArmament);
	}
}