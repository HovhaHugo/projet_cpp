
#ifndef DEF_CMATRIX
#define DEF_CMATRIX


#define EXCEPTION_InvalidType 3			//The readed type is not compatible with the current parser used
#define EXCEPTION_InvalidCondition 7	//If we can't do the multiplication or the division
#define EXCEPTION_DivisionByZero 8		//As the name said, we cant' divide by zero

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
	Type** pptypeMATMatrixContent;
public:
	//Constructors
	~CMatrix();
	CMatrix();
	CMatrix(Type** pptypeMatrixContent, unsigned int uiNbColomn, unsigned int uiNbLine);
	CMatrix(unsigned int uiNbColomn, unsigned int uiNbLine);
	CMatrix(const char* pcFilePath);
	CMatrix(CMatrix &MATParam);

	//Overload Operator (special case)
	CMatrix<Type>* operator=(CMatrix<Type> MATParam);

	//Method
	CMatrix<Type>* MATTransposer();
	void MATshow();
	unsigned int MATGetColumnNumber();
	unsigned int MATGetLineNumber();
	Type MATGetValue(unsigned int uiColomn, unsigned int uiLine);
	void MATSetValue(unsigned int uiColomn, unsigned int uiLine, Type tValue);
};


/***
* Destructor of a CMatrix
* Input: /
* Output: /
* Precondition: /
* Postcondition: The object has been deleted from memory
***/
template<class Type>
CMatrix<Type>::~CMatrix() {
	for (unsigned int uiLoop = 0; uiLoop < uiMATLineNumber; ++uiLoop)
		delete[] pptypeMATMatrixContent[uiLoop];
	delete[] pptypeMATMatrixContent;
}


/***
* Constructor of CMatrix, receive a file path and use the parser
* Input: const char* pcFilePath
* Output: /
* Precondition: /
* Postcondition: If the parser throw an exception, the matrix 
***/
template<class Type>
CMatrix<Type>::CMatrix(const char* pcFilePath) {

	try {
		pptypeMATMatrixContent = ParseDataDouble(pcFilePath, &uiMATColumnNumber, &uiMATLineNumber);
	}
	catch (CException& EXCException) {
		throw EXCException;
	}

}


/***
* Default constructor of a CMatrix
* Input: /
* Output: /
* Precondition: /
* Postcondition: The CMatrix is initialised with a size of 1*1
***/
template<class Type>
CMatrix<Type>::CMatrix() {
		uiMATColumnNumber = 0;
		uiMATLineNumber = 0;

		pptypeMATMatrixContent = new Type * [uiMATLineNumber];

		for (unsigned int uiLoop = 0; uiLoop < uiMATLineNumber; uiLoop++) {
			pptypeMATMatrixContent[uiLoop] = new Type[uiMATColumnNumber];
		}
	}


/***
* Constructor of a CMatrix
* Input: Type** ptTypeMatrix, unsigned int uiNbColomn, unsigned int uiNbLine
* Output: /
* Precondition: ptTypeMatrix have the size of uiNbColumn * uiNbLine elements
* Postcondition: The CMatrix is initialised with a size of uiNbColumn * uiNbLine and the
*	pptypeMatrixContent is set to ptTypeMatrix
***/
template<class Type>
CMatrix<Type>::CMatrix(Type** pptypeMatrixContent, unsigned int uiNbColomn, unsigned int uiNbLine) {

		uiMATColumnNumber = uiNbColomn;
		uiMATLineNumber = uiNbLine;
		pptypeMATMatrixContent = nullptr;
		pptypeMATMatrixContent = new Type* [uiMATLineNumber];

		for (unsigned int uiLoop = 0; uiLoop < uiMATLineNumber; uiLoop++)
			pptypeMATMatrixContent[uiLoop] = new Type[uiMATColumnNumber];

		for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
			for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
				pptypeMATMatrixContent[uiLoopLine][uiLoopColomne] = pptypeMatrixContent[uiLoopLine][uiLoopColomne];
			}
		}
	}


/***
* Constructor of a CMatrix
* Input: unsigned int uiNbColomn, unsigned int uiNbLine
* Output: /
* Precondition: /
* Postcondition: The CMatrix is initialised with a size of uiNbColumn * uiNbLine and the content is filled with ?????????????????????
***/
template<class Type>
CMatrix<Type>::CMatrix(unsigned int uiNbColomn, unsigned int uiNbLine) {
	uiMATColumnNumber = uiNbColomn;
	uiMATLineNumber = uiNbLine;
	pptypeMATMatrixContent = new Type * [uiMATLineNumber];
	for (unsigned int uiLoop = 0; uiLoop < uiMATLineNumber; uiLoop++){
		pptypeMATMatrixContent[uiLoop] = new Type[uiMATColumnNumber];
	}

	for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
			pptypeMATMatrixContent[uiLoopLine][uiLoopColomne] = NULL;
		}
	}
}


