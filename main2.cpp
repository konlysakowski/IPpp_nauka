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

    Zbior(Zbior&& orginal) noexcept;
    Zbior& operator=(Zbior&& orginal);

    friend void testTraceniaZasobu();
    friend void testPrawidlowegoPrzypisaniaZasobu();

    size_t getLiczbaElementow() const { return m_liczbaElementow; }

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

Zbior::Zbior(Zbior&& orginal) 
    :m_liczbaElementow(orginal.m_liczbaElementow)
{
    this->m_elementy = orginal.m_elementy;
    orginal.m_elementy = nullptr;
    this->m_dolnaGranica = orginal.m_dolnaGranica;
    orginal.m_dolnaGranica = NULL;
    this->m_gornaGranica = orginal.m_gornaGranica;
    orginal.m_gornaGranica = NULL;
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
        this->m_dolnaGranica = orginal.m_dolnaGranica;
        orginal.m_dolnaGranica = NULL;
        this->m_gornaGranica = orginal.m_gornaGranica;
        orginal.m_gornaGranica = NULL;
    }
    return *this;
}

class Agregat
{
    std::vector<Zbior> zbiory; 
public:
    void dodajZbior(Zbior&& zbior)
    {
        zbiory.push_back(std::move(zbior));
    }
    void usunZbior()
    {
        if (!zbiory.empty())
            zbiory.pop_back();
    }
    std::vector<Zbior> getZbiory() const { return zbiory; }
};

void testTraceniaZasobu()
{
    Zbior zb1(5, 0.0, 5.0), zb2(1.0, 0.0, 0.0);
    zb2 = std::move(zb1);

    if (zb1.m_elementy == nullptr && zb1.m_liczbaElementow == NULL && zb1.m_dolnaGranica == NULL && zb1.m_gornaGranica == NULL)
        std::cerr << "Test tracenia zasobu: OK" << std::endl;
    else
        std::cerr << "Test tracenia zasobu: FAIL" << std::endl;
}

void testPrawidlowegoPrzypisaniaZasobu()
{
    Zbior zb1(5, 0.0, 10.0), zb2(1, 0.0, 0.0); 
    zb2 = std::move(zb1);

    if(zb2.m_elementy != nullptr && zb2.m_liczbaElementow == 5 && zb2.m_dolnaGranica == 0.0 && zb2.m_gornaGranica == 10.0)
        std::cerr << "Test prawidlowego przypisania: OK" << std::endl;
    else
        std::cerr << "Test prawidlowego przypisania: FAIL" << std::endl;
}


class Funktor
{
    double m_dolnaGranica;
    double m_gornaGranica;
public:
    Funktor(double dolGran, double gorGran) : m_dolnaGranica(dolGran), m_gornaGranica(gorGran) {}

    bool operator()(const Zbior& zbior)
    {
        return  zbior.getLiczbaElementow() >= m_dolnaGranica && zbior.getLiczbaElementow() <= m_gornaGranica;
    }
};


int main()
{
    Agregat agregat;
    agregat.dodajZbior(Zbior(5, 0.0, 10.0));
    agregat.dodajZbior(Zbior(8, 1.0, 12.0));
    agregat.dodajZbior(Zbior(4, 2.0, 5.0));

    Funktor funktor(2.0, 6.0);

    int licznik = 0;
    for (auto& zbior : agregat.getZbiory())
        if (funktor(zbior))
            licznik++;


    std::cout << "Licznik: " << licznik << std::endl;


    testTraceniaZasobu();
    testPrawidlowegoPrzypisaniaZasobu();
}


















































