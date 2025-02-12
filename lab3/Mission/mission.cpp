#include "mission.hpp"

namespace Prog3 {
	void Mission::CreatePirate(const std::shared_ptr<Ship>& pirate, std::string callSign, const Point& coordinates){
		if (this->pirate.size() == maxPirate) {
			throw std::invalid_argument("the table is full!");
		}
		Participant participant(coordinates, pirate);
		this->pirate.push_front({ participant, callSign });////
	}

	void Mission::DestroyPirate(std::string callSign) {
		pirate.erase(callSign);

		/*for (auto& participant : pirate) {
			if (participant.key == callSign) {
				participant.value.ship = nullptr;
				break;
			}
		}*/
	}

	void Mission::BuyConvoyShip(const std::shared_ptr<Ship>& ship, std::string callSign, const Point& coordinates){
		if (this->convoy.size() == maxConvoy) {
			throw std::invalid_argument("the table is full!");
		}
		if (ship->GetCostShip() > this->currentAmount) {
			throw std::invalid_argument("invalid argument!");
		}else {
			Participant participant(coordinates, ship);
			currentAmount -= ship->GetCostShip();
			this->convoy.push_front({ participant, callSign });/////
		}
	}

	void Mission::SellConvoyShip(std::string callSign) {
		auto it = convoy.find(callSign);
		if (it == convoy.end()) return;
		currentAmount += it->value.ship->GetCostShip();
		convoy.erase(it);

		/*for (auto it = convoy.begin(); it != convoy.end(); ++it) {
			if (it->key == callSign) {
				currentAmount += it->value.ship->GetCostShip();
				convoy.erase(it);
				return;
			}
		}*/

		//throw std::invalid_argument("invalid argument!");
	}
	void Mission::BuyWeapon(const Armament& armament, std::string callSign, int location){
		if (currentAmount - armament.GetCostArmament() < 0) {
			throw std::invalid_argument("invalid argument!");
		}
		for (auto& participant : convoy) {
			if (participant.key == callSign) {
				std::shared_ptr<MilitaryFacility> ship = std::dynamic_pointer_cast<MilitaryFacility>(participant.value.ship);
				if (ship == nullptr) continue;
				ship->AddWeapons(location, armament);
				currentAmount -= armament.GetCostArmament();
				return;
			}
		}
		throw std::invalid_argument("invalid argument!");
	}

	void Mission::SellWeapon(std::string callSign, int location, std::string typeArmament){
		for (auto& participant : convoy) {
			if (participant.key != callSign) continue;

			std::shared_ptr<MilitaryFacility> ship = std::dynamic_pointer_cast<MilitaryFacility>(participant.value.ship);
			if (ship == nullptr) continue;

			ship->RemoveWeapons(location, typeArmament);
			std::array<WeaponsPlace, 4> weaponsPlace = ship->GetWeapons();
			std::vector<Armament> armaments = weaponsPlace[location].GetArmaments();

			for (auto& armament : armaments) {
				if (armament.GetTypeArmament() == typeArmament) {
					currentAmount += armament.GetCostArmament();
					break;
				}
			}
			weaponsPlace[location].SetArmaments(armaments);
			ship->SetWeapons(weaponsPlace);
			return;
		}
		throw std::invalid_argument("invalid argument!");
	}

	void Mission::DestroyConvoy(std::string callSign){
		for (auto& participant : convoy) {
			if (participant.key != callSign) continue;

			std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(participant.value.ship);
			if (ship == nullptr) {
				participant.value.ship = nullptr;
				return;
			}
			else {
				cargo.weightLost += ship->GetCurrentWeight();
				participant.value.ship = nullptr;
			}
			break;
		}
	}

	double Mission::Distance(const Point& p1, const Point& p2) {
		return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
	}

	void Mission::ShootConvoy(double distance){ // атака конвоя
		unsigned int damageShip = 0;

		for (auto& participant : convoy) {
			std::shared_ptr<MilitaryFacility> shipConvoy = std::dynamic_pointer_cast<MilitaryFacility>(participant.value.ship);
			if (shipConvoy == nullptr) continue;

			unsigned int survivability = 0;
			unsigned int minSurvivability = INT_MAX;
			auto it_p = pirate.begin();
			for (auto iter_p = pirate.begin(); iter_p != pirate.end(); ++iter_p) {
				std::shared_ptr<Ship> shipPirate = std::dynamic_pointer_cast<Ship>(iter_p->value.ship);
				if (shipPirate == nullptr) continue;

				double distance_ship = Distance(participant.value.coordinates, iter_p->value.coordinates);
				if (distance < distance_ship) continue;

				survivability = shipPirate->GetCurrentSurvivability();
				if (minSurvivability > survivability) {
					minSurvivability = survivability;
					it_p = iter_p;
				}
			}
			if (minSurvivability != INT_MAX) {
				damageShip = shipConvoy->Shoot(participant.value.coordinates.x, participant.value.coordinates.y, 
					it_p->value.coordinates.x, it_p->value.coordinates.y);
				std::shared_ptr<Ship> shipPirate = std::dynamic_pointer_cast<Ship>(it_p->value.ship);
				shipPirate->TakeDamage(damageShip);
			}
		}
	}

