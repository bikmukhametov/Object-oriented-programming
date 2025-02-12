#include "transport_ship.hpp"
#include <cmath>

namespace Prog3 {

	void TransportShip::TakeDamage(unsigned int damage) {
		unsigned int currentSurvivability = GetCurrentSurvivability();
		if (currentSurvivability < damage) {
			currentSurvivability = 0;
		}else {
			currentSurvivability -= damage;
		}
		SetCurrentSurvivability(currentSurvivability);
	}

	void TransportShip::CurrentSpeedRange(double from, double to) {
		if (from > GetMaxSpeed() || to < 0) {
			throw std::invalid_argument("invalid argument!");
		}
		if (to > GetMaxSpeed()) {
			SetCurrentSpeed(GetMaxSpeed());
		}else {
			SetCurrentSpeed(to);
		}
	}

	void TransportShip::Move(Point& start, const Point& end) {						//перемещение за 1 секунду
		double distance = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));	//весь путь
		double currentDistance = GetCurrentSpeed();									//расстояние за одну секунду
		start.x = start.x + (end.x - start.x) * (currentDistance / distance);
		start.y = start.y + (end.y - start.y) * (currentDistance / distance);
	}

	double TransportShip::MaxSpeed(unsigned int weight) {
		double speed = GetMaxSpeed() - (reductionRatio * GetMaxSpeed() * 
			(weight / static_cast<double>((GetMaxWeight())) / 100));
		return speed;
	}
}