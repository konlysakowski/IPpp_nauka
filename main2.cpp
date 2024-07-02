#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

enum class Typ {mieszkalny, publiczny, komercyjny};

class Miejscowosc
{
	char nazwa[50];
public:
	
	Miejscowosc(const char* nazwa)
	{
		strncpy(this->nazwa, nazwa, 50);
	}

	const char* getNazwa() { return nazwa; }

};

class Budynek
{
	char adres[100];
	double metraz; 
	Typ typ;
	Miejscowosc miejscowosc; 
	static int licznikNiepublicznych;

	void sprawdzanieAdresu(const char* ulica, const char* numer, const char* kodPocztowy)
	{
		if (strlen(ulica) == 0 || strlen(numer) == 0 || strlen(kodPocztowy) == 0)
			throw invalid_argument("Dane adresowe niepoprawne");

		for (int i = 0; numer[i] != '\0'; i++)
		{
			if (numer[i] < '0' || numer[i] > '9')
				throw invalid_argument("Numer nie sk³ada siê z cyfr");
		}

		for (int i = 0; kodPocztowy[i] != '\0'; i++)
		{
			if (kodPocztowy[i] < '0' || kodPocztowy[i] > '9')
				throw invalid_argument("Kod pocztowy nie sk³ada siê z cyfr");
		}
	}

	void sprawdzanieMetrazu(double metry)
	{
		if (metry <= 0)
			throw invalid_argument("Niepoprawny metra¿");
	}

public:

	void setAdres(const char* ulica, const char* numer, const char* kodPocztowy)
	{ 
		sprawdzanieAdresu(ulica, numer, kodPocztowy);
		snprintf(this->adres, sizeof(adres), "%s, %s, %s", ulica, numer, kodPocztowy);
	}

	void setMetraz(double metraz) 
	{ 
		sprawdzanieMetrazu(metraz);
		this->metraz = metraz;
	}

	void setTyp(Typ typ) 
	{
		this->typ = typ; 

		if (this->typ == Typ::publiczny && typ != Typ::publiczny)
		{
			licznikNiepublicznych++;
		}
		else if (this->typ != Typ::publiczny && typ == Typ::publiczny)
		{
			licznikNiepublicznych--;
		}
	}

	void setMiejscowosc(Miejscowosc miejscowosc) { this->miejscowosc = miejscowosc; }

	const char* getAdres() { return adres; }
	double getMetraz() const { return metraz; }
	Typ getTyp() const { return typ; }
	Miejscowosc getMiejscowosc() const { return miejscowosc; }

	Budynek(const char* ulica, const char* numer, const char* kodPocztowy, double metraz, Typ typ, Miejscowosc miejscowosc)
		:miejscowosc(miejscowosc)
	{
		setAdres(ulica, numer, kodPocztowy);
		setMetraz(metraz);
		setTyp(typ);

		if (typ != Typ::publiczny)
			licznikNiepublicznych++;
	}

	~Budynek()
	{
		if (typ != Typ::publiczny)
			licznikNiepublicznych--;
	}

	virtual double podatek()
	{
		return 10.0 * metraz;
	}

	operator double()
	{
		return sqrt(2 * metraz); 
	}
};

int Budynek::licznikNiepublicznych = 0;

class Posiadlosc : public Budynek
{
	double dzialka; 

	void sprawdzanieDzialki(double dzialka)
	{
		if (dzialka <= 0)
			throw invalid_argument("Niepoprawna powierzchnia dzialki");
	}

public:

	void setDzialka(double dzialka)
	{
		sprawdzanieDzialki(dzialka);
		this->dzialka = dzialka;
	}

	double getDzialka() const { return dzialka; }

	Posiadlosc(const char* ulica, const char* numer, const char* kodPocztowy, double metraz, Typ typ, Miejscowosc miejscowosc, double dzialka)
		:Budynek(ulica, numer, kodPocztowy, metraz, typ, miejscowosc), dzialka(dzialka)
	{}

	double podatek() override
	{
		return Budynek::podatek() + 5.0 * dzialka;
	}

	bool operator==(const Posiadlosc& rhs) const
	{
		
		if (strcmp(this->getMiejscowosc().getNazwa(), rhs.getMiejscowosc().getNazwa()) == 0 && this->getMetraz() == rhs.getMetraz() && this->dzialka == rhs.dzialka)
		{
			if (this->getTyp() != rhs.getTyp())
				throw invalid_argument("Posiadlosci maja rozne typy");
			return true;
		}
	}
};


int main()
{

}