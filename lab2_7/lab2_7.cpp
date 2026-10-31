#include <iostream>
#include <Windows.h>
#include "Account.h"

#pragma pack(push, 1)
struct MoneyPacked {
    int counts[15];
};
struct AccountPacked {
    string surname;
    unsigned int nomer;
    double percent;
    MoneyPacked summa;
};
#pragma pack(pop)

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Розмір Money без pack(1): " << sizeof(Money) << " байт" << endl;
    cout << "Розмір Money з pack(1): " << sizeof(MoneyPacked) << " байт" << endl;
    cout << "Розмір Account без pack(1): " << sizeof(Account) << " байт" << endl;
    cout << "Розмір Account з pack(1): " << sizeof(AccountPacked) << " байт\n" << endl;

    Money m1(100.50);
    Money m2;
    cout << "Створення m2:" << endl;
    cin >> m2;

    cout << "Сума 1: " << m1 << endl;
    cout << "Сума 2: " << m2 << endl;
    cout << "m1 + m2 = " << (m1 + m2) << endl;
    cout << "m1 * 2 = " << (m1 * 2) << endl;
    cout << "m1 > m2 : " << (m1 > m2 ? "Так" : "Ні") << endl;

    ++m1;
    cout << "m1 після інкременту (додано 1 коп): " << m1 << endl;

    Account acc1("Іваненко", 12345, 5.0, Money(1992.28));
    cout << acc1 << endl;
    cout << "Сума прописом: " << string(acc1) << endl;

    acc1.calculate_percent();
    cout << "Після нарахування відсотків: " << acc1 << endl;

    acc1++; 
    cout << "Після збільшення відсотку (acc1++): " << acc1 << endl;

    Account acc2 = acc1; 
    acc2.change_owner("Петренко");
    cout << "Копія рахунку з новим власником: " << acc2 << endl;

    Account accounts[2];
    accounts[0] = Account("Шевченко", 111, 2.5, Money(10000));
    accounts[1] = Account("Бойко", 222, 3.0, Money(5000));

    for (int i = 0; i < 2; i++) {
        cout << "[" << i << "]: " << accounts[i] << endl;
    }

    return 0;
}