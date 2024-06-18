#include <iostream>

using namespace std;

enum class Aktywnosc
{
	aktywny,
	nieaktywny
};


class Klient
{
	char nazwaKlienta[50];
public:

	Klient(const char* nazwa)
	{
		strncpy(nazwaKlienta, nazwa, 50);
	}
};

class KontoBankowe
{
protected:
	char numerKonta[26];
	double stanKonta;
	Aktywnosc aktywnosc;
	Klient* wlasciciel; 
	static int aktywneKonta;

	bool czyNumerKontaPoprawny(const char* numer) { return strlen(numer) == 26; }
public:
	void setNumerKonta(const char* numer) 
	{ 
		if (!czyNumerKontaPoprawny(numer))
		{
			throw invalid_argument("Niepoprawny numer konta");
		}

		strncpy(numerKonta, numer, 26); 
	}
	void setStanKonta(double stan) { stanKonta = stan; }
	void setAktywnosc(Aktywnosc _aktywnosc) { aktywnosc = _aktywnosc; }
	void setWlasciciel(Klient* _wlasciciel) { wlasciciel = _wlasciciel; }

	const char* getNumerKonta() { return numerKonta; }
	double getStanKonta() { return stanKonta; }
	Aktywnosc getAktywnosc() { return aktywnosc; }
	Klient* getWlasciciel() { return wlasciciel; }

	KontoBankowe(const char* numer, double stan, Aktywnosc aktyw, Klient* wlasc)
		:stanKonta(stan), aktywnosc(aktyw), wlasciciel(wlasc)
	{
		if (!czyNumerKontaPoprawny(numer))
		{
			throw invalid_argument("Niepoprawny numer konta");
		}

		setNumerKonta(numer);

		if (aktywnosc == Aktywnosc::aktywny)
		{
			aktywneKonta++;
		}
	}

	~KontoBankowe()
	{
		aktywneKonta--;
	}

	virtual void prognoza()
	{
		cout << "Prognozowany stan konta: " << stanKonta * 0 + stanKonta << endl;
	}

	operator double()
	{
		return stanKonta;
	}

	void operator+=(double kwota)
	{
		stanKonta += kwota;
	}

	friend ostream& operator<<(ostream&, const KontoBankowe&);

};

ostream& operator<<(ostream& os, const KontoBankowe& k)
{
	if (k.aktywnosc == Aktywnosc::aktywny)
	{
		os << "[" << k.numerKonta << "]" << "[" << k.wlasciciel << "]" << " : " << "[" << k.stanKonta << "]" << endl; 
	}
	else
	{
		os << "[" << k.numerKonta << "] " << "NIEAKTYWNE" << endl;
	}
}

class KontoOszczednosciowe : public KontoBankowe
{
private:
	double stopaOprocentowania; 
public:
	void setStopaOprocentowania(double stopa) { stopaOprocentowania = stopa; }
	
	double getStopaOprocentowania() { return stopaOprocentowania; }

	KontoOszczednosciowe(const char* numer, double stan, Aktywnosc aktyw, Klient* wlasc, double stopa)
		:KontoBankowe(numer, stan, aktyw, wlasc)
	{
		if (stopa > 0)
		{
			setStopaOprocentowania(stopa);
		}
	}

	void prognoza() override
	{
		cout << "Prognozowany stan konta: " << stanKonta * stopaOprocentowania + stanKonta << endl;
	}

};

KontoBankowe KlientDoKontaBankowego(Klient* klient)
{
	return { "3276891218892998768190119", 0.0, Aktywnosc::aktywny, klient };
}

int main()
{
	Klient klient1("Mateusz Janek"), klient2("Tadeusz Norek");

	KontoBankowe k1("2211112223333444555326666", 1500.45, Aktywnosc::aktywny, klient1);


	

}

