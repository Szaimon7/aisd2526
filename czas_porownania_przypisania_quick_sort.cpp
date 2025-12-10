#include <iostream>
#include <algorithm>
#include <utility>      
#include <chrono>       
#include <cstdlib>      
#include <ctime>        
#include <vector>       
using namespace std::chrono;
using namespace std;

void swap_with_count(int &a, int &b, long long &przypisania) {
    int temp = a;
    a = b;
    b = temp;
    przypisania += 3;
}


int PARTITION(int A[], int poczatek, int koniec) {

    int x = A[koniec];        
    int i = poczatek - 1;

// Szukamy pivota //
    for (int j = poczatek; j < koniec; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
// Zamieniamy elementy tak aby pivot był na swoim miejscu //
    swap(A[i + 1], A[koniec]);
    return i + 1;
}


void QUICK_SORT(int A[], int p, int k) {
    if (p < k) {

        // inicjujemy środek
        int s = PARTITION(A, p, k);

        // Pivot oddziela na dwie części więc w każdej połówce 
        // znajdujemy kolejne pivoty aż już pivot będzie jedynym elementem każdej z części
        QUICK_SORT(A, p, s - 1);
        QUICK_SORT(A, s + 1, k);
    }
}

pair <int,int> PARTITION_2(int A[], int poczatek_2, int koniec_2, long long &porównania, long long &przypisania){

    int y = A[poczatek_2];
    przypisania++; 
    int k = A[koniec_2];
    przypisania++; 
    
    int m = poczatek_2 + 1;
    przypisania++; 
    int n = koniec_2 - 1;
    przypisania++; 

    //Zamiana jeżeli ostatni element jest mniejszy niż pierwszy
    porównania++; 
    if (y > k) {
        swap_with_count(A[poczatek_2], A[koniec_2], przypisania);
        y = A[poczatek_2];
        przypisania++; 
        k = A[koniec_2];
        przypisania++; 
    }

    for (int p = m; p <= n;) {
        porównania++; 

        // Jeżeli element z pętli jest mniejszy od pivota to
        // zamieniamy go z A[m] gdzie m determinuje ile
        // elementów jest mniejszych od pivota_1
        porównania++; 
        if (A[p] < y) {
            swap_with_count(A[p], A[m], przypisania);
            m++;
            przypisania++; 
            p++;               
            przypisania++; 
        }
        else {
            porównania++; 
            if (A[p] > k) {
                swap_with_count(A[p], A[n], przypisania);
                n--;    
                przypisania++; 
                continue;
            }
            // Musi być continue, ponieważ jeżeli zamienimy
            // elementy to dalej może nie być on pomiędzy 
            // pivotami
            else {
                p++;              
                przypisania++; 
            }
        }
    }
    porównania++; 

    swap_with_count(A[poczatek_2], A[m - 1], przypisania);
    swap_with_count(A[koniec_2], A[n + 1], przypisania);

    // W całym algorytmie zwiększamy p tylko wtedy
    // gdy element jest mniejszy lub na środku

    return {m - 1, n + 1};
}
    
void QUICK_SORT_2(int A[], int left, int right, long long &porównania, long long &przypisania) {

    porównania++; 
    if (left < right) {

        // inicjujemy środek
        pair<int,int> pivot = PARTITION_2(A, left, right, porównania, przypisania);
        przypisania++; 

        int pivot_1 = pivot.first;
        przypisania++; 
        int pivot_2 = pivot.second;
        przypisania++; 

        // Dzielimy 3 razy ponieważ są 2 pivoty 

        QUICK_SORT_2(A, left, pivot_1 - 1, porównania, przypisania);   
        QUICK_SORT_2(A, pivot_1 + 1, pivot_2 - 1, porównania, przypisania);
        QUICK_SORT_2(A, pivot_2 + 1, right, porównania, przypisania); 
    }
}

int main() {
    int n;
    cout << "Podaj n: ";
    cin >> n;
    
    int *tab = new int[n]; 
    
    srand(time(0));
    for (int i = 0; i < n; i++) {
        tab[i] = rand() % 999 + 1;
    }

    cout << "Pierwsze 30 elementów tablicy przed posortowaniem to: " << endl;
    for (int i = 0; i < min(30, n); i++) {
        cout << tab[i] << " ";
    }
    cout << endl << endl;

    // Zaczynamy porównania i przypisania inicjując jego wartość równą 0
    long long por = 0;
    long long prz = 0;

    // funkcje na czas   
    auto start = chrono::high_resolution_clock::now();
    
    QUICK_SORT_2(tab, 0, n-1, por, prz);
    
    auto end = chrono::high_resolution_clock::now();
    auto czas = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Tablica po sortowaniu przez QUICK_SORT_2 (z 2 pivotami):" << endl;
    for (int i = 0; i < min(30, n); i++) {
        cout << tab[i] << " ";
    }
    cout << endl << endl;

    cout << "QUICK_SORT_2 ma " << por << " porównań oraz " << prz << " przypisań, a czas to: " << czas.count() 
    << " mirkosekund, ponieważ ilość operacji to: "<< (por + prz) << endl;
    
    delete[] tab;
    return 0;
}