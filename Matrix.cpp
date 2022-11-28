#include "Matrix.h"
#include "exception.h"
#include <iostream>

using namespace std;

rcMatrix::rcMatrix(){
    mattab = new Matrix();
}


rcMatrix::rcMatrix(const char* nameFile){
    mattab = new Matrix(nameFile);
}


rcMatrix::rcMatrix(const rcMatrix& m){
    mattab = m.mattab;
    mattab->ref++;
}

rcMatrix::~rcMatrix(){
    if(--mattab->ref == 0){
        delete mattab;
    }
}

rcMatrix::rcMatrix(int row, int col, double** data){
    mattab = new Matrix(row, col, data);
}

rcMatrix& rcMatrix::operator= (const rcMatrix& m){
    m.mattab->ref++;
    if(--mattab->ref == 0){
        delete mattab;
    }
    mattab = m.mattab;
    return *this;
}

rcMatrix& rcMatrix::operator+= (const rcMatrix& m){
    if(mattab->row != m.mattab->row || mattab->col != m.mattab->col){
        throw wrong_matrix_error();
    }
    Matrix* new_matrix = new Matrix(mattab->row, mattab->col, mattab->data);
    new_matrix->add(m.mattab);
    if (--mattab->ref == 0){
	    delete mattab;
    }
    mattab = new_matrix;
    return *this;
}

rcMatrix rcMatrix::operator+ (const rcMatrix& m) const{
    rcMatrix temp(*this);
    temp += m;
    return temp;
}

rcMatrix& rcMatrix::operator-= (const rcMatrix& m){
    if(mattab->row != m.mattab->row || mattab->col != m.mattab->col){
        throw wrong_matrix_error();
    }
    Matrix* new_matrix = new Matrix(mattab->row, mattab->col, mattab->data);
    new_matrix->sub(m.mattab);
    if (--mattab->ref == 0){
	    delete mattab;
    }
    mattab = new_matrix;
    return *this;
}

rcMatrix rcMatrix::operator- (const rcMatrix& m) const{
    rcMatrix temp(*this);
    temp -= m;
    return temp;
}

rcMatrix& rcMatrix::operator*= (const rcMatrix& m){
    if(mattab->row != m.mattab->row || mattab->col != m.mattab->col){
        throw wrong_matrix_error();
    }
    Matrix* new_matrix = new Matrix(mattab->row, m.mattab->col);
    new_matrix->multiply(mattab, m.mattab);
    if (--mattab->ref == 0){
	    delete mattab;
    }
    mattab = new_matrix;
    return *this;
}

rcMatrix rcMatrix::operator* (const rcMatrix& m) const{
    rcMatrix temp(*this);
    temp *= m;
    return temp;
}

ostream& operator<< (ostream& out, const rcMatrix& m){
    out << m.mattab->row << " " << m.mattab->col << endl;
    for(int i = 0; i < m.mattab->row; i++){
        for(int j = 0; j < m.mattab->col; j++){
            out << m.mattab->data[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

double rcMatrix::read(int i, int j) const{
    return mattab->read(i, j);
}

void rcMatrix::write(int i, int j, double d){
    if(mattab->ref > 1){
        mattab = mattab->detach();
    }
    mattab->write(i, j, d);
}

rcMatrix::Cref rcMatrix::operator() (int i, int j){
    return Cref(*this, i, j);
}









int findbiggervalue(int num1, int num2){
    if(num1 > num2){
        return num1;
    }
    else{
        return num2;
    }
}