# ��������� ������ CMake
cmake_minimum_required(VERSION 3.16)

# �������� ������� (�����������)
project(oopprog2)

# ��������� ��������� ����� - C++20
set(CMAKE_CXX_STANDARD 20)

# ��������� ������ �����������: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# ���������� ���������� � �����������


# ���������� ����������:
add_subdirectory(table)
add_subdirectory(resource)
#add_subdirectory(tests)


# �������� ������������ ����� ��� ���������� ���������
add_executable(main prog2.cpp )

# ����������� ���������� resource � ���������� ���������
target_link_libraries(main resource table)
