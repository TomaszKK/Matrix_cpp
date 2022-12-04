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
		rcMatrix(double);
		~rcMatrix();

		rcMatrix& operator= (const rcMatrix&);
		rcMatrix& operator+= (const rcMatrix&);
		friend rcMatrix operator+ (const rcMatrix&, const rcMatrix&);
		rcMatrix& operator-= (const rcMatrix&);
		friend rcMatrix operator- (const rcMatrix&, const rcMatrix&);
		rcMatrix& operator*= (const rcMatrix&);
		friend rcMatrix operator* (const rcMatrix&, const rcMatrix&);
		rcMatrix& operator*= (double);
		friend rcMatrix operator* (const rcMatrix&, double);
		friend bool operator == (const rcMatrix&, const rcMatrix&);
		friend bool operator != (const rcMatrix&, const rcMatrix&);

		Cref operator() (int,int);
		friend ostream& operator << (ostream &, const rcMatrix &);
		double read(int, int) const;
		void write(int, int, double);
};

class rcMatrix::Cref
{
	friend class rcMatrix;
	rcMatrix& m;
	int row, col;

	public:
		Cref (rcMatrix& mm, int i, int j): m(mm), row(i), col(j) {};
		operator double() const;
		rcMatrix::Cref& operator=(double);
		rcMatrix::Cref& operator=(const Cref&);
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

	void add(const struct Matrix*);
	void sub(const struct Matrix*);
  	void multiply(const struct Matrix*, const struct Matrix*);
	void mulbynum(double);
	bool check(const struct Matrix*);
	Matrix* detach();
};
