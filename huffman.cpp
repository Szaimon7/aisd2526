#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

// zmienne globalne do zliczania operacji
long long liczba_porownan = 0;
long long liczba_przypisan = 0;

// struktura węzła
struct Node {
    char character;
    int freq;
    Node *left;
    Node *middle;   
    Node *right;
    Node *parent;

    Node(char c, int f) : character(c), freq(f), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}
};

// kolejka priorytetowa
struct Compare {
    bool operator()(Node* l, Node* r) {

        liczba_porownan++; 
        return l->freq > r->freq;
    }
};

// zzyszczenie pamięci
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->middle);
    deleteTree(root->right);
    delete root;
}

// funkcja do generowania kodów
void generateCodes(Node* root, string str, map<char, string>& codeMap) {
    if (!root) return;
    if (!root->left && !root->middle && !root->right) {
        if (root->character != '\0') {
            codeMap[root->character] = str;
        }
        return;
    }
    if (root->left)   generateCodes(root->left,   str + "0", codeMap);
    if (root->middle) generateCodes(root->middle, str + "1", codeMap);
    if (root->right)  generateCodes(root->right,  str + "2", codeMap);
}

// Huffman ternarny
Node* TernaryHuffman(const map<char, int>& C) {
    priority_queue<Node*, vector<Node*>, Compare> Q;

    
    liczba_przypisan++; 
    for (auto const& [key, val] : C) {
        liczba_porownan++; 
        Q.push(new Node(key, val));
        liczba_przypisan++; 
    }

    // Sprawdzenie parzystości
    liczba_porownan++; 
    if (Q.size() % 2 == 0) {
        Q.push(new Node('\0', 0)); 
        liczba_przypisan++; 
    }

    //budowanie drzewa
    while (true) {
        liczba_porownan++; 
        if (Q.size() <= 1) break;


        Node* z = new Node('\0', 0);
        liczba_przypisan++; 


        Node* x = Q.top(); 
        Q.pop();
        x->parent = z;
        z->left = x;
        liczba_przypisan += 3; 


        Node* y = Q.top(); 
        Q.pop();
        y->parent = z;
        z->middle = y;
        liczba_przypisan += 3;


        Node* w = nullptr;
        liczba_przypisan++;

        liczba_porownan++; 
        if (!Q.empty()) {
            w = Q.top(); 
            Q.pop();
            w->parent = z;
            z->right = w;
            liczba_przypisan += 3;
        }


        liczba_porownan++; 
        z->freq = x->freq + y->freq + (w ? w->freq : 0);
        liczba_przypisan++;


        Q.push(z);
        
    }

    return Q.top();
}

// funkcja generująca  tekst
string generateRandomText(int length) {
    string text = "";
    //
    const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; 
    for (int i = 0; i < length; i++) {
        text += alphabet[rand() % alphabet.length()];
    }
    return text;
}

int main() {
    srand(time(0));

    // Zestaw testowy: długości generowanego tekstu
    vector<int> text_sizes = { 100, 1000, 10000, 100000, 500000, 1000000 };

    cout << "testy algorytmu dla wersji ternarnej" << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    printf("%-10s | %-12s | %-15s | %-15s | %-15s\n", "długosc", "unikalne znaki", "czas (us)", "porownania", "przypisania");
    cout << "--------------------------------------------------------------------------------------------------" << endl;

    for (int n : text_sizes) {

        string text = generateRandomText(n);
        map<char, int> frequencies;
        for (char c : text) frequencies[c]++;

        int unique_chars = frequencies.size();

        // reset liczników
        liczba_porownan = 0;
        liczba_przypisan = 0;

        // pomiar czasu 
        auto start = chrono::high_resolution_clock::now();

        Node* root = TernaryHuffman(frequencies);

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

        // wypisanie wyników
        printf("%-10d | %-12d | %-15lld | %-15lld | %-15lld\n", 
            n, unique_chars, duration, liczba_porownan, liczba_przypisan);

        // sprzątanie pamięci
        deleteTree(root);
    }

    cout << "--------------------------------------------------------------------------------------------------" << endl;

    return 0;
}