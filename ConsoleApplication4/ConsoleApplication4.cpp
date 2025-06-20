#include <iostream>

int main() {
    double budget = 60.0;    // million rubles
    double percent = 35.0;   // percent of expenses
    double expense;

    double hundred = 100.0;

    __asm {
        fld percent; load percent(35)
        fld budget; load budget(60)
        fmulp st(1), st(0); multiply budget* percent, result in st(0)
        fld hundred; load 100
        fdivp st(1), st(0); divide by 100, result in st(0)
        fstp expense; store result in expense
    }

    std::cout.precision(10);
    std::cout << "Expenses for the budget item: " << expense << " million rubles\n";

    return 0;
}
