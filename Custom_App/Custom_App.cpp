#include <iostream>
#include <string>


using namespace std;
using trescTekstowa = char[500];

enum class typZadania
{
    latwe = 0,
    podstawowe = 1,
    ambitne = 2,
};

struct Przedmiot
{
    trescTekstowa nazwaPrzedmiotu;
};

struct Zadanie
{
    trescTekstowa tresc;
    int liczbaPunktow;
    typZadania rodzaj;
    Przedmiot nazwa; //0 - matematyka, 1 - programowanie, 2 - prace domowe 
};

void wypelnianie(Zadanie& z, const char* tr, int pkt, typZadania typ, Przedmiot naz)
{
    strcpy(z.tresc, tr);
    z.liczbaPunktow = pkt;
    z.rodzaj = typ;
    z.nazwa = naz;
}

void wypisywanie(Zadanie& z)
{
    cout << "Treœæ zadania:\t" << z.tresc << endl
        << "Liczba punktów:\t" << z.liczbaPunktow << endl;
    cout << "Typ zadania:\t" << static_cast<int>(z.rodzaj) << endl
        << "Nazwa przedmiotu:\t" << z.nazwa.nazwaPrzedmiotu << endl;
}

int zadaniaONajdluzszejTresci(Zadanie* tablica, const char* przedmiot)
// Funkcja przyjmuje tablice zadan i przedmiot 
// Ma wyznaczyæ jakiego typu jest zadnie z tego przedmiotu,
// które ma najdluzsza tresc
// UWAGA: funkcja zawiera bledy czasu kompilacji i czasu wykonania
{
    int typPrzedmiotu = 0, maxDlugosc = 0;

    for (int i = 0; i < sizeof(tablica); i++)
    {
        if (tablica[i].nazwa.nazwaPrzedmiotu == przedmiot)
        {
            if (strlen(tablica[i].tresc) > maxDlugosc)
            {
                maxDlugosc = strlen(tablica[i].tresc);
                typPrzedmiotu = static_cast<int>(tablica[i].rodzaj);
            }
        }
    }
}

int main()
{

    setlocale(LC_ALL, "");
    Przedmiot nazwa;

    Zadanie zadania[] = {
        {"Oblicz srednia", 2, typZadania::latwe, {"Matematyka"}},
        {"Znajdz x w rownaniu", 5, typZadania::podstawowe, {"Matematyka"}},
        {"Pokoloruj drwala... proceduralnie", 30, typZadania::ambitne, {"Programowanie"}},
        {"Oblicz ca³ke", 10, typZadania::podstawowe, {"Matematyka"}},
        {"Wynies smieci", 1, typZadania::latwe, {"Prace domowe"}},
        {"Kup flaszke dla profesora", 10, typZadania::ambitne, {"Matematyka"}},
        {"Napisz program komputerowy", 20, typZadania::ambitne, {"Programowanie"}}
    };

    cout << zadaniaONajdluzszejTresci(zadania, "Programowanie") << endl;
}


























































