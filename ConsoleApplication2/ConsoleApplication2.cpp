#include <iostream>
using namespace std;

int main() {
    int population = 1000000; // количество жителей
    int area = 50000;         // площадь территории (например, в кв.км)

    double density;

    __asm {
        // Делим population на area: целочисленное деление
        mov eax, population; загрузить population в eax
        cdq; расширить eax в edx : eax для знакового деления
        idiv area; eax = population / area

        // Поместить результат целочисленного деления в переменную density как double
        // Для простоты используем преобразование в C++ после asm блока
        mov ebx, eax; сохранить результат в ebx
    }

    // Переводим целочисленный результат в double
    density = static_cast<double>(static_cast<int>(0)); // инициализация

    // Копируем значение из ebx (результат деления) в density
    // К сожалению, прямого доступа из asm в double сложнее,
    // поэтому лучше считать в int, а дальше переводить в double в C++

    // Воспользуемся вот таким трюком — объявим переменную для результата:
    int int_density;

    __asm {
        mov eax, population
        cdq
        idiv area
        mov int_density, eax
    }

    density = static_cast<double>(int_density);

    cout << "Population density = " << density << " people per unit area" << endl;

    return 0;
}
