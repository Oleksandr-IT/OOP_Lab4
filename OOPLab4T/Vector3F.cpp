#include <iostream>
using namespace std;

enum State { OK, NULLPTR, DIV0, BAD_INDEX };

class Vector3F {
private:
    float x, y, z;
    static int count;    

public:
    State state;          // стан помилки

    Vector3F() : x(0), y(0), z(0), state(OK) { count++; }

    Vector3F(float a) : x(a), y(a), z(a), state(OK) { count++; }

    Vector3F(float* p) {
        if (!p) {
            state = NULLPTR;
            x = y = z = 0;
        } else {
            x = p[0]; y = p[1]; z = p[2];
            state = OK;
        }
        count++;
    }

    ~Vector3F() {
        cout << "Destroying Vector3F: (" << x << ", " << y << ", " << z << ")\n";
        count--;
    }

    Vector3F& operator++() { x++; y++; z++; return *this; }    // prefix ++
    Vector3F operator++(int) { Vector3F tmp = *this; ++(*this); return tmp; }

    Vector3F& operator--() { x--; y--; z--; return *this; }    // prefix --
    Vector3F operator--(int) { Vector3F tmp = *this; --(*this); return tmp; }

    bool operator!() const { return !(x || y || z); }

    Vector3F operator~() const { return Vector3F(-y, x, 0); } // перпендикуляр

    Vector3F operator-() const { return Vector3F(-x, -y, -z); }

    // --- Присвоєння ---
    Vector3F& operator=(const Vector3F& v) {
        if (this != &v) {
            x = v.x; y = v.y; z = v.z;
            state = v.state;
        }
        return *this;
    }

    Vector3F operator+(const Vector3F& v) const { return Vector3F(x + v.x, y + v.y, z + v.z); }
    Vector3F operator-(const Vector3F& v) const { return Vector3F(x - v.x, y - v.y, z - v.z); }

    // Множення / ділення на число
    Vector3F operator*(float k) const { return Vector3F(x * k, y * k, z * k); }

    Vector3F operator/(float k) {
        if (k == 0) { state = DIV0; return *this; }
        return Vector3F(x / k, y / k, z / k);
    }

    int operator%(float k) {
        if (k == 0) { state = DIV0; return 0; }
        return int(x) % int(k);
    }

    Vector3F operator&(const Vector3F& v) const {
        return Vector3F(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    float& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        if (i == 2) return z;
        state = BAD_INDEX;
        return x; // повертаємо щось, щоб не було UB
    }

    const float& operator[](int i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        if (i == 2) return z;
        return x;
    }

    // Порівняння
    bool operator==(const Vector3F& v) const { return x == v.x && y == v.y && z == v.z; }
    bool operator!=(const Vector3F& v) const { return !(*this == v); }

    bool operator>(const Vector3F& v) const { return x > v.x && y > v.y && z > v.z; }
    bool operator<(const Vector3F& v) const { return x < v.x && y < v.y && z < v.z; }
    bool operator>=(const Vector3F& v) const { return x >= v.x && y >= v.y && z >= v.z; }
    bool operator<=(const Vector3F& v) const { return x <= v.x && y <= v.y && z <= v.z; }

    float operator()() const { return x + y + z; }

    friend Vector3F operator>>(const Vector3F& v, int s) {
        return Vector3F(int(v.x) >> s, int(v.y) >> s, int(v.z) >> s);
    }

    friend Vector3F operator<<(const Vector3F& v, int s) {
        return Vector3F(int(v.x) << s, int(v.y) << s, int(v.z) << s);
    }

    friend ostream& operator<<(ostream& out, const Vector3F& v) {
        out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return out;
    }

    friend istream& operator>>(istream& in, Vector3F& v) {
        in >> v.x >> v.y >> v.z;
        return in;
    }

    Vector3F(float a, float b, float c) : x(a), y(b), z(c), state(OK) { count++; }

    static int getCount() { return count; }
};

int Vector3F::count = 0;

int main() {
    Vector3F v1(1, 2, 3);
    Vector3F v2(4, 5, 6);

    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1 + v2 = " << (v1 + v2) << endl;

    return 0;
}
