#ifndef OOPPROG3_REPOSITORY_HPP
#define OOPPROG3_REPOSITORY_HPP
#include "../Mission/mission.hpp"
#include "../Ship_types/Transport_Ship/transport_ship.hpp"
#include "../Ship_types/Guarded_Transport_Ship/guarded_transport_ship.hpp"
#include "../Ship_types/Pirate_Ship/pirate_ship.hpp"
#include "../Ship_types/Security_Ship/security_ship.hpp"

namespace Prog3 {
	class Repository {
	public:
		Mission mission;
		std::vector<std::shared_ptr<Ship>> shipBuy;
		std::vector<Armament> armamentsBuy;

		Repository();
		void PirateDefault();
		~Repository() = default;
	};
}
#endif //REPOSITORY_HPP