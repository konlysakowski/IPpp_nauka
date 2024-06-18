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
};

class KontoBankowe
{
protected:
	int numerKonta;
	double stanKonta;
	Aktywnosc aktywnosc;
	Klient* wlasciciel; 
	static int aktywneKonta;
public:
	void setNumerKonta(int numer) { numerKonta = numer; }
	void setStanKonta(double stan) { stanKonta = stan; }
	void setAktywnosc(Aktywnosc _aktywnosc) { aktywnosc = _aktywnosc; }
	void setWlasciciel(Klient* _wlasciciel) { wlasciciel = _wlasciciel; }

	int getNumerKonta() { return numerKonta; }
	double getStanKonta() { return stanKonta; }
	Aktywnosc getAktywnosc() { return aktywnosc; }
	Klient* getWlasciciel() { return wlasciciel; }

	KontoBankowe(int numer, double stan, Aktywnosc aktyw, Klient* wlasc)
		:numerKonta(numer), stanKonta(stan), aktywnosc(aktyw), wlasciciel(wlasc)
	{
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

};

class KontoOszczednosciowe : public KontoBankowe
{
private:
	double stopaOprocentowania; 
public:
	void setStopaOprocentowania(double stopa) { stopaOprocentowania = stopa; }
	
	double getStopaOprocentowania() { return stopaOprocentowania; }

	KontoOszczednosciowe(int numer, double stan, Aktywnosc aktyw, Klient* wlasc, double stopa)
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

int main()
{

}

