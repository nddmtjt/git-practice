#include <iostream>

using namespace std;

class Equation {
    friend bool operator==(const Equation& lhs, const Equation& rhs);
    friend ostream& operator<<(ostream& out, const Equation& eq);
public:
    Equation(double coefficients[], int number) : size{number}, coeff{new double[size]{}} {
        for (int i{0}; i<size; i++) {
            coeff[i] += coefficients[i];
        }
    }
    Equation(const Equation& rhs) : size{rhs.size}, coeff{new double[size]{}} {
        for (size_t i{0}; i < size; i++)
            coeff[i] = rhs.coeff[i];
    }             // copy constructor
    ~Equation() {
        delete[] coeff;
    }
    int degree() const {
        return size - 1;
    }
    Equation& operator=(const Equation& rhs) {
        if (this != &rhs) {
            if (size != rhs.size) {
                size = rhs.size;
                delete[] coeff;
                coeff = new double[size]{};
            }
            for (int i{0}; i<size; i++) {
                coeff[i] = rhs.coeff[i];
            }
        }
        return *this;
    }
    Equation& operator+=(const Equation& rhs) {
        if (size >= rhs.size) {
            for (int i{0}; i<rhs.size; i++) {
                coeff[size-rhs.size+i] += rhs.coeff[i];
            }
        }
        else {
            double* result{new double[rhs.size]{}};
            for (int i{0}; i<rhs.size; i++) {
                result[i] += rhs.coeff[i];
            }
            for (int i{0}; i<size; i++) {
                result[rhs.size-size+i] += coeff[i];
            }
            delete[] coeff;
            coeff = result;
            size = rhs.size;
        }
        return *this;
    }
    Equation& operator-=(const Equation& rhs) {
        if (size >= rhs.size) {
            for (int i{0}; i<rhs.size; i++) {
                coeff[size-rhs.size+i] -= rhs.coeff[i];
            }
        }
        else {
            double* result{new double[rhs.size]{}};
            for (int i{0}; i<rhs.size; i++) {
                result[i] -= rhs.coeff[i];
            }
            for (int i{0}; i<size; i++) {
                result[rhs.size-size+i] += coeff[i];
            }
            delete[] coeff;
            coeff = result;
            size = rhs.size;
        }
        return *this;
    }
    Equation& operator*=(double rhs) {
        for (int i{0}; i<size; i++) {
            coeff[i] *= rhs;
        }
        return *this;
    }
private:
    int size;       // size of the coeff array (= degree + 1)
    double* coeff;  // coeff is a pointer to an array
};

Equation operator+(const Equation& lhs, const Equation& rhs) {
    Equation result{lhs};
    result+=rhs;
    return result;
}
Equation operator-(const Equation& lhs, const Equation& rhs) {
    Equation result{lhs};
    result-=rhs;
    return result;
}
Equation operator*(const Equation& lhs, double rhs) {
    Equation result{lhs};
    result*=rhs;
    return result;
}
Equation operator*(double lhs, const Equation& rhs) {
    Equation result{rhs};
    result*=lhs;
    return result;
}

bool operator==(const Equation& lhs, const Equation& rhs) {
    if (lhs.degree() != rhs.degree()) {
        return false;
    }
    for (size_t i{0}; i < lhs.size; i++)
        if (lhs.coeff[i] != rhs.coeff[i])
            return false;
    return true;
}

ostream& operator<<(ostream& out, const Equation& eq) {
    for (int i{0}; i<eq.size-1; i++) {
        if (eq.coeff[i] != 0) {
            out << eq.coeff[i] << "x^" << eq.degree() - i;
        }
        if (eq.coeff[i+1] > 0) {
            out << '+';
        }
    }
    if (eq.coeff[eq.degree()] != 0) {
        out << eq.coeff[eq.degree()];
    }
    out << "=0";
    return out;
}

int main() {
    int n;
    cout << "Number of terms in equation eq1: " ;
    cin >> n;
    double* element1{new double[n]{}};
    cout << "Coefficients from the highest terms: ";
    for (int i{0}; i<n; i++) {
        cin >> element1[i];
    }
    Equation eq1(element1, n);
    cout << "Number of terms in equation eq2: " ;
    cin >> n;
    double* element2{new double[n]{}};
    cout << "Coefficients from the highest terms: ";
    for (int i{0}; i<n; i++) {
        cin >> element2[i];
    }
    Equation eq2(element2, n);
    cout << "eq1: " << eq1 << endl;
    cout << "eq2: " << eq2 << endl;

    Equation C{ eq1 + eq2 };
    cout << "eq1+eq2: " << C << endl;
    if (eq1 == eq2)
        cout << "eq1 and eq2 are equal" << endl;
    else {
        cout << "eq1 and eq2 are not equal" << endl;
        Equation D{ eq1 - eq2};
        cout << "eq1-eq2: " << D << endl;
    }
    Equation eq3{eq1};
    cout << "eq3 after eq3(eq1): " << eq3 << endl;
    eq3 += eq2;
    cout << "eq3 after eq3+=eq2: " << eq3 << endl;
    Equation eq4{ eq3 * 0.5 };
    cout << "eq3*0.5: " << eq4 << endl;
    Equation eq5{ 4 * eq3 };
    cout << "4*eq3: " << eq5 << endl;

    return 0;
}
