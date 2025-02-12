#ifndef OOPPROG3_MILITARY_FACILITY_HPP
#define OOPPROG3_MILITARY_FACILITY_HPP

#include <string>
#include <iostream>
#include <compare>
#include <vector>
#include <array>
#include <cmath>

//#include "../Ship/ship.hpp"

namespace Prog3 {

	class Armament {
	public:
		struct Characteristics {
			unsigned int damage = 100;
			unsigned int fireRate = 1;		//скорострельность 
			unsigned int firingRange = 10;	//дальность стрельбы
			unsigned int maxAmmunition = 20;
			unsigned int costArmament = 1000;
		};
	private:
		std::string typeArmament;
		unsigned int currentAmmunition;
		Characteristics characteristics;
	public:
		Armament() : typeArmament("typeArmament"), currentAmmunition(20), characteristics() {}

		Armament(std::string typeArmament, unsigned int currentAmmunition, Characteristics chars) :
			typeArmament(typeArmament), currentAmmunition(currentAmmunition), characteristics(chars) {}

		std::string GetTypeArmament() const { return typeArmament; }
		unsigned int GetDamage() const { return characteristics.damage; }
		unsigned int GetFireRate() const { return characteristics.fireRate; }
		unsigned int GetFiringRange() const { return characteristics.firingRange; }
		unsigned int GetMaxAmmunition() const { return characteristics.maxAmmunition; }
		unsigned int GetCurrentAmmunition() const { return currentAmmunition; }
		unsigned int GetCostArmament() const { return characteristics.costArmament; }

		Armament& SetCurrentAmmunition(unsigned int currentAmmunition) { this->currentAmmunition = currentAmmunition; return *this; }

		virtual unsigned int Shoot(double p1_x, double p1_y, double p2_x, double p2_y);

		virtual ~Armament() = default;//v
	};

	class WeaponsPlace {
	private:
		int location;
		std::vector<Armament> armaments;
	public:
		enum {
			FRONT = 0,
			BACK = 1,
			LEFT = 2,
			RIGHT = 3,
		};

		WeaponsPlace():location(FRONT) {}
		WeaponsPlace(int location, std::vector<Armament>& armaments): location(location), armaments(armaments){}

		int GetLocation() const { return location; }
		const std::vector<Armament>& GetArmaments() { return armaments; }
		WeaponsPlace& SetLocation(int idWeapons) { this->location = location; return *this; }
		WeaponsPlace& SetArmaments(const std::vector<Armament>& armaments) { this->armaments = armaments; return *this; }

		void AddWeapon(Armament armament);
		void RemoveWeapon(std::string typeArmament);

		virtual ~WeaponsPlace() = default;//v
	};



	class MilitaryFacility{
	private:
		std::array<WeaponsPlace, 4> weapons;
	public:
		MilitaryFacility() {}
		MilitaryFacility(std::array<WeaponsPlace, 4> weapons) { this->weapons = weapons; }

		const std::array<WeaponsPlace, 4>& GetWeapons() { return weapons; }
		MilitaryFacility& SetWeapons(const std::array<WeaponsPlace, 4>& weapons){ this->weapons = weapons; return *this; }

		virtual unsigned int Shoot(double p1_x, double p1_y, double p2_x, double p2_y) = 0;
		virtual void AddWeapons(int location, Armament armament);
		virtual void RemoveWeapons(int location, std::string typeArmament);

		virtual ~MilitaryFacility() = default;
	};
}
#endif //MILITARY_FACILITY_HPP