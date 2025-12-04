// PhoneBook.h

#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Entry {
    string phoneNumber; 
    string fullName;    // Прізвище, ім'я, по-батькові
};

class PhoneBook {
private:
    vector<Entry> entries;
    int CodeError; // Код помилки

public:
    PhoneBook() : CodeError(0) {}

    void addEntry(const string& phone, const string& name);
    
    // Оператор індексації [] (Індекс: Телефон -> Повертає: ПІБ)
    string operator[](const string& phoneIndex);
    
    // Оператор виклику функції () (Індекс: ПІБ -> Повертає: Телефон)
    string operator()(const string& nameIndex);

    // Дружні операції введення та виведення
    friend ostream& operator<<(ostream& os, const PhoneBook& book);
    friend istream& operator>>(istream& is, PhoneBook& book);

    void createSet(); // Функція створення набору
    int getErrorCode() const { return CodeError; }
};

#endif // PHONEBOOK_H