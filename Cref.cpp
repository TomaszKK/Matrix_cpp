#include "Matrix.h"
#include "exception.h"

Matrix::ElementRef::operator double() const
{
    return m.read(row, col);
}

Matrix::ElementRef& Matrix::ElementRef::operator=(double d)
{
    m.write(row, col, d);
    return *this;
}

Matrix::ElementRef& Matrix::ElementRef::operator=(const ElementRef& ref)
{
    return operator=(double(ref));
}

Matrix::ElementRef Matrix::operator()(int i, int j)
{
    if ((i < 0 || i >= mattab->row) || (j < 0 || j >= mattab->col)) {
        throw out_of_index_error();
    }
    return ElementRef(*this, i, j);
}
