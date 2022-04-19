
#include "CException.h"
#include <stdio.h>
#include<string.h>


CException::CException() {
	uiEXCvalue = 0;

	const char* s = "Undefined function";

	sprintf_s(pcEXCfunction, 19, s);

}

CException::CException(unsigned int uiValueParam, char* pcFunctionParam) {
	uiEXCvalue = uiValueParam;
	pcEXCfunction = pcFunctionParam;
}

CException::~CException() {}

void CException::EXCsetFunction(char* pcFunctionParam) {

	size_t ulLength = strlen(pcFunctionParam);
	if (pcEXCfunction != nullptr)
		delete pcEXCfunction;

	sprintf_s(pcEXCfunction, ulLength, pcFunctionParam);

}

void CException::EXCsetValue(unsigned int uiValueParam) {
	uiEXCvalue = uiValueParam;
}

char* CException::EXCgetFunction() {
	return pcEXCfunction;
}

unsigned int CException::EXCgetValue() {
	return uiEXCvalue;
}
