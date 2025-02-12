#include "user_interface.hpp"

namespace Prog3 {

    void UserInterface::MissionParameters(Service& service, Repository& repository) {
        std::cout << "|                 MISSION PARAMENTS:                 |" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "                     captain's name: --> ";
        std::string commanderName;
        std::cin >> commanderName;
        std::cout << "                     captain's rank: --> ";
        int commanderRank = getNum<int>(1, 3);
        Captain commander(commanderName, commanderRank);

        std::cout << "Maximum number of ships in a convoy: --> ";
        unsigned int countConvoy = getNum<unsigned int>(1, 20);

        //std::cout << "Maximum number of ships in a pirate: --> ";
        unsigned int countPirate = 10;
        //std::cout << std::endl;

        std::cout << "                             Budget: --> ";
        unsigned int budget = getNum<unsigned int>(0, INT_MAX);

        std::cout << "          Available weight of cargo: --> ";
        unsigned int weightAvailable = getNum<unsigned int>(0, INT_MAX);
        std::cout << "              Weight Need Delivered: --> ";
        unsigned int weightNeedDelivered = getNum<unsigned int>(0, INT_MAX);
        Cargo cargo(weightAvailable, weightNeedDelivered, 0, 0);
        std::cout << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << std::endl << std::endl;

        service.MissionParameters(repository, commander, countConvoy, countPirate, budget, cargo);
    }


    void UserInterface::Dialog(Service& service, Repository& repository) {
        const char* msgs[] = {
            "0. End the program",
            "1. Buy a ship",
            "2. Sell the ship",
            "3. Load all ships",
            "4. Load the ship",
            "5. Unload all ships",
            "6. Unload the ship",
            "7. Buy weapons",
            "8. Sell weapons",
            "9. Pirate Status",
            "10.Convoy status",
            "11.Mission information",
            "12.Full information",
            "13.GO to the destination"
        };
        const int N = sizeof(msgs) / sizeof(msgs[0]);
        while (true) {
            try {
                std::cout << "------------------------------------------------------" << std::endl;
                for (int i = 0; i < N; i++)
                    puts(msgs[i]);
                std::cout << "------------------------------------------------------" << std::endl;
                std::cout << "\nMake your choice: --> ";
                int choose = getNum<int>(0, 13);
                std::cout << std::endl;
                int chooseShip = 0;
                int chooseArmament = 0;
                int location = 0;
                std::string callsign;
                std::string typeArmament;
                Base BaseA;
                Base BaseB;
                unsigned int A_radius = 0;
                double A_x = 0;
                double A_y = 0;
                unsigned int B_radius = 0;
                double B_x = 0;
                double B_y = 0;
                unsigned int weight = 0;
                switch (choose) {
                    case 0:
                        return;
                        break;
                    case 1:
                        ShowShipBuy(repository);
                        std::cout << "What ship: --> ";
                        chooseShip = getNum<int>(0, repository.shipBuy.size());
                        std::cout << "Callsign:  --> ";
                        std::cin >> callsign;
                        service.BuyShip(repository, callsign, chooseShip - 1);
                        std::cout << std::endl;
                        break;
                    case 2:
                        std::cout << "Callsign:  --> ";
                        std::cin >> callsign;
                        service.SellShip(repository, callsign);
                        std::cout << std::endl;
                        break;
                    case 3:
                        std::cout << "Weight:    --> ";
                        weight = getNum<unsigned int>(0, INT_MAX, 100);
                        service.LoadConvoy(repository, weight);
                        std::cout << std::endl;
                        break;
                    case 4:
                        std::cout << "Callsign:  --> ";
                        std::cin >> callsign;
                        std::cout << "Weight:    --> ";
                        weight = getNum<unsigned int>(0, INT_MAX);
                        service.LoadShip(repository, callsign, weight);
                        std::cout << std::endl;
                        break;
                    case 5:
                        service.UnLoadConvoy(repository);
                        break;
                    case 6:
                        std::cout << "Callsign:  --> ";
                        std::cin >> callsign;
                        service.UnLoadShip(repository, callsign);
                        std::cout << std::endl;
                        break;
                    case 7:
                        ShowArmamentBuy(repository);
                        std::cout << "What Armament: --> ";
                        chooseArmament = getNum<int>(0, repository.armamentsBuy.size());
                        std::cout << "Callsign:      --> ";
                        std::cin >> callsign;
                        std::cout << std::endl;

                        std::cout << "FRONT = 0 | BACK = 1 | LEFT = 2 | RIGHT = 3\n";
                        std::cout << "Location:      --> ";
                        location = getNum<int>(0, 3);
                        service.BuyWeapon(repository, chooseArmament - 1, callsign, location);
                        std::cout << std::endl;
                        break;
                    case 8:
                        std::cout << "Callsign:      --> ";
                        std::cin >> callsign;
                        std::cout << std::endl;

                        std::cout << "FRONT = 0 | BACK = 1 | LEFT = 2 | RIGHT = 3\n";
                        std::cout << "Location:      --> ";
                        location = getNum<int>(0, 3);

                        std::cout << "type Armament: --> ";
                        std::cin >> typeArmament;
                        std::cout << std::endl;
                        service.SellWeapon(repository, callsign, location, typeArmament);
                        break;
                    case 9:
                        std::cout << "|                PIRATE ";
                        ShowShip(repository.mission.GetPirate());
                        break;
                    case 10:
                        std::cout << "|                CONVOY ";
                        ShowShip(repository.mission.GetConvoy());
                        break;
                    case 11:
                        ShowMissioninformation(repository);
                        break;
                    case 12:
                        ShowMissioninformation(repository);
                        std::cout << "|                CONVOY ";
                        ShowShip(repository.mission.GetConvoy());
                        std::cout << "|                PIRATE ";
                        ShowShip(repository.mission.GetPirate());
                        break;
                    case 13:
                        std::cout << "Base A: ";
                        std::cout << std::endl;
                        std::cout << "  radius --> ";
                        A_radius = getNum<int>(0, INT_MAX);
                        std::cout << "       x --> ";
                        A_x = getNum<int>();
                        std::cout << "       y --> ";
                        A_y = getNum<int>();
                        BaseA = Base(A_x, A_y, A_radius);
                        std::cout << std::endl;

                        std::cout << "Base B: ";
                        std::cout << std::endl;
                        std::cout << "  radius --> ";
                        B_radius = getNum<int>(0, INT_MAX);
                        std::cout << "       x --> ";
                        B_x = getNum<int>();
                        std::cout << "       y --> ";
                        B_y = getNum<int>();
                        BaseB = Base(B_x, B_y, B_radius);

                        service.InputBasa(repository, BaseA, BaseB);
                        if (service.Mission(repository)) {
                            std::cout << std::endl << "  ======= MISSION ACCOMPLISHED ======= ";
                        }else {
                            std::cout << std::endl << "  ======= MISSION FAILED ======= ";
                        }

                        MissionResult(repository);
                        break;
                default:
                    std::cout << "Mistake! Enter a number [0 , 13]";
                    break;
                }
            }
            catch (const std::invalid_argument& ia) {
                std::cerr << ia.what() << std::endl << std::endl;
            }
            catch (...) {
                throw;
            }
        }
    }

