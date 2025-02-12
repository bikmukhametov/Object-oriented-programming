#ifndef OOPPROG3_SHIP_HPP
#define OOPPROG3_SHIP_HPP

#include <string>
#include <iostream>
#include <compare>

namespace Prog3 {
	//captain
	class Captain{
	public:
		//The name of captain
		std::string nameCaptain;
		//The rank of captain
		int rankCaptain;
		/*!
		* @brief constructor with set values
		* @param nameCaptain name of the captain
		* @param rankCaptain rank of the captain
		*/
		Captain(std::string nameCaptain, int rankCaptain): nameCaptain(nameCaptain), rankCaptain(rankCaptain){}
	};

	//point
	class Point {
	public:
		double x;
		double y;
		Point(double x, double y) : x(x), y(y) {}
	};

	//expandable ship class
	class Ship {
	public:
		struct Characteristics {
			//The captain of the ship
			Captain captain = { "nameCaptain", 3 };
			//maximum speed of the ship
			double maxSpeed = 50;
			//maximum survivability of the ship
			unsigned int maxSurvivability = 10000;
		};
	private:
		//The name of a ship
		std::string nameShip;
		//The current speed of a ship
		double currentSpeed;
		//The current survivability of a ship
		unsigned int currentSurvivability;
		//The characteristics of a ship: captain: name and rank, maximum speed, maximum survivability
		Characteristics characteristics;
	public:
		/*!
		* @brief Empty constructor, creates a ship
		*/
		Ship():nameShip("nameShip"), currentSpeed(5), currentSurvivability(10000), characteristics() {}

		/*!
		* @brief constructor with set values
		* @param nameShip The name of a ship
		* @param currentSpeed The current speed of a ship
		* @param currentSurvivability The current survivability of a ship
		* @param chars The characteristics of a ship
		*/
		Ship(std::string nameShip, double currentSpeed, unsigned int currentSurvivability, Characteristics chars):
			nameShip(nameShip), currentSpeed(currentSpeed), currentSurvivability(currentSurvivability), characteristics(chars){}

		/*!
		* @brief Get the name of the ship
		* @returns name of the ship
		*/
		std::string GetNameShip() const { return nameShip; }

		/*!
		* @brief Get the name of captain of the ship
		* @returns name of the captain
		*/
		std::string GetNameCaptain() const { return characteristics.captain.nameCaptain; }

		/*!
		* @brief Get the rank of captain of the ship
		* @returns rank of the captain
		*/
		int GetRankCaptain() const { return characteristics.captain.rankCaptain; }

		/*!
		* @brief Get the maximum speed of the ship
		* @returns maximum speed of the ship
		*/
		double GetMaxSpeed() const { return characteristics.maxSpeed; }

		/*!
		* @brief Get the current speed of the ship
		* @returns current speed of the ship
		*/
		double GetCurrentSpeed() const { return currentSpeed; }

		/*!
		* @brief Get the maximum survivability of the ship
		* @returns maximum survivability of the ship
		*/
		unsigned int GetMaxSurvivability() const { return characteristics.maxSurvivability; }

		/*!
		* @brief Get the current survivability of the ship
		* @returns current survivability of the ship
		*/
		unsigned int GetCurrentSurvivability() const { return currentSurvivability; }

		/*!
		* @brief changes the value of the maximum speed
		* @param maxSpeed - new maximum speed value
		* @returns reference to a ship
		*/
		Ship& SetMaxSpeed(double maxSpeed) { this->characteristics.maxSpeed = maxSpeed; return *this; }
		
		/*!
		* @brief changes the value of the current speed
		* @param currentSpeed - new current speed value
		* @returns reference to a ship
		*/
		Ship& SetCurrentSpeed(double currentSpeed) { this->currentSpeed  = currentSpeed; return *this; }
		
		/*!
		* @brief changes the value of the current survivability
		* @param currentSpeed - new current survivability value
		* @returns reference to a ship
		*/
		Ship& SetCurrentSurvivability(unsigned int currentSurvivability) { this->currentSurvivability = currentSurvivability; return *this; }

		/*!
		* @brief virtual function of Get the cost of the ship
		* @returns cost of ship
		*/
		virtual unsigned int GetCostShip() const { return 0; }

		/*!
		* @brief virtual function of Get the deceleration factor of the ship
		* @note this applies to cargo ships, 
				* the speed of the ship depends on its loading
		* @returns deceleration factor
		*/
		virtual unsigned int GetReductionRatio() const { return 0; }

		/*!
		* @brief virtual function of changes the value of cost of the ship
		* @returns reference to a ship
		*/
		virtual Ship& SetCostShip(unsigned int costShip) { return *this; }
		
		/*!
		* @brief virtual function of changes the value of deceleration factor of the ship
		* @note this applies to cargo ships, 
				* the speed of the ship depends on its loading
		* @returns reference to a ship
		*/
		virtual Ship& SetReductionRatio(unsigned int reductionRatio) { return *this; }

		/*!
		* @brief virtual function of taking damage to the ship
		* @note The specified amount of damage 
				* is deducted from her survivability
		* @param damage the amount of damage
		*/
		virtual void TakeDamage(unsigned int damage) = 0;

		/*!
		* @brief virtual function of ship move
		* @param start current location
		* @param end point indicating the direction of movement
		* @note The method implements changing the coordinates 
				* of the start parameter to coordinates 
				* that are the result of moving the ship in 1 second, 
				* with a given direction of movement
		*/
		virtual void Move(Point& start, const Point& end) = 0;

		/*!
		* @brief virtual function of set the ship's speed in the range
		* @param from the beginning of the range
		* @param to the end of the range
		* @note Sets the speed of the ship in a given range. 
				* It is necessary to check for the correctness 
				* of the set parameters and 
				* take into account the maximum speed of the ship
		*/
		virtual void CurrentSpeedRange(double from, double to) = 0;

		/*!
		* @brief virtual function for getting the maximum speed at a given weight
		* @param weight the cargo weight
		* @note A method for determining the maximum possible speed 
				* for a ship at a given weight. 
				* (Some ships may slow down as cargo increases). 
				* The method does not change the fields of the class. 
				* This method can be used for optimal distribution of cargo, 
				* taking into account the maximum speed of all ships in the convoy.
		* @returns maximum possible speed
		*/
		virtual double MaxSpeed(unsigned int weight) = 0;

		//destructor of ship
		virtual ~Ship() = default;
	};
}
#endif //SHIP_HPP