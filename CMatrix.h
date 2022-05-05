
#ifndef DEF_CMATRIX
#define DEF_CMATRIX

#define EXCEPTION_TypeMissmatch 1		//They are not the same type of matrix
#define EXCEPTION_DivisionByZero 2		//As the name said, we cant' divide by zero
#define EXCEPTION_InvalidType 3			//For the different type of operation, we chose not to accept object or char

#include "Parser.h"
#include "CException.h"
#include <stdio.h>
#include <iostream>
using namespace std;


template<class Type>
class CMatrix
{
private:
	unsigned int uiMATColumnNumber;
	unsigned int uiMATLineNumber;
	Type** pptypeMatrixContent;
public:
	//Constructors
	CMatrix();
	CMatrix(Type** ptTypeMatrix, unsigned int uiNbColomn, unsigned int uiNbLine);
	CMatrix(unsigned int uiNbColomn, unsigned int uiNbLine);
	CMatrix(const char* pcFilePath);
	CMatrix(CMatrix &MATParam);

	//Overloaded Operators
	CMatrix* operator*(double dMultiplicator);
	CMatrix* operator/(double dDivisor);
	CMatrix* operator*(CMatrix MATParam);
	CMatrix* operator+(CMatrix MATParam);
	CMatrix* operator-(CMatrix MATParam);
	CMatrix* operator=(CMatrix MATParam); //Just the same as the copy constructor

	//Method
	void MATTransposer();
	void MATshow();
	unsigned int MATGetColumnNumbre();
	unsigned int MATGetLineNumbre();
	Type* MATGetValue(unsigned int uiColomn, unsigned int uiLine);
};


//Constructors
template<class Type>
CMatrix<Type>::CMatrix(const char* pcFilePath) {

		try {
			pptypeMatrixContent = ParseDataDouble(pcFilePath, &uiMATColumnNumber, &uiMATLineNumber);
		}
		catch (CException& EXCException) {
			printf("An error occured\nError code: %d\nFunction: %s\n",EXCException.EXCgetValue(),EXCException.EXCgetFunction());
		}

	}

template<class Type>
CMatrix<Type>::CMatrix() {
		uiMATColumnNumber = 0;
		uiMATLineNumber = 0;
		pptypeMatrixContent = new Type * [uiMATLineNumber];
		for (unsigned int uiLoop = 0; uiLoop < uiMATLineNumber; uiLoop++) {
			pptypeMatrixContent[uiLoop] = new Type[uiMATColumnNumber];
		}
	}

template<class Type>
CMatrix<Type>::CMatrix(Type** ptTypeMatrix, unsigned int uiNbColomn, unsigned int uiNbLine) {
		uiMATColumnNumber = uiNbColomn;
		uiMATLineNumber = uiNbLine;
		pptypeMatrixContent = nullptr;
		pptypeMatrixContent = new Type* [uiMATLineNumber];
		for (unsigned int uiLoop = 0; uiLoop < uiMATLineNumber; uiLoop++)
			pptypeMatrixContent[uiLoop] = new Type[uiMATColumnNumber];

		for (unsigned int iLoopColomne = 0; iLoopColomne < uiMATColumnNumber; iLoopColomne++) {
			for (unsigned int iLoopLine = 0; iLoopLine < uiMATLineNumber; iLoopLine++) {
				pptypeMatrixContent[iLoopColomne][iLoopLine] = ptTypeMatrix[iLoopColomne][iLoopLine];
			}
		}
	}

template<class Type>
CMatrix<Type>::CMatrix(unsigned int uiNbColomn, unsigned int uiNbLine) {
	uiMATColumnNumber = uiNbColomn;
	uiMATLineNumber = uiNbLine;
	double dValue = 0.0;
	pptypeMatrixContent = new Type * [uiMATLineNumber];
	for (unsigned int uiLoop = 0; uiLoop < uiMATLineNumber; uiLoop++){
		pptypeMatrixContent[uiLoop] = new Type[uiMATColumnNumber];
	}
	
	for (unsigned int iLoopColomne = 0; iLoopColomne < uiMATColumnNumber; iLoopColomne++) {
		for (unsigned int iLoopLine = 0; iLoopLine < uiMATLineNumber; iLoopLine++) {
			pptypeMatrixContent[iLoopColomne][iLoopLine] = dValue;
			dValue++;
		}
	}
}

