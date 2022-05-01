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

	cout << "test fini" << endl;
}