#include <iostream>

using namespace std;

class Matrix {
  private:
    struct MatrixData;
    MatrixData* mattab;
    double read(int row, int col) const;
    void write(int row, int col, double d);

  public:
    class ElementRef;
    Matrix();
    Matrix(const char* nameFile);
    Matrix(int row, int col, double** data);
    Matrix(const Matrix& m);
    Matrix(double num);
    ~Matrix();

    Matrix& operator=(const Matrix& m);
    Matrix& operator+=(const Matrix& m);
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    Matrix& operator-=(const Matrix& m);
    friend Matrix operator-(const Matrix& m1, const Matrix& m2);
    Matrix& operator*=(const Matrix& m);
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);
    Matrix& operator*=(double num);
    friend Matrix operator*(const Matrix& m, double num);
    friend bool operator==(const Matrix& m1, const Matrix& m2);
    friend bool operator!=(const Matrix& m1, const Matrix& m2);

    ElementRef operator()(int i, int j);
    friend ostream& operator<<(ostream& out, const Matrix& m);
    int getrefcount();
};

class Matrix::ElementRef {
    friend class Matrix;
    Matrix& m;
    int row, col;

  public:
    ElementRef(Matrix& mm, int i, int j) : m(mm), row(i), col(j){};
    operator double() const;
    Matrix::ElementRef& operator=(double d);
    Matrix::ElementRef& operator=(const ElementRef& ref);
};

struct Matrix::MatrixData {
    int row;
    int col;
    double** data;
    int ref;

    MatrixData();
    MatrixData(int row, int col);
    MatrixData(int row, int col, double** data);
    MatrixData(const char* nameFile);
    ~MatrixData();

    void add(const struct MatrixData* m);
    void sub(const struct MatrixData* m);
    void multiply(const struct MatrixData* m1, const struct MatrixData* m2);
    void mulbynum(double num);
    bool check(const struct MatrixData* m);
    MatrixData* detach();
};
