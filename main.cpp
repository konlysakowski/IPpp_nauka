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

//WERSJA 2 KOLOKWIUM PRZYKLADOWE

#include <iostream>
using namespace std;
const int ROZMIAR_NUMERU = 26;

class klient;
class konto_bankowe;
enum class aktywnosc
{
	aktywne,
	nieaktywne
};

class Klient
{
	char m_nazwa[20];
public:
	void noweKonto();
};
class konto_bankowe
{
protected:
	static int s_aktywne_konta;
	char m_numer_konta[ROZMIAR_NUMERU];
	aktywnosc m_stan;
	double m_fundusze;
	Klient* m_wlasciciel;
public:
	virtual double stanZaRok()
	{
		return m_fundusze;
	}
	char* getNumerKonta()
	{
		return m_numer_konta;
	}
	aktywnosc getStan()
	{
		return m_stan;
	}
	double getFundusze()
	{
		return m_fundusze;
	}
	Klient* getWlasciciel()
	{
		return m_wlasciciel;
	}
	void setNumerKonta(const char* numer)
	{
		for (int i = 0; i < ROZMIAR_NUMERU; i++)
		{
			//Na wypadek gdyby ktoœ poda³ za krótki numer
			if (numer[i] == NULL) { m_numer_konta[i] = 0; }
			m_numer_konta[i] = numer[i];
		}
	}
	void setStan(aktywnosc aktywnosc)
	{
		// sprawdzam czy ktoœ nie nadpisuje poprzedniej wartoœci
		if (aktywnosc == aktywnosc::aktywne && m_stan != aktywnosc)
		{
			s_aktywne_konta++;
		}
		else if (aktywnosc == aktywnosc::nieaktywne && m_stan != aktywnosc)
		{
			s_aktywne_konta--;
		}
		m_stan = aktywnosc;
	}
	void setFundusze(double fundusze)
	{
		if (fundusze < 0)
		{
			cout << "Nie mozesz wprowadzic ujemnego stanu konta!";
			m_fundusze = 0;
		}
		else { m_fundusze = fundusze; }
	}
	void setWlasciciel(Klient* wlasciciel)
	{
		m_wlasciciel = wlasciciel;
	}
	operator double()
	{
		return m_fundusze;
	}
	konto_bankowe& operator +=(double liczba)
	{
		m_fundusze += liczba;
		return *this;
	}
	konto_bankowe(const char* numer, aktywnosc aktywnosc, double fundusze, Klient* wlasciciel)
	{
		setNumerKonta(numer);
		setStan(aktywnosc);
		setFundusze(fundusze);
		setWlasciciel(wlasciciel);
	}
	~konto_bankowe()
	{
		s_aktywne_konta--;
	}
	friend ostream& operator<<(ostream& s, const konto_bankowe&);
};
void Klient::noweKonto()
{
	konto_bankowe("00000000000000000000000000", aktywnosc::aktywne, 0, this);
}
ostream& operator<<(ostream& s, const konto_bankowe& k)
{
	if (k.m_stan == aktywnosc::aktywne)
	{
		s << k.m_numer_konta << " " << k.m_wlasciciel << " : " << k.m_fundusze;
		return s;
	}
	else {
		s << k.m_numer_konta << " NIEAKTYWNE";
		return s;
	}
}
class konto_oszczedniosciowe : public konto_bankowe
{
	double m_stopa_oprocentowania;

public:

	void setStopa(double stopa)
	{
		m_stopa_oprocentowania = stopa;
	}
	konto_oszczedniosciowe(konto_bankowe knt, double stopa) : konto_bankowe(knt)
	{
		setStopa(stopa);
	}
	double stanZaRok() override
	{
		double poczatkowy = m_fundusze;
		for (int i = 1; i <= 12; i++)
		{
			poczatkowy = poczatkowy + (poczatkowy * m_stopa_oprocentowania);
		}
		return poczatkowy;
	}
};
int konto_bankowe::s_aktywne_konta = 0;
int main()
{

}