	void Mission::ShootPirate(double distance) { // атака врага
		unsigned int damageShip = 0;

		for (auto& participant : pirate) {
			std::shared_ptr<MilitaryFacility> shipPirate = std::dynamic_pointer_cast<MilitaryFacility>(participant.value.ship);
			if (shipPirate == nullptr) continue;

			unsigned int survivability = 0;
			unsigned int minSurvivability = INT_MAX;
			auto it_c = convoy.begin();
			for (auto iter_c = convoy.begin(); iter_c != convoy.end(); ++iter_c) {
				std::shared_ptr<Ship> shipConvoy = std::dynamic_pointer_cast<Ship>(iter_c->value.ship);
				if (shipConvoy == nullptr) continue;

				double distance_ship = Distance(participant.value.coordinates, iter_c->value.coordinates);
				if (distance < distance_ship) continue;

				survivability = shipConvoy->GetCurrentSurvivability();
				if (minSurvivability > survivability) {
					minSurvivability = survivability;
					it_c = iter_c;
				}
			}
			if (minSurvivability != INT_MAX) {
				damageShip = shipPirate->Shoot(participant.value.coordinates.x, participant.value.coordinates.y,
					it_c->value.coordinates.x, it_c->value.coordinates.y);
				std::shared_ptr<Ship> shipConvoy = std::dynamic_pointer_cast<Ship>(it_c->value.ship);
				shipConvoy->TakeDamage(damageShip);
			}
		}
	}

	void Mission::LoadShip(std::string callSign, unsigned int weight){
		bool m = false;
		for (auto& participant : convoy) {
			if (participant.key != callSign) continue;

			std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(participant.value.ship);
			if (ship == nullptr) break;

			m = ship->Load(weight);
			break;
		}
		if (m == false) throw std::invalid_argument("invalid argument!");
		cargo.weightAvailable -= weight;
	}

	void Mission::UnLoadShip(std::string callSign){
		for (auto& participant : convoy) {
			if (participant.key == callSign) {
				std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(participant.value.ship);
				if (ship == nullptr) break;

				cargo.weightAvailable += ship->Unload();
				return;
			}
		}
		throw std::invalid_argument("invalid argument!");

	}

	void Mission::UnLoadConvoy() {
		for (auto& participant : convoy) {
			std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(participant.value.ship);
			if (ship == nullptr) continue;

			cargo.weightAvailable += ship->Unload();
		}
	}

	void Mission::LoadConvoy(unsigned int weight) {
		if (weight > cargo.weightAvailable) {
			throw std::invalid_argument("invalid argument!");
		}
		bool flag = false;
		bool m = false;
		for (int i = 0; i < weight; i += 100) {
			double maxSpeed = 0;
			double speed = 0;
			unsigned int currentWeight = 0;
			unsigned int maxWeight = 0;
			auto iter = convoy.end();
			for (auto it = convoy.begin(); it != convoy.end(); ++it) {
				std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(it->value.ship);
				if (ship == nullptr) continue;

				currentWeight = ship->GetCurrentWeight();
				maxWeight = ship->GetMaxWeight();
				speed = it->value.ship->MaxSpeed(currentWeight + 100);

				if ((maxWeight >= currentWeight + 100) && (speed > maxSpeed)) {
					maxSpeed = speed;
					iter = it;
				}
			}
			if (iter == convoy.end()) continue;
			std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(iter->value.ship);
			if (ship == nullptr) continue;
			m = ship->Load(100);
			cargo.weightAvailable -= 100;
			if (m) flag = true;
		}
		if (flag == false) {
			throw std::invalid_argument("invalid argument!");
		}
		if (m == false) {
			throw std::invalid_argument("invalid argument! But we loaded all the ships to the maximum");
		}
	}

	unsigned int Mission::CurrentWeight() {
		unsigned int currentWeight = 0;
		for (auto& participant : convoy) {
			if (std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(participant.value.ship)) {
				currentWeight += ship->GetCurrentWeight();
			}
		}
		return currentWeight;
	}
}