/*
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








//WERSJA 2 TELEFON S4

#include <iostream>
#include <cstring>

using namespace std;

class Operator {
private:
    char name[50];
public:
    Operator(const char* name) {
        strncpy(this->name, name, 49);
        this->name[49] = '\0';
    }

    const char* getName() const {
        return name;
    }
};

class Telefon {
public:
    enum Stan { Wlaczony, Wylaczony, Zablokowany };

private:
    char numer[12];
    int stanBaterii; // 0-100%
    Stan stan;
    const Operator& operator_;
    const int pin;
    static int licznikZablokowanych;

    void validateBateria(int bateria) {
        if (bateria < 0 || bateria > 100) {
            throw invalid_argument("Stan baterii musi byæ w przedziale 0-100%");
        }
    }

    void validateNumer(const char* numer) {
        if (strlen(numer) != 11 || numer[3] != '-' || numer[7] != '-') {
            throw invalid_argument("Numer musi byæ w formacie XXX-XXX-XXX");
        }
    }

public:
    Telefon(const char* numer, int stanBaterii, Stan stan, const Operator& operator_, int pin)
        : operator_(operator_), pin(pin) {
        validateNumer(numer);
        validateBateria(stanBaterii);
        strncpy(this->numer, numer, 12);
        this->stanBaterii = stanBaterii;
        this->stan = (stan == Zablokowany) ? Wylaczony : stan;
    }

    const char* getNumer() const {
        return numer;
    }

    void setNumer(const char* numer) {
        validateNumer(numer);
        strncpy(this->numer, numer, 12);
    }

    int getStanBaterii() const {
        return stanBaterii;
    }

    void setStanBaterii(int stanBaterii) {
        validateBateria(stanBaterii);
        this->stanBaterii = stanBaterii;
        if (this->stanBaterii == 0) {
            setStan(Wylaczony);
        }
    }

    Stan getStan() const {
        return stan;
    }

    void setStan(Stan stan, int pin = -1) {
        if (this->stan == Zablokowany && stan != Zablokowany && pin != this->pin) {
            throw invalid_argument("Niepoprawny PIN");
        }
        if (this->stan == Zablokowany && stan != Zablokowany) {
            licznikZablokowanych--;
        }
        else if (this->stan != Zablokowany && stan == Zablokowany) {
            licznikZablokowanych++;
        }
        this->stan = stan;
    }

    const Operator& getOperator() const {
        return operator_;
    }

    static int getLicznikZablokowanych() {
        return licznikZablokowanych;
    }

    virtual int czasDzialania() const {
        return stanBaterii * 20; // 20 minut na ka¿dy procent baterii
    }

    virtual ~Telefon() {
        if (stan == Zablokowany) {
            licznikZablokowanych--;
        }
    }

    Telefon& operator+=(int doladowanie) {
        setStanBaterii(stanBaterii + doladowanie);
        return *this;
    }
};

int Telefon::licznikZablokowanych = 0;

class SystemOperacyjny {
private:
    char nazwa[50];
    double kosztObliczeniowy; // 0.0 - 1.0

    void validateKosztObliczeniowy(double koszt) {
        if (koszt < 0.0 || koszt > 1.0) {
            throw invalid_argument("Koszt obliczeniowy musi byæ w przedziale 0.0 - 1.0");
        }
    }

public:
    SystemOperacyjny(const char* nazwa, double kosztObliczeniowy) {
        validateKosztObliczeniowy(kosztObliczeniowy);
        strncpy(this->nazwa, nazwa, 49);
        this->nazwa[49] = '\0';
        this->kosztObliczeniowy = kosztObliczeniowy;
    }

    const char* getNazwa() const {
        return nazwa;
    }

    double getKosztObliczeniowy() const {
        return kosztObliczeniowy;
    }
};

class Smartfon : public Telefon {
private:
    SystemOperacyjny system;

public:
    Smartfon(const char* numer, int stanBaterii, Stan stan, const Operator& operator_, int pin, const SystemOperacyjny& system)
        : Telefon(numer, stanBaterii, stan, operator_, pin), system(system) {}

    const SystemOperacyjny& getSystem() const {
        return system;
    }

    void setSystem(const SystemOperacyjny& system) {
        this->system = system;
    }

    int czasDzialania() const override {
        return getStanBaterii() * (20 - 10 * system.getKosztObliczeniowy());
    }
};

Smartfon konwertujNaSmartfon(const Telefon& telefon, const SystemOperacyjny& system) {
    return Smartfon(telefon.getNumer(), telefon.getStanBaterii(), telefon.getStan(), telefon.getOperator(), 0, system);
}


*/






