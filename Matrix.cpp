#include <locale.h>
#include <iostream>
#include <string.h>
#include <list>
#include <cstdlib>
#include <vector>

#include <cmath>

#include "Matrix.h"

using namespace std;

Matrix::Matrix(string path)   // Инициализация объекта класса Matrix
{
    // Считывание матрицы из файла (с обработкой возможной ошибки ввода матрицы)
    try{
        this->read_matrix(path);
    }
    catch (exception& err){
        cout << "Matrix input is incorrect. Make sure that the .txt file of your matrix ends with a blank line." << endl;
    }
    vector <vector <int>> matrix;   // Двумерный массив со всеми числами матрицы
    int order = 0;  // Порядок квадратной матрицы
    int rank = 0;   // Ранг квадратной матрицы
    // int obuslovlennost = 0;
}

void Matrix::read_matrix(string path=".\\matrix.txt") {
    // Открытие файла
    FILE *f1;
    f1 = fopen(path.c_str(), "r");
    // Проверка на корректное открытие
    if (f1 == NULL){   // Проверка на успешное открытие файла
        cout << "File not found: " + path << endl;
        fclose(f1);
    }

    // Считывание файла
    int temp_number;
    char temp_char;
    int columns_amount = 0;
    int rows_amount = 0;
    vector <int> file_input;
    while (true){
        fscanf(f1, "%i", &temp_number);   // Считывание числа
        fscanf(f1, "%c", &temp_char);   // Считывание пробела или переноса строки
        
        // Счет количества строк и столбцов
        if ((temp_char == ' ') && (rows_amount == 0)){
            columns_amount++;
        } else if (temp_char == '\n'){
            rows_amount++;
        }

        if (feof(f1)) break;   // Проверка на конец файла, если поместить её в конец цикла то последнее число считается дважды
        file_input.push_back(temp_number);   // Сохранение числа в временный вектор
    }
    // Корректировка значений
    rows_amount--;
    columns_amount++;
    // Закрытие файла
    fclose(f1);

    // Проверка на квадратность матрицы:
    bool flag = false;
    for (int i = 0; i < 100; i++){
        if (i * i == file_input.size()){
            // Присвоение порядка матрицы:
            this->order = i;
            flag = true;
        }
    }
    // Обработка исключения (матрциа была записана неверно)
    if ((!flag) || (columns_amount!= rows_amount)){
        throw exception();
    }
    // Запись данных в переменную матрицы matrix[][]
    for (int i = 0; i < rows_amount; i++){
        matrix.push_back(vector<int>());
        for (int j = 0; j < columns_amount; j++){
            this->matrix.at(i).push_back(file_input.at(i * columns_amount + j));
        }
    }
}

void Matrix::print_matrix(){
    for (int i = 0; i < this->order; i++){
        for (int j = 0; j < this->order; j++){
            if (j == 0){
                cout << endl;
            }
            cout << this->matrix.at(i).at(j) << " ";
        }
    }
}

int Matrix::get_determinant(){
    return this->count_minor(this->order, matrix);
}

int Matrix::count_minor(int minor_size, vector <vector <int>> minor){
    // Если матрица (минор) - 2 на, то считаем по формуле
    if (minor_size == 2){
        return (minor[0][0] * minor[1][1] - minor[1][0] * minor[0][1]);
    } else {   // иначе
        // Для каждого столбца
        for (int i = 0; i < minor_size; i++){
            // первой строки
            int j = 0;
            // формируем минор по принципы (добавляем все, кроме элементов с j = 0 и текущим i)
            vector <vector <int>> minor_2;
                for (int i_1 = 0; i_1 < minor_size; i_1++){
                    if (i_1 != i){
                        minor_2.push_back(vector<int>());
                        for (int j_1 = 1; j_1 < minor_size; j_1++){
                            minor_2[minor_2.size() - 1].push_back(minor[i_1][j_1]);
                        }
                    }
                    
                }
                // Добавляем к значению определителя элемент с индексом (i, j) умноженный на (-1) ^ (i + j) и на его минор (минор находится Рекурсивно)
                this->determinant += pow(-1, i + j) * minor[i][j] * count_minor(minor_size - 1, minor_2);
        }
        return this->determinant;
    }
}


Matrix::~Matrix()
{

}