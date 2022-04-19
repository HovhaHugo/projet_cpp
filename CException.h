
#ifndef DEF_CEXCEPTION
#define DEF_CEXCEPTION


class CException
{
private:
	unsigned int uiEXCvalue;
	char* pcEXCfunction;

public:
	CException();
	CException(unsigned int uiValueParam);
	CException(unsigned int uiValueParam, char* pcFunctionParam);
	~CException();
	void EXCsetFunction(char* pcFunctionParam);
	void EXCsetValue(unsigned int uiValueParam);
	char* EXCgetFunction();
	unsigned int EXCgetValue();
};


#endif
