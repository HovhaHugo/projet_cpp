
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
	uiNbColomne = MATParam.MATGetColumnNumbre();
	uiNbLine = MATParam.MATGetLineNumbre();
	Type tValue = NULL;

	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Multiplication
	for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
			tValue = MATParam.MATGetValue(uiLoopColomne, uiLoopLine) * dMultiplicator;
			MATTMatrix->MATSetValue(uiLoopColomne, uiLoopLine, tValue);
		}
	}

	return MATTMatrix;
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
	uiNbColomne = MATParam.MATGetColumnNumbre();
	uiNbLine = MATParam.MATGetLineNumbre();
	Type tValue = NULL;

	//We create a new object and send it at the end of the function
	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Division
	for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
			tValue = MATParam.MATGetValue(uiLoopColomne, uiLoopLine) / dDivisor;
			MATTMatrix->MATSetValue(uiLoopColomne, uiLoopLine, tValue);
		}
	}

	return MATTMatrix;
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

	//Check size
	if (MATParam1.MATGetColumnNumbre() != MATParam2.MATGetLineNumbre()) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}

	//Check type
	if (typeid(MATParam1.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam1.MATGetValue(0, 0)) == typeid(MATParam1)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam1.MATGetColumnNumbre();
	uiNbLine = MATParam1.MATGetLineNumbre();
	Type tValue = NULL;

	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Multiplication
	for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
			tValue = MATParam1.MATGetValue(uiLoopColomne, uiLoopLine) *(MATParam2.MATGetValue(uiLoopColomne, uiLoopLine));
			MATTMatrix->MATSetValue(uiLoopColomne, uiLoopLine, tValue);
		}
	}

	return MATTMatrix;
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
	if (MATParam1.MATGetColumnNumbre() != MATParam2.MATGetColumnNumbre() && 
		MATParam1.MATGetLineNumbre() != MATParam2.MATGetLineNumbre()) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}

	//Check type
	if (typeid(MATParam1.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam1.MATGetValue(0, 0)) == typeid(MATParam1)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam1.MATGetColumnNumbre();
	uiNbLine = MATParam1.MATGetLineNumbre();
	Type tValue = NULL;

	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Operation
	for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
			tValue = MATParam1.MATGetValue(uiLoopColomne, uiLoopLine) +MATParam2.MATGetValue(uiLoopColomne, uiLoopLine);
			MATTMatrix->MATSetValue(uiLoopColomne, uiLoopLine, tValue);

		}
	}

	return MATTMatrix;
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
	if (MATParam1.MATGetColumnNumbre() != MATParam2.MATGetColumnNumbre() && 
		MATParam1.MATGetLineNumbre() != MATParam2.MATGetLineNumbre()) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}

	//Check type
	if (typeid(MATParam1.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam1.MATGetValue(0, 0)) == typeid(MATParam1)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam1.MATGetColumnNumbre();
	uiNbLine = MATParam1.MATGetLineNumbre();
	Type tValue = NULL;

	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Soustraction
	for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
			tValue = MATParam1.MATGetValue(uiLoopColomne, uiLoopLine) - MATParam2.MATGetValue(uiLoopColomne, uiLoopLine);
			MATTMatrix->MATSetValue(uiLoopColomne, uiLoopLine, tValue);
		}
	}

	return MATTMatrix;

}

#endif
