# установка версии CMake
cmake_minimum_required(VERSION 3.16)

# название проекта (обязательно)
project(oopprog2)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# добавление подпроекта с библиотекой


# добавление подпроекта:
add_subdirectory(table)
add_subdirectory(resource)
#add_subdirectory(tests)


# создание исполняемого файла для диалоговой программы
add_executable(main prog2.cpp )

# подключение библиотеки resource к диалоговой программе
target_link_libraries(main resource table)
