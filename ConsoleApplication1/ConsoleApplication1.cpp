#include <iostream>
using namespace std;

int main() {
    // Numerators and denominators for the two fractions
    int num1 = 10, den1 = 99;
    int num2 = 23, den2 = 9;

    // Variables to store product numerator and denominator
    int num_product, den_product;

    // Assembly block to multiply numerators and denominators
    __asm {
        mov eax, num1
        imul eax, num2
        mov num_product, eax

        mov eax, den1
        imul eax, den2
        mov den_product, eax
    }

    // Calculate decimal value of the product
    double y = static_cast<double>(num_product) / den_product;

    cout << "y (fraction) = " << num_product << "/" << den_product << endl;
    cout << "y (decimal) = " << y << endl;

    return 0;
}
