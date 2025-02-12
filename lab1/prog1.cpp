#include <iostream>
#include <climits>
#include "Prog1.h"

namespace Prog1 {
    // функция ввода
    Matrix input() {
        Matrix matrix;                                       // выделение памяти для матрицы
        try {
            std::cout << "Enter number of lines: --> ";      // вводим количество строк
            matrix.n = getNum<int>(0);
            std::cout << "Enter the number of columns: --> ";// вводим количество столбцов
            matrix.m = getNum<int>(0);
            std::cout << "Enter the number of items: --> ";  // вводим количество элементов
            matrix.number = getNum<int>(0);

            for (int i = 0; i < matrix.number; i++) {
                std::cout << "Enter a value: --> ";
                int value = getNum<int>();
                std::cout << "Enter a row: --> ";
                int row = getNum<int>(0, matrix.n - 1);
                std::cout << "Enter a column: --> ";
                int column = getNum<int>(0, matrix.m - 1);
                std::cout << std::endl;

                Node* item = matrix.head;                    //проверка на повторение
                int flag = 0;
                while (item != nullptr) {
                    if ((item->row == row) && (item->column == column)) { 
                        i--;
                        flag = 1;
                        std::cout << "repeat, enter again!" << std::endl;
                    }
                    item = item->next;
                }
                if (value == 0) {
                    flag = 1;
                    matrix.number -= 1;
                    i -= 1;
                }

                if (flag == 0) {
                    Node* nodePrevious = matrix.head;
                    Node* node = new Node{ value, row, column };
                    node->next = nodePrevious;
                    matrix.head = node;
                }
            }
        }
        catch (...)
        {
            erase(matrix);      // очищаем уже выделенную память
            throw;              // перекидываем то же исключение дальше
        }
        return matrix;
    }

    // функция вывода
    void output(const char* msg, const Matrix& matrix) {
        std::cout << msg << ":" << std::endl;
        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.m; j++) {
                Node* node = matrix.head;
                int value = 0;
                for (int k = 0; k < matrix.number; k++) {
                    if (node->row == i && node->column == j) {
                        value = node->value;
                    }
                    node = node->next;
                }
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
    }

    // функция освобождения занятой памяти
    void erase(Matrix& matrix) {
        if (matrix.head != nullptr) {
            while (matrix.head != nullptr) {
                Node* node = matrix.head;
                matrix.head = node->next;
                delete node;
                node = nullptr;
            }
            delete matrix.head;
        }
        matrix.head = nullptr;
        matrix.n = 0;
        matrix.m = 0;
        matrix.number = 0;
    }

    // функция вычисления индексов max элементов строки
    void fillArray(int arrayIndex[], const Matrix& matrix) {
        int* arrayValue = new int[matrix.n];
        for (int j = 0; j < matrix.n; j++) {
            arrayIndex[j] = INT_MIN;
            arrayValue[j] = INT_MIN;
        }
        Node* node = matrix.head;
        for (int i = 0; i < matrix.number; i++) {
            if ((node->value > arrayValue[node->row]) ||
                ((node->value == arrayValue[node->row]) && (node->column > arrayIndex[node->row]))) {
                arrayIndex[node->row] = node->column;
                arrayValue[node->row] = node->value;
            }
            node = node->next;
        }
        delete[] arrayValue;
    }
    //создание новой матрицы
    void fillMatrix(int arrayIndex[], Matrix& matrixFirst, Matrix& matrixSecond) {
        Node* node = matrixFirst.head;
        for (int i = 0; i < matrixFirst.number; i++) {
            if (node->column <= arrayIndex[node->row]) {
                Node* item = new Node{ node->value, node->row, node->column, nullptr };
                if (matrixSecond.head == nullptr) {
                    matrixSecond.head = item;
                }
                else {
                    Node* itemPrevious = matrixSecond.head;
                    item->next = itemPrevious;
                    matrixSecond.head = item;
                }
                matrixSecond.number++;
            }
            node = node->next;
        }
        matrixSecond.n = matrixFirst.n;
        matrixSecond.m = matrixFirst.m;
    }
}