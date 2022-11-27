#include "Matrix.h"

rcMatrix::Cref::operator double(){
    return m.read(i,j);
}

rcMatrix::Cref& rcMatrix::Cref::operator=(double d){
    m.write(i,j,d);
    return *this;
}

