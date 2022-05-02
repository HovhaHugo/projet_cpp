
#ifndef DEF_CMATRIX
#define DEF_CMATRIX

#include "Parser.h"
#include "CException.h"
#include <stdio.h>


template<class Type>
class CMatrix
{
private:
	

public:

	unsigned int uiMATColumnNumber;
	unsigned int uiMATLineNumber;
	Type** pptypeMatrixContent;
	//Constructors
	CMatrix();
	CMatrix(Type** ptTypeMatrix,unsigned int uiNbColomn, unsigned int uiNbLine);
	CMatrix(const char* pcFilePath);
	CMatrix(CMatrix MATParam);

	//Overloaded Operators
	operator*(Type tMultiplication);
	operator*(CMatrix MATParam);
	operator+(CMatrix MATParam);
	operator-(CMatrix MATParam);

	//Method
	CMatrix MATTransposer();
	void MATshow();
	unsigned int MATGetColumnNumbre();
	unsigned int MATGetLineNumbre();
	Type MATGetValue(unsigned int uiColomn, unsigned int uiLine);

	CMatrix(const char* pcFilePath) {

		try {
			pptypeMatrixContent = ParseDataDouble(pcFilePath, &uiMATColumnNumber, &uiMATLineNumber);
		}
		catch (CException& EXCException) {
			printf("An error occured\nError code: %d\nFunction: %s\n",EXCException.EXCgetValue(),EXCException.EXCgetFunction());
		}

	}

	CMatrix() {
		uiMATColumnNumber = 0;
		uiMATLineNumber = 0;
		lisMATContent = NULL;
	}

	CMatrix(Type** ptTypeMatrix, unsigned int uiNbColomn, unsigned int uiNbLine) {
		uiMATColumnNumber = uiNbColomn;
		uiMATLineNumber = uiNbLine;
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				lisMATContent[iLoopColomne][iLoopLine] = ptTypeMatrix[iLoopColomne][iLoopLine];
			}
		}
	}

	CMatrix(const char* pcChemin) {
		uiMATColumnNumber = 0;
		uiMATLineNumber = 0;
		lisMATContent = Parser.PARParseData(pcChemin, &uiMATColomneNumber, &uiMATLineNumber);
	}

	CMatrix(CMatrix MATParam) {
		uiMATColumnNumber = MATParam.uiMATColumnNumber;
		uiMATLineNumber = MATParam.uiMATLineNumber;
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				lisMATContent[iLoopColomne][iLoopLine] = MATParam.MATGetValue(iLoopColomne, iLoopLine);
			}
		}
	}

	CMatrix MATTransposer() {

	}

	void MATshow() {
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			cout << "(";
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				cout<<lisMATContent[iLoopColomne][iLoopLine] ;
			}
			cout << ")\n";
		}
	}
	
	unsigned int MATGetColumnNumbre() {
		return uiMATColumnNumber;
	}

	unsigned int MATGetLineNumbre() {
		return uiMATLineNumber;
	}

	Type MATGetValue(unsigned int uiColomn, unsigned int uiLine) {
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				if (iLoopLine == uiLine && iLoopColomne == uiColomn) {
					return lisMATContent[iLoopColomne][iLoopLine];
				}
			}
		}
	}

};


#endif