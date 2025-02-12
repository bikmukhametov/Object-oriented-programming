#ifndef OOPPROG3_SERVICE_HPP
#define OOPPROG3_SERVICE_HPP

#include <thread>
#include "../Repository/repository.hpp"
#include "../Mission/mission.hpp"

namespace Prog3 {
	class Service {
	public:
		void MissionParameters(Repository& repository, const Captain& commander, unsigned int countConvoy,
			unsigned int countPirate, unsigned int budget, const Cargo& cargo);
		void InputBasa(Repository& repository, const Base& BaseA, const Base& BaseB);
		void BuyShip(Repository& repository, std::string callsign, int chooseShip);
		void SellShip(Repository& repository, std::string callsign);
		void LoadConvoy(Repository& repository, unsigned int weight);
		void LoadShip(Repository& repository, std::string callsign, unsigned int weight);
		void UnLoadConvoy(Repository& repository);
		void UnLoadShip(Repository& repository, std::string callsign);
		void BuyWeapon(Repository& repository, int chooseArmament, std::string callsign, int location);
		void SellWeapon(Repository& repository, std::string callsign, int location, std::string typeArmament);

		bool Mission(Repository& repository);
		void Move(Repository& repository, Point& current, const Point& end);
		void War(Repository& repository, unsigned int distance);
		void ResultCollision(Repository& repository, const Table<Participant, std::string>& participants);
		bool Sensor(Repository& repository, const Point& point, unsigned int distance);
		unsigned int CurrentSpeed(Repository& repository);
		bool EmptyConvoy(const Repository& repository, const Table<Participant, std::string>& participants);

		~Service() = default;
	};
}


#endif //SERVICE_HPP