/***
* Constructor by copy of a CMatrix
* Input: CMatrix<Type> &MATParam
* Output: /
* Precondition: /
* Postcondition: The CMatrix object is initialised with a copy of the MATParam's values
***/
template<class Type>
CMatrix<Type>::CMatrix(CMatrix<Type> &MATParam) {
		uiMATColumnNumber = MATParam.MATGetColumnNumber();
		uiMATLineNumber = MATParam.MATGetLineNumber();

		pptypeMATMatrixContent = new Type * [uiMATLineNumber];
		for (unsigned int uiLoop = 0; uiLoop < uiMATLineNumber; uiLoop++) {
			pptypeMATMatrixContent[uiLoop] = new Type[uiMATColumnNumber];
		}

		for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
			for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
				pptypeMATMatrixContent[uiLoopLine][uiLoopColomne] = MATParam.MATGetValue(uiLoopLine, uiLoopColomne);
			}
		}
	}



/***
* Overloaded operator =, does the same work as the copy constructir
* Input: CMatrix<Type> &MATParam
* Output: /
* Precondition: /
* Postcondition: The CMatrix object is initialised with a copy of the MATParam's values
***/
template<class Type>
CMatrix<Type>* CMatrix<Type>::operator=(CMatrix<Type> MATParam) {
	CMatrix<Type>* pMATMatrix = new CMatrix<Type>(MATParam.uiMATColumnNumber, MATParam.uiMATLineNumber);

	for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
			pMATMatrix.pptypeMatrixContent[uiLoopLine][uiLoopColomne] = MATParam.MATGetValue(uiLoopLine, uiLoopColomne);
		}
	}

	return pMATMatrix;
}



/***
* Transposition of a CMatrix
* Input: /
* Output: CMatrix<Type>*
* Precondition: /
* Postcondition: The returned CMatrix is a transposition version of the calling CMatrix object
***/
template<class Type>
CMatrix<Type>* CMatrix<Type>::MATTransposer() {
	//We create a new matrix to do the transposition
	CMatrix<Type>* pMATMatrix = new CMatrix<Type>(uiMATLineNumber, uiMATColumnNumber);

	//Transposition
	for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
			pMATMatrix->pptypeMATMatrixContent[uiLoopLine][uiLoopColomne] = pptypeMATMatrixContent[uiLoopLine][uiLoopColomne];
		}
	}

	return pMATMatrix;
}



/***
* Show the content of a CMatrix
* Input: /
* Output: /
* Precondition: /
* Postcondition: The CMatrix is ​​displayed in the console
***/
template<class Type>
void CMatrix<Type>::MATshow() {
	if (pptypeMATMatrixContent == nullptr) {
		cout << "(null)\n";
	}
	else {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
			cout << "(";
			for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
				cout << MATGetValue(uiLoopLine, uiLoopColomne);
				cout << ", ";
			}
			cout << ")\n";
		}
	}
}


/***
* Getter of the column number of a CMatrix
* Input: /
* Output: unsigned int
* Precondition: /
* Postcondition: The return value is the number of column of the CMatrix
***/
template<class Type>
unsigned int CMatrix<Type>::MATGetColumnNumber() {
	return uiMATColumnNumber;
}


/***
* Getter of the line number of a CMatrix
* Input: /
* Output: unsigned int
* Precondition: /
* Postcondition: The return value is the number of line of the CMatrix
***/
template<class Type>
unsigned int CMatrix<Type>::MATGetLineNumber() {
	return uiMATLineNumber;
}


/***
* Getter of a value of a CMatrix
* Input: unsigned int uiColomn, unsigned int uiLine
* Output: Type
* Precondition: /
* Postcondition: If the uiColumn and uiLine are out of bound, an error is thrown.
*	Else, the return value is a copy of the element present at these coordinates
***/
template<class Type>
Type CMatrix<Type>::MATGetValue(unsigned int uiLine, unsigned int uiColomn) {

	//If the value are in our number of colomne/line, we return the value
	if(uiColomn <= uiMATColumnNumber && uiLine <= uiMATLineNumber){
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
			for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
				if (uiLoopLine == uiLine && uiLoopColomne == uiColomn) {
					return pptypeMATMatrixContent[uiLoopLine][uiLoopColomne];
				}
			}
		}
	}
	else {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}
	return NULL;
}


/***
* Setter of a value of a CMatrix
* Input: unsigned int uiColomn, unsigned int uiLine, Type tValue
* Output: /
* Precondition: /
* Postcondition: If the uiColumn and uiLine are out of bound, an error is thrown.
*	Else, the input element is copied in the CMatrix at these coordinates
***/
template<class Type>
void CMatrix<Type>::MATSetValue(unsigned int uiLine, unsigned int uiColomn, Type tValue) {

	//Check type
	if (typeid(MATGetValue(0, 0)) != typeid(tValue)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	//If the value are out of bound, we return an exception
	if (uiColomn > uiMATColumnNumber || uiLine > uiMATLineNumber) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}
	//Else, we return the value.
	else {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiMATLineNumber; uiLoopLine++) {
			for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiMATColumnNumber; uiLoopColomne++) {
				if (uiLoopLine == uiLine && uiLoopColomne == uiColomn) {
					pptypeMATMatrixContent[uiLoopLine][uiLoopColomne] = tValue;
				}
			}
		}
	}
}

#endif
