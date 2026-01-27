#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;


// Zmienne globalne do zliczania operacji
long long liczba_porownan = 0;
long long liczba_przypisan = 0;


// Funkcja pomocnicza do wypisywania rozwiązania
void print_solution(const vector<int>& s, int n) {
    cout << "Optymalne ciecia: ";
    while (n > 0) {
        cout << s[n] << " ";
        n = n - s[n];
    }
    cout << endl;
}


//  Wersja Naiwna 
int naiwny_algorytm(const vector<int>& p, int n) {
    liczba_porownan++; 
    if (n == 0) return 0;

    int q = INT_MIN;
    liczba_przypisan++; 

    liczba_przypisan++; 
    for (int i = 1; i <= n; i++) {
        liczba_porownan++; 

        int temp = p[i] + naiwny_algorytm(p, n - i);
        
        liczba_porownan++; 
        liczba_przypisan++;
        q = max(q, temp);

        liczba_przypisan++; 
    }
    liczba_porownan++; 

    return q;
}


//  Algorytm ze spamiętywaniem 
int spamietywanie_algorytm_worker(const vector<int>& p, int n, vector<int>& r, vector<int>& s) {
    liczba_porownan++; 
    if (r[n] >= 0) return r[n];

    int q;
    liczba_porownan++; 
    if (n == 0) {
        q = 0;
        liczba_przypisan++; 
    }
    else {
        q = INT_MIN; //Inicjujemy -oo
        liczba_przypisan++; 

        liczba_przypisan++; 
        for (int i = 1; i <= n; i++) {
            liczba_porownan++; 

            int val = p[i] + spamietywanie_algorytm_worker(p, n - i, r, s);
            liczba_przypisan++; 

            liczba_porownan++; 
            if (q < val) {
                q = val;
                liczba_przypisan++; 
                s[n] = i; 
                liczba_przypisan++; 
            }
            liczba_przypisan++; 
        }
        liczba_porownan++; 
    }
    r[n] = q;
    liczba_przypisan++; 
    return q;
}

int spamietywanie_algorytm(const vector<int>& p, int n, vector<int>& s) {
    vector<int> r(n + 1, -1); // Inicjalizacja tablicy 
    liczba_przypisan += (n + 1); // koszt inicjalizacji -1
    return spamietywanie_algorytm_worker(p, n, r, s);
}


// Iteracyjna wersja 
int iteracyjny_algorytm(const vector<int>& p, int n, vector<int>& s) {
    vector<int> r(n + 1);
    
    r[0] = 0;
    liczba_przypisan++; 

    liczba_przypisan++; 
    for (int j = 1; j <= n; j++) {
        liczba_porownan++; 

        int q = INT_MIN;
        liczba_przypisan++; 

        liczba_przypisan++;
        for (int i = 1; i <= j; i++) {
            liczba_porownan++; 

            liczba_porownan++; 
            if (q < p[i] + r[j - i]) {
                q = p[i] + r[j - i];
                liczba_przypisan++; 
                s[j] = i;
                liczba_przypisan++; 
            }
            liczba_przypisan++; 
        }
        liczba_porownan++; 

        r[j] = q;
        liczba_przypisan++; 
        
        liczba_przypisan++; 
    }
    liczba_porownan++; 

    return r[n]; 
}




int main() {
    srand(time(0));

    vector<int> test_sizes = { 10, 50, 100, 300, 500, 1000, 2000, 5000 };

    cout << "testy porównawcze:" << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;
    // Nagłówek tabeli (wyrównanie kolumn)
    printf("%-6s | %-15s | %-15s | %-15s | %-15s\n", "N", "Naiwny (us)", "spam (us)", "Iter (us)", "Wynik (Iter)");
    cout << "------------------------------------------------------------------------------------------------" << endl;

    for (int n : test_sizes) {
        // 1. Generowanie danych dla aktualnego n
        vector<int> p(n + 1);
        p[0] = 0;
        for (int i = 1; i <= n; i++) {
            p[i] = (i * 2) + (rand() % 10); // Przykładowe ceny
        }

        // Zmienne na wyniki czasowe
        long long t_naiwny = -1; // -1 oznacza pominięty
        long long t_memo = 0;
        long long t_iter = 0;
        int max_profit = 0;

        vector<int> s(n + 1); // Tablica pomocnicza 


        // test 1: Naiwny (tylko dla małych n)

        if (n <= 28) { // granica(powyżej algorytm trwa długo)
            liczba_porownan = 0; liczba_przypisan = 0;
            auto start = chrono::high_resolution_clock::now();
            
            naiwny_algorytm(p, n);
            
            auto end = chrono::high_resolution_clock::now();
            t_naiwny = chrono::duration_cast<chrono::microseconds>(end - start).count();
        }

        // test 2: Spamiętywanie

        vector<int> s_memo(n + 1, 0);
        liczba_porownan = 0; liczba_przypisan = 0;
        auto start_m = chrono::high_resolution_clock::now();
        
        spamietywanie_algorytm(p, n, s_memo);
        
        auto end_m = chrono::high_resolution_clock::now();
        t_memo = chrono::duration_cast<chrono::microseconds>(end_m - start_m).count();


        // test 3: Iteracyjny

        vector<int> s_iter(n + 1, 0);
        liczba_porownan = 0; liczba_przypisan = 0;
        auto start_i = chrono::high_resolution_clock::now();
        
        max_profit = iteracyjny_algorytm(p, n, s_iter);
        
        auto end_i = chrono::high_resolution_clock::now();
        t_iter = chrono::duration_cast<chrono::microseconds>(end_i - start_i).count();



        // wypisanie wyników w tabeli

        string s_naiwny = (t_naiwny == -1) ? "---" : to_string(t_naiwny);
        
        printf("%-6d | %-15s | %-15lld | %-15lld | %-15d\n", 
            n, s_naiwny.c_str(), t_memo, t_iter, max_profit);
    }
    
    cout << "------------------------------------------------------------------------------------------------" << endl;
    cout << "Koniec testów." << endl;

    return 0;
}