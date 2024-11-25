#pragma once
#include <vector>
#include <functional>

class Zbior
{
	size_t m_liczbaElementow = 0;
	double* m_elementy = nullptr;
	double m_dolnaGranica = 0;
	double m_gornaGranica = 0;
	void alokuj(int);
	void zwolnij();
public:
	Zbior(size_t liczElem, double dGran, double gGran);
	~Zbior() {} 

	Zbior(const Zbior& orginal);
	Zbior& operator=(const Zbior& orginal);

	Zbior(Zbior&& orginal);
	Zbior& operator=(Zbior&& orginal);

	void setLiczbaElementow(size_t); 

	void wyswietlanie(); 

};

class Zbiory
{
	std::vector<Zbior> zbiory; 
public: 
	void dodajZbior(const Zbior& zbior);
	void usunZbior(size_t n);

	void sortuj(std::function<bool(const Zbior&, const Zbior&)> predykat); 
};

