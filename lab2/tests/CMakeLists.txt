# ���� � ������� ����� Catch2 ��� ������������
# ���������� �������������� ���������� ����� �������� �������� (����. sudo># ��� ������� �� ���-����������� https://github.com/catchorg/Catch2
find_package(Catch2 2 REQUIRED)
# �������� ������������ ����� ��� ��������� ������������
add_executable(table_testing testing.cpp)
# ����������� ��������� circle � Catch2 � �����
target_link_libraries(table_testing table resource Catch2::Catch2)