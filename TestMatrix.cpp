#include "Matrix.h"
#include <iostream>

using namespace std;

int main(){
	try {
		double** data1;
		double** data2;

		data1 = new double*[3];
		data2 = new double*[3];

		for(int i = 0; i < 3; i++){
			data1[i] = new double[3];
			data2[i] = new double[3];
		}

		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				data1[i][j] = i;
				data2[i][j] = i+j;
			}
		}


		
		rcMatrix F;
		rcMatrix G(3 ,3 , data2);
		rcMatrix H("mat_3x3_1.txt");
		
		
		cout << "--- Macierz 1 ---" << endl << endl << H << endl;
		
		cout << "--- Macierz 2 ---" << endl << endl << G << endl;
		
		cout << "--- + i - ---" << endl;
		//cout << (F = G + H) <<  endl;

		//cout << (F = G - H) <<  endl;
		/*
		cout << "--- += i -= ---" << endl;
		cout << (G += G) << endl;
		cout << (H -= H) << endl;
	*/
		
		cout << "--- *= i * ---" << endl;
		cout << (F = H * G) <<  endl;
		//cout << (G *= G) << endl;

		for(int i = 0; i < 3; i++){
			delete[] data1[i];
			delete[] data2[i];
		}
		delete[] data1;
		delete[] data2;

		} catch(exception& e) {
		cout << "Wystapil blad - " << e.what() << endl;
		} catch(...) {
		cout << "Wystapil nieznany blad." << endl;
		}
	return 0;
}
