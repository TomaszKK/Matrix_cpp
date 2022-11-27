#include "Matrix.h"
#include <iostream>

using namespace std;

int main(){
	try {
		rcMatrix A("matrix.txt");
		rcMatrix B("matrix2.txt");
		rcMatrix C;
		rcMatrix D("mat_3x3_1.txt");
		rcMatrix E("mat_3x3_2.txt");
		rcMatrix F;
		cout << "--- Macierz 1 ---" << endl << endl << D << endl;
		cout << "--- Macierz 2 ---" << endl << endl << E << endl;
		cout << "--- + i - ---" << endl;
		cout << (F = D + E) <<  endl;
		cout << (F = E - D) <<  endl;
		cout << "--- += i -= ---" << endl;
		cout << (D += E) << endl;
		cout << (E -= D) << endl;
		cout << "--- *= i * ---" << endl;
		cout << "--- Macierz 1 ---" << endl << endl << A << endl;
		cout << "--- Macierz 2 ---" << endl << endl << B << endl;
		cout << (C = B * A) <<  endl;
		cout << (B *= A) << endl;
		} catch(exception& e) {
		cout << "Wystapil blad - " << e.what() << endl;
		} catch(...) {
		cout << "Wystapil nieznany blad." << endl;
		}
	return 0;
}
