
#include "Parser.h"
#include "CException.h"
#include <fstream>
#include <string.h>

#define LINE_LENGTH 255

/***
* Convert the parameter pcOrigin to uppercase and store it in pcOutput
* Input: char*:pcOutput, char*:pcOrigin
* Output: char*:pcOutput
* Precondition: pcOutput must be initialized as the same size as pcOrigin
* Postcondition: pcOutput contains pcOrigin converted to uppercase
***/
void toupper(char* pcOutput, const char* pcOrigin) {
    for (int iLoop = 0; pcOrigin[iLoop] != '\0'; iLoop++) {
        pcOutput[iLoop] = toupper(pcOrigin[iLoop]);
    }
}


/***
* Clear the content of a chain of character. Replace all the element by \0
* Input: char*:pcInput, unsigned int: uiSize
* Output: char*:pcInput
* Precondition: uiSize must be the size of pcOutput
* Postcondition: pcOutput is fill with \0
***/
void clear(char* pcOutput, unsigned int uiSize) {
    for (unsigned int uiLoop = 0; uiLoop < uiSize ; uiLoop++) {
        pcOutput[uiLoop] = '\0';
    }
}


/***
* Delete all the matrix memory
* Input: double** ppdMatrix, unsigned int uiNbOfLine
* Output: /
* Precondition: ppdMatrix has been allocated explicitly in memory
* Postcondition: ppdMatrix has been deleted from memory
***/
void matrixDelete(double** ppdMatrix,unsigned int uiNbOfLine) {
    for (unsigned int uiLoop = 0; uiLoop < uiNbOfLine; ++uiLoop)
        delete[] ppdMatrix[uiLoop];
    delete[] ppdMatrix;
}


