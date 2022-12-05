#include "Matrix.h"
#include "exception.h"
#include <iostream>

using namespace std;

Matrix::Matrix(){
    mattab = new MatrixData();
}


Matrix::Matrix(const char* nameFile){
    mattab = new MatrixData(nameFile);
}

Matrix::Matrix(double num){
    this->mattab = new MatrixData(1,1);
    this->mattab->data[0][0] = num;
}

Matrix::Matrix(const Matrix& m){
    m.mattab->ref++;
    mattab = m.mattab;
}

Matrix::~Matrix(){
    if(--mattab->ref == 0){
        delete mattab;
    }
}

Matrix::Matrix(int row, int col, double** data){
    mattab = new MatrixData(row, col, data);
}

Matrix& Matrix::operator= (const Matrix& m){
    if(--mattab->ref == 0){
        delete mattab;
    }
    mattab = m.mattab;
    mattab->ref++;
    return *this;
}

Matrix& Matrix::operator+= (const Matrix& m){
    if(mattab->row != m.mattab->row || mattab->col != m.mattab->col){
        throw wrong_matrix_error();
    }
    MatrixData* new_matrix = new MatrixData(mattab->row, mattab->col, mattab->data);
    new_matrix->add(m.mattab);
    if (--mattab->ref == 0){
	    delete mattab;
    }
    mattab = new_matrix;
    return *this;
}

Matrix operator+ (const Matrix& m1, const Matrix& m2){
    Matrix temp(m1);
    temp += m2;
    return temp;
}

Matrix& Matrix::operator-= (const Matrix& m){
    if(mattab->row != m.mattab->row || mattab->col != m.mattab->col){
        throw wrong_matrix_error();
    }
    MatrixData* new_matrix = new MatrixData(mattab->row, mattab->col, mattab->data);
    new_matrix->sub(m.mattab);
    if (--mattab->ref == 0){
	    delete mattab;
    }
    mattab = new_matrix;
    return *this;
}

Matrix operator- (const Matrix& m1, const Matrix& m2){
    Matrix temp(m1);
    temp -= m2;
    return temp;
}

Matrix& Matrix::operator*= (const Matrix& m){
    MatrixData* new_matrix = new MatrixData(mattab->row, m.mattab->col);
    new_matrix->multiply(mattab, m.mattab);
    if (--mattab->ref == 0){
	    delete mattab;
    }    
    mattab = new_matrix;
    
    return *this;
}

Matrix operator* (const Matrix& m1, const Matrix& m2){
    if(m1.mattab->row == 1 && m1.mattab->col == 1){
        Matrix temp(m2);
        temp *= m1.mattab->data[0][0];
        return temp;
    } else if(m2.mattab->row == 1 && m2.mattab->col == 1){
        Matrix temp(m1);
        temp *= m2.mattab->data[0][0];
        return temp;
    } else {
        Matrix temp(m1);
        temp *= m2;
        return temp;
    }
    
}

Matrix& Matrix::operator*= (double num){
    MatrixData* new_matrix = new MatrixData(mattab->row, mattab->col, mattab->data);
    new_matrix->mulbynum(num);
    if (--mattab->ref == 0){
        delete mattab;
    }
    mattab = new_matrix;
    return *this;
}
Matrix operator*(const Matrix &m, double num){
    Matrix temp = m;
    temp *= num;
    return temp;
}

ostream& operator<< (ostream& out, const Matrix& m){
    out << m.mattab->row << " " << m.mattab->col << endl;
    for(int i = 0; i < m.mattab->row; i++){
        for(int j = 0; j < m.mattab->col; j++){
            out << m.mattab->data[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

bool operator== (const Matrix& m1, const Matrix& m2){
    if(m1.mattab->row != m2.mattab->row || m1.mattab->col != m2.mattab->col){
        return false;
    }
    for(int i = 0; i < m1.mattab->row; i++){
        for(int j = 0; j < m1.mattab->col; j++){
            if(m1.mattab->data[i][j] != m2.mattab->data[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool operator!= (const Matrix& m1, const Matrix& m2){
    return !(m1 == m2);
}

double Matrix::read(int i, int j) const{
    if((0 > i || i >= mattab->row)||(0 > j || j>= mattab->col)){
        throw out_of_index_error();
    }
        return mattab->data[i][j];
}

void Matrix::write(int i, int j, double d){
    if((0 > i || i >= mattab->row)||(0 > j || j>= mattab->col)){
        throw out_of_index_error();
    }
    mattab = mattab->detach();
    mattab->data[i][j] = d;
}













