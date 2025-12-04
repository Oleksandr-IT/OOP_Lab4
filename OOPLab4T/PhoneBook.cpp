#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

enum CodeError {
    OK,
    INDEX_ERROR,
    NOT_FOUND
};

class Assoc {
private:
    struct Pair {
        string phone;
        string pib; // Прізвище, ім’я, по-батькові
    };

    Pair* arr;        // масив пар
    int size;         // кількість елементів
    CodeError state;  // код помилки

public:
    Assoc() : arr(nullptr), size(0), state(OK) {}

    Assoc(int n) {
        if (n <= 0) {
            size = 0;
            arr = nullptr;
            state = INDEX_ERROR;
        } else {
            size = n;
            arr = new Pair[n];
            state = OK;
        }
    }

    ~Assoc() {
        delete[] arr;
    }

    Pair& operator[](int index) {
        if (index < 0 || index >= size) {
            state = INDEX_ERROR;
            static Pair dummy = {"", ""};
            return dummy;
        }
        state = OK;
        return arr[index];
    }

    string operator()(const string& phone) {
        for (int i = 0; i < size; i++) {
            if (arr[i].phone == phone) {
                state = OK;
                return arr[i].pib;
            }
        }
        state = NOT_FOUND;
        return "";
    }

    CodeError getState() const {
        return state;
    }

    friend ostream& operator<<(ostream& os, const Assoc& a);
    friend istream& operator>>(istream& is, Assoc& a);
};

ostream& operator<<(ostream& os, const Assoc& a) {
    for (int i = 0; i < a.size; i++) {
        os << "[" << i << "]  "
           << a.arr[i].phone << "  ->  "
           << a.arr[i].pib << endl;
    }
    return os;
}

istream& operator>>(istream& is, Assoc& a) {
    for (int i = 0; i < a.size; i++) {
        cout << "Телефон #" << i << ": ";
        is >> a.arr[i].phone;
        is.ignore();
        cout << "ПІБ #" << i << ": ";
        getline(is, a.arr[i].pib);
    }
    return is;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n;
    cout << "Кількість елементів: ";
    cin >> n;

    Assoc book(n);
    cin >> book;

    cout << "\nВаш асоціативний масив:\n";
    cout << book;

    cout << "\nПошук по індексу 0:\n";
    cout << "Телефон: " << book[0].phone << endl;
    cout << "ПІБ: " << book[0].pib << endl;

    cout << "\nПошук по номеру телефону:\n";
    string t;
    cout << "Введіть номер: ";
    cin >> t;

    string result = book(t);
    if (book.getState() == OK)
        cout << "Знайдено: " << result << endl;
    else
        cout << "Немає такого номера!" << endl;

    return 0;
}