template<class Type>
CMatrix<Type>::CMatrix(CMatrix<Type> &MATParam) {
		uiMATColumnNumber = MATParam.MATGetColumnNumbre();
		uiMATLineNumber = MATParam.MATGetLineNumbre();

		pptypeMatrixContent = new Type * [uiMATLineNumber];
		for (unsigned int uiLoop = 0; uiLoop < uiMATLineNumber; uiLoop++) {
			pptypeMatrixContent[uiLoop] = new Type[uiMATColumnNumber];
		}

		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
			for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
				pptypeMatrixContent[uiLoopColomne][uiLoopLine] = *MATParam.MATGetValue(uiLoopColomne, uiLoopLine);
			}
		}
	}

//Operator overload
template<class Type>
CMatrix<Type>* CMatrix<Type>::operator*(double dMultiplicator){
	if (typeid(*this->MATGetValue(0,0)) == typeid(char) || typeid(*this->MATGetValue(0, 0)) == typeid(class)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}
	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiMATColumnNumber, uiMATLineNumber);

	//Multiplication
	if (typeid(MATTMatrix->pptypeMatrixContent[0][0]) == typeid(double)) {
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
			for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
				MATTMatrix->pptypeMatrixContent[uiLoopColomne][uiLoopLine] = *MATTMatrix->MATGetValue(uiLoopColomne, uiLoopLine) * dMultiplicator;
			}
		}
	}
	
	return MATTMatrix;
}

template<class Type>
CMatrix<Type>* CMatrix<Type>::operator/(double dDivisor){
		//Exception management
		if(dDivisor == 0){
			CException EXCError(EXCEPTION_DivisionByZero);
        	throw EXCError;
		}

		if (typeid(*this->MATGetValue(0, 0)) == typeid(char) || typeid(*this->MATGetValue(0, 0)) == typeid(class)) {
			CException EXCError(EXCEPTION_InvalidType);
			throw EXCError;
		}

		//We create a new object and send it at the end of the function
		CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiMATColumnNumber, uiMATLineNumber);

		//Division
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
			for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
				MATTMatrix->pptypeMatrixContent[uiLoopColomne][uiLoopLine] = *MATGetValue(uiLoopColomne, uiLoopLine)/ dDivisor;
			}
		}
		
		return MATTMatrix;
	}

template<class Type>
CMatrix<Type>* CMatrix<Type>::operator*(CMatrix<Type> MATParam){
	if(uiMATColumnNumber != MATParam.MATGetLineNumbre()){
		CException EXCError(EXCEPTION_MissingFile);
		throw EXCError;
	}

	if (typeid(*this->MATGetValue(0, 0)) == typeid(char) || typeid(*this->MATGetValue(0, 0)) == typeid(class)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiMATColumnNumber, uiMATLineNumber);

	//Transposition
	for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
			MATTMatrix->pptypeMatrixContent[uiLoopColomne][uiLoopLine] = *MATGetValue(uiLoopColomne, uiLoopLine)*(*MATParam.MATGetValue(uiLoopColomne, uiLoopLine));
		}
	}
	
	return MATTMatrix;
}

template<class Type>
CMatrix<Type>* CMatrix<Type>::operator+(CMatrix<Type> MATParam){
		if(uiMATColumnNumber != MATParam.MATGetColumnNumbre() && uiMATLineNumber != MATParam.MATGetLineNumbre()){
			CException EXCError(EXCEPTION_MissingFile);
        	throw EXCError;
		}

		if (typeid(*this->MATGetValue(0, 0)) == typeid(char) || typeid(*this->MATGetValue(0, 0)) == typeid(class)) {
			CException EXCError(EXCEPTION_InvalidType);
			throw EXCError;
		}

		CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiMATColumnNumber, uiMATLineNumber);

		//Transposition
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
			for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
				MATTMatrix->pptypeMatrixContent[uiLoopColomne][uiLoopLine] = *MATGetValue(uiLoopColomne, uiLoopLine)+ 
					*MATParam.MATGetValue(uiLoopColomne, uiLoopLine);
			}
		}
		
		return MATTMatrix;
	}

