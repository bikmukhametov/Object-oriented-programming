#ifndef OOPPROG1_PROG1_H
#define OOPPROG1_PROG1_H

#include <iostream>
#include <string>
#include <limits>
#include <cstring>

namespace Prog1 {
                           // структура для задания элемента
    struct Node {
        int value = 0;     // значение  
        int row = 0;       // строка
        int column = 0;    // столбец
        Node* next = nullptr;
    };

                              // структура для задания матрицы
    struct Matrix {
        int n = 0;            // количество строк
        int m = 0;            // количество столбцов 
        int number = 0;       // количество элементов
        Node* head = nullptr; // список элементов
    };

                              // шаблонная функция ввода одного числа
    template<class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while (true) {
            std::cin >> a;
            if (std::cin.eof())              // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if (std::cin.bad())         // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            else if (std::cin.fail()) {      // прочие ошибки (неправильный формат ввода)
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else if (a >= min && a <= max)   // если число входит в заданный диапазон
                return a;
            else
                std::cout << "the number is not in the range, enter again" << std::endl;;
        }
    }

    // прототипы функций
    Matrix input();                                     // ввод матрицы
    void output(const char* msg, const Matrix& matrix); // вывод матрицы
    void erase(Matrix& matrix);                         // освобождение занятой памяти
    void fillArray(int arrayIndex[], const Matrix& matrix);//инициализация массива индексов
    void fillMatrix(int arrayIndex[], Matrix& matrixFirst, Matrix& matrixSecond);//создание новой матрицы
}

#endif //OOPPROG1_PROG1_H