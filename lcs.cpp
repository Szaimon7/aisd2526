#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// symbole pomocnicze dla tablicy 
const int SKOS = 1; // skos
const int GORA = 2; // góra
const int LEWO = 3; // lewo

// funkcja rekonstruująca
void wywołaj_rozwiązanie(const vector<vector<int>>& b, int* X, int i, int j) {
    if (i > 0 && j > 0) { 
        if (b[i][j] == SKOS) { 
            wywołaj_rozwiązanie(b, X, i - 1, j - 1); 
            cout << X[i] << " "; 
        } else if (b[i][j] == GORA) { 
            wywołaj_rozwiązanie(b, X, i - 1, j); 
        } else { 
            wywołaj_rozwiązanie(b, X, i, j - 1); 
        }
    }
}

// wersja iteracyjna
void LCS_ITERACYJNY(int* X, int m, int* Y, int n, int &por, int &prz) {

    vector<vector<int>> b(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        c[i][0] = 0; prz++;
    }

    for (int j = 1; j <= n; j++) {
        c[0][j] = 0; prz++;
    }


    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            por++; 
            if (X[i] == Y[j]) { 
                c[i][j] = c[i - 1][j - 1] + 1; 
                b[i][j] = SKOS; 
                prz += 2;
            } else {
                por++;
                if (c[i - 1][j] >= c[i][j - 1]) {
                    c[i][j] = c[i - 1][j]; 
                    b[i][j] = GORA; 
                    prz += 2;
                } else {
                    c[i][j] = c[i][j - 1];  
                    b[i][j] = LEWO; 
                    prz += 2;
                }
            }
        }
    }

}

// wersja rekurencyjna_spamietywanie
int LCS_rekurencyjny(int* X, int* Y, int i, int j, vector<vector<int>>& c, vector<vector<int>>& b, int &por, int &prz) {
    if (i == 0 || j == 0) return 0;
    
    if (c[i][j] != -1) return c[i][j];

    por++;
    if (X[i] == Y[j]) {
        prz += 2;
        b[i][j] = SKOS;
        return c[i][j] = LCS_rekurencyjny(X, Y, i - 1, j - 1, c, b, por, prz) + 1;
    } else {
        int gora = LCS_rekurencyjny(X, Y, i - 1, j, c, b, por, prz);
        int lewo = LCS_rekurencyjny(X, Y, i, j - 1, c, b, por, prz);
        por++;
        if (gora >= lewo) {
            prz += 2;
            b[i][j] = GORA;
            return c[i][j] = gora;
        } else {
            prz += 2;
            b[i][j] = LEWO;
            return c[i][j] = lewo;
        }
    }
}

int main() {
    srand(time(0));


    vector<int> test_sizes = { 10, 20, 100, 500, 1000, 2000, 5000 };

    cout << "testy LCS" << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    printf("%-6s | %-15s | %-15s | %-15s | %-15s\n", "N", "Iter (us)", "Rekur (us)", "Wynik (dł)", "Przypisania(It)");
    cout << "--------------------------------------------------------------------------------------------------" << endl;

    for (int n : test_sizes) {
        int m = n; 

        // Generowanie danych 
        int *X = new int[n + 1];
        int *Y = new int[n + 1];
        
        for(int i = 1; i <= n; i++){
            X[i] = rand() % 26 + 65; 
            Y[i] = rand() % 26 + 65;
        }

        // Zmienne 
        int por_iter = 0, prz_iter = 0;
        int por_rec = 0, prz_rec = 0;
        
        // test 1: iteracyjny
        auto start1 = chrono::high_resolution_clock::now();
        
    
        LCS_ITERACYJNY(X, n, Y, m, por_iter, prz_iter);
        
        auto end1 = chrono::high_resolution_clock::now();
        auto time_iter = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();

     
        int len_lcs = 0; 


        // test 2: rekurencyjny
        vector<vector<int>> c_rec(n + 1, vector<int>(m + 1, -1));
        vector<vector<int>> b_rec(n + 1, vector<int>(m + 1, 0));

        auto start2 = chrono::high_resolution_clock::now();
        
        len_lcs = LCS_rekurencyjny(X, Y, n, m, c_rec, b_rec, por_rec, prz_rec);
        
        auto end2 = chrono::high_resolution_clock::now();
        auto time_rec = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();


        // Wypisanie 
        printf("%-6d | %-15lld | %-15lld | %-15d | %-15d\n", 
            n, time_iter, time_rec, len_lcs, prz_iter);

        delete[] X;
        delete[] Y;
    }

    cout << "--------------------------------------------------------------------------------------------------" << endl;

    return 0;
}