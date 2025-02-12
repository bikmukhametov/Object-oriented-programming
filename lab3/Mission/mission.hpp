#ifndef OOPPROG3_MISSION_HPP
#define OOPPROG3_MISSION_HPP

#include <string>
#include <iostream>
#include <compare>
#include <vector>
#include <memory>

//#include "../Ship_types/Transport_Ship/transport_ship.hpp"
//#include "../Ship_types/Guarded_Transport_Ship/guarded_transport_ship.hpp"
//#include "../Ship_types/Pirate_Ship/pirate_ship.hpp"
//#include "../Ship_types/Security_Ship/security_ship.hpp"


#include "../Ship/ship.hpp"
#include "../Cargo_Object/cargo_object.hpp"
#include "../Military_Facility/military_facility.hpp"
#include "../Table/table.hpp"


namespace Prog3 {
	 
	class Base{
	public:
		Point coordinates;
		double radius;

		Base(): coordinates(0, 0), radius(0){}
		Base(const Point coordinates, double radius) : coordinates(coordinates), radius(radius) {}
		Base(double x, double y, double radius) : coordinates(x, y), radius(radius) {}
		bool operator==(const Base& other) const {
			return std::tie(coordinates.x, coordinates.y, radius) == std::tie(other.coordinates.x, other.coordinates.y, other.radius);
		}
	};

	class Cargo {
	public:
		unsigned int weightAvailable;		//доступная масса груза
		unsigned int weightNeedDelivered;	//количество груза необходимое довезти
		unsigned int weightLost;			//масса потерянного груза
		unsigned int weightDelivered;		//масса доставленного груза

		Cargo(): weightAvailable(10000), weightNeedDelivered(5000), weightLost(0), weightDelivered(0) {}
		Cargo(unsigned int weightAvailable, unsigned int weightNeedDelivered, unsigned int weightLost, unsigned int weightDelivered) :
			weightAvailable(weightAvailable), weightNeedDelivered(weightNeedDelivered),
			weightLost(weightLost), weightDelivered(weightDelivered) {}
	};

	class Participant {
	public:
		Point coordinates;
		std::shared_ptr<Ship> ship;

		Participant() : 
			coordinates(0,0){}
		Participant(Point coordinates, std::shared_ptr<Ship> ship) : 
			coordinates(coordinates), ship(ship){}
		bool operator==(const Participant& other) const {
			return (this->coordinates.x == other.coordinates.x) && (this->coordinates.y == other.coordinates.y) &&
				(this->ship == other.ship);
		}
	};

	class Mission {
	private:
		unsigned int maxConvoy;
		unsigned int maxPirate;
		unsigned int budget;
		unsigned int currentAmount;
		Captain commander;

		Table<Participant, std::string> convoy;
		Table<Participant, std::string> pirate;

		Base BaseA;
		Base BaseB;
		Cargo cargo;
	public:
		Mission() : maxConvoy(10), maxPirate(10), budget(500000000), currentAmount(500000000), commander("AAA", 1), BaseA(0, 0, 1), BaseB(100, 100, 1), cargo() {}

		Mission(unsigned int maxConvoy, unsigned int maxPirate, unsigned int budget, unsigned int currentAmount, Captain commander, Table<Participant, std::string>& convoy,
			Table<Participant, std::string>& pirate, Base BaseA, Base BaseB, Cargo cargo):
			maxConvoy(maxConvoy), maxPirate(maxPirate), budget(budget), currentAmount(currentAmount), commander(commander), convoy(convoy),
			pirate(pirate), BaseA(BaseA), BaseB(BaseB), cargo(cargo){}

		Mission(unsigned int maxConvoy, unsigned int maxPirate, unsigned int budget, unsigned int currentAmount, std::string com_name, int com_rank,
			Table<Participant, std::string>& convoy, Table<Participant, std::string>& pirate, double a_x, double a_y, double a_r, double b_x, double b_y, double b_r,
			unsigned int weightTotal, unsigned int weightNeedDelivered, unsigned int weightLost, unsigned int weightDelivered) :
			maxConvoy(maxConvoy), maxPirate(maxPirate), budget(budget), currentAmount(currentAmount), commander(com_name, com_rank), convoy(convoy),
			pirate(pirate), BaseA(a_x, a_y, a_r), BaseB(b_x, b_y, b_r),
			cargo(weightTotal, weightNeedDelivered, weightLost, weightDelivered) {}

		unsigned int GetMaxConvoy() const { return maxConvoy; }
		unsigned int GetMaxPirate() const { return maxPirate; }
		unsigned int GetBudget() const { return budget; }
		unsigned int GetCurrentAmount() const { return currentAmount; }
		const Captain& GetCommander() const { return commander; }
		const Table<Participant, std::string>& GetConvoy() { return convoy; }
		const Table<Participant, std::string>& GetPirate() { return pirate; }
		const Base& GetBaseA() const { return BaseA; }
		const Base& GetBaseB() const { return BaseB; }
		const Cargo& GetCargo() const { return cargo; }


		Mission& SetMaxConvoy(unsigned int maxConvoy) { this->maxConvoy = maxConvoy; return *this; }
		Mission& SetMaxPirate(unsigned int maxPirate) { this->maxPirate = maxPirate; return *this; }
		Mission& SetBudget(unsigned int budget) { this->budget = budget; return *this; }
		Mission& SetCurrentAmount(unsigned int currentAmount) { this->currentAmount = currentAmount; return *this; }
		Mission& SetCommander(Captain commander) { this->commander = commander; return *this; }
		Mission& SetConvoy(const Table<Participant, std::string>& convoy) { this->convoy = convoy; return *this; }
		Mission& SetPirate(const Table<Participant, std::string>& pirate) { this->pirate = pirate; return *this; }
		Mission& SetBaseA(Base BaseA) { this->BaseA = BaseA; return *this; }
		Mission& SetBaseB(Base BaseB) { this->BaseB = BaseB; return *this; }
		Mission& SetCargo(Cargo cargo) { this->cargo = cargo; return *this; }
		Mission& SetWeightDelivered(unsigned int weightDelivered) { cargo.weightDelivered = weightDelivered; return *this; }


		void CreatePirate(const std::shared_ptr<Ship>& pirate, std::string callSign, const Point& coordinates);
		void BuyConvoyShip(const std::shared_ptr<Ship>& ship, std::string callSign, const Point& coordinates);
		void SellConvoyShip(std::string callSign);
		void BuyWeapon(const Armament& armament, std::string callSign, int location);
		void SellWeapon(std::string callSign, int location, std::string typeArmament);
		void DestroyPirate(std::string callSign);
		void DestroyConvoy(std::string callSign);

		void ShootConvoy(double distance);
		void ShootPirate(double distance);

		void LoadShip(std::string callSign, unsigned int weight);
		void UnLoadShip(std::string callSign);
		void UnLoadConvoy();
		void LoadConvoy(unsigned int weight);
		double Distance(const Point& p1,const Point& p2);
		unsigned int CurrentWeight();

		~Mission() = default;
	};
}

#endif //MISSION_HPP