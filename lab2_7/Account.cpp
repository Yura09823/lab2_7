#include "Account.h"
#include <sstream>
#include <cmath>

using namespace std;

Account::Account() : surname("нев≥домо"), nomer(0), percent(0.0), summa(0.0) {}

Account::Account(string s, unsigned int n, double p, const Money& m) {
    setSurname(s);
    setNomer(n);
    setPercent(p);
    setSumma(m);
}

Account::Account(const Account& other)
    : surname(other.surname), nomer(other.nomer), percent(other.percent), summa(other.summa) {
}

void Account::setSurname(string value) { surname = value.empty() ? "нев≥домо" : value; }
void Account::setNomer(unsigned int value) { nomer = (value > 0) ? value : 0; }
void Account::setPercent(double value) { percent = (value >= 0.0) ? value : 0.0; }
void Account::setSumma(const Money& value) { summa = value; }

Account& Account::operator=(const Account& other) {
    if (this != &other) {
        surname = other.surname;
        nomer = other.nomer;
        percent = other.percent;
        summa = other.summa;
    }
    return *this;
}

Account::operator string() const {
    double total = summa.getTotal();
    int UAH = (int)floor(total);
    int kopecks = (int)round((total - UAH) * 100);

    if (UAH == 0) return "нуль грн. " + to_string(kopecks) + " коп.";

    string ones[] = { "", "одна", "дв≥", "три", "чотири", "п'€ть", "ш≥сть", "с≥м", "в≥с≥м", "дев'€ть" };
    string teens[] = { "дес€ть", "одинадц€ть", "дванадц€ть", "тринадц€ть", "чотирнадц€ть", "п'€тнадц€ть", "ш≥стнадц€ть", "с≥мнадц€ть", "в≥с≥мнадц€ть", "дев'€тнадц€ть" };
    string tens[] = { "", "", "двадц€ть", "тридц€ть", "сорок", "п'€тдес€т", "ш≥стдес€т", "с≥мдес€т", "в≥с≥мдес€т", "дев'€носто" };
    string hundreds[] = { "", "сто", "дв≥ст≥", "триста", "чотириста", "п'€тсот", "ш≥стсот", "с≥мсот", "в≥с≥мсот", "дев'€тсот" };

    string result = "";
    int thousands = (UAH / 1000) % 1000;
    int units = UAH % 1000;

    if (thousands > 0) {
        result += hundreds[thousands / 100] + (thousands / 100 > 0 ? " " : "");
        int th_tens = thousands % 100;
        if (th_tens >= 10 && th_tens <= 19) {
            result += teens[th_tens - 10] + " тис€ч ";
        }
        else {
            result += tens[th_tens / 10] + (th_tens / 10 > 0 ? " " : "");
            result += ones[th_tens % 10] + (th_tens % 10 > 0 ? " " : "");
            if (th_tens % 10 == 1) result += "тис€ча ";
            else if (th_tens % 10 >= 2 && th_tens % 10 <= 4) result += "тис€ч≥ ";
            else result += "тис€ч ";
        }
    }
    if (units > 0) {
        result += hundreds[units / 100] + (units / 100 > 0 ? " " : "");
        int un_tens = units % 100;
        if (un_tens >= 10 && un_tens <= 19) {
            result += teens[un_tens - 10] + " ";
        }
        else {
            result += tens[un_tens / 10] + (un_tens / 10 > 0 ? " " : "");
            result += ones[un_tens % 10] + (un_tens % 10 > 0 ? " " : "");
        }
    }
    if (!result.empty() && result.back() == ' ') result.pop_back();

    stringstream ss;
    ss << result << " грн. " << (kopecks < 10 ? "0" : "") << kopecks << " коп.";
    return ss.str();
}

Account& Account::operator++() {
    percent += 1.0;
    return *this;
}

Account Account::operator++(int) {
    Account temp(*this);
    ++(*this);
    return temp;
}

Account& Account::operator--() {
    if (percent >= 1.0) percent -= 1.0;
    return *this;
}

Account Account::operator--(int) {
    Account temp(*this);
    --(*this);
    return temp;
}

void Account::change_owner(string newOwner) { setSurname(newOwner); }
bool Account::zabraty_money(const Money& amount) {
    if (summa >= amount) {
        summa = summa - amount;
        return true;
    }
    return false;
}
void Account::put_money(const Money& amount) { summa = summa + amount; }
void Account::calculate_percent() { summa = summa + (summa * (percent / 100.0)); }
double Account::to_dolar(double exchange) const { return summa.getTotal() / exchange; }
double Account::to_euro(double exchange) const { return summa.getTotal() / exchange; }

ostream& operator<<(ostream& out, const Account& acc) {
    out << "¬ласник: " << acc.surname << ", –ахунок: " << acc.nomer
        << ", ¬≥дсоток: " << acc.percent << "%, Ѕаланс: " << string(acc.summa);
    return out;
}

istream& operator>>(istream& in, Account& acc) {
    string s; unsigned int n; double p; Money m;
    cout << "¬вед≥ть пр≥звище: "; in >> s;
    cout << "¬вед≥ть номер рахунку: "; in >> n;
    cout << "¬вед≥ть в≥дсоток: "; in >> p;
    in >> m;
    acc = Account(s, n, p, m);
    return in;
}