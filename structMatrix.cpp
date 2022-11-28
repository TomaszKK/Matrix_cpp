#include "Matrix.h"
#include "exception.h"
#include <iostream>
#include <fstream>

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
    data = new double*[row];
    for(int i = 0; i < row; i++){
        data[i] = new double[col];
    }
    ref = 1;
}

rcMatrix::Matrix::Matrix(int row, int col, double** data){
    if (data!= NULL){
        this->row = row;
        this->col = col;
        this->data = new double*[row];
        for(int i = 0; i < row; i++){
            this->data[i] = new double[col];
            for(int j = 0; j < col; j++){
                this->data[i][j] = data[i][j];
            }
        }
    }
    else{
        this->row = 0;
		this->col = 0;
		this->data = NULL;
    }
    ref = 1;
}

rcMatrix::Matrix::Matrix(const char* nameFile){
    fstream file;
    file.open(nameFile, ios::in);
    if(file.good() == 0)
    {
      throw file_error();
    }
    file >> row;
    file >> col;
    data = new double*[row];
    for(int i=0;i<row;i++){
        data[i] = new double[col];
        for(int j=0;j<col;j++){
            file >> data[i][j];
        }
    }
    ref = 1;
}

rcMatrix::Matrix::~Matrix(){
    for(int i = 0; i < col; i++){
        delete[] data[i];
    }
    delete[] data;
}

void rcMatrix::Matrix::add(const struct Matrix* m){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            data[i][j] += m->data[i][j];
        }
    }
}

void rcMatrix::Matrix::sub(const struct Matrix* m){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            data[i][j] -= m->data[i][j];
        }
    }
}


void rcMatrix::Matrix::multiply(const struct Matrix* m1, const struct Matrix* m2){
    if(m1->col == m2->row && m1->row == m2->col){
        Matrix* temp = new Matrix(m1->row, m2->col);
        for(int i = 0; i < m1->row; i++){
            for(int j = 0; j < m2->col; j++){
                double wynik = 0;
                for(int k = 0;k<m1->col; k++){
                    wynik += m1->data[i][k] * m2->data[k][j];
                }
                temp->data[i][j] = wynik;
            }
        }
        for(int i = 0; i < row; i++){
            data[i] = new double[col];
            for(int j = 0; j < col; j++){
                data[i][j] = temp->data[i][j];
            }
        }
        delete temp;
    }
    else{
        throw wrong_matrix_error();
    }
}

rcMatrix::Matrix* rcMatrix::Matrix::detach()
{
    if (ref == 1)
        return this;
    ref--;
    return new Matrix(row, col, data);
}

double rcMatrix::Matrix::read(int i, int j) const{
    if(i < 0 || i >= row || j < 0 || j >= col){
        throw out_of_index_error();
    }
    return data[i][j];
}

void rcMatrix::Matrix::write(int i, int j, double d){
    if(i < 0 || i >= row || j < 0 || j >= col){
        throw out_of_index_error();
    }
    data[i][j] = d;
}