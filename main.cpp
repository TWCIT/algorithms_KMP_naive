#include "PrefixHeader.pch"
//Dla obsługi stringstream, wczesniej implicit problem był
#include <sstream>

using namespace std;
using namespace chrono;

// Funkcja wczytująca tekst z pliku
string odczytajTekst(string nazwaPliku) {
    string tekst;
    cout << "Start funkcji, wczytaj plik" << endl;
    if (!nazwaPliku.empty()){
        ifstream plik(nazwaPliku);
        stringstream bufor;
        bufor << plik.rdbuf();
        tekst = bufor.str();
        cout<<tekst;
    }
    cout<<endl;
    cout<<"Koniec funkcji, odczytaj Tekst"<<endl;
    return tekst;
}

// Funkcja wczytująca wzorzec z pliku lub z klawiatury
//string odczytajWzorzec(string nazwaPliku) {
//    string wzorzec;
//    if (!nazwaPliku.empty()){
//        ifstream plik(nazwaPliku);
//        getline(plik, wzorzec);
//    } else {
//        cout << "Wprowadź wzorzec: ";
//        getline(cin, wzorzec);
//    }
//    return wzorzec;
//}



// Algorytm naiwny wyszukiwania wzorca w tekście
int wyszukajNaiwne(string text, string pattern) {
    int m = pattern.length();
    int n = text.length();
    int temp = 0;
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++)
            if (text[i+j] != pattern[j])
                break;
        if (j == m) {
            temp++;
            j = 0;
        }
    }
    return temp;
}

// Algorytm KMP wyszukiwania wzorca w tekście
int KMP(string& tekst, const string& wzorzec) {
    int licznik = 0;
    unsigned long n = tekst.length();
    unsigned long m = wzorzec.length();
    vector<int> lps(m);
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j && wzorzec[i] != wzorzec[j]) j = lps[j - 1];
        if (wzorzec[i] == wzorzec[j]) j++;
        lps[i] = j;
    }
    j = 0;
    for (int i = 0; i < n; i++) {
        while (j && tekst[i] != wzorzec[j]) j = lps[j - 1];
        if (tekst[i] == wzorzec[j]) j++;
        if (j == m) {
            licznik++;
            j = lps[j - 1];
        }
    }
    return licznik;
}

int main() {
    string wzorzec = "dolor";
    string nazwaPlikuTekst, nazwaPlikuWzorzec;
    string tekst = odczytajTekst("File.txt");
    //cout << "Podaj nazwę pliku z wzorcem lub pozostaw puste jeśli chcesz wprowadzić wzorzec z klawiatury: ";
    //cin >> nazwaPlikuWzorzec;
    //string wzorzec = odczytajWzorzec(nazwaPlikuWzorzec);


    // Pomiar czasu dla algorytmu naiwnego
    auto start = high_resolution_clock::now();
    int licznikNaiwny = wyszukajNaiwne(tekst, wzorzec);
    auto end = high_resolution_clock::now();
    auto czasNaiwny = duration_cast<microseconds>(end - start).count();

    // Pomiar czasu dla algorytmu KMP
    start = high_resolution_clock::now();
    int licznikKMP = KMP(tekst, wzorzec);
    end = high_resolution_clock::now();
    auto czasKMP = duration_cast<microseconds>(end - start).count();

    // Wyniki Pomiarowe KMP&Naiwny
    cout << endl;
    cout << "Algorytm naiwny znalazł wzorzec " << licznikNaiwny << " razy." << endl;
    cout << "Czas działania algorytmu naiwnego: " << czasNaiwny << " mikrosekund." << endl;
    cout << "Algorytm KMP znalazł wzorzec " << licznikKMP << " razy." << endl;
    cout << "Czas działania algorytmu KMP: " << czasKMP << " mikrosekund." << endl;
    return 0;
}
