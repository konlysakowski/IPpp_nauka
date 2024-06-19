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
	char numerKonta[27];
	double stanKonta;
	Aktywnosc aktywnosc;
	Klient* wlasciciel; 
	static int aktywneKonta;

	bool czyNumerKontaPoprawny(const char* numer) { if (strlen(numer) != 26){ return true; }else{ return false; } }
public:
	void setNumerKonta(const char* numer) 
	{ 
		if (czyNumerKontaPoprawny(numer))
		{
			throw invalid_argument("Niepoprawny numer konta");
		}

		strncpy(numerKonta, numer, 27); 
		
	}
	void setStanKonta(double stan) { stanKonta = stan; }
	void setAktywnosc(Aktywnosc _aktywnosc) 
	{ 
		if (aktywnosc != _aktywnosc)
		{
			if (_aktywnosc == Aktywnosc::aktywny)
			{
				aktywneKonta++;
			}
			else
			{
				aktywneKonta--;
			}
			aktywnosc = _aktywnosc;
		}
	}
	void setWlasciciel(Klient* _wlasciciel) { wlasciciel = _wlasciciel; }

	const char* getNumerKonta() { return numerKonta; }
	double getStanKonta() { return stanKonta; }
	Aktywnosc getAktywnosc() { return aktywnosc; }
	Klient* getWlasciciel() { return wlasciciel; }

	KontoBankowe(const char* numer, double stan, Aktywnosc aktyw, Klient* wlasc)
	{

		setNumerKonta(numer);
		setStanKonta(stan);
		setAktywnosc(aktyw);
		setWlasciciel(wlasc);

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
	return os;
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

	KontoBankowe k1("92345678901234567890123453", 1500.23, Aktywnosc::aktywny, klient1);
	KontoBankowe k2("12546786543247890756432456", 12342.45, Aktywnosc::aktywny, klient2);

	cout << k1 << endl;
	cout << k2 << endl; 

	k1.prognoza(); 
	k2.prognoza(); 

}