template<class Type>
CMatrix<Type>* CMatrix<Type>::operator-(CMatrix<Type> MATParam){
		if(uiMATColumnNumber != MATParam.MATGetColumnNumbre() && uiMATLineNumber != MATParam.MATGetLineNumbre()){
			CException EXCError(EXCEPTION_MissingFile);
        	throw EXCError;
		}

		if (typeid(*this->MATGetValue(0, 0)) == typeid(char) || typeid(*this->MATGetValue(0, 0)) == typeid(class)) {
			CException EXCError(EXCEPTION_InvalidType);
			throw EXCError;
		}

		CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiMATColumnNumber, uiMATLineNumber);

		//Transposition
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
			for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
				MATTMatrix->pptypeMatrixContent[uiLoopColomne][uiLoopLine] = *MATGetValue(uiLoopColomne, uiLoopLine)- 
					*MATParam.MATGetValue(uiLoopColomne, uiLoopLine);
			}
		}
		
		return MATTMatrix;

	}

template<class Type>
CMatrix<Type>*	CMatrix<Type>::operator=(CMatrix<Type> MATParam){
		CMatrix<Type>* MATTMatrix = new CMatrix<Type>(MATParam.uiMATColumnNumber, MATParam.uiMATLineNumber);

		for (int iLoopColomne = 0; iLoopColomne < uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine < uiMATLineNumber; iLoopLine++) {
				MATTMatrix.pptypeMatrixContent[iLoopColomne][iLoopLine] = MATParam.MATGetValue(iLoopColomne, iLoopLine);
			}
		}

		return MATTMatrix;
	}

//Method
/**
	 * @brief Transpose la matrice actuelle 
	 * 
	 * @return CMatrix La matrice transposer
*/
template<class Type>
void CMatrix<Type>::MATTransposer() {
		//We create a new matrix to do the transposition
		CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiMATLineNumber, uiMATColumnNumber);

		//Transposition
		for (unsigned int iLoopColomne = 0; iLoopColomne < uiMATColumnNumber; iLoopColomne++) {
			for (unsigned int iLoopLine = 0; iLoopLine < uiMATLineNumber; iLoopLine++) {
				MATTMatrix->pptypeMatrixContent[iLoopColomne][iLoopLine] = pptypeMatrixContent[iLoopLine][iLoopColomne];
			}
		}
		
		uiMATColumnNumber = MATTMatrix->MATGetColumnNumbre();
		uiMATLineNumber = MATTMatrix->MATGetLineNumbre();
		pptypeMatrixContent = MATTMatrix->pptypeMatrixContent;
		
		//Not sure, might be not use that freeed this variable. 
		delete MATTMatrix;
	}

/**
	 * @brief Permet l'affichage de la matrice.
	 * 
	 */
template<class Type>
void CMatrix<Type>::MATshow() {
	if (pptypeMatrixContent == nullptr) {
		cout << "(null)\n";
	}
	else {
		for (unsigned int iLoopColomne = 0; iLoopColomne < uiMATColumnNumber; iLoopColomne++) {
			cout << "(";
			for (unsigned int iLoopLine = 0; iLoopLine < uiMATLineNumber; iLoopLine++) {
				cout << *MATGetValue(iLoopColomne,iLoopLine);
				cout << ", ";
			}
			cout << ")\n";
		}
	}
}
	
/**
	 * @brief Permet la récupération du nombre de colonnes
	 * 
	 * @return unsigned int Le nombre de colonnes
	 */
template<class Type>
unsigned int CMatrix<Type>::MATGetColumnNumbre() {
	return uiMATColumnNumber;
}

/**
	 * @brief Permet la récupération du nombre de lignes 
	 * 
	 * @return unsigned int Le nombre de lignes
	 */
template<class Type>
unsigned int CMatrix<Type>::MATGetLineNumbre() {
	return uiMATLineNumber;
}

/**
	 * @brief Permet de récupérer la valeur dans la matrice à la uiColomn-iéme colonne
	 * et uiLine-iéme ligne.
	 * @param uiColomn 	La colonne
	 * @param uiLine 	La ligne
	 * @return Type 	La valeur dans la matrice.
	 */
template<class Type>
Type* CMatrix<Type>::MATGetValue(unsigned int uiColomn, unsigned int uiLine) {
		//If the value are superior avec our number of colomne/line, we return an exception
		if(uiColomn > uiMATColumnNumber || uiLine > uiMATLineNumber){
			return NULL;
		}
		//Else, we return the value.
		else{
			for (unsigned int iLoopColomne = 0; iLoopColomne < uiMATColumnNumber; iLoopColomne++) {
				for (unsigned int iLoopLine = 0; iLoopLine < uiMATLineNumber; iLoopLine++) {
					if (iLoopLine == uiLine && iLoopColomne == uiColomn) {
						return &pptypeMatrixContent[iLoopColomne][iLoopLine];
					}
				}
			}
		}
	}

#endif