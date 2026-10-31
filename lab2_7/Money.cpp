#include "Money.h"
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

void Money::distributeFromTotal(double totalAmount) {
    if (totalAmount < 0) totalAmount = 0;
    long totalKopecks = round(totalAmount * 100);

    n500 = totalKopecks / 50000; totalKopecks %= 50000;
    n200 = totalKopecks / 20000; totalKopecks %= 20000;
    n100 = totalKopecks / 10000; totalKopecks %= 10000;
    n50 = totalKopecks / 5000;  totalKopecks %= 5000;
    n20 = totalKopecks / 2000;  totalKopecks %= 2000;
    n10 = totalKopecks / 1000;  totalKopecks %= 1000;
    n5 = totalKopecks / 500;   totalKopecks %= 500;
    n2 = totalKopecks / 200;   totalKopecks %= 200;
    n1 = totalKopecks / 100;   totalKopecks %= 100;

    m50 = totalKopecks / 50;    totalKopecks %= 50;
    m25 = totalKopecks / 25;    totalKopecks %= 25;
    m10 = totalKopecks / 10;    totalKopecks %= 10;
    m5 = totalKopecks / 5;     totalKopecks %= 5;
    m2 = totalKopecks / 2;     totalKopecks %= 2;
    m1 = totalKopecks / 1;     totalKopecks %= 1;
}

double Money::getTotal() const {
    return (n500 * 500) + (n200 * 200) + (n100 * 100) + (n50 * 50) +
        (n20 * 20) + (n10 * 10) + (n5 * 5) + (n2 * 2) + (n1 * 1) +
        (m50 * 0.50) + (m25 * 0.25) + (m10 * 0.10) +
        (m5 * 0.05) + (m2 * 0.02) + (m1 * 0.01);
}

Money::Money() { distributeFromTotal(0); }
Money::Money(double amount) { distributeFromTotal(amount); }
Money::Money(const Money& other) { distributeFromTotal(other.getTotal()); }

Money& Money::operator=(const Money& other) {
    if (this != &other) {
        distributeFromTotal(other.getTotal());
    }
    return *this;
}

Money::operator string() const {
    stringstream sout;
    double total = getTotal();
    long grn = floor(total);
    long kop = round((total - grn) * 100);
    sout << grn << "," << setfill('0') << setw(2) << kop << " грн";
    return sout.str();
}

Money& Money::operator++() {
    distributeFromTotal(getTotal() + 0.01);
    return *this;
}

Money Money::operator++(int) {
    Money temp(*this);
    ++(*this);
    return temp;
}

Money& Money::operator--() {
    distributeFromTotal(getTotal() - 0.01);
    return *this;
}

Money Money::operator--(int) {
    Money temp(*this);
    --(*this);
    return temp;
}

ostream& operator<<(ostream& out, const Money& m) {
    out << static_cast<string>(m);
    return out;
}

istream& operator>>(istream& in, Money& m) {
    double amount;
    cout << "¬вед≥ть суму: ";
    in >> amount;
    m.distributeFromTotal(amount);
    return in;
}

Money operator+(const Money& a, const Money& b) { return Money(a.getTotal() + b.getTotal()); }
Money operator-(const Money& a, const Money& b) { return Money(a.getTotal() - b.getTotal()); }
double operator/(const Money& a, const Money& b) { return (b.getTotal() == 0) ? 0 : a.getTotal() / b.getTotal(); }
Money operator/(const Money& a, double scalar) { return (scalar > 0) ? Money(a.getTotal() / scalar) : Money(0); }
Money operator*(const Money& a, double scalar) { return (scalar > 0) ? Money(a.getTotal() * scalar) : Money(0); }
Money operator*(double scalar, const Money& a) { return a * scalar; }

bool operator==(const Money& a, const Money& b) { return abs(a.getTotal() - b.getTotal()) < 0.001; }
bool operator!=(const Money& a, const Money& b) { return !(a == b); }
bool operator>(const Money& a, const Money& b) { return a.getTotal() > b.getTotal(); }
bool operator<(const Money& a, const Money& b) { return b > a; }
bool operator>=(const Money& a, const Money& b) { return a > b || a == b; }
bool operator<=(const Money& a, const Money& b) { return a < b || a == b; }