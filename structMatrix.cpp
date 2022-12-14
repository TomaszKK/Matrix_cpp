#include "Matrix.h"
#include "exception.h"
#include <fstream>
#include <iostream>

using namespace std;

Matrix::MatrixData::MatrixData()
{
    row = 0;
    col = 0;
    data = NULL;
    ref = 1;
}

Matrix::MatrixData::MatrixData(int row, int col)
{
    this->row = row;
    this->col = col;
    data = new double*[row];
    for (int i = 0; i < row; i++) {
        data[i] = new double[col];
    }
    ref = 1;
}

Matrix::MatrixData::MatrixData(int row, int col, double** data)
{
    if (data != NULL) {
        this->row = row;
        this->col = col;
        this->data = new double*[row];
        for (int i = 0; i < row; i++) {
            this->data[i] = new double[col];
            for (int j = 0; j < col; j++) {
                this->data[i][j] = data[i][j];
            }
        }
    }
    else {
        this->row = 0;
        this->col = 0;
        this->data = NULL;
    }
    ref = 1;
}

Matrix::MatrixData::MatrixData(const char* nameFile)
{
    fstream file;
    file.open(nameFile, ios::in);
    if (file.good() == 0) {
        throw file_error();
    }
    file >> this->row;
    file >> this->col;
    this->data = new double*[this->row];
    for (int i = 0; i < this->row; i++) {
        this->data[i] = new double[col];
        for (int j = 0; j < this->col; j++) {
            file >> this->data[i][j];
        }
    }
    file.close();
    this->ref = 1;
}

Matrix::MatrixData::~MatrixData()
{
    for (int i = 0; i < row; i++) {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::MatrixData::add(const struct MatrixData* m)
{
    if (col == m->col && row == m->row) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[i][j] += m->data[i][j];
            }
        }
    }
    else {
        throw wrong_matrix_error();
    }
}

void Matrix::MatrixData::sub(const struct MatrixData* m)
{
    if (col == m->col && row == m->row) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[i][j] -= m->data[i][j];
            }
        }
    }
    else {
        throw wrong_matrix_error();
    }
}

void Matrix::MatrixData::mulbynum(double num)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data[i][j] *= num;
        }
    }
}

void Matrix::MatrixData::multiply(const struct MatrixData* m1,
                                  const struct MatrixData* m2)
{
    if (m1->col == m2->row && m1->row == m2->col) {
        for (int i = 0; i < m1->row; i++) {
            for (int j = 0; j < m2->col; j++) {
                this->data[i][j] = 0;
                for (int k = 0; k < m1->col; k++) {
                    this->data[i][j] += m1->data[i][k] * m2->data[k][j];
                }
            }
        }
    }
    else {
        throw wrong_matrix_error();
    }
}

Matrix::MatrixData* Matrix::MatrixData::detach()
{
    if (ref == 1)
        return this;
    ref--;
    return new MatrixData(row, col, data);
}
