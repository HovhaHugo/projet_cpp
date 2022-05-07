// projet_cpp.cpp : Ce fichier contient la fonction 'main'. L'execution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CMatrix.h"
#include "OverloadedOperator.h"
using namespace std;


int main(int argc, char *argv[])
{
	cout << "test commence" << endl;

	//const char* test = "C:/Users/mathi/OneDrive/Bureau/test.txt";
    //CMatrix<double> *matricetest = new CMatrix<double>(test);
    
    /*CMatrix<double>* matricetest = new CMatrix<double>(3,3);
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

	cout << "test fini" << endl;*/

    unsigned int uiMatrixNbRead = argc-1;

    //For each mpath file send, we create a matrix 
    CMatrix<double>* pMatrixList = (CMatrix<double>*) malloc(sizeof(CMatrix<double>) * uiMatrixNbRead);
    if (pMatrixList == nullptr) {
        //Exception
    }



    for (unsigned int uiLoop = 1; uiLoop < uiMatrixNbRead; uiLoop++) {
    
        //Je sais pas trop comment faire
        pMatrixList[uiLoop] = new CMatrix<double>(argv[uiLoop]);
    
    }



    //Demander a l'utilisateur de saisir une valeur c
    double dVal = 0;
    cout << "Entrez une valeur :";
    cin >> dVal;
    


    //Afficher le resultat de la multiplication de chacune des matrices par la valeur c
    for (unsigned int uiLoop = 0; uiLoop < uiMatrixNbRead; uiLoop++) {

        CMatrix<double>* resultMatrix = pMatrixList[uiLoop] * dVal;
        resultMatrix->MATshow();
        delete resultMatrix;

    }



    //Afficher le resultat de la division de chacune des matrices par la valeur c
    for (unsigned int uiLoop = 0; uiLoop < uiMatrixNbRead; uiLoop++) {

        CMatrix<double>* resultMatrix = pMatrixList[uiLoop] / dVal;
        resultMatrix->MATshow();
        delete resultMatrix;

    }



    //Afficher le resultat de l'addition de toute les matrices entre elles : M1 + M2 + M3 + ...
    CMatrix<double>* resultMatrix = new CMatrix<double>(pMatrixList[0]);
    for (unsigned int uiLoop = 1; uiLoop < uiMatrixNbRead; uiLoop++) {

        //Il y aura surement une fuite memoire, car *resultMatrix + pMatrixList[uiLoop]
        //Cree un objet qui sera copie a resultMatrix, MAIS pas supprime ensuite
        resultMatrix = *resultMatrix + pMatrixList[uiLoop];

    }
    delete resultMatrix;



    //Afficher le resultat de l'opÃ©ration suivante : M1 - M2 + M3 - M4 + M5 - ...
    CMatrix<double>* resultMatrix = new CMatrix<double>(pMatrixList[0]);
    bool bPlus = false;
    for (unsigned int uiLoop = 0; uiLoop < uiMatrixNbRead; uiLoop++) {
        
        if (bPlus == true) {
            resultMatrix = *resultMatrix + pMatrixList[uiLoop];
            bPlus = false;
        }
        else {
            resultMatrix = *resultMatrix - pMatrixList[uiLoop];
            bPlus = true;
        }

    }
    delete resultMatrix;



    //Afficher le resultat de l'addition de toute les matrices entre elles : M1 + M2 + M3 + ...
    CMatrix<double>* resultMatrix = new CMatrix<double>(pMatrixList[0]);
    for (unsigned int uiLoop = 1; uiLoop < uiMatrixNbRead; uiLoop++) {

        //Il y aura surement une fuite memoire, car *resultMatrix + pMatrixList[uiLoop]
        //Cree un objet qui sera copie a resultMatrix, MAIS pas supprime ensuite
        resultMatrix = *resultMatrix * pMatrixList[uiLoop];

    }
    delete resultMatrix;
}