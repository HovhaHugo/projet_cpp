// projet_cpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CMatrix.h"
#include "OverloadedOperator.h"
using namespace std;


int main(int argc, char *argv[])
{
    unsigned int uiMatrixNbRead = argc - 1;
    if (uiMatrixNbRead == 0) {
        cerr << "ERREUR : Pas d'arguments passes en parametre" << endl;
        return -1;
    }

    //For each path file send, we create a matrix
    CMatrix<double>** ppMATMatrixList = (CMatrix<double>**) malloc(sizeof(CMatrix<double>) * uiMatrixNbRead);
    if (ppMATMatrixList == nullptr) {
        cerr << "ERREUR : Erreur d'allocation mémoire" << endl;
        return -1;
    }

    cout << "Debut du test : " << endl;
    cout << "---------------------------" << endl;
    cout << "Affichage de la/les matrice.s" << endl;

    //For each matrix we show them
    for (unsigned int uiLoop = 1; uiLoop <= uiMatrixNbRead; uiLoop++) {
        try {
            cout << "Matrice numero " << uiLoop << ":" << endl;
            ppMATMatrixList[uiLoop - 1] = new CMatrix<double>(argv[uiLoop]);
            ppMATMatrixList[uiLoop - 1]->MATshow();
            cout << "---------------------------" << endl;
        }
        catch (CException EXCError) {
            cerr << "ERREUR :";
            switch (EXCError.EXCgetValue()) {
            case 1:
                cerr << "Fichier introuvable" << endl; break;
            case 2:
                cerr << "Erreur de conversion, une lettre est lue comme un chiffre" << endl; break;
            case 3:
                cerr << "Type incompatible" << endl; break;
            case 4:
                cerr << "Valeur manquante" << endl; break;
            case 5:
                cerr << "Matrice lue differente de la matrice precedente" << endl; break;
            case 6:
                cerr << "Erreur d'allocation mémoire" << endl; break;
            }
            return -1;
        }
    }



    //Ask the user to bring a value
    double dVal = 0;
    cout << "Entrez un chiffre: ";
    cin >> dVal;

    if (dVal == 0) {
        cout << "Vous avez soit entre 0 soit autre chose qu'un chiffre" << endl;
        cout << "S'il s'agit d'une erreur, merci de saisir un nouveau chiffre :" << endl;
        cin >> dVal;
    }



    cout << "Multiplication avec c" << endl;
    //We show the result of the multiplication of each matrix with dValue
    for (unsigned int uiLoop = 0; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            cout << "Matrice numero " << uiLoop << ":" << endl;
            CMatrix<double>* resultMatrix = (*ppMATMatrixList[uiLoop]) * dVal;
            resultMatrix->MATshow();
            delete resultMatrix;
            cout << "---------------------------" << endl;
        }
        catch (CException EXCError) {
            cerr << "ERREUR :";
            switch (EXCError.EXCgetValue()) {
            case 3:
                cerr << "Type incompatible" << endl; break;
            }
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
                CMatrix<double>* resultMatrix = *ppMATMatrixList[uiLoop] / dVal;
                resultMatrix->MATshow();
                delete resultMatrix;
                cout << "---------------------------" << endl;
            }
            catch (CException EXCError) {
                cerr << "ERREUR :";
                switch (EXCError.EXCgetValue()) {
                case 3:
                    cerr << "Type incompatible" << endl; break;
                case 8:
                    cerr << "Division par zero" << endl; break;
                }
                return -1;
            }

        }
    }
    cout << "---------------------------" << endl;


    cout << "Addition des matrices" << endl;
    //We show the result of the multiplication of every matrix
    CMatrix<double>* pMATResulMatrix = new CMatrix<double>(*ppMATMatrixList[0]);
    for (unsigned int uiLoop = 1; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            pMATResulMatrix = *pMATResulMatrix + *ppMATMatrixList[uiLoop];
        }
        catch (CException EXCError) {
            cerr <<"ERREUR :";
            switch (EXCError.EXCgetValue()) {
            case 3 : 
                cerr << "Type incompatible" << endl; break;
            case 7:
                cerr << "Conditions d'operation non respectees" << endl; break;
            }
            return -1;
        }

    }
    pMATResulMatrix->MATshow();
    cout << "---------------------------" << endl;
    delete pMATResulMatrix;


    cout << "Addition et soustraction des matrices" << endl;
    //We show the result of this operation : M1 - M2 + M3 - M4 + M5 - ...
    CMatrix<double>* pMATResulMatrix2 = new CMatrix<double>(*ppMATMatrixList[0]);
    bool bPlus = false;
    for (unsigned int uiLoop = 0; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            if (bPlus == true) {
                pMATResulMatrix2 = *pMATResulMatrix2 + *ppMATMatrixList[uiLoop];
                bPlus = false;
            }
            else {
                pMATResulMatrix2 = *pMATResulMatrix2 - *ppMATMatrixList[uiLoop];
                bPlus = true;
            }
        }
        catch (CException EXCError) {
            cerr << "ERREUR :";
            switch (EXCError.EXCgetValue()) {
            case 3:
                cerr << "Type incompatible pour l'operation" << endl; break;
            case 7:
                cerr << "Conditions d'opération non respectees" << endl; break;
            }
            return -1;
        }
    }
    pMATResulMatrix2->MATshow();
    cout << "---------------------------" << endl;
    delete pMATResulMatrix2;


    cout << "Multiplication des matrices" << endl;
    //We show the result of the sum of every matrix  : M1 + M2 + M3 + ...
    CMatrix<double>* pMATResulMatrix3 = new CMatrix<double>(*ppMATMatrixList[0]);
    for (unsigned int uiLoop = 1; uiLoop < uiMatrixNbRead; uiLoop++) {
        try {
            pMATResulMatrix3 = *pMATResulMatrix3 * *ppMATMatrixList[uiLoop];
        }
        catch (CException EXCError) {
            cerr << "ERREUR :";
            switch (EXCError.EXCgetValue()) {
            case 3:
                cerr << "Type incompatible" << endl; break;
            case 7:
                cerr << "Conditions d'operation non respectees" << endl; break;
            case 8:
                cerr << "Division par zero" << endl; break;
            }
            return -1;
        }

    }
    pMATResulMatrix3->MATshow();
    cout << "---------------------------" << endl;
    delete pMATResulMatrix3;
}
