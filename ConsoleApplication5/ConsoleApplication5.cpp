#include <iostream>
#include <cmath>

// q(x) = (1 - 2x^2) / (2 - 3x^2)
double calculate_q(double x) {
    double result;
    double one = 1.0, two = 2.0, three = 3.0;

    double numerator, denominator;

    __asm {
        fld x; ST0 = x
        fmul st(0), st(0); x ^ 2
        fld two; 2.0
        fmulp st(1), st(0); 2 * x ^ 2
        fld one; 1.0
        fsubp st(1), st(0); 1 - 2x ^ 2->numerator
        fstp numerator

        fld x
        fmul st(0), st(0); x ^ 2
        fld three; 3.0
        fmulp st(1), st(0); 3 * x ^ 2
        fld two; 2.0
        fsubp st(1), st(0); 2 - 3x ^ 2->denominator
        fstp denominator

        fld numerator
        fld denominator
        fdivp st(1), st(0); numerator / denominator
        fstp result
    }

    return result;
}

// b(x) = 2 - (3x^2) / (3 + x^3) + 2 * sqrt(x^2 / 8)
double calculate_b(double x) {
    double result;
    double two = 2.0, three = 3.0, eight = 8.0;

    double term2, term3;

    __asm {
        // term2 = -(3x^2) / (3 + x^3)
        fld x
        fmul st(0), st(0); x ^ 2
        fld three; 3.0
        fmulp st(1), st(0); 3 * x ^ 2
        fstp term2; save numerator for term2

        fld x
        fmul st(0), st(0); x ^ 2
        fld x
        fmulp st(1), st(0); x ^ 3 = x ^ 2 * x
        fld three; 3.0
        faddp st(1), st(0); 3 + x ^ 3
        fld term2; numerator 3x ^ 2
        fdivp st(1), st(0); (3x ^ 2) / (3 + x ^ 3)
        fchs; negate
        fstp term2

        // term3 = 2 * sqrt(x^2 / 8)
        fld x
        fmul st(0), st(0); x ^ 2
        fld eight; 8.0
        fdivp st(1), st(0); x ^ 2 / 8
        fsqrt; sqrt(x ^ 2 / 8)
        fld two; 2.0
        fmulp st(1), st(0); 2 * sqrt(...)
        fstp term3

        // result = 2 + term2 + term3
        fld two
        fadd term2
        fadd term3
        fstp result
    }

    return result;
}

int main() {
    double x;
    std::cout << "Enter x: ";
    std::cin >> x;

    double q = calculate_q(x);
    double b = calculate_b(x);

    std::cout.precision(10);
    std::cout << "q(" << x << ") = " << q << "\n";
    std::cout << "b(" << x << ") = " << b << "\n";

    return 0;
}
