#pragma once
#include <string>
#include <iostream>

using namespace std;

class Money {
private:
    int n500, n200, n100, n50, n20, n10, n5, n2, n1;
    int m50, m25, m10, m5, m2, m1;

    void distributeFromTotal(double totalAmount);

public:
    Money();
    Money(double amount);
    Money(const Money& other);

    double getTotal() const;

    Money& operator=(const Money& other);
    operator string() const;

    Money& operator++();
    Money operator++(int);
    Money& operator--();
    Money operator--(int);

    friend ostream& operator<<(ostream& out, const Money& m);
    friend istream& operator>>(istream& in, Money& m);

    friend Money operator+(const Money& a, const Money& b);
    friend Money operator-(const Money& a, const Money& b);
    friend double operator/(const Money& a, const Money& b);
    friend Money operator/(const Money& a, double scalar);
    friend Money operator*(const Money& a, double scalar);
    friend Money operator*(double scalar, const Money& a);

    friend bool operator==(const Money& a, const Money& b);
    friend bool operator!=(const Money& a, const Money& b);
    friend bool operator>(const Money& a, const Money& b);
    friend bool operator<(const Money& a, const Money& b);
    friend bool operator>=(const Money& a, const Money& b);
    friend bool operator<=(const Money& a, const Money& b);
};