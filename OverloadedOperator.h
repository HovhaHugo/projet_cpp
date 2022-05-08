
#ifndef DEF_OVERLOADINGOPERATOR
#define DEF_OVERLOADINGOPERATOR

#include "CMatrix.h"


/***
* Multiplication between a constant and a CMatrix
* Input: double: dConstantParam, CMatrix<Type>& MATMatrixParam
* Output: CMatrix<Type>*
* Precondition: /
* Postcondition: The return contains the input CMatrix multiplied by dConstantParam
* Note : Function calls operator*(CMatrix<Type>& MATParam, double dMultiplicator)
***/
template<class Type>
CMatrix<Type>* operator*(double dConstantParam, CMatrix<Type>& MATMatrixParam) {
	return MATMatrixParam * dConstantParam;
}


/***
* Multiplication between a CMatrix and a constant
* Input: CMatrix<Type>& MATMatrixParam, double: dConstantParam
* Output: CMatrix<Type>*
* Precondition: /
* Postcondition: The return contains the input CMatrix multiplied by dConstantParam
***/
template<class Type>
CMatrix<Type>* operator*(CMatrix<Type>& MATParam, double dMultiplicator) {
	
	//Check type
	if (typeid(MATParam.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam.MATGetValue(0, 0)) == typeid(MATParam)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam.MATGetColumnNumber();
	uiNbLine = MATParam.MATGetLineNumber();
	Type tValue = NULL;

	CMatrix<Type>* pMATMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Multiplication
	for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
			tValue = MATParam.MATGetValue(uiLoopLine, uiLoopColomne) * dMultiplicator;
			pMATMatrix->MATSetValue(uiLoopLine, uiLoopColomne, tValue);
		}
	}
	return pMATMatrix;
}


/***
* Division of a CMatrix by a divisor
* Input: CMatrix<Type>& MATParam, double dDivisor
* Output: CMatrix<Type>*
* Precondition: /
* Postcondition: If dDvisor == 0, an error is thrown, else
	The return contains the input CMatrix divised by dDivisor
***/
template<class Type>
CMatrix<Type>* operator/(CMatrix<Type>& MATParam, double dDivisor) {
	
	//Check division by 0
	if (dDivisor == 0) {
		CException EXCError(EXCEPTION_DivisionByZero);
		throw EXCError;
	}

	//Check type
	if (typeid(MATParam.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam.MATGetValue(0, 0)) == typeid(MATParam)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam.MATGetColumnNumber();
	uiNbLine = MATParam.MATGetLineNumber();
	Type tValue = NULL;

	CMatrix<Type>* pMATMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Division
	for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
			tValue = MATParam.MATGetValue(uiLoopLine, uiLoopColomne)/ dDivisor;
			pMATMatrix->MATSetValue(uiLoopLine, uiLoopColomne, tValue);
		}
	}

	return pMATMatrix;
}


/***
* Multiplication between a CMatrix and an other CMatrix
* Input: CMatrix<Type>& MATParam1, CMatrix<Type>& MATParam2
* Output: CMatrix<Type>*
* Precondition: /
* Postcondition: If the 2 matrix' size are not compatibles or if they
*	don't have the same type, an error is thrown.
*	Else, the ouput matrix contains the result of the multiplication
***/
template<class Type>
CMatrix<Type>* operator*(CMatrix<Type>& MATParam1, CMatrix<Type>& MATParam2) {
	
	//check size
	if (MATParam1.MATGetColumnNumber() != MATParam2.MATGetLineNumber()) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}

	//check type
	if (typeid(MATParam1.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam1.MATGetValue(0, 0)) == typeid(MATParam1)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam1.MATGetColumnNumber();
	uiNbLine = MATParam1.MATGetLineNumber();
	Type tValue = NULL;

	CMatrix<Type>* pMATMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//multiplication
	for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
			tValue = MATParam1.MATGetValue(uiLoopLine, uiLoopColomne) * (MATParam2.MATGetValue(uiLoopLine, uiLoopColomne));
			pMATMatrix->MATSetValue(uiLoopLine, uiLoopColomne, tValue);
		}
	}

	return pMATMatrix;
}


/***
* Addition between a CMatrix and an other CMatrix
* Input: CMatrix<Type>& MATParam1, CMatrix<Type>& MATParam2
* Output: CMatrix<Type>*
* Precondition: /
* Postcondition: If the 2 matrix' size are not compatibles or if they
*	don't have the same type, an error is thrown.
*	Else, the ouput matrix contains the result of the addition
***/
template<class Type>
CMatrix<Type>* operator+(CMatrix<Type>& MATParam1, CMatrix<Type>& MATParam2) {
	
	//Check size
	if (MATParam1.MATGetColumnNumber() != MATParam2.MATGetColumnNumber() ||
		MATParam1.MATGetLineNumber() != MATParam2.MATGetLineNumber()) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}

	//Check type
	if (typeid(MATParam1.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam1.MATGetValue(0, 0)) == typeid(MATParam1)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam1.MATGetColumnNumber();
	uiNbLine = MATParam1.MATGetLineNumber();
	Type tValue = NULL;

	CMatrix<Type>* pMATMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Addition
	for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
			tValue = MATParam1.MATGetValue(uiLoopLine, uiLoopColomne) + (MATParam2.MATGetValue(uiLoopLine, uiLoopColomne));
			pMATMatrix->MATSetValue(uiLoopLine, uiLoopColomne, tValue);
		}
	}

	return pMATMatrix;
}


/***
* Soustraction between a CMatrix and an other CMatrix
* Input: CMatrix<Type>& MATParam1, CMatrix<Type>& MATParam2
* Output: CMatrix<Type>*
* Precondition: /
* Postcondition: If the 2 matrix' size are not compatibles or if they
*	don't have the same type, an error is thrown.
*	Else, the ouput matrix contains the result of the soustraction
***/
template<class Type>
CMatrix<Type>* operator-(CMatrix<Type>& MATParam1, CMatrix<Type>& MATParam2) {
	
	//Check size
	if (MATParam1.MATGetColumnNumber() != MATParam2.MATGetColumnNumber() ||
		MATParam1.MATGetLineNumber() != MATParam2.MATGetLineNumber()) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}

	//check type
	if (typeid(MATParam1.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam1.MATGetValue(0, 0)) == typeid(MATParam1)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam1.MATGetColumnNumber();
	uiNbLine = MATParam1.MATGetLineNumber();
	Type tValue = NULL;

	CMatrix<Type>* pMATMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//soustraction
	for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
		for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
			tValue = MATParam1.MATGetValue(uiLoopLine, uiLoopColomne) - (MATParam2.MATGetValue(uiLoopLine, uiLoopColomne));
			pMATMatrix->MATSetValue(uiLoopLine, uiLoopColomne, tValue);
		}
	}

	return pMATMatrix;

}

#endif
