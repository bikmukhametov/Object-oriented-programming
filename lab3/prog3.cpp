#include <iostream>

#include "User_Interface/user_interface.hpp"
#include "Service/service.hpp"

using namespace Prog3;

int main() {
	try {
		Service service;
		UserInterface userinterface;
		Repository repository;

		userinterface.MissionParameters(service, repository);
		userinterface.Dialog(service, repository);
	}
	catch (const std::bad_alloc& ba) {
		std::cerr << "Not enough memory" << std::endl << std::endl;;
		return 1;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl << std::endl;;
		return 1;
	}
	return 0;

}