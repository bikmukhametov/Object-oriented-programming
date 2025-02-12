#ifndef OOPPROG3_USERINTERFACE_HPP
#define OOPPROG3_USERINTERFACE_HPP

#include "../Service/service.hpp"
#include "lib.hpp"

namespace Prog3 {
	class UserInterface {
		public:
		void Dialog(Service& service, Repository& repository);
		void MissionParameters(Service& service, Repository& repository);
		void ShowShipBuy(const Repository& repository);
		void ShowShip(const Table<Participant, std::string>& participants);
		void ShowMissioninformation(const Repository& repository);
		void ShowArmamentBuy(const Repository& repository);
		void MissionResult(const Repository& repository);

		~UserInterface() = default;
	};
}

#endif //USERINTERFACE_HPP