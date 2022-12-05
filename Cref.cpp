#include "Matrix.h"
#include "exception.h"


Matrix::Cref::operator double() const{
    return m.read(row, col);
}

Matrix::Cref& Matrix::Cref::operator=(double d){
    m.write(row, col,d);
    return *this;
}

Matrix::Cref& Matrix::Cref::operator=(const Cref& ref){
    return operator=(double(ref));
}

Matrix::Cref Matrix::operator() (int i, int j){
    if((i<0 || i >= mattab->row)||(j<0 || j>= mattab->col)){
        throw out_of_index_error();
    }
    return Cref(*this, i, j);
}