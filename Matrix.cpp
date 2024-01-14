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
    this->determinant = this->count_minor(this->order, this->matrix);
    // Расчет определителя при создании матрицы
    if (!this->determinant == 0){
        this->count_inverted_matrix();
    }
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
            this->matrix[i].push_back(file_input.at(i * columns_amount + j));
        }
    }
}

void Matrix::print_matrix(){
    for (int i = 0; i < this->order; i++){
        for (int j = 0; j < this->order; j++){
            if (j == 0){
                cout << endl;
            }
            cout << this->matrix[i][j] << " ";
        }
    }
    cout << endl;
}

int Matrix::get_determinant(){
    return this->determinant;
}

int Matrix::count_minor(int minor_size, vector <vector <int>> minor){
    // Если матрица (минор) - 1 на 1, возвращаем ее значение
    if (minor_size == 1){
        return minor[0][0];
    }
    // Если матрица (минор) - 2 на 2, то считаем по формуле
    else if (minor_size == 2){
        return (minor[0][0] * minor[1][1] - minor[1][0] * minor[0][1]);
    } else {    // иначе
    int temp_sum = 0;
        // Для каждого столбца
        for (int j = 0; j < minor_size; j++){
            // первой строки
            int i = 0;
            // формируем минор по принципы (добавляем все, кроме элементов с j = 0 и текущим i)
            vector <vector <int>> minor_2;
                for (int i_1 = 0; i_1 < minor_size; i_1++){
                    if (i_1 != i){
                        minor_2.push_back(vector<int>());
                        for (int j_1 = 0; j_1 < minor_size; j_1++){
                            if ((j_1 != j)){
                                minor_2[minor_2.size() - 1].push_back(minor[i_1][j_1]);
                            }
                        }
                    }
                    
                }
                // Добавляем к значению определителя элемент с индексом (i, j) умноженный на (-1) ^ (i + j) и на его минор (минор находится Рекурсивно)
                temp_sum += pow(-1, i + j) * minor[i][j] * count_minor(minor_size - 1, minor_2);
        }
        // Если функция была вызвана рекунсивно - возвращаем сумму (определитель данноро минора). Впоследствии она умножится на элементы первой строки исходной матрицы
        if (minor_size == this->order){
            this->determinant = temp_sum;
            return this->determinant;
        } else {   // если же функция была вызвана впервые - происзошли все вычисления (данный размер минора матрицы - порядок исходной матрицы) - возвращаем ответ.
            return temp_sum;
        }
    }
}

int Matrix::get_rank(){
    // Создаем копию матрицы для манипуляций для расчета ранга (методом Гаусса-Жордана)
    vector <vector<float>> matrix_copy;
    for (int i = 0; i < this->order; i++){
        matrix_copy.push_back(vector <float>());
        for (int j = 0; j < this->order; j++){
            matrix_copy[i].push_back(static_cast <float>(matrix[i][j]));
        }
    }
    // Для каждой строки
    for (int i = 0; i < this->order - 1; i++){
        // Для каждой оставшейся строки
        for (int i_delta = i + 1; i_delta <this->order; i_delta++){
            // Если элемент этой строки на главной диоганали не равен нулю
            if (!matrix_copy[i][i] == 0){
                // Вычисляем разницу в элементах чтобы вычесть из следующей строки прошлую, умноженную на эту разницу
                float diff = matrix_copy[i_delta][i] / matrix_copy[i][i];
                // Для каждого элемента строки
                for (int j = 0; j < this->order; j++){
                    // вычитаем элемент прошлой с таким же индексом, умноженный на разницу diff
                    matrix_copy[i_delta][j] -= diff * matrix_copy[i][j];
                }
            } else {
                // Если элемент главной диоганали равен нулю, нужно попытаться поменять местами строки ниже текущей.
                for (int j = i + 1; j < this->order; j++){
                    if (matrix_copy[j][i] != 0){   // если есть строка с ненулевым значением в данном столбце
                        vector <float> new_line;   // временная переменная для перезаписи значений
                        new_line.clear();
                        for (int q = 0; q < this->order; q++){   // перезапись значений
                            new_line.push_back(matrix_copy[i][q]);
                            matrix_copy[i][q] = matrix_copy[j][q];
                            matrix_copy[j][q] = new_line[q];
                        }
                    }
                }
            }
        }
    }   // В конце получаем матрицу с нулями НИЖЕ главной диоганали

    // Получаем нули ВЫШЕ главной диоганали
    // Для каждой строки
    for (int i = this->order - 1; i > 0; i--){
        // Для каждой оставшейся строки
        for (int i_delta = i - 1; i_delta >= 0; i_delta--){
            // Если элемент этой строки на главной диоганали не равне нулю
            if (!matrix_copy[i][i] == 0){
                // Вычисляем разницу в элементах чтобы вычесть из следующей строки прошлую, умноженную на эту разницу
                float diff = matrix_copy[i_delta][i] / matrix_copy[i][i];
                // Для каждого элемента строки
                for (int j = 0; j < this->order; j++){
                    // вычитаем элемент прошлой с таким же индексом, умноженный на разницу diff
                    matrix_copy[i_delta][j] -= diff * matrix_copy[i][j];
                }
            }
        }
    }
    // Высчитываем ранг как количество ненулевых строк в копии матрицы matrix_copy
    int temp_rank = 0;
    for (int i = 0; i < this->order; i++){
        if (!this->is_zero_line(matrix_copy[i])){
            temp_rank++;
        }
    }
    // А так же присваеваем значение ранга матрице
    this->rank = temp_rank;
    return this->rank;
}

