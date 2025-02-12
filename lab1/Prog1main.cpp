#include <iostream>
#include "Prog1.h"

using namespace Prog1;

                                          // основная функция
int main() {
    Matrix matrixFirst;                            // исходная матрица
    Matrix matrixSecond;                           // новая матрица
    try {
        matrixFirst = input();                     // ввод матрицы
        int* arrayIndex = new int [matrixFirst.n]; // массив с индексами max-элементов
        fillArray(arrayIndex, matrixFirst);        //инициализация массива индексов
        fillMatrix(arrayIndex, matrixFirst, matrixSecond);   //создание новой матрицы
        output("Sourced matrix", matrixFirst);     // вывод матрицы
        output("New matrix", matrixSecond);
        erase(matrixFirst);                        // освобождение памяти
        erase(matrixSecond);
        delete[] arrayIndex;
    }
    catch (const std::bad_alloc& ba) {             // в случае ошибок выделения памяти
        std::cerr << "Not enough memory" << std::endl;
        erase(matrixFirst);
        return 1;
    }
    catch (const std::exception& e) {              // в случае прочих исключений
        std::cerr << e.what() << std::endl;
        erase(matrixFirst);
       return 1;
    }
    return 0;
}