
#ifndef DEF_PARSER
#define DEF_PARSER

#include "CList.h"

#define EXCEPTION_MissingFile 0
#define EXCEPTION_ConversionError 1
#define EXCEPTION_InvalideType 2
#define EXCEPTION_MissingDataFile 3
#define EXCEPTION_MissingDataMatrix 4
#define EXCEPTION_WrongMatrix 5

template <class Type> class Parser
{
public:
	static CList<CList<Type>>* PARParseData(char* filePath, unsigned int& uiNbOfColumnParam, unsigned int& uiNbOfLineParam);

};


#endif
