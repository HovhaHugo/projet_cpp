// projet_cpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CMatrix.h"
#include "OverloadedOperator.h"
using namespace std;


int main(int argc, char *argv[])
{
    unsigned int uiMatrixNbRead = argc - 1;

    //For each path file send, we create a matrix
    CMatrix<double>** pMatrixList = (CMatrix<double>**) malloc(sizeof(CMatrix<double>) * uiMatrixNbRead);
    if (pMatrixList == nullptr) {
        CException EXCError(EXCEPTION_InvalidCondition);
        throw EXCError;
    }

    cout << "Debut du test : " << endl;
    cout << "---------------------------" << endl;
    cout << "Affichage de la/les matrice.s" << endl;

    //For each matrix we show them
    for (unsigned int uiLoop = 1; uiLoop <= uiMatrixNbRead; uiLoop++) {
        try {
            cout << "Matrice numero " << uiLoop << ":" << endl;
            pMatrixList[uiLoop - 1] = new CMatrix<double>(argv[uiLoop]);
            pMatrixList[uiLoop - 1]->MATshow();
            cout << "---------------------------" << endl;
        }
        catch (CException EXCError) {
            cerr << EXCError.EXCgetFunction();
            return -1;
        }
    }



    //Ask the user to bring a value
    double dVal = 0;
    cout << "Entrez un chiffre: ";
    cin >> dVal;

    if (dVal == 0) {
        cout << "Vous avez soit taper 0 soit un autre chose qu'un chiffre" << endl;
        cout << "S'il s'agit d'une erreur, merci de saisir un nouveau chiffre :" << endl;
        cin >> dVal;
    }



    cout << "Multiplication avec c" << endl;
    //We show the result of the multiplication of each matrix with dValue
    for (unsigned int uiLoop = 0; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            cout << "Matrice numero " << uiLoop << ":" << endl;
            CMatrix<double>* resultMatrix = (*pMatrixList[uiLoop]) * dVal;
            resultMatrix->MATshow();
            delete resultMatrix;
            cout << "---------------------------" << endl;
        }
        catch (CException EXCError) {
            cerr << EXCError.EXCgetFunction();
            return -1;
        }
    }
    cout << "---------------------------" << endl;


    cout << "Division avec c" << endl;
    if (dVal == 0) {
        cout << "Division impossible avec 0, opertation passer" << endl;
    }
    else {
        //We show the result of the division of each matrix with dValuec
        for (unsigned int uiLoop = 0; uiLoop < uiMatrixNbRead; uiLoop++) {
            cout << "Matrice numero " << uiLoop << ":" << endl;
            try {
                CMatrix<double>* resultMatrix = *pMatrixList[uiLoop] / dVal;
                resultMatrix->MATshow();
                delete resultMatrix;
                cout << "---------------------------" << endl;
            }
            catch (CException EXCError) {
                cerr << EXCError.EXCgetFunction();
                return -1;
            }

        }
    }
    cout << "---------------------------" << endl;


    cout << "Addition des matrices" << endl;
    //We show the result of the multiplication of every matrix
    CMatrix<double>* resultMatrix = new CMatrix<double>(*pMatrixList[0]);
    for (unsigned int uiLoop = 1; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            resultMatrix = *resultMatrix + *pMatrixList[uiLoop];
        }
        catch (CException EXCError) {
            cerr << EXCError.EXCgetFunction();
            //return -1;
        }

    }
    resultMatrix->MATshow();
    cout << "---------------------------" << endl;
    delete resultMatrix;


    cout << "Addition et soustraction des matrices" << endl;
    //We show the result of this operation : M1 - M2 + M3 - M4 + M5 - ...
    CMatrix<double>* resultMatrix2 = new CMatrix<double>(*pMatrixList[0]);
    bool bPlus = false;
    for (unsigned int uiLoop = 0; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            if (bPlus == true) {
                resultMatrix2 = *resultMatrix2 + *pMatrixList[uiLoop];
                bPlus = false;
            }
            else {
                resultMatrix2 = *resultMatrix2 - *pMatrixList[uiLoop];
                bPlus = true;
            }
        }
        catch (CException EXCError) {
            cerr << EXCError.EXCgetFunction();
            return -1;
        }
    }
    resultMatrix2->MATshow();
    cout << "---------------------------" << endl;
    delete resultMatrix2;


    cout << "Multiplication des matrices" << endl;
    //We show the result of the sum of every matrix  : M1 + M2 + M3 + ...
    CMatrix<double>* resultMatrix3 = new CMatrix<double>(*pMatrixList[0]);
    for (unsigned int uiLoop = 1; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            resultMatrix3 = *resultMatrix3 * *pMatrixList[uiLoop];
        }
        catch (CException EXCError) {
            cerr << EXCError.EXCgetFunction();
            return -1;
        }

    }
    resultMatrix3->MATshow();
    cout << "---------------------------" << endl;
    delete resultMatrix3;
}
