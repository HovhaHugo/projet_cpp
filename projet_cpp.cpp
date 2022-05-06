// projet_cpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CMatrix.h"
#include "OverloadedOperator.h"
using namespace std;


int main()
{
	cout << "test commence" << endl;

	//const char* test = "C:/Users/mathi/OneDrive/Bureau/test.txt";
    //CMatrix<double> *matricetest = new CMatrix<double>(test);
    
    CMatrix<double>* matricetest = new CMatrix<double>(3,3);
    cout << "Matrice " << endl;
    cout << "-----------------" << endl;
    cout << "Nombre de colonne :" << matricetest->MATGetColumnNumbre() << endl;
    cout << "Nombre de ligne   : " << matricetest->MATGetLineNumbre() << endl;
    cout << "Contenue de la matrice :" << endl;
    matricetest->MATshow();

    cout << "Transposer" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceTransposer = matricetest->MATTransposer();

    matriceTransposer->MATshow();

    cout << "Multiplication x2" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceMultiple = (2.0 * *matricetest);
    
    matriceMultiple->MATshow();

    cout << "Division /2" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceDivision = (*matriceMultiple /2.0);
    
    matriceDivision->MATshow();

    cout << "Multiplication xMatrice" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceMultiple2 = (*matriceDivision * *matriceMultiple);

    matriceMultiple2->MATshow();

    cout << "Addition +Matrice" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceAddition = (*matriceDivision + *matriceMultiple);

    matriceAddition->MATshow();

    cout << "Substraction -Matrice" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceSoustraction = (*matriceDivision - *matriceMultiple);

    matriceSoustraction->MATshow();

    delete matricetest;

	cout << "test fini" << endl;
}