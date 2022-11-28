#include <iostream>

using namespace std;

class rcMatrix{
	private:
		struct Matrix;
	public:
		Matrix *mattab;
		class Cref;
		rcMatrix();
		rcMatrix(const char*);
		rcMatrix(int, int, double**);
		rcMatrix(const rcMatrix&);
		~rcMatrix();
		rcMatrix& operator= (const rcMatrix&);
		rcMatrix& operator+= (const rcMatrix&);
		rcMatrix operator+ (const rcMatrix&) const;
		rcMatrix& operator-= (const rcMatrix&);
		rcMatrix operator- (const rcMatrix&) const;
		rcMatrix& operator*= (const rcMatrix&);
		rcMatrix operator* (const rcMatrix&) const;
		Cref operator() (int,int);
		friend ostream& operator << (ostream &, const rcMatrix &);
		double read(int, int) const;
		void write(int, int, double);
		
		// Pamietaj jeszcze o == i !=
};

class rcMatrix::Cref
{
	friend class rcmatrix;
	rcMatrix& m;
	int i, j;

	public:
		Cref (rcMatrix& mm, int ii, int jj): m(mm), i(ii), j(jj) {};
		operator double();
		rcMatrix::Cref& operator=(double);

};

struct rcMatrix::Matrix{
	int row;
	int col;
	double **data;
	int ref;

	Matrix();
	Matrix(int, int);
	Matrix(int, int, double**);
	Matrix(const char* nameFile);
	~Matrix();

	double read(int, int) const;
	void write(int, int, double );
	
	void add(const struct Matrix*);
	void sub(const struct Matrix*);
  	void multiply(const struct Matrix*, const struct Matrix*);
	Matrix* detach();
};

int findbiggervalue(int, int);