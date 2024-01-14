#include <locale.h>
#include <iostream>
#include <string.h>
#include <list>
#include <cstdlib>
#include <vector>
#include "Matrix.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "Russian");
    // Создание объекта класса Matrix, а так же ее считывание из файла matrix.txt расположенном в рабочем каталоге
    Matrix* my_matrix = new Matrix(".\\matrix.txt");
    // Вывод в консоль матрицы
    my_matrix->print_matrix();
    // Вывод в консоль определителя матрицы
    cout << "Det = " << my_matrix->get_determinant() << endl;
    // Вывод в консоль ранга матрицы
    cout << "Rank = " << my_matrix->get_rank() << endl;
    // Вывод в консоль обусловленность матрциы
    cout << "Condition number = " << my_matrix->cond() << endl;

    string a;
    cin >> a;

    // Удаление объекта my_matrix
    delete my_matrix;
    return 1;
}