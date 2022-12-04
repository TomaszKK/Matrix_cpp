#include "Matrix.h"
#include "exception.h"


rcMatrix::Cref::operator double() const{
    return m.read(row, col);
}

rcMatrix::Cref& rcMatrix::Cref::operator=(double d){
    m.write(row, col,d);
    return *this;
}

rcMatrix::Cref& rcMatrix::Cref::operator=(const Cref& ref){
    return operator=(double(ref));
}

rcMatrix::Cref rcMatrix::operator() (int i, int j){
    if((i<0 || i >= mattab->row)||(j<0 || j>= mattab->col)){
        throw out_of_index_error();
    }
    return Cref(*this, i, j);
}