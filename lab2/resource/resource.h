#ifndef OOPPROG2_RESOURCE_H
#define OOPPROG2_RESOURCE_H

#include <string>
#include <iostream>
#include <compare>

namespace Prog2 {
	class Resource {
	private:
		//имя
		std::string name;
		// потребление (кг/д)
		int consumption;  
		// производство (кг/д)
		int production;
		// цена (у.е./кг)
		int price;		 

	public:
		/*!
		@brief construct a default object.
		@param name - the name of the resource. "AAA" by default.
		@param consumption - kilogram consumption / division. 1 by default.
		@param production - kilogram production / division. 1 by default.
		@param price - unit price / per kilogram. 1 by default.
		*/
		Resource();


		/*!
		@brief construct by name and price.
		@param name - the name of the resource.
		@param consumption - kilogram consumption / division. 1 by default.
		@param production - kilogram production / division. 1 by default.
		@param price - unit price / per kilogram.
		*/
		Resource(std::string name, int price);


		/*!
		@brief construct by name, consumption, production and price.
		@param name - the name of the resource.
		@param consumption - kilogram consumption / division.
		@param production - kilogram production / division.
		@param price - unit price / per kilogram.
		*/
		Resource(std::string name, int consumption, int production, int price);


		/*!
		@brief calculates the profit of the resource for the week.
		@returns profit for the week.
		*/
		int profit() const { return (production - consumption) * 7 * price; }   //прибыль за неделю


		/*!
		@brief increases resource turnover.
		@param n - how many times to increase.
		throws std::invalid_argument("illegal argument"), when n < 1.
		*/
		void increase(int n);											        //увеличить на (n) раз


		/*!
		@brief changes the value of the name.
		@param n - new name value
		@returns reference to a resource.
		*/
		Resource& setName(std::string n) { this->name = n; return *this; }


		/*!
		@brief changes the value of the consumption.
		@param cons - new consumption value.
		@returns reference to a resource.
		*/
		Resource& setConsumption(int cons) { this->consumption = cons; return *this; }


		/*!
		@brief changes the value of the production.
		@param prod - new production value.
		@returns reference to a resource.
		*/
		Resource& setProduction(int prod) { this->production = prod; return *this; }


		/*!
		@brief changes the value of the price.
		@param pr - new price value.
		@returns reference to a resource.
		*/
		Resource& setPrice(int pr) { this->price = pr; return *this; }


		/*!
		@brief Get the name of the resource object.
		@returns resource name.
		*/
		const std::string &GetName() const { return name; }


		/*!
		@brief Get the consumption of the resource object.
		@returns resource consumption.
		*/
		int GetConsumption() const { return consumption; }


		/*!
		@brief Get the production of the resource object.
		@returns resource production.
		*/
		int GetProduction() const { return production; }


		/*!
		@brief Get the price of the resource object.
		@returns resource price.
		*/
		int GetPrice() const { return price; }


		/*!
		@brief addition operator for resources
		@param rhs - constant reference to the resource.
		@returns reference to a resource.
		*/
		Resource operator + (const Resource& rhs) const;	//обьединение (+)


		/*!
		@brief compares resources for equivalence.
		@param rhs - constant reference to the resource
		@returns bool as the result of the comparison.
		*/
		bool operator == (const Resource& rhs) const;		//сравнение (==)


		/*!
		@brief compares resources by a sign less.
		@param rhs - constant reference to the resource.
		@returns bool as the result of the comparison.
		*/
		bool operator < (const Resource& rhs) const;		//сравнение (<)


		/*!
		@brief copying operator.
		@param other - constant reference to the resource.
		@returns reference to a resource.
		*/
		Resource& operator = (const Resource& other);		//присваивание (=)


		/*!
		@brief resource input function.
		@param c - flow into the input signal.
		@param recource - reference to the resource.
		@returns flow into the input signal.
		*/
		friend std::istream& operator >> (std::istream& c, Resource& recource);			//ввод
		//std::istream& operator >> (std::istream& c);			//ввод

		/*!
		@brief resource output function.
		@param c - flow into the output signal.
		@param recource - constant reference to the resource.
		@returns flow into the output signal.
		*/
		friend std::ostream& operator << (std::ostream& c, const Resource& recource);	//вывод
	};
}

#endif //RESOURCE_H