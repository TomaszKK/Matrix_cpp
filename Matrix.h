#include <iostream>

using namespace std;

class Matrix{
	private:
		struct MatrixData;
	public:
		MatrixData *mattab;
		class Cref;
		Matrix();
		Matrix(const char*);
		Matrix(int, int, double**);
		Matrix(const Matrix&);
		Matrix(double);
		~Matrix();

		Matrix& operator= (const Matrix&);
		Matrix& operator+= (const Matrix&);
		friend Matrix operator+ (const Matrix&, const Matrix&);
		Matrix& operator-= (const Matrix&);
		friend Matrix operator- (const Matrix&, const Matrix&);
		Matrix& operator*= (const Matrix&);
		friend Matrix operator* (const Matrix&, const Matrix&);
		Matrix& operator*= (double);
		friend Matrix operator* (const Matrix&, double);
		friend bool operator == (const Matrix&, const Matrix&);
		friend bool operator != (const Matrix&, const Matrix&);

		Cref operator() (int,int);
		friend ostream& operator << (ostream &, const Matrix &);
		double read(int, int) const;
		void write(int, int, double);
};

class Matrix::Cref
{
	friend class Matrix;
	Matrix& m;
	int row, col;

	public:
		Cref (Matrix& mm, int i, int j): m(mm), row(i), col(j) {};
		operator double() const;
		Matrix::Cref& operator=(double);
		Matrix::Cref& operator=(const Cref&);
};

struct Matrix::MatrixData{
	int row;
	int col;
	double **data;
	int ref;

	MatrixData();
	MatrixData(int, int);
	MatrixData(int, int, double**);
	MatrixData(const char* nameFile);
	~MatrixData();

	void add(const struct MatrixData*);
	void sub(const struct MatrixData*);
  	void multiply(const struct MatrixData*, const struct MatrixData*);
	void mulbynum(double);
	bool check(const struct MatrixData*);
	MatrixData* detach();
};
