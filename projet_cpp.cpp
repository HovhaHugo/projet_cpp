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
        CException EXCError(EXCEPTION_MallocError);
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
        cout << "Vous avez soit entre 0 soit un autre chose qu'un chiffre" << endl;
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
        cout << "Division impossible avec 0, operation passee" << endl;
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
    CMatrix<double>* pMATResulMatrix = new CMatrix<double>(*pMatrixList[0]);
    for (unsigned int uiLoop = 1; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            pMATResulMatrix = *pMATResulMatrix + *pMatrixList[uiLoop];
        }
        catch (CException EXCError) {
            cerr << EXCError.EXCgetFunction();
            //return -1;
        }

    }
    pMATResulMatrix->MATshow();
    cout << "---------------------------" << endl;
    delete pMATResulMatrix;


    cout << "Addition et soustraction des matrices" << endl;
    //We show the result of this operation : M1 - M2 + M3 - M4 + M5 - ...
    CMatrix<double>* pMATResulMatrix = new CMatrix<double>(*pMatrixList[0]);
    bool bPlus = false;
    for (unsigned int uiLoop = 0; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            if (bPlus == true) {
                pMATResulMatrix = *pMATResulMatrix + *pMatrixList[uiLoop];
                bPlus = false;
            }
            else {
                pMATResulMatrix = *pMATResulMatrix - *pMatrixList[uiLoop];
                bPlus = true;
            }
        }
        catch (CException EXCError) {
            cerr << EXCError.EXCgetFunction();
            return -1;
        }
    }
    pMATResulMatrix->MATshow();
    cout << "---------------------------" << endl;
    delete pMATResulMatrix;


    cout << "Multiplication des matrices" << endl;
    //We show the result of the sum of every matrix  : M1 + M2 + M3 + ...
    CMatrix<double>* pMATResulMatrix = new CMatrix<double>(*pMatrixList[0]);
    for (unsigned int uiLoop = 1; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            pMATResulMatrix = *pMATResulMatrix * *pMatrixList[uiLoop];
        }
        catch (CException EXCError) {
            cerr << EXCError.EXCgetFunction();
            return -1;
        }

    }
    pMATResulMatrix->MATshow();
    cout << "---------------------------" << endl;
    delete pMATResulMatrix;
}
