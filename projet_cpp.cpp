// projet_cpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CMatrix.h"
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
    matricetest->MATTransposer();

    matricetest->MATshow();

    cout << "Multiplication x2" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceMultiple = new CMatrix<double>(*(*matricetest * 2.0));
    
    matriceMultiple->MATshow();

    cout << "Division /2" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceDivision = new CMatrix<double>(*(*matriceMultiple /2.0));
    
    matriceDivision->MATshow();

    cout << "Multiplication xMatrice" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceMultiple2 = new CMatrix<double>(*(*matriceDivision * *matriceMultiple));

    matriceMultiple2->MATshow();

    cout << "Addition +Matrice" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceAddition = new CMatrix<double>(*(*matriceDivision + *matriceMultiple));

    matriceAddition->MATshow();

    cout << "Substraction -Matrice" << endl;
    cout << "-----------------" << endl;
    CMatrix<double>* matriceSoustraction = new CMatrix<double>(*(*matriceDivision - *matriceMultiple));

    matriceSoustraction->MATshow();

	cout << "test fini" << endl;
}