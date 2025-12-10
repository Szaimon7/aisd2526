#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    Node* next;
    float val;

    Node(float data) {
        next = nullptr;
        val = data;
    }
};

struct List {
    Node* start = nullptr;
};

void INSERT(List* list, Node* wagonik) {
    if (list->start == nullptr) { // przypadek dla pustej listy
        list->start = wagonik;
    }
    if (wagonik->val <= list->start->val) {
        wagonik->next = list->start;
        list->start = wagonik;
    }
    else {
        Node* mniejszy = list->start;
        while (mniejszy->next != nullptr && !(wagonik->val <= mniejszy->next->val)) {
            mniejszy = mniejszy->next;
        }
        if (mniejszy->next == nullptr) {
            mniejszy->next = wagonik;
            wagonik->next = nullptr;
        }
        else {
            wagonik->next = mniejszy->next;
            mniejszy->next = wagonik;
        }
    }
}

void BUCKET_SORT(float tab[], int n) {
    float najmniejsza = /*!!! najmniejsza wartosc w tablicy*/ 73;
    float najwieksza = /*!!! najwieksza wartosc w tablicy*/ 73;
    List* buckets[n]; // tablica bucketow (list); (robimy n bucketów bo tak mamy zrobić ale może być jakakolwiek ilosc)
    for (int i = 0; i < n; i++) {
        // c++ zjebany i nie da sie zrobić tablicy pustych list od razu i trzeba w petli
        buckets[i] = new List();
    }

    for (int i = 0; i < n; i++) {
        int do_ktorego_bucketa = /*!!! tak jak w pseudokodzie na stronie tylko dla przedziału od najmniejszej do najwiekszej, trzeba uwazac zeby nie bylo tutaj n*/73;
        Node* wagonik_dla_bucketa = new Node(tab[i]);
        INSERT(buckets[do_ktorego_bucketa], wagonik_dla_bucketa); // wstawiamy (wstawia też do pustej listy - komentarz w INSERT)
    }
    
    // teraz wsadzamy po kolei wartości bucketów w tablice
    int indeks_w_tablicy = 0;
    for (int ktory_bucket = 0; ktory_bucket < n; ktory_bucket++) {
        Node* aktualny = buckets[ktory_bucket]->start;
        while (aktualny != nullptr) { // iterujemy bucketa (listę)
            tab[indeks_w_tablicy] = aktualny->val;
            indeks_w_tablicy++;
            aktualny = aktualny->next;
        }
    }
}

int main() {
    int n;
    cin >> n;
    float tab[n];
    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }

    BUCKET_SORT(tab, n);

    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;

    return 0;
}