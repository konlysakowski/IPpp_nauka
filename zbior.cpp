#include "zbior.h"
#include <new>
#include <random>
#include <cassert>
#include <iostream>

void Zbior::alokuj(int n)
{
	assert(n > 0);
	m_elementy = new(std::nothrow) double[n]{};
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

Zbior::Zbior(const Zbior& orginal)
	:m_liczbaElementow(orginal.m_liczbaElementow)
{
	if (orginal.m_elementy != nullptr)
	{
		alokuj(orginal.m_liczbaElementow);
		for (int i = 0; i < orginal.m_liczbaElementow; i++)
		{
			this->m_elementy[i] = orginal.m_elementy[i];
		}
	}
}

Zbior& Zbior::operator=(const Zbior& orginal)
{
	if (this != &orginal)
	{
		bool innyRozmiar = this->m_liczbaElementow != orginal.m_liczbaElementow;
		if (this->m_elementy != nullptr && innyRozmiar)
			zwolnij();
		if (orginal.m_elementy != nullptr)
		{
			if (innyRozmiar)
				alokuj(orginal.m_liczbaElementow);

			for (int i = 0; i < orginal.m_liczbaElementow; i++)
				this->m_elementy[i] = orginal.m_elementy[i];
		}
		this->m_liczbaElementow = orginal.m_liczbaElementow;
	}
	return *this;
}

Zbior::Zbior(Zbior&& orginal)
	:m_liczbaElementow(orginal.m_liczbaElementow)
{
	this->m_elementy = orginal.m_elementy;
	orginal.m_elementy = nullptr;
}

Zbior& Zbior::operator=(Zbior&& orginal)
{
	if (this != &orginal)
	{
		if (this->m_elementy != nullptr)
			zwolnij();

		this->m_elementy = orginal.m_elementy;
		this->m_liczbaElementow = orginal.m_liczbaElementow; 
		orginal.m_elementy = nullptr;
	}
	return *this;
}

void Zbior::setLiczbaElementow(size_t liczbaElementow)
{

}

void Zbior::wyswietlanie()
{
	for (size_t i = 0; i < m_liczbaElementow; i++)
		std::cout << m_elementy[i] << ", "; 
}

void testKopii()
{
	Zbior zbior1(5, 0.0, 10.0); 
	Zbior zbior2(zbior1);

	std::cerr << "Zbior 1: ";
	zbior1.wyswietlanie(); 
	
	std::cerr << "Zbior 2: ";
	zbior2.wyswietlanie();
}

void Zbiory::dodajZbior(const Zbior& zbior)
{
	zbiory.push_back(zbior);
}

void Zbiory::usunZbior(size_t n)
{
	if (n < zbiory.size())
		zbiory.erase(zbiory.begin() + n); 
}

void Zbiory::sortuj(std::function<bool(const Zbior&, const Zbior&)> predykat)
{
	std::sort(zbiory.begin(), zbiory.end(), predykat); 
}

