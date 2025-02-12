cmake_minimum_required(VERSION 3.16)

# название проекта (обязательно)
project(oopprog3)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# добавление подпроекта:
add_subdirectory(ship)
add_subdirectory(cargo_object)
add_subdirectory(military_facility)
add_subdirectory(ship_types)
add_subdirectory(table)
add_subdirectory(mission)
add_subdirectory(service)
add_subdirectory(repository)
add_subdirectory(user_interface)

# создание исполняемого файла для диалоговой программы
add_executable(main prog3.cpp)

target_link_libraries(main ship military_facility cargo_object guarded_transport_ship pirate_ship security_ship transport_ship table mission service repository user_interface)