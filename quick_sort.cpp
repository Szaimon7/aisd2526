#include <iostream>
#include <algorithm>
using namespace std;

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

pair <int,int> PARTITION_2(int A[], int poczatek_2, int koniec_2){

    int y = A[poczatek_2];
    int k = A[koniec_2];
    
    int m = poczatek_2 + 1;
    int n = koniec_2 - 1;

    //Zamiana jeżeli ostatni element jest mniejszy niż pierwszy
    if (y > k) {
        swap(A[poczatek_2], A[koniec_2]);
        y = A[poczatek_2];
        k = A[koniec_2];
    }

    for (int p = m; p <= n;) {

        // Jeżeli element z pętli jest mniejszy od pivota to
        // zamieniamy go z A[m] gdzie m determinuje ile
        // elementów jest mniejszych od pivota_1
        if (A[p] < y) {
            swap(A[p], A[m]);
            m++;
            p++;               
        }
        else if (A[p] > k) {
            swap(A[p], A[n]);
            n--;    
            continue;
        }
        // Musi być continue, ponieważ jeżeli zamienimy
        // elementy to dalej może nie być on pomiędzy 
        // pivotami
        else {
            p++;              
        }
    }
    swap(A[poczatek_2], A[m - 1]);
    swap(A[koniec_2], A[n + 1]);

    // W całym algorytmie zwiększamy p tylko wtedy
    // gdy element jest mniejszy lub na środku

    return {m - 1, n + 1};
}
    
void QUICK_SORT_2(int A[], int left, int right) {

    if (left < right) {


        pair<int,int> pivot = PARTITION_2(A, left, right);

        int pivot_1 = pivot.first;
        int pivot_2 = pivot.second;

        // Dzielimy 3 razy ponieważ są 2 pivoty 

        QUICK_SORT_2(A, left, pivot_1 - 1);   
        QUICK_SORT_2(A, pivot_1 + 1, pivot_2 - 1);
        QUICK_SORT_2(A, pivot_2 + 1, right); 
    }
}

int main() {
    int n;
    cin >> n;
    int tab[n];
    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }

    QUICK_SORT_2(tab, 0, n-1);

    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;

    return 0;
}