// WERSJA 3 KOLOKWIUM PRZYKLAD
#include <iostream>
enum class dopuszczenie { dopuszczony, niedopuszczony };
using namespace std;
class wlasciciel
{
	char m_nazwisko[20];

public:
	wlasciciel(const char* nazwisko)
	{
		memcpy(m_nazwisko, nazwisko, sizeof(char) * 20);
	}
};
class samochod
{
protected:
	char m_numrej_litery[3];
	int m_numrej_cyfry[5];
	int m_licznik;
	dopuszczenie m_stan;
	wlasciciel* m_posiadacz;
	static int s_ostatni_numer[5];
public:
	void setLicznik(int licznik)
	{
		if (licznik < 0) { m_licznik = 0; }
		else { m_licznik = licznik; }
	}
	int getLicznik()
	{
		return m_licznik;
	}
	void setNumRej(const char* num_rej)
	{
		for (int i = 0; i < 3; i++)
		{
			if (num_rej[i] >= 65 && num_rej[i] <= 90)
			{
				m_numrej_litery[i] = num_rej[i];
			}
			else if (num_rej[i] >= 97 && num_rej[i] <= 122)
			{
				m_numrej_litery[i] = num_rej[i] - 32;
			}
			else
			{
				cout << "Bledna rejestracja" << endl;
				memcpy(m_numrej_litery, "ZZZ", sizeof(char) * 3);
			}
		}
	}
	void setStan(dopuszczenie stan)
	{
		m_stan = stan;
	}
	dopuszczenie getStan()
	{
		return m_stan;
	}
	void setWlasciciel(wlasciciel* wlasciciel)
	{
		m_posiadacz = wlasciciel;
	}
	wlasciciel* getWlasciciel()
	{
		return m_posiadacz;
	}
};
class samochod_elektryczny : public samochod
{
	double bateria;

};
int samochod::s_ostatni_numer[5] = {};
int main()
{

}


//WERSJA 4 PRZYKLADOWE

#include <iostream>
#include <stdexcept>
#include <cstring>

using namespace std;

// Klasa Autor
class Autor {
	char nazwisko[100];
public:
	Autor(const char* nazwisko) {
		strncpy(this->nazwisko, nazwisko, sizeof(this->nazwisko) - 1);
		this->nazwisko[sizeof(this->nazwisko) - 1] = '\0';
	}
	const char* getNazwisko() const { return nazwisko; }
};

// Klasa Ksiazka
class Ksiazka {
	char tytul[100];
	int liczbaStron;
	bool dostepna;
	Autor* autor;

	static Ksiazka* wzorcowaKsiazka;

public:
	// Konstruktor argumentowy
	Ksiazka(const char* tytul, int liczbaStron, bool dostepna, Autor* autor)
		: liczbaStron(liczbaStron), dostepna(dostepna), autor(autor) {
		if (liczbaStron <= 0) throw invalid_argument("Liczba stron musi byæ dodatnia");
		if (!autor) throw invalid_argument("Ksi¹¿ka musi mieæ przypisanego autora");
		strncpy(this->tytul, tytul, sizeof(this->tytul) - 1);
		this->tytul[sizeof(this->tytul) - 1] = '\0';
	}

	// Konstruktor kopiuj¹cy
	Ksiazka(const Ksiazka& other)
		: liczbaStron(other.liczbaStron), dostepna(other.dostepna) {
		strncpy(this->tytul, other.tytul, sizeof(this->tytul) - 1);
		this->tytul[sizeof(this->tytul) - 1] = '\0';
		autor = new Autor(*other.autor);  // Tworzymy kopiê autora
	}

	// Destruktor
	~Ksiazka() {
		delete autor;  // Usuwamy autora, aby unikn¹æ wycieku pamiêci
	}

