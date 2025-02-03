#include <new>
#include <random>
#include <cassert>
#include <algorithm>
#include <iostream>

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

	Zbior(const Zbior& org) = delete; //konstruktor kopiuj¹cy 
	Zbior(Zbior&& org); //konstruktor przenosz¹cy
	Zbior& operator=(const Zbior& org); //kopiuj¹cy operator
	Zbior& operator=(Zbior&& org) = delete; //przenosz¹cy operator

	friend void testKopiowaniaZRotacja();

	size_t getLiczbaElementow();

};

void Zbior::alokuj(int n)
{
	assert(n > 0);
	m_elementy = new(std::nothrow) double[n] {};
	m_liczbaElementow = n;

}

void Zbior::zwolnij()
{
	delete[] m_elementy;
}

Zbior::Zbior(size_t liczElem, double dGran, double gGran)
{
	alokuj(liczElem);
	std::uniform_real_distribution<double> zakres(dGran, gGran);
	std::random_device generator;
	for (int elem = 0; elem < liczElem; elem++)
		m_elementy[elem] = zakres(generator);
}

Zbior::Zbior(Zbior&& org)
	:m_liczbaElementow(org.m_liczbaElementow)
{
	this->m_elementy = org.m_elementy;
	org.m_elementy = nullptr;
	this->m_dolnaGranica = org.m_dolnaGranica;
	org.m_dolnaGranica = NULL;
	this->m_gornaGranica = org.m_gornaGranica;
	org.m_gornaGranica = NULL;
}

Zbior& Zbior::operator=(const Zbior& org)
{
	if (this != &org)
	{
		if ((this->m_elementy != nullptr) && (this->m_liczbaElementow != org.m_liczbaElementow))
		{
			zwolnij();
		}
		if (org.m_elementy != nullptr)
		{
			if (this->m_liczbaElementow != org.m_liczbaElementow)
				alokuj(org.m_liczbaElementow);

			for (int i = 0; i < org.m_liczbaElementow; i++)
				this->m_elementy[i] = org.m_elementy[i];

			this->m_dolnaGranica = org.m_dolnaGranica;
			this->m_gornaGranica = org.m_gornaGranica;

			std::rotate(m_elementy, m_elementy + 2, m_elementy + m_liczbaElementow);
		}
		this->m_liczbaElementow = org.m_liczbaElementow;
	}
	return *this;
}

void testKopiowaniaZRotacja()
{
	Zbior zb1(3, 0.0, 10.0), zb2(5, 0.0, 0.0);
	zb2 = zb1;

	if (zb1.m_elementy[0] == zb2.m_elementy[1] && zb1.m_elementy[1] == zb2.m_elementy[2] && zb1.m_elementy[2] == zb2.m_elementy[0])
		std::cerr << "Test kopii z rotacj¹: OK" << std::endl;
	else
		std::cerr << "Test kopii z rotacj¹: FAIL" << std::endl;
}

size_t Zbior::getLiczbaElementow()
{
	return m_liczbaElementow;
}

class Agregat
{
	static const int MAX_LICZBA_ZBIOROW = 10;
	Zbior* zbiory[MAX_LICZBA_ZBIOROW];
	int liczbaZbiorow;
public:
	void dodajZbior(Zbior& zbior)
	{
		for (int i = 0; i < liczbaZbiorow; i++)
		{
			if (zbiory[i] == &zbior)
				return;
		}

		if (liczbaZbiorow < MAX_LICZBA_ZBIOROW)
			zbiory[liczbaZbiorow++] = &zbior;
		else
			std::cout << "BRAK WOLNYCH MIEJSC" << std::endl;
	}

	void usunZbior(Zbior& zbior)
	{
		for (int i = 0; i < liczbaZbiorow; i++)
		{
			if (zbiory[i] == &zbior)
			{
				zbiory[i] == zbiory[--liczbaZbiorow];
				zbiory[liczbaZbiorow] = nullptr;
			}
		}
	}

};

class Funktor
{
	int m_stan = 0;
public:
	Funktor(int stan) : m_stan(stan) {}

	bool operator()(Zbior& zbior)
	{
		return zbior.getLiczbaElementow() > m_stan;
	}

};

void testSpelnieniaWarunku()
{
	Zbior zbior(10, 1.0, 10.0);
	Funktor funktor(5);

	bool wynik = funktor(zbior);

	if (wynik)
		std::cerr << "Test spelnienia warunku: OK" << std::endl;
	else
		std::cerr << "Test spelnienia warunku: FALSE" << std::endl;
}

void testBrakuSpelnieniaWarunku()
{
	Zbior zbior(5, 1.0, 6.0);
	Funktor funktor(10);

	bool wynik = funktor(zbior);

	if (!wynik)
		std::cerr << "Test braku spelnienia: OK" << std::endl;
	else
		std::cerr << "Test braku spelnienia: FALSE" << std::endl;
}

int main()
{
	testKopiowaniaZRotacja();
	testSpelnieniaWarunku();
	testBrakuSpelnieniaWarunku();
}