bool Matrix::is_zero_line(vector<float> line){
    bool flag = true;
    for (int j = 0; j < this->order; j++){
        if (line[j] != 0){   // если элемент строки - не ноль
            flag = false;   // строка не нулевая
        }
    }
    return flag;
}

void Matrix::print_inverted_matrix(){
    for (int i = 0; i < this->order; i++){
        for (int j = 0; j < this->order; j++){
            if (j == 0){
                cout << endl;
            }
            cout << this->inverted_matrix[i][j] << " ";
        }
    }
}

string Matrix::cond(){
    // Если матрица вырожденная - она считается плохо обусловленной
    if (this->determinant == 0){
        return "inf";
    }
    // Преобразование самой матрицы в матрицу вида vector <vector <float>> для вычисление нормы
    vector <vector <float>> A;
    for (int i = 0; i < this->order; i++){
        A.push_back(vector <float>());
        for (int j = 0; j < this->order; j++){
            A[i].push_back(static_cast <float> (this->matrix[i][j]));
        }
    }
    // Вычисление числа обусловленности
    return to_string(this->norm(A) * this->norm(this->inverted_matrix));
}


void Matrix::count_inverted_matrix(){
    vector <vector <float>> inverted_a;
    // Заполнение матрицы нулями
    for (int i = 0; i < this->order; i++){
        inverted_a.push_back(vector <float>());
        for (int j = 0; j < this->order; j++){
            inverted_a[i].push_back(0.0);
        }
    }
    // Для каждой строки
    for (int i = 0; i < this->order; i++){
        // Для каждого столбца
        for (int j = 0; j < this->order; j++){
            // Объявляем минор
            vector <vector<int>> temp_minor;
            // Заполняем минор
            for (int i_1 = 0; i_1 < this->order; i_1++){
                if (i != i_1){
                    temp_minor.push_back(vector <int>());
                    for (int j_1 = 0; j_1 < this->order; j_1++){
                        if (j != j_1){
                            temp_minor[temp_minor.size() - 1].push_back(matrix[i_1][j_1]);
                        }
                    }
                }
            }
            // Высчитываем значение обратной матрицы под индексом (i, j)
            inverted_a[j][i] = (pow(-1, i + j)) * static_cast <float>(this->count_minor(this->order - 1, temp_minor)) * (1 / static_cast <float>(this->determinant));
        }
    }
    // Присвоение полученной обратной матрицы объекту класса
    this->inverted_matrix = inverted_a;
}

float Matrix::norm(vector< vector<float>> A){
    float sum_of_squares = 0.0;
    // Сумма квадратов всех элементов
    for (int i = 0; i < this->order; i++){
        for (int j = 0; j < this->order; j++){
            sum_of_squares += pow(A[i][j], 2);
        }
    }
    // Квадратный корень из этой суммы
    return pow(sum_of_squares, 0.5);
}

Matrix::~Matrix()
{

}