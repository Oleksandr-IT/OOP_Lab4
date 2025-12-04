// Vector3F.h

#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include <string>
#include <cmath> 
#include <stdexcept>

using namespace std;

// Коди помилок
enum ErrorCode {
    E_OK = 0,
    E_NULL_PTR = 1,
    E_DIVISION_BY_ZERO = 2,
    E_INDEX_OUT_OF_RANGE = 3
};

class Vector3F {
private:
    float *x, *y, *z; // Динамічне виділення пам'яті
    ErrorCode State;  // Змінна стану
    static int objectCount; // Лічильник об'єктів

    void allocateMemory(); 
    void deallocateMemory(); 

public:
    // Конструктори
    Vector3F(); 
    Vector3F(float value); 
    Vector3F(float vx, float vy, float vz);
    Vector3F(const float* arr); // З вказівником
    Vector3F(const Vector3F& other); 
    ~Vector3F(); // Деструктор

    // Оператор присвоєння
    Vector3F& operator=(const Vector3F& other);

    // Інкремент/декремент (префіксні/постфіксні)
    Vector3F& operator++(); 
    Vector3F operator++(int);
    Vector3F& operator--();
    Vector3F operator--(int);

    // Унарні оператори
    bool operator!() const; 
    Vector3F operator~() const; // Побітове заперечення (перпендикуляр)
    Vector3F operator-() const; 

    // Оператор індексації []
    float& operator[](int index);
    const float& operator[](int index) const;

    // Оператори присвоєння з арифметичною дією
    Vector3F& operator+=(const Vector3F& other);
    Vector3F& operator-=(const Vector3F& other);
    Vector3F& operator*=(float scalar);
    Vector3F& operator/=(float scalar);
    
    // --- Дружні функції (Бінарні та I/O) ---
    friend ostream& operator<<(ostream& os, const Vector3F& v);
    friend istream& operator>>(istream& is, Vector3F& v);

    friend Vector3F operator+(const Vector3F& v1, const Vector3F& v2);
    friend Vector3F operator-(const Vector3F& v1, const Vector3F& v2);
    friend Vector3F operator*(const Vector3F& v, float scalar);
    friend Vector3F operator/(const Vector3F& v, float scalar);
    
    friend Vector3F operator&(const Vector3F& v1, const Vector3F& v2); // Векторний добуток
    friend float operator%(const Vector3F& v1, const Vector3F& v2);    // Остача від ділення

    // Оператори порівняння (потрібні як friend для доступу до приватних полів)
    friend bool operator==(const Vector3F& v1, const Vector3F& v2);
    friend bool operator!=(const Vector3F& v1, const Vector3F& v2);
    friend bool operator>(const Vector3F& v1, const Vector3F& v2);
    friend bool operator<(const Vector3F& v1, const Vector3F& v2);
    friend bool operator>=(const Vector3F& v1, const Vector3F& v2);
    friend bool operator<=(const Vector3F& v1, const Vector3F& v2);

    ErrorCode getState() const { return State; }
    static int getObjectCount() { return objectCount; }
    void checkWorkingStatus() const; 
};

#endif // VECTOR3F_H