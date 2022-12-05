#include "Matrix.h"
#include <iostream>

using namespace std;

void printTwoMatrix(const Matrix&, const Matrix&);
void testAddandSub(const Matrix&, const Matrix&);
void testMult(const Matrix&, const Matrix&);
void testEquality(const Matrix&, const Matrix&);
void testReadandWrite(const Matrix&);
void testReferenceCounting(const Matrix&, const Matrix&);
void testException(const Matrix&, const Matrix&, const Matrix&, const Matrix&);

int main(){
	try {
		Matrix A("mat_3x3_1.txt");
		Matrix B("mat_3x3_2.txt");
		Matrix mat_2x3("mat_2x3.txt");
		Matrix mat_3x2("mat_3x2.txt");

		testAddandSub(A, B);
		testMult(mat_2x3, mat_3x2);
		testEquality(A, B);
		testReadandWrite(A);
		cout<<endl<<"Value of Referece Counting of A before passing to function = "<<(A.mattab->ref)<<endl;
		testReferenceCounting(A, B);
		testException(A,B, mat_2x3, mat_3x2);

		} catch(exception& e) {
		cout << "Error - " << e.what() << endl;
		} catch(...) {
		cout << "An unknown error occurred." << endl;
		}
	return 0;
}

void printTwoMatrix(const Matrix& A, const Matrix& B){
	cout << "--- Matrix A ---" << endl << endl << A << endl;
   	cout << "--- Matrix B ---" << endl << endl << B << endl;
}

void testAddandSub(const Matrix& A, const Matrix& B){
	cout<<endl<<"--- Test Add and Sub ---"<<endl<<endl;
	Matrix C;
	printTwoMatrix(A, B);
	cout << "C = A + B" << endl<< (C = A + B) <<  endl;
	cout << "C += A" << endl <<(C += A) << endl;
   	cout << "C = A - B" << endl << (C = A - B) <<  endl;
	cout<< "C -= A" << endl << (C -= A) << endl;
}

void testMult(const Matrix& A, const Matrix& B){
	cout<<endl<<"--- Test Multiplication ---"<<endl<<endl;
	Matrix C;
	printTwoMatrix(A, B);
	cout << "C = A * B" << endl << (C = A * B) << endl;
	C = B;
	cout << "B *= A" << endl << (C *= A) << endl;
	cout << "C = A * 2" << endl << (C = A * 2) << endl;
	cout << "C = 2 * A" << endl << (C = 2 * A) << endl;
	cout << "C *= 2" << endl << (C *= 2) << endl;
}

void testEquality(const Matrix& A, const Matrix& B){
	cout<<endl<<"--- Test Equality ---"<<endl<<endl;
	printTwoMatrix(A, B);
	cout << "A == B" << endl << (A == B) << endl;
	cout << "A != B" << endl << (A != B) << endl;
}

void testReadandWrite(const Matrix& A){
	cout<<endl<<"--- Test Read and Write ---"<<endl<<endl;
	Matrix C = A;
	cout<<"Matrix C"<<endl<<C<<endl;
	cout<<"C(0,0) = "<<C(0,0)<<endl;
	cout<<"C(0,1) = "<<C(0,1)<<endl;
	cout<<"C(0,2) = "<<C(0,2)<<endl;
	cout<<"C(0,0) change to 100 = "<<(C(0,0)=100)<<endl;
	cout<<"C(0,1) change to 200 = "<<(C(0,1)=200)<<endl;
	cout<<"C(0,2) change to 300 = "<<(C(0,2)=300)<<endl;
	cout<<endl<<"Matrix C after write"<<endl<<C<<endl;
}

void testReferenceCounting(const Matrix& A, const Matrix& B){
	cout<<endl<<"--- Test Reference Counting ---"<<endl<<endl;
	cout<<"Reference Count of A before creat C(A)= "<<(A.mattab->ref)<<endl;
	cout<<"Copy A to C"<<endl;
	Matrix C(A);
	cout<<"Reference Count of A = "<<(A.mattab->ref)<<endl;
	cout<<"Reference Count of C = "<<(C.mattab->ref)<<endl;
}

void testException(const Matrix& A, const Matrix& B, const Matrix& C, const Matrix& D){
	cout<<endl<<"--- Test Exception ---"<<endl<<endl;
	cout<<"Matrix A"<<endl<<A<<endl;
	cout<<"Matrix B"<<endl<<B<<endl;
	cout<<"Matrix C"<<endl<<C<<endl;
	cout<<"Matrix D"<<endl<<D<<endl;
	Matrix E("mat_3x3_1.txt");
	cout<<(E = A + C)<<endl;
	//Matrix F("mat.txt");
	//cout<<E(5,5)<<endl;
}
	