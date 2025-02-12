#include <iostream>
#include "Prog1.h"

using namespace Prog1;

                                          // �������� �������
int main() {
    Matrix matrixFirst;                            // �������� �������
    Matrix matrixSecond;                           // ����� �������
    try {
        matrixFirst = input();                     // ���� �������
        int* arrayIndex = new int [matrixFirst.n]; // ������ � ��������� max-���������
        fillArray(arrayIndex, matrixFirst);        //������������� ������� ��������
        fillMatrix(arrayIndex, matrixFirst, matrixSecond);   //�������� ����� �������
        output("Sourced matrix", matrixFirst);     // ����� �������
        output("New matrix", matrixSecond);
        erase(matrixFirst);                        // ������������ ������
        erase(matrixSecond);
        delete[] arrayIndex;
    }
    catch (const std::bad_alloc& ba) {             // � ������ ������ ��������� ������
        std::cerr << "Not enough memory" << std::endl;
        erase(matrixFirst);
        return 1;
    }
    catch (const std::exception& e) {              // � ������ ������ ����������
        std::cerr << e.what() << std::endl;
        erase(matrixFirst);
       return 1;
    }
    return 0;
}