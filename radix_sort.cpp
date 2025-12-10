#include <iostream>
#include <bits/stdc++.h>
#include <functional>
#include <cmath>
using namespace std;

void COUNTING_SORT(int A[], int n, int d, function<int(int)> f) {
    int C[d];
    int B[n];
    // Inicjalizacja tablicy zerami
    for (int j = 0; j < d; j++) {
        C[j] = 0;
    }

    //Zliczenie wystapień cyfry
    for (int i = 0; i < n; i++) {
        C[f(A[i])]++;
    }

    
    for (int j = 1; j < d; j++) {
        C[j] += C[j-1];
    }
    for (int i = n - 1; i >= 0; i--) {
        B[C[f(A[i])]-1] = A[i];
        C[f(A[i])]--;
    }
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
}

void RADIX_SORT(int tab[], int n, int d, int k) {

    // Pozwala na sortowanie ujemnych liczb 
    long long przesuniecie = pow(d, k);
    for (long long i = 1; i <= pow(d, k+1); i*=d) {
        COUNTING_SORT(tab, n, d, [&](int x) -> int {return (x + przesuniecie) % (d*i) / i; });
    }
}


int main() {
    int n, d, k;
    cin >> n >> d >> k;
    int tab[n];
    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }

    RADIX_SORT(tab, n, d, k);

    // Wypisanie posortowanej tablicy
    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;

    return 0;
}