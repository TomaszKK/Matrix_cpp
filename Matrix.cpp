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

rcMatrix& rcMatrix::operator= (const rcMatrix& m){
    if(--mattab->ref == 0){
        delete mattab;
    }
    mattab = m.mattab;
    mattab->ref++;
    return *this;
}

rcMatrix& rcMatrix::operator+= (const rcMatrix& m){
    if(mattab->row != m.mattab->row || mattab->col != m.mattab->col){
        throw wrong_matrix_error();
    }
    if(mattab->ref > 1){
        mattab = mattab->detach();
    }
    mattab->add(m.mattab);
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
    if(mattab->ref > 1){
        mattab = mattab->detach();
    }
    mattab->sub(m.mattab);
    return *this;
}

rcMatrix rcMatrix::operator- (const rcMatrix& m) const{
    rcMatrix temp(*this);
    temp -= m;
    return temp;
}

rcMatrix& rcMatrix::operator*= (const rcMatrix& m){
    if(mattab->col != m.mattab->row){
        throw wrong_matrix_error();
    }
    if(mattab->ref > 1){
        mattab = mattab->detach();
    }
    mattab->multiply(mattab, m.mattab);
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
            out << m.mattab->data[i*m.mattab->col+j] << " ";
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








