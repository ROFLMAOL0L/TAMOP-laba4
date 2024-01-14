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
    // Создание объекта класса Matrix
    Matrix* my_matrix = new Matrix(".\\matrix.txt");
    my_matrix->print_matrix();
    cout << "Det = " << my_matrix->get_determinant() << endl;;
    delete my_matrix;
    return 1;
}