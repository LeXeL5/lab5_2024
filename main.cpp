#include <iostream>
using namespace std;
const int hashSize = 26;
void menu() {
    cout << "(0) shutdown program" << endl;
    cout << "(1) add" << endl;
    cout << "(2) remove" << endl;
    cout << "(3) clear" << endl;
    cout << "(4) contains" << endl;
    cout << "(5) count" << endl;
    cout << "(6) ToArray and cout" << endl;
}
struct HashSet {
    struct Node {
        string data = "";
        Node* next = nullptr;
    };
    Node* table[hashSize];
    int size;
    HashSet() {
        size = 0;
        for (int i = 0; i < hashSize; i++) {
            table[i] = nullptr;
        }
    }
    int hashFunc(string line) {
        return abs((int)line[0]) % hashSize;
    }
    void add(string line) {
        int index = hashFunc(line);
        Node* current = table[index];
        size++;
        if (current == nullptr) {
            table[index] = new Node{ line };
            return;
        }
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node{ line };
    }
    void remove(string line) {
        int index = hashFunc(line);
        if (table[index] == nullptr) return;
        Node* current = table[index];
        if (current->data == line) {
            table[index] = current->next;
            delete current;
            size--;
            return;
        }
        while (current->next != nullptr) {
            if (current->next->data == line) {
                Node* temp = current->next->next;
                delete current->next;
                current->next = temp;
                size--;
                return;
            }
            current = current->next;
        }
    }
    void clear() {
        for (int i = 0; i < hashSize; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current->next;
                delete current;
                size--;
                current = temp;
            }
            table[i] = nullptr;
        }
    }
    bool contains(string line) {
        int index = hashFunc(line);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->data == line) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    int count() {
        return size;
    }
    string* ToArray() {
        if (!size) return nullptr;
        string* arr = new string[size];
        int j = 0;
        for (Node* current : table) {
            while (current != nullptr) {
                arr[j] = current->data;
                j++;
                current = current->next;
            }
        }
        return arr;
    }
};
int main() {
    HashSet hashset;
    int switch_on;
    string input;
    string* arr;
    while (true) {
        system("cls");
        menu();
        cout << endl;
        cout << "Choice: ";
        cin >> switch_on;
        switch (switch_on) {
        case 0:
            return 0;
        case 1:
            cout << "line to add: ";
            cin >> input;
            hashset.add(input);
            cout << "line is added!";
            break;
        case 2:
            cout << "line to remove: ";
            cin >> input;
            hashset.remove(input);
            cout << "line is removed!";
            break;
        case 3:
            hashset.clear();
            cout << "Hash set is cleared!";
            break;
        case 4:
            cout << "line to search: ";
            cin >> input;
            if (hashset.contains(input)) {
                cout << "This line IS IN hash set!";
            }
            else {
                cout << "This line IS NOT IN hash set!";
            }
            break;
        case 5:
            cout << "Hash set size: " << hashset.count();
            break;
        case 6:
            arr = hashset.ToArray();
            for (int i = 0; i < hashset.count(); i++) {
                cout << arr[i] << " ";
            }
            break;
        default:
            cout << "Unknown command, try again";
            break;
        }
        cout << endl;
        system("pause");
    }
}