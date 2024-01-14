#ifndef MATRIX_H
#define MATRIX_H

#include <locale.h>
#include <iostream>
#include <string.h>
#include <list>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <cstdlib>

using namespace std;

#pragma once

class Matrix
{
public:
    // Конструктор (аргумент - путь к файлу)
    Matrix(string);
    ~Matrix();   // Деконструктор
    // Функция вывода в консоль значений матрицы
    void print_matrix();
    // Метод для рассчета орпеделителя, завязан на приватном рекурсивном методе count_minor
    int get_determinant();
    // Метод для нахождения ранга матрицы (методом ГАУССА-ЖОРДАНА)
    int get_rank();
    // Функция вывода в консоль значений обратной матрицы
    void print_inverted_matrix();
    // Метод нахождения числа обусловленности (с помощью перемножения нормы A и нормы A^(1); нормы находятся способом Фробениуса (ЕВКЛИДОВА НОРМА))
    string cond();

private:
    // Двумерный вектор, используемый для хранения значений матрицы
    vector <vector <int>> matrix;
    int order;   // Порядок матрицы
    int rank;   // Ранг матрицы
    int determinant;   // Определитель матрицы
    float condition_number;   // Число обусловленности
    // Метод для считывания матрицы из текстового файла (+ обработка исключения ошибки ввода)
    void read_matrix(string);
    // Рекурсивный метод для рассчета минора
    int count_minor(int minor_size, vector <vector <int>> minor);
    // Метод для проверки, является ли конкретная строка нулевой
    bool is_zero_line(vector <float>);
    // Переменная хранящая обратную матрицу
    vector <vector <float>> inverted_matrix;
    // Метод для высчитывания обратной матрицы
    void count_inverted_matrix();
    // Метод для расчета нормы способом Фробениуса
    float norm(vector <vector <float>>);
};

#endif