#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    Node* next;
    int val;

    Node(int data) {
        next = nullptr;
        val = data;
    }
};
// struktura listy
struct List {
    Node* start = nullptr;
};


void LIST_INSERTION_SORT(List* list) {
    Node* sorted_start = list->start;
    Node* unsorted_start = sorted_start->next;
    sorted_start->next = nullptr;

    while (unsorted_start != nullptr) {
        Node* kolejny = unsorted_start->next;

        // Wstawienie elementu na początek
        if (unsorted_start->val <= sorted_start->val) {
            unsorted_start->next = sorted_start;
            sorted_start = unsorted_start;
        }
        // Wstawienie w środek
        else {
            Node* mniejszy = sorted_start;
            while (mniejszy->next != nullptr && !(unsorted_start->val <= mniejszy->next->val)) {
                mniejszy = mniejszy->next;
            }
            if (mniejszy->next == nullptr) {
                mniejszy->next = unsorted_start;
                unsorted_start->next = nullptr;
            }
            else {
                unsorted_start->next = mniejszy->next;
                mniejszy->next = unsorted_start;
            }
        }
        unsorted_start = kolejny;
    }

    list->start = sorted_start;
}

int main() {
    int n;
    cin >> n;

    List* list = new List();
    int x;
    cin >> x;
    Node* end = new Node(x);
    list->start = end;

    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        end->next = new Node(x);
        end = end->next;
    }

    LIST_INSERTION_SORT(list);

    Node* current = list->start;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;

    return 0;
}