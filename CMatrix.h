
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
	CMatrix(const char* pcFilePath);

};

template<class Type>
CMatrix<Type>::CMatrix(const char* pcFilePath) {

	try {
		pptypeMatrixContent = ParseDataDouble(pcFilePath, &uiMATColumnNumber, &uiMATLineNumber);
	}
	catch (CException& EXCException) {
		printf("An error occured\nError code: %d\nFunction: %s\n",EXCException.EXCgetValue(),EXCException.EXCgetFunction());
	}

}


#endif
