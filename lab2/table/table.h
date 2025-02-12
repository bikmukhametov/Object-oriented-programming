#ifndef OOPPROG2_TABLE_H
#define OOPPROG2_TABLE_H

#include <string>
#include <iostream>
#include <compare>
#include <vector>
#include "../resource/lib.h"
#include "../resource/resource.h"


namespace Prog2 {
	class Table {
	private:
		// указатель на пространство ключей
		Resource* ks;					
		// размер таблицы
		int m_size;				
		// количество элементов
		int c_size;						
		// шаг
		static const int step = 10;		

	public:
		/*!
		@brief construct a default object.
		@param ks - pointer to the key space. nullptr by default.
		@param m_size - number of elements. 0 by default.
		@param c_size - table size. 0 by default.
		*/
		Table(): ks(nullptr), m_size(0), c_size(0){};


		/*!
		@brief copying constructor.
		@param t - copy object.
		@throws std::bad_alloc - in case of memory shortage
		*/
		Table(const Table& t);									// копирующий конструктор


		/*!
		@brief moving constructor.
		@param t - moving object.
		*/
		Table(Table&& t) noexcept;								// перемещающий конструктор


		/*!
		@brief destructor. frees up the memory allocated for the table.
		*/
		~Table() { delete[] ks; m_size = 0; c_size = 0; };		// деструктор


		/*!
		@brief Get the number of elements.
		@returns m_size -  number of elements.
		*/
		int Get_m_size() const { return m_size; }

		/*!
		@brief Get the table size.
		@returns c_size - table size.
		*/
		int Get_c_size() const { return c_size; }


		/*!
		@brief Get pointer to the key space.
		@returns ks - pointer to the key space.
		*/
		Resource* Get_ks() const { return ks; }

		/*!
		@brief copying assignment of a table.
		@param t - constant reference to the table.
		@returns reference to the table.
		@throws std::bad_alloc - in case of memory shortage
		*/
		Table& operator = (const Table& t);						// копирующее присваивание


		/*!
		@brief moving table assignment.
		@param t - reference to the table.
		@returns reference to the table.
		*/
		Table& operator = (Table&& t) noexcept;					// перемещающее присваивание


		/*!
		@brief adding a resource to a table.
		@param resource - constant reference to the resource.
		@returns reference to the table.
		@throws std::bad_alloc - in case of memory shortage
		*/
		Table& operator += (const Resource& resource);				// (+) добавление элеменнта


		/*!
		@brief resource search operator in the table by name. the state of the class may change.
		@param str - constant reference to the name.
		@returns reference to the resource.
		@throws std::invalid_argument - when the element does not exist.
		*/
		Resource& operator [] (const std::string& str);				// [] по наименованию


		/*!
		@brief resource search operator in the table by name. the state of the class cannot change.
		@param str - constant reference to the name.
		@returns reference to the resource.
		@throws std::invalid_argument - when the element does not exist.
		*/
		const Resource& operator [] (const std::string& str) const;	// [] по наименованию 


		/*!
		@brief deletion by name.
		@param str - constant reference to the name.
		@throws std::invalid_argument - when the element does not exist.
		@throws std::bad_alloc - in case of memory shortage.
		*/
		void removal (const std::string& str);					// удаление по наименованию 


		/*!
		@brief binary search for a resource in a table.
		@param str - constant reference to the name.
		@throws std::invalid_argument - when the element does not exist.
		*/
		int binary_search(const std::string& str) const;		// двоичный поиск


		/*!
		@brief memory allocation or release of 10 items.
		@throws std::bad_alloc - in case of memory shortage.
		*/
		void resize();											// изменить размер


		/*!
		@brief table status (empty, partially filled or full)
		@returns string
		*/
		std::string condition() const;											// состояние (пустая, частично заполнена или полная)


		/*!
		@brief initializing a table with a resource array.
		@param vector - array of resources.
		@param count - the number of resources specified.
		@throws std::invalid_argument - when the element does not exist.
		@throws std::bad_alloc - in case of memory shortage.
		*/
		void init_vector(const Resource vector[], int count);					// инициализация из вектора


		/*!
		@brief renaming a given resource.
		@param old_name - current name.
		@param new_name - new name.
		@throws std::invalid_argument - when the element does not exist.
		@throws std::bad_alloc - in case of memory shortage.
		*/
		void rename(const std::string& old_name, const std::string& new_name);	// переименование ресурса


		/*!
		@brief increases the turnover of all table resources.
		@param n - how many times to increase.
		throws std::invalid_argument("illegal argument"), when n < 1.
		*/
		void increase(int n);											        // увеличить на (n) раз


		/*!
		@brief profit per week for all resources.
		@returns profit for the week.
		*/
		int profit() const;														// прибыль в неделю по всем ресурсам


		/*!
		@brief table output function.
		@param c - flow into the output signal.
		@param table - constant reference to the table.
		@returns flow into the output signal.
		*/
		friend std::ostream& operator << (std::ostream& c, const Table& table); // вывод

		// std::ostream& operator << (std::ostream& c);


		/*!
		@brief table input function.
		@param c - flow into the input signal.
		@param table - reference to the table.
		@returns flow into the input signal.
		*/
		friend std::istream& operator >> (std::istream& c, Table& table);		// ввод
	};
}

#endif //TABLE_H