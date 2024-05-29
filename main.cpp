#include <iostream>

using namespace std;

struct Node {
    int key;
    Node* next;
    Node(int k) : key(k), next(nullptr) {}
};

class PriorityQueue {
public:
    PriorityQueue() : head(nullptr) {}

    void insert(int key) {
        Node* newNode = new Node(key);
        if (!head || head->key > key) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->key <= key) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    int getMin() {
        if (!head) {
            cout << "Kolejka jest pusta.\n";
            return -1;
        }
        return head->key;
    }

    void deleteMin() {
        if (!head) {
            cout << "Kolejka jest pusta!" << endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void increaseKey(int old_val, int new_val) {
        if (!head) {
            cout << "Kolejka jest pusta." << endl;
            return;
        }
        Node* current = head;
        Node* prev = nullptr;
        while (current && current->key != old_val) {
            prev = current;
            current = current->next;
        }
        if (!current) {
            cout << "Klucz " << old_val << " nie został znaleziony." << endl;
            return;
        }
        if (new_val <= old_val) {
            cout << "Nowy klucz musi byc wiekszy niz stary klucz." << endl;
            return;
        }
        if (prev) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        delete current;
        insert(new_val);
    }

    void display() {

        if (!head) {
            cout << "Kolejka jest pusta!" << endl;
            return;
        }

        Node* current = head;
        while (current) {
            cout << current->key << " ";
            current = current->next;
        }
        cout << endl;
    }

private:
    Node* head;
};

void menu() {
    PriorityQueue pq;
    int choice, value_1, value_2;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Wstaw" << endl;
        cout << "2. Znajdz wartosc minimalna" << endl;
        cout << "3. Usun wartosc minimalna" << endl;
        cout << "4. Zamien klucz na wiekszy" << endl;
        cout << "5. Wyswietl kolejke" << endl;
        cout << "6. Wyjdz" << endl;
        cout << "Wybierz opcje: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Wprowadz wartosc do wstawienia: ";
                cin >> value_1;
                pq.insert(value_1);
                break;
            case 2:
                value_1 = pq.getMin();
                if (value_1 != -1) {
                    cout << "Minimalna wartosc to: " << value_1 << endl;
                }
                break;
            case 3:
                pq.deleteMin();
                cout << "Minimalna wartosc zostala usunieta" << endl;
                break;
            case 4:
                cout << "Wprowadz stary klucz: ";
                cin >> value_1;
                cout << "Wprowadz nowy klucz: ";
                cin >> value_2;
                pq.increaseKey(value_1, value_2);
                break;
            case 5:
                pq.display();
                break;
            case 6:
                return;
            default:
                cout << "Nieprawidlowa opcja...\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