    void UserInterface::ShowMissioninformation(const Repository& repository) {
        std::cout << "|                  MISSION INFORMATION:              |" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;

        std::cout << " * Commander: " << std::endl;
        std::cout << "      Name: -> " << repository.mission.GetCommander().nameCaptain << std::endl;
        std::cout << "      Rank: -> " << repository.mission.GetCommander().rankCaptain << std::endl;
        std::cout << " * Budget         : " << repository.mission.GetBudget() << std::endl;
        std::cout << " * Current Amount : " << repository.mission.GetCurrentAmount() << std::endl;
        std::cout << " * Max Convoy     : " << repository.mission.GetMaxConvoy() << std::endl;
        std::cout << " * Max Pirate     : " << repository.mission.GetMaxPirate() << std::endl;
        std::cout << std::endl;

        std::cout << " * Coordinates Basa A: " << std::endl;
        std::cout << "      x:      -> " << repository.mission.GetBaseA().coordinates.x << std::endl;
        std::cout << "      y:      -> " << repository.mission.GetBaseA().coordinates.y << std::endl;
        std::cout << "      radius: -> " << repository.mission.GetBaseA().radius << std::endl;
        std::cout << std::endl;

        std::cout << " * Coordinates Basa B: " << std::endl;
        std::cout << "      x:      -> " << repository.mission.GetBaseB().coordinates.x << std::endl;
        std::cout << "      y:      -> " << repository.mission.GetBaseB().coordinates.y << std::endl;
        std::cout << "      radius: -> " << repository.mission.GetBaseB().radius << std::endl;
        std::cout << std::endl;

        std::cout << " * Cargo: " << std::endl;
        std::cout << "      weight Available:    -> " << repository.mission.GetCargo().weightAvailable << std::endl;
        std::cout << "      weightDelivered:     -> " << repository.mission.GetCargo().weightDelivered << std::endl;
        std::cout << "      weightLost:          -> " << repository.mission.GetCargo().weightLost << std::endl;
        std::cout << "      weightNeedDelivered: -> " << repository.mission.GetCargo().weightNeedDelivered << std::endl;
        std::cout << "------------------------------------------------------" << std::endl << std::endl; 
    }