/*
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

class MillionaireGame {
private:
    struct Question {
        string questionText;
        vector<string> options;
        char correctOption;
    };

    vector<Question> allQuestions; 
    vector<Question> selectedQuestions; 
    int currentQuestion;
    int moneyWon;

    bool FiftyFiftyUsed = false;
    bool SwapQuestionUsed = false;
    bool AudienceHelpUsed = false;

public:
    MillionaireGame() : currentQuestion(0), moneyWon(0) {
        initializeAllQuestions();
        selectRandomQuestions();
    }


    void initializeAllQuestions() {
        Question q1 = { "Gdzie Œl¹zaczki nosz¹ laczki?", {"A. Na g³owie", "B. Na rêkach", "C. Na nogach", "D. Na plecach"}, 'C' };
        allQuestions.push_back(q1);
        Question q2 = { "Ragdoll, czyli szmaciana lalka, to rasa...", {"A. Kotów", "B. Psów", "C. Królików", "D. Chomików"}, 'A' };
        allQuestions.push_back(q2);
        Question q3 = { "Ile kosztuje chleb, który pierwotnie kosztowa³ 10 z³, nastêpnie potania³ do 8 z³, a póŸniej jego cena wzros³a o 20 proc.?", {"A. 8,20 z³", "B. 9 z³", "C. 9,60 z³", "D. 10 z³"}, 'C' };
        allQuestions.push_back(q3);
        Question q4 = { "Co jest prawd¹ o podkarpackim mieœcie, które ma w nazwie urz¹dzenie w³ókiennicze?", {"A. s³ynie z hut szk³a", "B. w X w. by³o stolic¹ Polski", "C. ma milion mieszkañców", "D. ma w herbie ³ódŸ"}, 'A' };
        allQuestions.push_back(q4);
        Question q5 = { "Kuchenny synonim przekrêtu...", {"A. t³uczek", "B. wa³ek", "C. blat", "D. garnek"}, 'B' };
        allQuestions.push_back(q5);
        Question q6 = { "Kojot wygl¹da jak coœ pomiêdzy...", {"A. rysiem a ¿bikiem", "B. bobrem a wiewiórk¹", "C. kun¹ a ³asic¹", "D. wilkiem a szakalem"}, 'D' };
        allQuestions.push_back(q6);
        Question q7 = { "Kto w marcu 2023 r. w meczu z Albani¹ w trakcie eliminacji do Euro strzeli³ zwyciêskiego gola dla Polski?", {"A. Jan Bednarek", "B. Piotr Zieliñski", "C. Karol Œwiderski", "D. Robert Lewandowski"}, 'C' };
        allQuestions.push_back(q7);
        Question q8 = { "Jaka jest œrednia wieku w grupie sk³adaj¹cej siê z trzech 4-latków, czterech 11-latków, dwóch 12-latków i jednego 20-latka?", {"A. 10 lat", "B. 8 lat", "C. 15 lat", "D. 18 lat"}, 'A' };
        allQuestions.push_back(q8);
        Question q9 = { "Awanturka to pasta...", {"A. polerska", "B. cukrowa", "C. do kanapek", "D. do butów"}, 'C' };
        allQuestions.push_back(q9);
        Question q10 = { "Trzy zwyczaje ³¹cz¹ siê z noc¹ œwiêtojañsk¹, a jeden nie. Który?", {"A. szukanie kwiatu paproci", "B. puszczanie wianków nad wodê", "C. skoki przez ognisko", "D. topienie marzanny"}, 'D' };
        allQuestions.push_back(q10);
        Question q11 = { "Który z ptaków kuka?", {"A. samica kuku³ki", "B. samiec kuku³ki", "C. samica g¿eg¿ó³ki", "D. samica zazuli"}, 'B' };
        allQuestions.push_back(q11);
        Question q12 = { "Co pojawia siê w znanym ³amañcu jêzykowym o czytaj¹cym tacie?", {"A. passusy Passenta", "B. wersy z Verne'a", "C. maksymy Maksymusa", "D. cytaty z Tacyta"}, 'D' };
        allQuestions.push_back(q12);
        Question q13 = { "To klasyczny kszta³t kobiecych brwi...", {"A. mysie ogonki", "B. kocie grzbiety", "C. skrzyd³a jaskó³ki", "D. strza³y Amora"}, 'C' };
        allQuestions.push_back(q13);
        Question q14 = { "Który to legendarny angielski pirat?", {"A. Sinobrody", "B. Czarnobrody", "C. D³ugonogi", "D. Krzywousty"}, 'B' };
        allQuestions.push_back(q14);
        Question q15 = { "O co chodzi we frazeologizmie: coœ jest warte lub niewarte zachodu?", {"A. o kierunek geograficzny", "B. o mekkê dla Polaków za PRL-u", "C. o czasownik zabieganie", "D.o czasownik wybieganie"}, 'C' };
        allQuestions.push_back(q15);
        Question q16 = { "Którego kraju stolica ma najwiêcej liter?", {"A. Madagaskaru", "B. Kenii", "C. Egiptu", "D. Maroko"}, 'A' };
        allQuestions.push_back(q16);
        Question q17 = { "W wilka i w owce najczêœciej gra siê na planszy...", {"A. do chiñczyka", "B. do warcabów", "C. do scrabble", "D. do m³ynka"}, 'B' };
        allQuestions.push_back(q17);
        Question q18 = { "Ile odcinków prostych znajdziemy w rzymskiej cyfrze 50?", {"A. siedem", "B. piêæ", "C. dwa", "D. jeden"}, 'C' };
        allQuestions.push_back(q18);
        Question q19 = { "Jakie lekarstwo na problemy z pamiêci¹ zaordynowa³ S³oniowi Tr¹balskiemu kowal z wiersza Juliana Tuwima?", {"A. podkucie przednich nóg", "B. przek³ucie uszu", "C. supe³ek na tr¹bie", "D. kokardkê na ogonie"}, 'C' };
        allQuestions.push_back(q19);
        Question q20 = { "Kto zdoby³ Z³ot¹ Pi³kê w 2018 roku?", {"A. Lionel Messi", "B. Cristiano Ronaldo", "C. Robert Lewandowski", "D. Luka Modriæ"}, 'D' };
        allQuestions.push_back(q20);


        random_shuffle(allQuestions.begin(), allQuestions.end());
    }

    void selectRandomQuestions() {
        selectedQuestions.clear();
        for (int i = 0; i < 10 && i < allQuestions.size(); ++i) {
            selectedQuestions.push_back(allQuestions[i]);
        }
    }

    void displayQuestion() {
        cout << "Pytanie " << currentQuestion + 1 << ": " << selectedQuestions[currentQuestion].questionText << endl;
        for (int i = 0; i < 4; ++i) {
            cout << selectedQuestions[currentQuestion].options[i] << endl;
        }
    }

    void FiftyFifty() {
        vector<char> availableOptions = { 'A', 'B', 'C', 'D' };
        availableOptions.erase(remove(availableOptions.begin(), availableOptions.end(), selectedQuestions[currentQuestion].correctOption), availableOptions.end());
        random_shuffle(availableOptions.begin(), availableOptions.end());
        for (int i = 0; i < 2; ++i) {
            char removedOption = availableOptions.back();
            availableOptions.pop_back();
            for (auto& option : selectedQuestions[currentQuestion].options) {
                if (option[0] == removedOption) {
                    option = " ";
                }
            }
        }
    }

    void SwapQuestion() {
        cout << "Zamiana pytania! Oto nowe pytanie:" << endl;
        int newIndex = rand() % allQuestions.size();
        selectedQuestions[currentQuestion] = allQuestions[newIndex];
    }

    void AudienceHelp() {
        cout << "Publicznoœæ myœli..." << endl;
        int correctPercentage = rand() % 51 + 50;
        int incorrectPercentage = 100 - correctPercentage;

        cout << "A: " << (selectedQuestions[currentQuestion].correctOption == 'A' ? correctPercentage : incorrectPercentage) << "%   "
            << "B: " << (selectedQuestions[currentQuestion].correctOption == 'B' ? correctPercentage : incorrectPercentage) << "%   "
            << "C: " << (selectedQuestions[currentQuestion].correctOption == 'C' ? correctPercentage : incorrectPercentage) << "%   "
            << "D: " << (selectedQuestions[currentQuestion].correctOption == 'D' ? correctPercentage : incorrectPercentage) << "%" << endl;
    }

    bool answerQuestion(char userAnswer) {
        if (userAnswer == 'L') {
            if (!FiftyFiftyUsed) {
                FiftyFifty();
                cout << "U¿y³eœ ko³a ratunkowego \"Pó³ na pó³\"!" << endl;
                FiftyFiftyUsed = true; 
            }
            else {
                cout << "To ko³o ratunkowe zosta³o ju¿ u¿yte!" << endl;
            }
        }
        else if (userAnswer == 'Z') {
            if (!SwapQuestionUsed) {
                SwapQuestion();
                cout << "U¿y³eœ ko³a ratunkowego \"Zamiana pytania\"!" << endl;
                SwapQuestionUsed = true;
            }
            else {
                cout << "To ko³o ratunkowe zosta³o ju¿ u¿yte!" << endl;
            }
        }
        else if (userAnswer == 'P') {
            if (!AudienceHelpUsed) {
                AudienceHelp();
                cout << "U¿y³eœ ko³a ratunkowego \"Pytanie do publicznoœci\"!" << endl;
                AudienceHelpUsed = true; 
            }
            else {
                cout << "To ko³o ratunkowe zosta³o ju¿ u¿yte!" << endl;
            }
           }
        else {
            if (userAnswer == selectedQuestions[currentQuestion].correctOption) {
                cout << "Poprawna odpowiedŸ! Wygrywasz " << calculatePrize() << " z³!" << endl;
                ++currentQuestion;
                if (currentQuestion == selectedQuestions.size()) {
                    cout << "Gratulacje! Wygra³eœ ca³¹ grê!" << endl;
                    return false; 
                }
                return true;
            }
            else {
                cout << "Niestety, z³a odpowiedŸ. Koniec gry." << endl;
                return false;
            }
        }

        return true;
    }

    int calculatePrize() {
        return 1000 * (currentQuestion + 1);
    }
};

int main() {

    setlocale(LC_ALL, "");
    srand(time(0)); 
    MillionaireGame game;
    char userAnswer;

    cout << "Witaj w grze \"Mini Milionerzy\"! Odpowiedz na pytania, aby wygraæ 10 000 z³otych!" << endl;
    
    do {
        game.displayQuestion();
        cout << "Podaj odpowiedŸ (A, B, C, D) lub skorzystaj z kó³ ratunkowych (L - Pó³ na pó³, Z - Zamiana pytania, P - Pytanie do publicznoœci): ";
        cin >> userAnswer;
        userAnswer = toupper(userAnswer);
    } while (game.answerQuestion(userAnswer));
   
    
    return 0;
}

*/











