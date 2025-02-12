#include "service.hpp"

namespace Prog3 {
	void Service::MissionParameters(Repository& repository, const Captain& commander, unsigned int countConvoy, 
		unsigned int countPirate, unsigned int budget, const Cargo& cargo) {
		repository.mission.SetCommander(commander);
		repository.mission.SetMaxConvoy(countConvoy);
		repository.mission.SetMaxPirate(countPirate);
		repository.mission.SetBudget(budget);
		repository.mission.SetCargo(cargo);
		repository.mission.SetCurrentAmount(budget);
		repository.PirateDefault();
	}

	void Service::BuyShip(Repository& repository, std::string callsign, int chooseShip) {
		Base b_A = repository.mission.GetBaseA();
		Point p_A = { b_A.coordinates.x, b_A.coordinates.y };
		repository.mission.BuyConvoyShip(repository.shipBuy[chooseShip], callsign, p_A);
	}

	void Service::SellShip(Repository& repository, std::string callsign) {
		repository.mission.SellConvoyShip(callsign);
	}

	void Service::LoadConvoy(Repository& repository, unsigned int weight) {
		repository.mission.LoadConvoy(weight);
	}

	void Service::LoadShip(Repository& repository, std::string callsign, unsigned int weight) {
		repository.mission.LoadShip(callsign, weight);
	}

	void Service::UnLoadConvoy(Repository& repository) {
		repository.mission.UnLoadConvoy();
	}

	void Service::UnLoadShip(Repository& repository, std::string callsign) {
		repository.mission.UnLoadShip(callsign);
	}

	void Service::BuyWeapon(Repository& repository, int chooseArmament, std::string callsign, int location) {
		repository.mission.BuyWeapon(repository.armamentsBuy[chooseArmament], callsign, location);
	}

	void Service::SellWeapon(Repository& repository, std::string callsign, int location, std::string typeArmament) {
		repository.mission.SellWeapon(callsign, location, typeArmament);
	}

	void Service::InputBasa(Repository& repository, const Base& BaseA, const Base& BaseB) {
		repository.mission.SetBaseA(BaseA);
		repository.mission.SetBaseB(BaseB);
	}

	//Миссия
	bool Service::Mission(Repository& repository) {
		Point current(repository.mission.GetBaseA().coordinates.x, repository.mission.GetBaseA().coordinates.y);
		Point end(repository.mission.GetBaseB().coordinates.x, repository.mission.GetBaseB().coordinates.y);
		unsigned int baseSize = repository.mission.GetBaseB().radius;
		unsigned int distance = 10;
		auto pirate = repository.mission.GetPirate();
		auto convoy = repository.mission.GetConvoy();
		unsigned int speed = CurrentSpeed(repository);

		for (auto& participant : convoy) {								//устанавливаем координаты
			if (std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(participant.value.ship)) {
				participant.value.coordinates.x = current.x;
				participant.value.coordinates.y = current.y;
				ship->SetCurrentSpeed(speed);
			}
		}
		repository.mission.SetConvoy(convoy);

		while (repository.mission.Distance(current, end) > baseSize) {	//пока не доплывут
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "COORDINATES: " << "x -> " << current.x << "  y -> " << current.y << std::endl;
			if (Sensor(repository, current, distance)) {				// если обнаружили цель
				std::cout << "-- BATTLE --"<< std::endl;
				War(repository, distance);
				ResultCollision(repository, repository.mission.GetConvoy());
				ResultCollision(repository, repository.mission.GetPirate());
				if (EmptyConvoy(repository, repository.mission.GetConvoy())) {
					return false;
				}
			}
			Move(repository, current, end);								// передвижение
		}
		repository.mission.SetWeightDelivered(repository.mission.CurrentWeight());
		if (repository.mission.GetCargo().weightDelivered >= repository.mission.GetCargo().weightNeedDelivered) {
			return true;
		}
		return false;

	}

	//Передвижение
	void Service::Move(Repository& repository, Point& current, const Point& end) {
		Point res = current;
		auto convoy = repository.mission.GetConvoy();
		for (auto& participant : convoy) {
			std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(participant.value.ship);
			if (ship == nullptr) continue;

			res = current;
			ship->Move(res, end);

			participant.value.coordinates.x = res.x;
			participant.value.coordinates.y = res.y;

		}
		current = res;
		repository.mission.SetConvoy(convoy);
	}

	//Радар: существуют ли враги на заданном радиусе
	bool Service::Sensor(Repository& repository, const Point& point, unsigned int distance) {
		auto pirate = repository.mission.GetPirate();
		for (auto& participant : pirate){
			if (repository.mission.Distance(point, participant.value.coordinates) <= distance) {
				return true;
			}
		}
		return false;
	}

	//Сражение
	void Service::War(Repository& repository, unsigned int distance) {
		//repository.mission.ShootConvoy(distance);
		//repository.mission.ShootPirate(distance);

		std::thread convoy(&Mission::ShootConvoy, &repository.mission, distance);
		std::thread pirate(&Mission::ShootPirate, &repository.mission, distance);

		convoy.join();
		pirate.join();
	}

	//Устанавливаем текущую скорость
	unsigned int Service::CurrentSpeed(Repository& repository) {
		unsigned int minSpeed = INT_MAX;
		unsigned int speed = 0;
		unsigned int weight = 0;
		auto convoy = repository.mission.GetConvoy();
		for (auto& participant : convoy) {
			if (std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(participant.value.ship)) {
				weight = ship->GetCurrentWeight();
			}
			std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(participant.value.ship);
			if (ship == nullptr) continue;

			speed = ship->MaxSpeed(weight);
			if (speed < minSpeed) {
				minSpeed = speed;
			}
		}
		return minSpeed;
	}

	//Отмечаем убитых
	void Service::ResultCollision(Repository& repository, const Table<Participant, std::string>& participants) {
		for (auto& participant : participants){
			std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(participant.value.ship);
			if (ship == nullptr) continue;

			if ((participants == repository.mission.GetPirate()) && (ship->GetCurrentSurvivability() == 0)) {
				repository.mission.DestroyPirate(participant.key);
			}
			else if ((participants == repository.mission.GetConvoy()) && (ship->GetCurrentSurvivability() == 0)) {
				repository.mission.DestroyConvoy(participant.key);
			}
		}
	}

	bool Service::EmptyConvoy(const Repository& repository, const Table<Participant, std::string>& participants) {
		bool empty = true;
		for (auto& participant : participants) {
			if (std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(participant.value.ship)) {
				empty = false;
			}
		}
		return empty;
	}
}