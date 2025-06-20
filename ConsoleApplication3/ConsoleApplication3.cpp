#include <iostream>
#include <cmath>

double quadraticMeanAssembly(double a, double b, double c) {
    double result;
    double three = 3.0;

    __asm {
        fld a; загрузить a
        fmul st(0), st(0); a* a
        fld b; загрузить b
        fmul st(0), st(0); b* b
        faddp st(1), st(0); сложить a ^ 2 + b ^ 2
        fld c; загрузить c
        fmul st(0), st(0); c* c
        faddp st(1), st(0); сложить(a ^ 2 + b ^ 2) + c ^ 2
        fld three; загрузить 3.0
        fdivp st(1), st(0); разделить сумму на 3
        fsqrt; извлечь квадратный корень
        fstp result; сохранить результат
    }

    return result;
}

int main() {
    double a = 8.0, b = 9.0, c = 7.2;
    std::cout.precision(10);

    double qm = quadraticMeanAssembly(a, b, c);
    std::cout << "Result using asm: " << qm << "\n";
    std::cout << "Result using std: " << std::sqrt((a * a + b * b + c * c) / 3.0) << "\n";

    return 0;
}
