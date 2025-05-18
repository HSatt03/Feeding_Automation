#include <iostream>
#include <iomanip>
using namespace std;

void showBalanceBox(double balance) {
    string title = " your balance ";
    string currency = " toman ";
    string balanceStr = to_string((int)balance) + currency;
    int width = 30;

    cout << "+" << string(width, '-') << "+" << endl;
    cout << "|" << setw((width + title.size()) / 2) << right << title;
    cout << setw(width - ((width + title.size()) / 2)) << left << "" << "|" << endl;
    cout << "+" << string(width, '-') << "+" << endl;
    cout << "|" << setw((width + balanceStr.size()) / 2) << right << balanceStr;
    cout << setw(width - ((width + balanceStr.size()) / 2)) << left << "" << "|" << endl;
    cout << "+" << string(width, '-') << "+" << endl;
}

int main() {
    double balance = 48500;
    showBalanceBox(balance);
    return 0;
}