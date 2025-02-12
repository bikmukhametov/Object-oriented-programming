#include "repository.hpp"

namespace Prog3 {
	Repository::Repository() : mission() {
		Armament arm1("type_1", 20, Armament::Characteristics{ .damage = 500, .fireRate = 8, .firingRange = 5, .maxAmmunition = 20, .costArmament = 800 });
		Armament arm2("type_2", 30, Armament::Characteristics{ .damage = 600, .fireRate = 10, .firingRange = 6, .maxAmmunition = 30, .costArmament = 900 });
		Armament arm3("type_3", 40, Armament::Characteristics{ .damage = 600, .fireRate = 10, .firingRange = 7, .maxAmmunition = 30, .costArmament = 1000 });
		Armament arm4("type_4", 50, Armament::Characteristics{ .damage = 700, .fireRate = 12, .firingRange = 8, .maxAmmunition = 40, .costArmament = 1100 });
		Repository::armamentsBuy.push_back(arm1);
		Repository::armamentsBuy.push_back(arm2);
		Repository::armamentsBuy.push_back(arm3);
		Repository::armamentsBuy.push_back(arm4);

		TransportShip t1("T23", 100000, 20, Ship::Characteristics{.captain = {"A A A", 2}, .maxSpeed = 5, .maxSurvivability = 10000}, 0, 10000, 10000, 0);
		std::shared_ptr<Ship> tr1 = std::make_shared<TransportShip>(t1);
		TransportShip t2("T48", 90000, 15, Ship::Characteristics{ .captain = {"B B B", 3}, .maxSpeed = 6, .maxSurvivability = 10000 }, 0, 10000, 9000, 0);
		std::shared_ptr<Ship> tr2 = std::make_shared<TransportShip>(t2);
		TransportShip t3("T33", 80000, 25, Ship::Characteristics{ .captain = {"C C C", 1}, .maxSpeed = 4, .maxSurvivability = 10000 }, 0, 10000, 8000, 0);
		std::shared_ptr<Ship> tr3 = std::make_shared<TransportShip>(t3);
		Repository::shipBuy.push_back(tr1);
		Repository::shipBuy.push_back(tr2);
		Repository::shipBuy.push_back(tr3);

		SecurityShip sc1("SC40", 0, 10000, Ship::Characteristics{ .captain = {"T T T", 2}, .maxSpeed = 5, .maxSurvivability = 10000 }, 150000);
		std::shared_ptr<Ship> s1 = std::make_shared<SecurityShip>(sc1);
		SecurityShip sc2("SC50", 0, 10000, Ship::Characteristics{ .captain = {"K K K", 1}, .maxSpeed = 6, .maxSurvivability = 10000 }, 99000);
		std::shared_ptr<Ship> s2 = std::make_shared<SecurityShip>(sc2);
		SecurityShip sc3("SC36", 0, 10000, Ship::Characteristics{ .captain = {"L L L", 1}, .maxSpeed = 4, .maxSurvivability = 10000 }, 87000);
		std::shared_ptr<Ship> s3 = std::make_shared<SecurityShip>(sc3);
		Repository::shipBuy.push_back(s1);
		Repository::shipBuy.push_back(s2);
		Repository::shipBuy.push_back(s3);

		GuardedTransportShip gs1("G12", 0, 10000, Ship::Characteristics{ .captain = {"L L L", 1}, .maxSpeed = 7, .maxSurvivability = 10000 }, 10000, 0, 99000, 5);
		std::shared_ptr<Ship> g1 = std::make_shared<GuardedTransportShip>(gs1);
		GuardedTransportShip gs2("G12", 0, 10000, Ship::Characteristics{ .captain = {"O O O", 3}, .maxSpeed = 5, .maxSurvivability = 10000 }, 10000, 0, 100000, 6);
		std::shared_ptr<Ship> g2 = std::make_shared<GuardedTransportShip>(gs2);
		GuardedTransportShip gs3("G12", 0, 10000, Ship::Characteristics{ .captain = {"I I I", 2}, .maxSpeed = 6, .maxSurvivability = 10000 }, 10000, 0, 80000, 5);
		std::shared_ptr<Ship> g3 = std::make_shared<GuardedTransportShip>(gs3);
		Repository::shipBuy.push_back(g1);
		Repository::shipBuy.push_back(g2);
		Repository::shipBuy.push_back(g3);
	}

	void Repository::PirateDefault(){
		Armament ar1("type_1", 20, Armament::Characteristics{ .damage = 500, .fireRate = 5, .firingRange = 5, .maxAmmunition = 20, .costArmament = 800 });
		Armament ar2("type_2", 30, Armament::Characteristics{ .damage = 600, .fireRate = 5, .firingRange = 6, .maxAmmunition = 30, .costArmament = 900 });
		Armament ar3("type_3", 40, Armament::Characteristics{ .damage = 700, .fireRate = 6, .firingRange = 7, .maxAmmunition = 40, .costArmament = 1000 });
		Armament ar4("type_4", 50, Armament::Characteristics{ .damage = 800, .fireRate = 7, .firingRange = 8, .maxAmmunition = 50, .costArmament = 1100 });
		std::vector<Armament> arms1;
		std::vector<Armament> arms2;
		std::vector<Armament> arms3;
		std::vector<Armament> arms4;
		arms1.push_back(ar1);
		arms2.push_back(ar2);
		arms3.push_back(ar3);
		arms4.push_back(ar4);

		WeaponsPlace wp1(WeaponsPlace::FRONT, arms1);
		WeaponsPlace wp2(WeaponsPlace::FRONT, arms2);
		WeaponsPlace wp3(WeaponsPlace::FRONT, arms3);
		WeaponsPlace wp4(WeaponsPlace::FRONT, arms4);

		std::array<WeaponsPlace, 4> w1;
		std::array<WeaponsPlace, 4> w2;
		std::array<WeaponsPlace, 4> w3;
		std::array<WeaponsPlace, 4> w4;

		w1[0] = wp1;
		w2[0] = wp2;
		w3[0] = wp3;
		w4[0] = wp4;

		PirateShip pr1("P43", 0, 10000, Ship::Characteristics{ .captain = {"P P P", 2}, .maxSpeed = 0, .maxSurvivability = 10000 }, w1);
		std::shared_ptr<Ship> p1 = std::make_shared<PirateShip>(pr1);
		PirateShip pr2("P51", 0, 10000, Ship::Characteristics{ .captain = {"E E E", 1}, .maxSpeed = 0, .maxSurvivability = 10000 }, w2);
		std::shared_ptr<Ship> p2 = std::make_shared<PirateShip>(pr2);
		PirateShip pr3("P39", 0, 10000, Ship::Characteristics{ .captain = {"Q Q Q", 1}, .maxSpeed = 0, .maxSurvivability = 10000 }, w3);
		std::shared_ptr<Ship> p3 = std::make_shared<PirateShip>(pr3);
		PirateShip pr4("P20", 0, 10000, Ship::Characteristics{ .captain = {"M M M", 1}, .maxSpeed = 0, .maxSurvivability = 10000 }, w4);
		std::shared_ptr<Ship> p4 = std::make_shared<PirateShip>(pr4);

		mission.CreatePirate(p1, "A", Point(1, 1));
		mission.CreatePirate(p2, "B", Point(100, 100));
		mission.CreatePirate(p3, "C", Point(40, 30));
		mission.CreatePirate(p4, "D", Point(40, 30));
	}
}