    void UserInterface::ShowShip(const Table<Participant, std::string>& participants) {
        int i = 0;
        std::cout <<"SHIPS:                       |" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        for (auto it = participants.begin(); it != participants.end(); ++it) {
            i++;
            std::cout << i << ". " << std::endl;
            std::cout << "CallSign             : " << (it->key) << std::endl;
            std::cout << "Coordinates: " << std::endl;
            std::cout << "   x: -> " << (it->value.coordinates.x) << std::endl;
            std::cout << "   y: -> " << (it->value.coordinates.y) << std::endl;

            std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(it->value.ship);
            if (ship == nullptr) {
                std::cout << "( THE SHIP IS HIT! )" << std::endl;
                continue;
            }
            std::cout << "Name                 : " << (it->value.ship)->GetNameShip() << std::endl;
            std::cout << "Cost                 : " << (it->value.ship)->GetCostShip() << std::endl;
            std::cout << "Name Captain         : " << (it->value.ship)->GetNameCaptain() << std::endl;
            std::cout << "Rank Captain         : " << (it->value.ship)->GetRankCaptain() << std::endl;
            std::cout << "Max Speed            : " << (it->value.ship)->GetMaxSpeed() << std::endl;
            std::cout << "Current Speed        : " << (it->value.ship)->GetCurrentSpeed() << std::endl;
            std::cout << "Max Survivability    : " << (it->value.ship)->GetMaxSurvivability() << std::endl;
            std::cout << "Current Survivability: " << (it->value.ship)->GetCurrentSurvivability() << std::endl;

            if (std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(it->value.ship)) {
                std::cout << "      CARGO" << std::endl;
                std::cout << "  ---------------" << std::endl;
                std::cout << " - Reduction Ratio: " << (it->value.ship)->GetReductionRatio() << std::endl;
                std::cout << " - Current Weight : " << ship->GetCurrentWeight() << std::endl;
                std::cout << " - Max Weight     : " << ship->GetMaxWeight() << std::endl;
            }
            if (std::shared_ptr<MilitaryFacility> ship = std::dynamic_pointer_cast<MilitaryFacility>(it->value.ship)) {
                std::array<WeaponsPlace, 4> wp = ship->GetWeapons();
                std::cout << "      WEAPONS" << std::endl;
                std::cout << "  ---------------" << std::endl;
                for (int j = 0; j < 4; j++) {
                    std::cout << "   " << j << ". PLACE:" << std::endl;
                    auto armaments = wp[j].GetArmaments();
                    //std::vector<Armament> armaments = wp[j].GetArmaments();
                    int f = 0;
                    for (auto k = armaments.begin(); k != armaments.end(); ++k) {
                        std::cout << "  " << f << ". Armament:" << std::endl;
                        std::cout << " * Type Armament     : " << k->GetTypeArmament() << std::endl;
                        std::cout << " * Cost Armament     : " << k->GetCostArmament() << std::endl;
                        std::cout << " * Damage            : " << k->GetDamage() << std::endl;
                        std::cout << " * Fire Rate         : " << k->GetFireRate() << std::endl;
                        std::cout << " * Firing Range      : " << k->GetFiringRange() << std::endl;
                        std::cout << " * Current Ammunition: " << k->GetCurrentAmmunition() << std::endl;
                        std::cout << " * Max Ammunition    : " << k->GetMaxAmmunition() << std::endl;
                        std::cout << "         ---------------" << std::endl;

                        f++;
                    }
                }
            }
            std::cout << "---------------------------" << std::endl << std::endl;
        }
        std::cout << "------------------------------------------------------" << std::endl << std::endl;
    }

