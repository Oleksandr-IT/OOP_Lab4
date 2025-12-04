// main.cpp

#include "Vector3F.h"
#include "PhoneBook.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <iomanip>

using namespace std;

// Прототипи функцій демонстрації (реалізовані у Vector3F.cpp та PhoneBook.cpp)
void runVector3FDemo(); 
void runPhoneBookDemo(); 

// --- Реалізація Завдання 6: Середнє арифметичне крім a_i ---
void calculateAverageArray() {
    cout << "\n\n=======================================================" << endl;
    cout << "=== ЗАВДАННЯ 6: Середнє арифметичне крім a_i ===" << endl;
    cout << "=======================================================" << endl;

    const int MAX_N = 200;
    int n;

    // Введення розміру масиву
    cout << "Введіть розмір масиву N (N <= 200): ";
    if (!(cin >> n) || n <= 0 || n > MAX_N) {
        cout << "Використовуємо демонстраційний розмір N=5." << endl;
        n = 5;
    }
    // Очистка буфера для подальшого вводу
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<double> A(n);
    vector<double> B(n);
    double totalSum = 0.0;

    // Введення елементів масиву A (або використання демонстраційних даних)
    cout << "Введіть елементи масиву A (або 10 20 30 40 50 для демонстрації):" << endl;
    A = {10.0, 20.0, 30.0, 40.0, 50.0}; // Демонстраційні дані

    for (int i = 0; i < n; ++i) {
        // У реальній програмі тут буде ввід від користувача, але для демо використовуємо A
        totalSum += A[i];
    }
    
    // Побудова масиву B
    // b_i = (TotalSum - a_i) / (N - 1)
    if (n > 1) {
        for (int i = 0; i < n; ++i) {
            double sumWithoutCurrent = totalSum - A[i];
            B[i] = sumWithoutCurrent / (n - 1);
        }
    } else {
        // Випадок N=1: середнє арифметичне не визначене
        B[0] = 0.0; 
    }

    // Виведення результату
    cout << "\nМасив A: [";
    for (int i = 0; i < n; ++i) {
        cout << A[i] << (i == n - 1 ? "" : ", ");
    }
    cout << "]" << endl;
    
    cout << "Масив B (середнє арифметичне без A[i]): [";
    cout << fixed << setprecision(4); 
    for (int i = 0; i < n; ++i) {
        cout << B[i] << (i == n - 1 ? "" : ", ");
    }
    cout << "]" << endl;
}

// === ТОЧКА ВХОДУ ===
int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");

    cout << "--- Запуск Лабораторної роботи №4 ---\n";
    
    // Виконуємо всі завдання
    try {
        runVector3FDemo();
        runPhoneBookDemo();
        calculateAverageArray();
    } catch (const std::exception& e) {
        cerr << "\nКритична помилка виконання: " << e.what() << endl;
    } catch (...) {
        cerr << "\nВиникла невідома помилка виконання." << endl;
    }

    return 0;
}