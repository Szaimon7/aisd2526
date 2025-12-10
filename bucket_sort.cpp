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
    if (list->start == nullptr) { 
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
    float najmniejsza = 73;
    float najwieksza = 73;
    List* buckets[n]; 
    for (int i = 0; i < n; i++) {

        buckets[i] = new List();
    }

    for (int i = 0; i < n; i++) {
        int do_ktorego_bucketa = 73;
        Node* wagonik_dla_bucketa = new Node(tab[i]);
        INSERT(buckets[do_ktorego_bucketa], wagonik_dla_bucketa); 
    }
    
 
    int indeks_w_tablicy = 0;
    for (int ktory_bucket = 0; ktory_bucket < n; ktory_bucket++) {
        Node* aktualny = buckets[ktory_bucket]->start;
        while (aktualny != nullptr) {
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