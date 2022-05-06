
#ifndef DEF_OVERLOADINGOPERATOR
#define DEF_OVERLOADINGOPERATOR

#include "CMatrix.h"

template<class Type>
CMatrix<Type>* operator*(double dConstantParam, CMatrix<Type>& MATMatrixParam) {
	return MATMatrixParam * dConstantParam;
}

//Operator overload
template<class Type>
CMatrix<Type>* operator*(CMatrix<Type>& MATParam, double dMultiplicator) {
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

template<class Type>
CMatrix<Type>* operator/(CMatrix<Type>& MATParam, double dDivisor) {
	//Exception management
	if (dDivisor == 0) {
		CException EXCError(EXCEPTION_DivisionByZero);
		throw EXCError;
	}

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

template<class Type>
CMatrix<Type>* operator*(CMatrix<Type>& MATParam1, CMatrix<Type>& MATParam2) {
	if (MATParam1.MATGetColumnNumbre() != MATParam2.MATGetLineNumbre()) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}

	if (typeid(MATParam1.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam1.MATGetValue(0, 0)) == typeid(MATParam1)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam1.MATGetColumnNumbre();
	uiNbLine = MATParam1.MATGetLineNumbre();
	Type tValue = NULL;

	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Transposition
	for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
			tValue = MATParam1.MATGetValue(uiLoopColomne, uiLoopLine) *(MATParam2.MATGetValue(uiLoopColomne, uiLoopLine));
			MATTMatrix->MATSetValue(uiLoopColomne, uiLoopLine, tValue);
		}
	}

	return MATTMatrix;
}

template<class Type>
CMatrix<Type>* operator+(CMatrix<Type>& MATParam1, CMatrix<Type>& MATParam2) {
	if (MATParam1.MATGetColumnNumbre() != MATParam2.MATGetColumnNumbre() && 
		MATParam1.MATGetLineNumbre() != MATParam2.MATGetLineNumbre()) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}

	if (typeid(MATParam1.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam1.MATGetValue(0, 0)) == typeid(MATParam1)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam1.MATGetColumnNumbre();
	uiNbLine = MATParam1.MATGetLineNumbre();
	Type tValue = NULL;

	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Transposition
	for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
			tValue = MATParam1.MATGetValue(uiLoopColomne, uiLoopLine) +MATParam2.MATGetValue(uiLoopColomne, uiLoopLine);
			MATTMatrix->MATSetValue(uiLoopColomne, uiLoopLine, tValue);

		}
	}

	return MATTMatrix;
}

template<class Type>
CMatrix<Type>* operator-(CMatrix<Type>& MATParam1, CMatrix<Type>& MATParam2) {
	if (MATParam1.MATGetColumnNumbre() != MATParam2.MATGetColumnNumbre() && 
		MATParam1.MATGetLineNumbre() != MATParam2.MATGetLineNumbre()) {
		CException EXCError(EXCEPTION_InvalidCondition);
		throw EXCError;
	}

	if (typeid(MATParam1.MATGetValue(0, 0)) == typeid(char) || typeid(MATParam1.MATGetValue(0, 0)) == typeid(MATParam1)) {
		CException EXCError(EXCEPTION_InvalidType);
		throw EXCError;
	}

	unsigned int uiNbLine, uiNbColomne;
	uiNbColomne = MATParam1.MATGetColumnNumbre();
	uiNbLine = MATParam1.MATGetLineNumbre();
	Type tValue = NULL;

	CMatrix<Type>* MATTMatrix = new CMatrix<Type>(uiNbColomne, uiNbLine);

	//Transposition
	for (unsigned int uiLoopColomne = 0; uiLoopColomne < uiNbColomne; uiLoopColomne++) {
		for (unsigned int uiLoopLine = 0; uiLoopLine < uiNbLine; uiLoopLine++) {
			tValue = MATParam1.MATGetValue(uiLoopColomne, uiLoopLine) - MATParam2.MATGetValue(uiLoopColomne, uiLoopLine);
			MATTMatrix->MATSetValue(uiLoopColomne, uiLoopLine, tValue);
		}
	}

	return MATTMatrix;

}

#endif