/***
* Open a file and read the content to build a matrix
* Input: const char*: pcFilePath, unsigned int *uiNbOfColumnParam, unsigned int *uiNbOfLineParam
* Output: CList<CList<Type>>*, &uiNbOfColumnParam, &uiNbOfLineParam
* Precondition: /
* Postcondition: CList<CList<Type>> contains the list of lists (=matrix), uiNbOfColumnParam the number of column read:
* the size of the sub-lists, uiNbOfLineParam the number of row: the size of the main list.
***/
double** ParseDataDouble(const char* pcFilePath, unsigned int* uiNbOfColumnParam, unsigned int* uiNbOfLineParam)
{

    std::ifstream fichier(pcFilePath);

    if (!fichier.is_open()) {
        CException EXCError(EXCEPTION_MissingFile);
        throw EXCError;
    }

    //Data who will be use before to be assigned to the matrix's variables
    unsigned int uiNbOfColumn = 0;
    unsigned int uiNbOfLine = 0;

    double** ppdList = nullptr;

    char cLigne[LINE_LENGTH];

    bool bContinueMain = true;      //the loop for the reading
    bool bMatrixReading = false;    //the sub-loop only when the matrix is read

    unsigned int uiNbLineFound = 0;   //the number of rows that were read when reading the matrix

    //Read the file line to line
    while (bContinueMain) {

        if (fichier.eof()) {

            if (bMatrixReading) {
                matrixDelete(ppdList, uiNbLineFound);
                throw CException(EXCEPTION_ErrorDataFile);
            }     

            bContinueMain = false;
            continue;
        }

        fichier.getline(cLigne, LINE_LENGTH);

        if (cLigne[0] == '\0') {
            continue;
        }

        //If we are currently during the matrix's reading part
        if (bMatrixReading) {

            if (cLigne[0] == ']') {   //End of the reading

                if (uiNbOfLine != uiNbLineFound) {
                    matrixDelete(ppdList, uiNbLineFound);
                    throw CException(EXCEPTION_WrongMatrix);
                }

                *uiNbOfColumnParam = uiNbOfColumn;
                *uiNbOfLineParam = uiNbOfLine;

                bMatrixReading = false;
                continue;
            }

            uiNbLineFound++;
            if (uiNbLineFound > uiNbOfLine) {   //Incoherent with data read before
                matrixDelete(ppdList, uiNbLineFound);
                throw CException(EXCEPTION_WrongMatrix);
            }

            //Nb of column found
            unsigned int uiNbElementFound = 0;

            char* pcFound;
            pcFound = strtok(cLigne, " ");
            while (pcFound != nullptr) {

                uiNbElementFound++;

                if (uiNbElementFound > uiNbOfColumn) {   //Incoherent with data read before
                    matrixDelete(ppdList, uiNbLineFound);
                    throw CException(EXCEPTION_WrongMatrix);
                }

                char* pcEndPtr;
                double dFoundConverted = strtod(pcFound, &pcEndPtr);

                if (pcEndPtr == pcFound) {
                    matrixDelete(ppdList, uiNbLineFound);
                    throw CException(EXCEPTION_ConversionError);
                }

                //-1 because arrays start at 0
                ppdList[uiNbLineFound-1][uiNbElementFound-1] = dFoundConverted;
                
                pcFound = strtok(nullptr, " ");    //seek the next substring

            }//while(pcFound !=nullptr)

            if (uiNbElementFound < uiNbOfColumn) {
                matrixDelete(ppdList, uiNbLineFound);
                throw CException(EXCEPTION_WrongMatrix);
            }

            //Jump to the next iteration of while (bContinueMain)
            continue;

        }//if(bMatrixReading)

        //Identify which data is on this line
        char* pcLineIdentifier;
        pcLineIdentifier = strtok(cLigne, "=");

        //Put the word to upper to avoid case error
        char* tcUpperText = (char*)malloc(sizeof(char)*LINE_LENGTH);
        if (tcUpperText == nullptr) {
            throw CException(EXCEPTION_MallocError);
        }

        //strcpy(tcUpperText, pcLineIdentifier);
        toupper(tcUpperText, pcLineIdentifier);

        pcLineIdentifier = strtok(nullptr, " ");    //pcLineIdentifier contains now the data to get
        if (pcLineIdentifier == nullptr) {
            free(tcUpperText);
            throw CException(EXCEPTION_ErrorDataFile);
        }

        if (strstr(tcUpperText, "TYPEMATRICE")) {               //Identification of the matrix's type

            clear(tcUpperText,LINE_LENGTH);
            toupper(tcUpperText, pcLineIdentifier);

            if (strstr(tcUpperText, "DOUBLE")==0) {
                free(tcUpperText);
                throw CException(EXCEPTION_InvalideType);
            }

        }
        else if (strstr(tcUpperText, "NBLIGNES")) {           //Identification of the matrix's number of line 

            char* pcEndPtr;
            uiNbOfLine = strtod(pcLineIdentifier, &pcEndPtr);

            if (pcEndPtr == pcLineIdentifier) {
                throw CException(EXCEPTION_ConversionError);
            }

        }
        else if (strstr(tcUpperText, "NBCOLONNES")) {         //Identification of the matrix's number of column 

            char* pcEndPtr;
            uiNbOfColumn = strtod(pcLineIdentifier, &pcEndPtr);

            if (pcEndPtr == pcLineIdentifier) {
                throw CException(EXCEPTION_ConversionError);
            }

        }
        else if (strstr(tcUpperText, "MATRICE")) {            //Identification of the matrix's content

            if (uiNbOfLine == 0 || uiNbOfColumn == 0) {
                free(tcUpperText);
                throw CException(EXCEPTION_ErrorDataFile);
            }

            ppdList = new double* [uiNbOfLine];
            for (unsigned int uiLoop = 0; uiLoop < uiNbOfLine; uiLoop++)
                ppdList[uiLoop] = new double[uiNbOfColumn];

            bMatrixReading = true;

        }

        free(tcUpperText);

    }//while(bContinueMain)

    fichier.close();

    return ppdList;

}