/*

//WERSJA 3 S6

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

class Wlasciciel {
private:
    char nazwisko[50];
public:
    Wlasciciel(const char* nazwisko) {
        strncpy(this->nazwisko, nazwisko, 49);
        this->nazwisko[49] = '\0';
    }

    const char* getNazwisko() const {
        return nazwisko;
    }
};

class Samochod {
public:
    enum StanDopuszczenia { Dopuszczony, Niedopuszczony };

private:
    char numerRejestracyjny[10];
    int licznik; // stan licznika
    StanDopuszczenia stan;
    const Wlasciciel& wlasciciel;
    static int ostatniNumerRejestracyjny;

    void validateNumerRejestracyjny(const char* numer) {
        if (strlen(numer) != 8 || !isalpha(numer[0]) || !isalpha(numer[1]) || !isalpha(numer[2]) || numer[3] != '-') {
            throw invalid_argument("Numer rejestracyjny musi byæ w formacie XXX-YYYYY");
        }
    }

    void generateNumerRejestracyjny(const char* xxx) {
        validateNumerRejestracyjny(xxx);
        strncpy(numerRejestracyjny, xxx, 4);
        snprintf(numerRejestracyjny + 4, 6, "%05d", ++ostatniNumerRejestracyjny);
    }

public:
    Samochod(const char* xxx, int licznik, StanDopuszczenia stan, const Wlasciciel& wlasciciel)
        : wlasciciel(wlasciciel) {
        generateNumerRejestracyjny(xxx);
        this->licznik = licznik;
        this->stan = stan;
    }

    const char* getNumerRejestracyjny() const {
        return numerRejestracyjny;
    }

    void setNumerRejestracyjny(const char* xxx) {
        generateNumerRejestracyjny(xxx);
    }

    int getLicznik() const {
        return licznik;
    }

    void setLicznik(int licznik) {
        this->licznik = licznik;
    }

    StanDopuszczenia getStan() const {
        return stan;
    }

    void setStan(StanDopuszczenia stan) {
        this->stan = stan;
    }

    const Wlasciciel& getWlasciciel() const {
        return wlasciciel;
    }

    virtual int zasieg() const {
        return 800; // Sta³y zasiêg dla zwyk³ego samochodu
    }

    operator double() const {
        double wspSparw = (stan == Dopuszczony) ? 1.0 : 0.2;
        double wartosc = (10000.0 - 0.1 * licznik) * wspSparw; // Zak³adaj¹c WAR_POCZ = 10000
        return max(wartosc, 400.0);
    }

    bool operator==(const Samochod& other) const {
        return strncmp(numerRejestracyjny, other.numerRejestracyjny, 3) == 0 && abs(licznik - other.licznik) <= 10;
    }
};

int Samochod::ostatniNumerRejestracyjny = 0;

class SamochodElektryczny : public Samochod {
private:
    int stanBaterii; // 0-100%

    void validateStanBaterii(int stanBaterii) {
        if (stanBaterii < 0 || stanBaterii > 100) {
            throw invalid_argument("Stan baterii musi byæ w przedziale 0-100%");
        }
    }

public:
    SamochodElektryczny(const char* xxx, int licznik, StanDopuszczenia stan, const Wlasciciel& wlasciciel, int stanBaterii)
        : Samochod(xxx, licznik, stan, wlasciciel) {
        validateStanBaterii(stanBaterii);
        this->stanBaterii = stanBaterii;
    }

    int getStanBaterii() const {
        return stanBaterii;
    }

    void setStanBaterii(int stanBaterii) {
        validateStanBaterii(stanBaterii);
        this->stanBaterii = stanBaterii;
    }

    int zasieg() const override {
        return static_cast<int>(2.5 * stanBaterii);
    }
};

int main() {
    Wlasciciel wlasciciel1("Nowak");
    Samochod s1("ABC-", 12000, Samochod::Dopuszczony, wlasciciel1);
    SamochodElektryczny se1("XYZ-", 5000, Samochod::Dopuszczony, wlasciciel1, 80);

    cout << "Numer rejestracyjny s1: " << s1.getNumerRejestracyjny() << endl;
    cout << "Licznik s1: " << s1.getLicznik() << endl;
    cout << "Zasieg s1: " << s1.zasieg() << " km" << endl;
    cout << "Wartosc s1: " << fixed << setprecision(2) << double(s1) << " PLN" << endl;

    cout << "Numer rejestracyjny se1: " << se1.getNumerRejestracyjny() << endl;
    cout << "Licznik se1: " << se1.getLicznik() << endl;
    cout << "Stan baterii se1: " << se1.getStanBaterii() << "%" << endl;
    cout << "Zasieg se1: " << se1.zasieg() << " km" << endl;
    cout << "Wartosc se1: " << fixed << setprecision(2) << double(se1) << " PLN" << endl;

    // Porównanie samochodów
    Samochod s2("ABC-", 12005, Samochod::Dopuszczony, wlasciciel1);
    cout << "Czy s1 i s2 s¹ identyczne? " << (s1 == s2 ? "Tak" : "Nie") << endl;

    return 0;
}










//WERSJA 4 S1

#include <iostream>
#include <cstring>

using namespace std;

class Autor {
    char nazwisko[50];
public:
    Autor(const char* nazwisko) {
        strncpy(this->nazwisko, nazwisko, 50);
    }
    const char* getNazwisko() const {
        return nazwisko;
    }
};

class Ksiazka {
    char tytul[100];
    int liczbaStron;
    bool dostepnosc;
    Autor autor;
    static Ksiazka* instancjaWzorcowa;

public:
    // Konstruktor domyœlny, kopiuj¹cy instancjê wzorcow¹
    Ksiazka() {
        if (!instancjaWzorcowa) {
            throw logic_error("Brak zdefiniowanej instancji wzorcowej!");
        }
        strncpy(tytul, instancjaWzorcowa->tytul, 100);
        liczbaStron = instancjaWzorcowa->liczbaStron;
        dostepnosc = instancjaWzorcowa->dostepnosc;
        autor = instancjaWzorcowa->autor;
    }

    // Konstruktor argumentowy
    Ksiazka(const char* tytul, int liczbaStron, bool dostepnosc, const Autor& autor)
        : liczbaStron(liczbaStron), dostepnosc(dostepnosc), autor(autor) {
        strncpy(this->tytul, tytul, 100);
    }

    // Setery i getery
    void setTytul(const char* tytul) { strncpy(this->tytul, tytul, 100); }
    const char* getTytul() const { return tytul; }

    void setLiczbaStron(int liczbaStron) { this->liczbaStron = liczbaStron; }
    int getLiczbaStron() const { return liczbaStron; }

    void setDostepnosc(bool dostepnosc) { this->dostepnosc = dostepnosc; }
    bool getDostepnosc() const { return dostepnosc; }

    void setAutor(const Autor& autor) { this->autor = autor; }
    Autor getAutor() const { return autor; }

    // Ustawianie instancji wzorcowej
    static void ustawInstancjeWzorcowa(Ksiazka* instancja) {
        instancjaWzorcowa = instancja;
    }

    // Polimorficzna metoda obliczaj¹ca cenê ksi¹¿ki
    virtual double cena() const {
        return 1.0 * liczbaStron; // Cena w PLN
    }

    // Mechanizm konwersji Ksi¹¿ka ? const char*
    operator const char* () const {
        static char opis[256];
        snprintf(opis, sizeof(opis), "Tytu³: %s, Liczba stron: %d, Dostêpnoœæ: %s, Autor: %s",
            tytul, liczbaStron, dostepnosc ? "dostêpna" : "niedostêpna", autor.getNazwisko());
        return opis;
    }

    // Operator ==
    bool operator==(const Ksiazka& other) const {
        return liczbaStron == other.liczbaStron && dostepnosc == other.dostepnosc &&
            strcmp(autor.getNazwisko(), other.autor.getNazwisko()) == 0 &&
            strcmp(tytul, other.tytul) == 0;
    }
};

// Inicjalizacja statycznego pola klasy Ksiazka
Ksiazka* Ksiazka::instancjaWzorcowa = nullptr;

// Klasa EBook dziedzicz¹ca po Ksiazka
class EBook : public Ksiazka {
    double rozmiarMB;

public:
    EBook(const char* tytul, int liczbaStron, bool dostepnosc, const Autor& autor, double rozmiarMB)
        : Ksiazka(tytul, liczbaStron, dostepnosc, autor), rozmiarMB(rozmiarMB) {}

    // Przes³oniêta metoda obliczaj¹ca cenê eBooka
    double cena() const override {
        return 0.75 * Ksiazka::cena(); // eBook jest o 25% tañszy
    }
};

int main() {
    Autor autor("Kowalski");
    Ksiazka ksiazka("Pan Tadeusz", 300, true, autor);
    Ksiazka::ustawInstancjeWzorcowa(&ksiazka);

    // Testowanie konwersji Ksi¹¿ka ? const char*
    const char* opis = ksiazka;
    cout << opis << endl;

    // Testowanie operatora ==
    Ksiazka ksiazka2("Dziady", 250, true, autor);
    if (ksiazka == ksiazka2) {
        cout << "Ksi¹¿ki s¹ identyczne." << endl;
    }
    else {
        cout << "Ksi¹¿ki s¹ ró¿ne." << endl;
    }

    return 0;
}
*/