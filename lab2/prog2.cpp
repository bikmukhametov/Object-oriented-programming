#include <iostream>
#include "resource/resource.h"
#include "table/table.h"
#include "resource/lib.h"

using namespace Prog2;

int main() {
    const char* msgs[] = { "0. End the program", "1. Initialization from an array of resources",
        "2. (+=) Adding a new resource", "3. ([]) Getting a resource by its name",
        "4. Deleting a resource by its name", "5. Renaming a given resource",
        "6. Table status", "7. Total profit for all resources",
        "8. (*=) Increase in turnover of all resources", "9. table status", "10. (>>) entering a table"};

    Table t();
    
    //std::cout
    Resource vector[] = {
        Resource("aa", 11, 1, 1),
        Resource("ff", 22, 2, 2),
        Resource("bb", 33, 3, 3),
        Resource("gg", 44, 4, 4),
        Resource("cc", 55, 5, 5),
        Resource("ll", 66, 6, 6),
        Resource("qq", 77, 7, 7),
        Resource("tt", 88, 8, 8),
        Resource("vv", 99, 9, 9),
        Resource("mm", 100, 10, 10),
        Resource("re", 11, 1, 1),
        Resource("zi", 12, 2, 2),
        Resource("vcv", 13, 3, 3),
        Resource("dzv", 14, 4, 4),
        Resource("dsv", 15, 5, 5),
        Resource("lldv", 16, 6, 6),
        Resource("qqdv", 17, 7, 7),
        Resource("ttv", 18, 8, 8),
        Resource("vvv", 19, 9, 9)
    };

    int vector_len = sizeof(vector) / sizeof(vector[0]);
    for (int i = 0; i < vector_len; i++) {
        std::cout << vector[i] << "\n";
    }
    Table table;
    const int N = sizeof(msgs) / sizeof(msgs[0]);

    while (true) {
        try {
            for (int i = 0; i < N; i++)
                puts(msgs[i]);
            std::cout << "\nMake your choice: --> ";
            int choose = getNum<int>(0, 10);
            std::cout << "\n\n";
            Table table_new;
            Resource resource;
            std::string str;
            std::string old_str;

            switch (choose) {
            case 0:
                return 0;
                break;

            case 1:
                std::cout << "count: --> ";
                int count;
                count = getNum<int>(0, vector_len);
                std::cout << "\n";
                table.init_vector(vector, count);
                break;

            case 2:
                std::cout << "resource: \n";
                std::cin >> resource;
                table += resource;
                break;

            case 3:
                std::cout << "name: --> ";
                std::cin >> str;
                std::cout << "\n";
                resource = table[str];
                std::cout << "resource: \n" << resource;
                break;

            case 4:
                std::cout << "name: --> ";
                std::cin >> str;
                std::cout << "\n\n";
                table.removal(str);
                break;

            case 5:
                std::cout << "old name: --> ";
                std::cin >> old_str;
                std::cout << "new name: --> ";
                std::cin >> str;
                std::cout << "\n\n";
                table.rename(old_str, str);
                break;

            case 6:
                std::cout << table;
                std::cout << "\n\n";
                break;

            case 7:
                std::cout << "profit: --> " << table.profit() << "\n\n";
                break;

            case 8:
                std::cout << "increase: --> ";
                int n;
                n = getNum<int>(1);
                std::cout << "\n\n";
                table.increase(n);
                break;

            case 9:
                str = table.condition();
                std::cout << "condition: --> " << str << "\n";
                std::cout << "\n\n";
                break;
            case 10:
                std::cout << "table: \n";
                std::cin >> table;
                break;
            default:
                std::cout << "Mistake! Enter a number [0 , 10]";
                break;
            }
        }
        catch (const std::invalid_argument& ia) {       // некорректный аргумент
            std::cerr << ia.what() << std::endl << std::endl;
        }
        catch (const std::bad_alloc& ba) {              // в случае ошибок выделения памяти
            std::cerr << "Not enough memory" << std::endl << std::endl;;
            return 1;
        }
        catch (const std::exception& e) {              // в случае прочих исключений
            std::cerr << e.what() << std::endl << std::endl;;
            return 1;
        }
    }
    return 0;
}
