/*#include <iostream>
#include "resource/resource.h"
#include "resource/lib.h"

using namespace Prog2;

int main() {
    Resource a("item", 17, 19, 378);
    Resource b("item", 200);
    Resource c;

    a.print();
    b.print();

    c = a + b;  //обьединение  
    //c.operator=(a.operator+(b));

    std::cout << "----- the result (+): " << std::endl;
    c.print();


    //c.setPrice(8).setConsumption(5).setProduction(10);

    std::string name;
    while (true) {
        try {
            Resource d;              // создание пользователем
            std::cout << "name: ";
            std::cin >> name;
            d.setName(name);
            std::cout << "consumption: ";
            d.setConsumption(getNum<int>(0));
            std::cout << "production: ";
            d.setProduction(getNum<int>(0));
            std::cout << "price: ";
            d.setPrice(getNum<int>(0));
            std::cout << "\n";
            std::cout << "profit for the week: " << d.profit() << std::endl;


            while (true) {
                int x;
                std::cout << "increase in turnover by: ";
                x = getNum<int>(0);
                std::cout << "\n";
                if (std::cin.eof()) {
                    return 0;
                }
                if (std::cin.bad()) {
                    throw std::runtime_error("Input broken");
                }
                if (std::cin.good()) {
                    try {
                        d.increase(x);            //увеличение оборота
                        std::cout << "----- the result (*): " << std::endl;
                        d.print();

                        bool equality = d == a;   //сравнение (==)
                        std::cout << "----- equality: " << std::boolalpha << equality << std::endl << std::endl;


                        bool less = (d < a);      //сравнение (<)
                        std::cout << "----- less: " << std::boolalpha << less << std::endl << std::endl;
                    }
                    catch (const std::exception& e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    break;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            continue;
        }
    }
}*/