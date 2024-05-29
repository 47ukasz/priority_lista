#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* next;
    Node(int v) : value(v), next(nullptr) {}
};

class PriorityQueue {
private:
    Node* head;

public:
    PriorityQueue() : head(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head || head->value < value) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->value >= value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    int findMin() {
        if (!head) {
            cout << "Kolejka jest pusta" << endl;
            return -1;
        }

        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        return current->value;
    }

    void deleteMin() {
        if (!head) {
            cout << "Kolejka jest pusta" << endl;
            return;
        }

        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }

        Node* current = head;
        while (current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }

    void increaseKey(int oldValue, int newValue) {
        if (newValue <= oldValue) {
            cout << "Nowa wartosc musi byc wieksza od poprzedniej" << endl;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current && current->value != oldValue) {
            prev = current;
            current = current->next;
        }

        if (!current) {
            cout << "Element nie zostal znaleziony" << endl;
            return;
        }

        if (prev) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        delete current;

        insert(newValue);
    }

    void display() {
        Node* current = head;
        while (current) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    PriorityQueue pq;
    int choice, value, oldValue, newValue;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Dodaj" << endl;
        cout << "2. Minimum" << endl;
        cout << "3. Usun element (minimum)" << endl;
        cout << "4. Zwieksz klucz" << endl;
        cout << "5. Wyswietl" << endl;
        cout << "6. Wyjdz" << endl;
        cout << "Opcja: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Wprowadz wartosc: ";
                cin >> value;
                pq.insert(value);
                break;
            case 2:
                value = pq.findMin();
                if (value != -1) {
                    cout << "Wartosc minimalna: " << value << endl;
                }
                break;
            case 3:
                pq.deleteMin();
                break;
            case 4:
                cout << "Wprowadz stary klucz: ";
                cin >> oldValue;
                cout << "Wprowadz nowy klucz: ";
                cin >> newValue;
                pq.increaseKey(oldValue, newValue);
                break;
            case 5:
                pq.display();
                break;
            case 6:
                cout << "Wychodzenie..." << endl;
                return 0;
            default:
                cout << "Niepoprawna opcja..." << endl;
        }
    }

    return 0;
}
