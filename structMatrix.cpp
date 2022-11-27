#include "Matrix.h"
#include "exception.h"
#include <iostream>

using namespace std;

rcMatrix::Matrix::Matrix(){
    row = 0;
    col = 0;
    data = NULL;
    ref = 1;
}

rcMatrix::Matrix::Matrix(int row, int col){
    this->row = row;
    this->col = col;
    data = new double[row*col];
    ref = 1;
}

rcMatrix::Matrix::Matrix(int row, int col, double* data){
    this->row = row;
    this->col = col;
    this->data = data;
    ref = 1;
}

rcMatrix::Matrix::Matrix(const char* nameFile){
    FILE *file;
    file = fopen(nameFile, "r");
    if(file == NULL){
        throw file_error();
    }
    fscanf(file, "%d %d", &row, &col);
    data = new double[row*col];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fscanf(file, "%lf", &data[i*col+j]);
        }
    }
    fclose(file);
    ref = 1;
}

rcMatrix::Matrix::~Matrix(){
    delete[] data;
}

void rcMatrix::Matrix::add(const struct Matrix* m){
    if(row != m->row || col != m->col){
        throw wrong_matrix_error();
    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            data[i*col+j] += m->data[i*col+j];
        }
    }
}

void rcMatrix::Matrix::sub(const struct Matrix* m){
    if(row != m->row || col != m->col){
        throw wrong_matrix_error();
    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            data[i*col+j] -= m->data[i*col+j];
        }
    }
}

void rcMatrix::Matrix::multiply(const struct Matrix* m1, const struct Matrix* m2){
    if(m1->col != m2->row){
        throw wrong_matrix_error();
    }
    row = m1->row;
    col = m2->col;
    data = new double[row*col];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            data[i*col+j] = 0;
            for(int k = 0; k < m1->col; k++){
                data[i*col+j] += m1->data[i*m1->col+k] * m2->data[k*m2->col+j];
            }
        }
    }
}

rcMatrix::Matrix* rcMatrix::Matrix::detach(){
    if(ref == 1){
        return this;
    }
    ref--;
    return new Matrix(row, col, data);
}

double rcMatrix::Matrix::read(int i, int j) const{
    if(i < 0 || i >= row || j < 0 || j >= col){
        throw out_of_index_error();
    }
    return data[i*col+j];
}

void rcMatrix::Matrix::write(int i, int j, double d){
    if(i < 0 || i >= row || j < 0 || j >= col){
        throw out_of_index_error();
    }
    data[i*col+j] = d;
}