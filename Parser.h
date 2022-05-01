
#ifndef DEF_PARSER
#define DEF_PARSER

#pragma warning(disable: 4996)

#define EXCEPTION_MissingFile 1			//The file was not found
#define EXCEPTION_ConversionError 2		//Conversion error, a letter was read instead of a number
#define EXCEPTION_InvalideType 3		//The readed type is not compatible with the current parser used
#define EXCEPTION_ErrorDataFile 4		//Error from data in the file (missing main data like number of line/column, matrix content, ] symbol)
#define EXCEPTION_WrongMatrix 5			//The matrix read don't match with the data read before
#define EXCEPTION_MallocError 6			//Memory allocation error

double** ParseDataDouble(const char* filePath, unsigned int* uiNbOfColumnParam, unsigned int* uiNbOfLineParam);



#endif
