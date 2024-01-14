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
    // Двумерный вектор, используемый для хранения значений матрицы
    vector <vector <int>> matrix;
    int order;   // Порядок матрицы
    int rank;   // Ранг матрицы
    int determinant;   // Определитель матрицы
    ~Matrix();   // Деконструктор
    // Функция вывода на экран значений матрицы
    void print_matrix();
    int get_determinant();

private:
    // Метод для считывания матрицы из текстового файла (+ обработка исключения ошибки ввода)
    void read_matrix(string);
    // Метод для рассчета минора
    int count_minor(int minor_size, vector <vector <int>> minor);
};

#endif