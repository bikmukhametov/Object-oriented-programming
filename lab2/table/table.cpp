#include "table.h"

namespace Prog2 {

	void Table:: init_vector(const Resource vector[], int count) {  //инициализация из вектора
		if ((count < 0)  || (count > 10)) {
			throw std::invalid_argument("invalid number!");
		}
		for (int i = 0; i < count; i++) {
			*this += vector[i];
		}
	}

	Table::Table(const Table& t):ks(nullptr), m_size(t.m_size), c_size(t.c_size) {		//копирующий конструктор
		ks = new Resource[t.m_size];
		std::copy(t.ks, t.ks + t.c_size, ks);
	}

	Table::Table(Table&& t) noexcept: m_size(t.m_size), c_size(t.c_size), ks(t.ks) {	//перемещающий конструктор
		t.m_size = 0;
		t.m_size = 0;
		t.ks = nullptr;
	}

	Table& Table::operator = (const Table& t) {					//копирующее присваивание (Strong exception safety)
		if (this == &t)
			return *this;
		Resource* tmp = new Resource[t.m_size];
		std::copy(t.ks, t.ks + t.c_size, tmp);
		delete[] ks;
		ks = tmp;
		m_size = t.m_size;
		c_size = t.c_size;
		return *this;
	}

	Table& Table::operator = (Table&& t) noexcept{				//перемещающее присваивание
		m_size = t.m_size;
		c_size = t.c_size;
		delete[] ks;
		ks = t.ks;
		t.ks = nullptr;
		t.m_size = 0;
		t.c_size = 0;
		return *this;
	}

	void Table::resize() {										// изменить размер
		if ((m_size == c_size) || (m_size >= c_size + 10)) {
			int new_size = 0;
			if (m_size == c_size)
				new_size = m_size + step;
			else if (m_size >= c_size + 10)
				new_size = m_size - step;
			Resource* tmp = new Resource[new_size];
			std::copy(ks, ks + c_size, tmp);
			delete[] ks;
			ks = tmp;
			m_size = new_size;
		}
	}

	Table& Table::operator += (const Resource& resource) {		// (+=) оператор
		this->resize();
		int i = c_size - 1;
		while (i >= 0 && resource < ks[i]) {
			ks[i + 1] = ks[i];
			i = i - 1;
		}
		ks[i + 1] = resource;
		c_size += 1;
		return *this;
	}

	const Resource& Table:: operator [] (const std::string& str) const{	// ([]) оператор const
		int i = binary_search(str);
		return ks[i];
	}

	Resource& Table:: operator [] (const std::string& str){				// ([]) оператор
		int i = binary_search(str);
		return ks[i];
	}

	void Table::removal(const std::string& str) {						// удаление
		int i = binary_search(str);
		for (int j = i; j < c_size - 1; j++) {
			ks[j] = ks[j + 1];
		}
		c_size--;
		this->resize();
	}

	/*int Table::binary_search(const std::string& str) const {		// бинарный поиск
		int i = 0;
		int m = c_size - 1;
		int j = -1;
		while (i <= m) {
			j = (i + m) / 2;
			if (ks[j].GetName() < str)
				i = j + 1;
			else if (ks[j].GetName() > str)
				m = j - 1;
			else {
				return j;
			}
		}
		throw std::invalid_argument("there is no such element!");
	}*/

	int Table::binary_search(const std::string& str) const {		// бинарный поиск
		Resource y;
		y.setName(str);
		Resource *r = std::lower_bound(ks, ks + c_size, y);
		if(r == ks + c_size || r->GetName() != str)
			throw std::invalid_argument("there is no such element!");
		return r - ks;
	}

	std::string Table:: condition () const {				// состояние
		if (c_size == 0)
			return "empty";
		else if (c_size == m_size)
			return "full";
		else {
			return "partially filled";
		}
	}

	void Table::rename(const std::string& old_name, const std::string& new_name) { //переименование
		int i = binary_search(old_name);
		Resource resource = ks[i];
		this->removal(old_name);
		resource.setName(new_name);
		*this += resource;
	}

	void Table::increase(int n) {								//увеличить оборот в (n) раз
		for (int i = 0; i < c_size; i++) {
			ks[i].increase(n);
		}
	}

	int Table::profit() const {									//прибыль за неделю по всем ресурсам 
		int res = 0;
		for (int i = 0; i < c_size; i++) {
			res += ks[i].profit();
		}
		return res;
	}

	std::ostream& operator << (std::ostream& c, const Table& table){	//вывод
		if (table.c_size <= 0) {
			c << "The table is empty";
			return c;
		}
		for (int i = 0; i < table.c_size; i++) {
			c << i + 1 << ". ";
			c << table.ks[i];
		}
		return c;
	}


	std::istream& operator >> (std::istream& c, Table& table){			//ввод
		Table new_table;
		Resource resource;
		int count;
		c >> count;

		for (int i = 0; i < count; i++) {
			c >> resource;
			if (c.good()) {
				new_table += resource; //поймать исключение bad_alloc
			}
			else {
				return c;
			}
		}
		table = new_table;
		return c;
	}
}