	// Konstruktor domyœlny
	Ksiazka() {
		if (!wzorcowaKsiazka) throw runtime_error("Brak wzorcowej ksi¹¿ki");
		*this = *wzorcowaKsiazka;
	}

	// Setery i getery
	void setTytul(const char* tytul) {
		strncpy(this->tytul, tytul, sizeof(this->tytul) - 1);
		this->tytul[sizeof(this->tytul) - 1] = '\0';
	}
	const char* getTytul() const { return tytul; }

	void setLiczbaStron(int liczbaStron) {
		if (liczbaStron <= 0) throw invalid_argument("Liczba stron musi byæ dodatnia");
		this->liczbaStron = liczbaStron;
	}
	int getLiczbaStron() const { return liczbaStron; }

	void setDostepna(bool dostepna) { this->dostepna = dostepna; }
	bool isDostepna() const { return dostepna; }

	void setAutor(Autor* autor) {
		if (!autor) throw invalid_argument("Ksi¹¿ka musi mieæ przypisanego autora");
		delete this->autor;  // Usuwamy starego autora, aby unikn¹æ wycieku pamiêci
		this->autor = new Autor(*autor);  // Tworzymy kopiê nowego autora
	}
	Autor* getAutor() const { return autor; }

	// Statyczne wskazanie instancji wzorcowej
	static void setWzorcowaKsiazka(Ksiazka* ksiazka) { wzorcowaKsiazka = ksiazka; }

	// Obliczanie ceny ksi¹¿ki
	virtual double obliczCene() const {
		return static_cast<double>(liczbaStron);
	}

	// Konwersja Ksiazka ? const char*
	operator const char* () const {
		char* opis = new char[300];
		snprintf(opis, 300, "Tytul: %s, Liczba stron: %d, Dostepnosc: %s, Autor: %s",
			tytul, liczbaStron, (dostepna ? "dostepna" : "niedostepna"), autor->getNazwisko());
		return opis;
	}

	// Operator ==
	bool operator==(const Ksiazka& other) const {
		return liczbaStron == other.liczbaStron &&
			strcmp(autor->getNazwisko(), other.autor->getNazwisko()) == 0 &&
			dostepna == other.dostepna;
	}
};

Ksiazka* Ksiazka::wzorcowaKsiazka = nullptr;

// Klasa EBook
class EBook : public Ksiazka {
	double rozmiarMB;

public:
	EBook(const char* tytul, int liczbaStron, bool dostepna, Autor* autor, double rozmiarMB)
		: Ksiazka(tytul, liczbaStron, dostepna, autor), rozmiarMB(rozmiarMB) {
		if (rozmiarMB <= 0) throw invalid_argument("Rozmiar eBooka musi byæ dodatni");
	}

	void setRozmiarMB(double rozmiarMB) {
		if (rozmiarMB <= 0) throw invalid_argument("Rozmiar eBooka musi byæ dodatni");
		this->rozmiarMB = rozmiarMB;
	}
	double getRozmiarMB() const { return rozmiarMB; }

	double obliczCene() const override {
		return Ksiazka::obliczCene() * 0.75;
	}
};

int main() {
	try {
		Autor* autor = new Autor("Kowalski");
		Ksiazka* ksiazkaWzorcowa = new Ksiazka("Wzorcowy Tytul", 300, true, autor);
		Ksiazka::setWzorcowaKsiazka(ksiazkaWzorcowa);

		Ksiazka ksiazkaDomyslna;
		cout << static_cast<const char*>(ksiazkaDomyslna) << endl;
		delete[] static_cast<const char*>(ksiazkaDomyslna);  // Pamiêtaj o usuniêciu zaalokowanej pamiêci

		EBook ebook("Tytul Ebooka", 200, true, autor, 1.5);
		cout << "Cena ebooka: " << ebook.obliczCene() << " PLN" << endl;

		delete autor;
		delete ksiazkaWzorcowa;
	}
	catch (const exception& e) {
		cerr << "B³¹d: " << e.what() << endl;
	}

	return 0;