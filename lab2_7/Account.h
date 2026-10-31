#pragma once
#include <string>
#include <iostream>
#include "Money.h"

using namespace std;

class Account {
private:
    string surname;
    unsigned int nomer;
    double percent;
    Money summa;

public:
    Account();
    Account(string surname, unsigned int nomer, double percent, const Money& summa);
    Account(const Account& other);

    string getSurname() const { return surname; }
    int getNomer() const { return nomer; }
    double getPercent() const { return percent; }
    Money getSumma() const { return summa; }

    void setSurname(string value);
    void setNomer(unsigned int value);
    void setPercent(double value);
    void setSumma(const Money& value);

    void change_owner(string newOwner);
    bool zabraty_money(const Money& amount);
    void put_money(const Money& amount);
    void calculate_percent();
    double to_dolar(double exchange) const;
    double to_euro(double exchange) const;

    Account& operator=(const Account& other);
    operator string() const;

    Account& operator++();
    Account operator++(int);
    Account& operator--();
    Account operator--(int);

    friend ostream& operator<<(ostream& out, const Account& acc);
    friend istream& operator>>(istream& in, Account& acc);
};