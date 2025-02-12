#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <string>
#include <limits>
#include <cstring>


template<class T>
T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max(), T factor = 1) {
    T a;
    while (true) {
        std::cin >> a;
        if (std::cin.eof())              // ��������� ����� �����
            throw std::runtime_error("Failed to read number: EOF");
        else if (std::cin.bad())         // ���������� ��������������� ������ �������� ������
            throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
        else if (std::cin.fail()) {      // ������ ������ (������������ ������ �����)
            std::cin.clear();            // ������� ����� ��������� ������
            // ���������� ��� ������� �� ����� ������
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You are wrong! repeat please: --> ";
        }
        else if ((a >= min) && (a <= max) && (a % factor == 0))   // ���� ����� ������ � �������� ��������
            return a;
        else
            std::cout << "the number is not in the range, enter again: --> ";
    }
}
#endif //LIB_H