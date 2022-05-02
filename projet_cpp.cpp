// projet_cpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CMatrix.h"
using namespace std;


int main()
{
	cout << "test commence" << endl;

	const char* test = "C:/Users/mathi/OneDrive/Bureau/test.txt";
	CMatrix<double> *matricetest = new CMatrix<double>(test);

	delete matricetest;

	size_t stTaille = 3;
    int iVal1 = 1;
    int iVal2 = 2;
    int iVal3 = 3;
    int iVal4 = 4;
    int iVal5 = 5;
    int iVal6 = 6;
    int iVal7 = 7;
    int iVal8 = 8;
    int iVal9 = 9;
    //cout << iVal9;
    int* iLigne1 = new int();
    iLigne1[0] = iVal1;
    iLigne1[1] = iVal2;
    iLigne1[2] = iVal3;
    int* iLigne2 = new int();
    iLigne2[0] = iVal4;
    iLigne2[1] = iVal5;
    iLigne2[2] = iVal6;
    int* iLigne3 = new int();
    iLigne3[0] = iVal7;
    iLigne3[1] = iVal6;
    iLigne3[2] = iVal9;
    int** ptMatrix = new int* [3];
    ptMatrix[0] = iLigne1;
    ptMatrix[1] = iLigne2;
    ptMatrix[2] = iLigne3;

    cout << "Contenue de la matrice : \n";
    for (int x = 0; x < 3; x++) {
        cout << "(";
        for (int y = 0; y < 3; y++) {
            cout << ptMatrix[x][y];
            cout << " , ";
            //*ptMatrix++;
        }
        cout << ")\n";
    }

    CMatrix<int> matrice = CMatrix<int>(ptMatrix,3,3);
    matrice.MATGetColumnNumbre();

	cout << "test fini" << endl;
}