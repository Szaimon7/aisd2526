#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <climits>
#include <cstdio>
#include <string>

using namespace std;

// Zmienne globalne do zliczania operacji
long long liczba_porownan = 0;
long long liczba_przypisan = 0;

struct Activity {
    int id, s, f;
};

// rekurencyjny(naiwny)

void RECURSIVE_SELECT(int s[], int f[], int k, vector<int>& res) {
    int m = k - 1;
    liczba_przypisan++; 

    // Pętla szukająca pierwszego pasującego zajęcia od tyłu
    while (true) {
        liczba_porownan++;
        if (m < 1) break;

        liczba_porownan++; 
        if (f[m] <= s[k]) break;

        m--;
        liczba_przypisan++; 
    }

    liczba_porownan++; 
    if (m >= 1) {
        res.push_back(m);
        // Wywołanie rekurencyjne 
        RECURSIVE_SELECT(s, f, m, res);
    }
}


// iteracyjny 

vector<int> ITERATIVE_SELECT(int s[], int f[], int n) {
    vector<int> A;
    A.push_back(n); 

    int k = n;
    liczba_przypisan++; 

    liczba_przypisan++; 
    for (int m = n - 1; m >= 1; m--) {
        liczba_porownan++; 

        liczba_porownan++; 
        if (f[m] <= s[k]) {
            A.push_back(m);
            k = m;
            liczba_przypisan++; 
        }
        liczba_przypisan++; 
    }
    liczba_porownan++; 

    return A;
}


// spamiętywanie(dynamiczne)

int DYNAMIC_SELECT(int s[], int f[], int n) {
    // Inicjalizacja tablicy 
    vector<int> dp(n + 1, 1);
    liczba_przypisan += (n + 1); // Koszt inicjalizacji jedynkami

    liczba_przypisan++; 
    for (int i = 2; i <= n; i++) {
        liczba_porownan++; 

        liczba_przypisan++; 
        for (int j = 1; j < i; j++) {
            liczba_porownan++; 

            liczba_porownan++; 
            if (f[j] <= s[i]) {
                
                
                int val = dp[j] + 1; 
                
                liczba_porownan++; 
                
                if (val > dp[i]) {
                    dp[i] = val;
                    liczba_przypisan++; 
                }
            }
            liczba_przypisan++; 
        }
        liczba_porownan++; 

        liczba_przypisan++; 
    }
    liczba_porownan++; 

    
    return *max_element(dp.begin(), dp.end());
}


int main() {
    srand(time(0));


    vector<int> test_sizes = { 30, 100, 200, 500, 1000, 3000, 5000, 8000 };

    cout << "Testy porównawcze algorytmów wyboru zajec:" << endl;
    cout << "Naiwny(rekurencyjny), Spam(dynamiczny), Iter(zachłanny)" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

    printf("%-6s | %-15s | %-15s | %-15s | %-15s | %-15s\n", "N", "Naiwny (us)", "Spam DP (us)", "Iter (us)", "Wynik (Iter)", "Porownania(Iter)");
    cout << "" << endl;

    for (int n : test_sizes) {
        // Generowanie danych dla aktualnego n 
        vector<Activity> temp;
        for (int i = 0; i < n; i++) {
            int start = rand() % (n * 2); 
            int duration = (rand() % 50) + 1;
            temp.push_back({ i + 1, start, start + duration });
        }

        // Sortowanie wg czasu startu 
        sort(temp.begin(), temp.end(), [](Activity a, Activity b) {
            return a.s < b.s;
        });

        // Zmiana na normalne tablice 
        int* s = new int[n + 2];
        int* f = new int[n + 2];

        for (int i = 1; i <= n; i++) {
            s[i] = temp[i - 1].s;
            f[i] = temp[i - 1].f;
        }

        // Zmienne na wyniki
        long long t_naiwny = -1; 
        long long t_memo = 0;
        long long t_iter = 0;
        int result_iter = 0;
        long long ops_iter = 0; // Do wyświetlenia przykładowej złożoności


        if (n <= 4000) { 
            vector<int> res_rec;

            s[n + 1] = INT_MAX; 

            liczba_porownan = 0; liczba_przypisan = 0;
            auto start = chrono::high_resolution_clock::now();

            RECURSIVE_SELECT(s, f, n + 1, res_rec);

            auto end = chrono::high_resolution_clock::now();
            t_naiwny = chrono::duration_cast<chrono::microseconds>(end - start).count();
        }


        {
            liczba_porownan = 0; liczba_przypisan = 0;
            auto start_m = chrono::high_resolution_clock::now();

            DYNAMIC_SELECT(s, f, n);

            auto end_m = chrono::high_resolution_clock::now();
            t_memo = chrono::duration_cast<chrono::microseconds>(end_m - start_m).count();
        }

        // test: iteracyjny
        {
            liczba_porownan = 0; liczba_przypisan = 0;
            auto start_i = chrono::high_resolution_clock::now();

            vector<int> res = ITERATIVE_SELECT(s, f, n);
            result_iter = res.size();

            auto end_i = chrono::high_resolution_clock::now();
            t_iter = chrono::duration_cast<chrono::microseconds>(end_i - start_i).count();
            ops_iter = liczba_porownan + liczba_przypisan;
        }


        string s_naiwny = (t_naiwny == -1) ? "---" : to_string(t_naiwny);
        
        printf("%-6d | %-15s | %-15lld | %-15lld | %-15d | %-15lld\n",
            n, s_naiwny.c_str(), t_memo, t_iter, result_iter, ops_iter);


        delete[] s;
        delete[] f;
    }

    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Koniec testów" << endl;

    return 0;
}