    void UserInterface::ShowShipBuy(const Repository& repository) {
        int i = 0;
        std::cout << "SHIPS TO BUY:                     |" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        for (auto it = repository.shipBuy.begin(); it != repository.shipBuy.end(); ++it) {
            i++;
            std::cout << i << ". " << std::endl;
            std::cout << "Name                 : " << (*it)->GetNameShip() << std::endl;
            std::cout << "Cost                 : " << (*it)->GetCostShip() << std::endl;
            std::cout << "Name Captain         : " << (*it)->GetNameCaptain() << std::endl;
            std::cout << "Rank Captain         : " << (*it)->GetRankCaptain() << std::endl;
            std::cout << "Current Speed        : " << (*it)->GetCurrentSpeed() << std::endl;
            std::cout << "Current Survivability: " << (*it)->GetCurrentSurvivability() << std::endl;
            std::cout << "Max Speed            : " << (*it)->GetMaxSpeed() << std::endl;
            std::cout << "Max Survivability    : " << (*it)->GetMaxSurvivability() << std::endl;

            if (std::shared_ptr<CargoObject> ship = std::dynamic_pointer_cast<CargoObject>(*it)) {
                std::cout << "      CARGO" << std::endl;
                std::cout << "- Reduction Ratio: " << (*it)->GetReductionRatio() << std::endl;
                std::cout << "- Current Weight : " << ship->GetCurrentWeight() << std::endl;
                std::cout << "- Max Weight     : " << ship->GetMaxWeight() << std::endl;
            }
            if (std::shared_ptr<MilitaryFacility> ship = std::dynamic_pointer_cast<MilitaryFacility>(*it)) {
                std::array<WeaponsPlace, 4> wp = ship->GetWeapons();
                std::cout << "      WEAPONS" << std::endl;
                for (int j = 0; j < 4; j++) {
                    std::vector<Armament> armaments = wp[j].GetArmaments();
                    for (auto k = armaments.begin(); k != armaments.end(); ++k) {
                        std::cout << " * Type Armament     : " << k->GetTypeArmament() << std::endl;
                        std::cout << " * Cost Armament     : " << k->GetCostArmament() << std::endl;
                        std::cout << " * Current Ammunition: " << k->GetCurrentAmmunition() << std::endl;
                        std::cout << " * Damage            : " << k->GetDamage() << std::endl;
                        std::cout << " * Fire Rate         : " << k->GetFireRate() << std::endl;
                        std::cout << " * Firing Range      : " << k->GetFiringRange() << std::endl;
                        std::cout << " * Max Ammunition    : " << k->GetMaxAmmunition() << std::endl;
                    }
                }
            }
            std::cout << "---------------------------" << std::endl;
        }
        std::cout << "------------------------------------------------------" << std::endl << std::endl;
    }

    void UserInterface::ShowArmamentBuy(const Repository& repository) {
        int i = 0;
        std::cout << "|                  RMAMENT TO BUY:                   |" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        for (auto it = repository.armamentsBuy.begin(); it != repository.armamentsBuy.end(); ++it) {
            i++;
            std::cout << i << ". " << std::endl;
            std::cout << " * Type Armament     : " << it->GetTypeArmament() << std::endl;
            std::cout << " * Cost Armament     : " << it->GetCostArmament() << std::endl;
            std::cout << " * Current Ammunition: " << it->GetCurrentAmmunition() << std::endl;
            std::cout << " * Damage            : " << it->GetDamage() << std::endl;
            std::cout << " * Fire Rate         : " << it->GetFireRate() << std::endl;
            std::cout << " * Firing Range      : " << it->GetFiringRange() << std::endl;
            std::cout << " * Max Ammunition    : " << it->GetMaxAmmunition() << std::endl;
            std::cout << "---------------------------" << std::endl;
        }
        std::cout << "------------------------------------------------------" << std::endl << std::endl;
    }

    void UserInterface::MissionResult(const Repository& repository) {
        std::cout << std::endl;
        std::cout << "------------------------------------------------------" << std::endl << std::endl;
        std::cout << "Weight of the lost cargo      : " << repository.mission.GetCargo().weightLost << std::endl;
        std::cout << "Weight of the required cargo  : " << repository.mission.GetCargo().weightNeedDelivered << std::endl;
        std::cout << "Weight of the delivered cargo : " << repository.mission.GetCargo().weightDelivered << std::endl;
        std::cout << "------------------------------------------------------" << std::endl << std::endl;
    }
}