# ищем в системе пакет Catch2 дл€ тестировани€
# необходимо предварительно установить через пакетный менеджер (напр. sudo># или скачать из гит-репозитори€ https://github.com/catchorg/Catch2
find_package(Catch2 2 REQUIRED)
# создание исполн€емого файла дл€ программы тестировани€
add_executable(table_testing testing.cpp)
# подключение библиотек circle и Catch2 к тесту
target_link_libraries(table_testing table resource Catch2::Catch2)