#include "resource.h"
#include "lib.h"

#include <string>
#include <iostream>
#include <compare>
#include <tuple>
#include <utility>

namespace Prog2 {

	Resource::Resource() :
		name("AAA"), consumption(1), production(1), price(1) {}

	Resource::Resource(std::string name, int price) :
		name(name), consumption(1), production(1), price(price) {}

	Resource::Resource(std::string name, int consumption, int production, int price) :
		name(name), consumption(consumption), production(production), price(price) {}

	void Resource::increase(int n) {
		if (n < 1) {
			throw std::invalid_argument("illegal argument");
		}
		consumption *= n;
		production *= n;
	}

	Resource Resource::operator + (const Resource& rhs) const { //обьединение (+)
		Resource res;
		res.name = rhs.name;
		res.consumption = consumption + rhs.consumption;
		res.production = production + rhs.production;
		res.price = std::min(price, rhs.price);
		return res;
	}

	bool Resource::operator == (const Resource& rhs) const {  //сравнение (==)
		return ((name == rhs.name) && (consumption == rhs.consumption)
			&& (production == rhs.production) && (price == rhs.price));
	}

	bool Resource::operator < (const Resource& rhs) const {  //сравнение (<)
		return std::tie(name, consumption, production, price)
			< std::tie(rhs.name, rhs.consumption, rhs.production, rhs.price);
	}

	Resource& Resource::operator = (const Resource& rhs) {
		consumption = rhs.consumption;
		production = rhs.production;
		price = rhs.price;
		name = rhs.name;
		return *this;
	}

	std::ostream& operator << (std::ostream& c, const Resource& resource) {		//вывод
		c << resource.name << " "
			<< resource.consumption << " "
			<< resource.production << " "
			<< resource.price << "\n";
		return c;
	}
	
	std::istream& operator >> (std::istream& c, Resource& resource) {			//ввод
		Resource new_resource;
		c >> new_resource.name >> new_resource.consumption >> new_resource.production >> new_resource.price;

		if(c.good()) {
			if ((new_resource.consumption >= 0) && (new_resource.production >= 0) && (new_resource.price >= 0)) {
				resource = new_resource;
			}
			else {
				c.setstate(std::ios::failbit);
			}
		}
		return c;
	}
}