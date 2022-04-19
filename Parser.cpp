
#include "Parser.h"
#include "CException.h"
#include "CList.h"
#include <fstream>
#include <string.h>

#define LINE_LENGTH 255

#define TYPE_DOUBLE 1

using namespace std;


/***
* Convert the parameter pcOrigin to uppercase and store it in pcOutput
* Input: char*:pcOutput, char*:pcOrigin
* Output: char*:pcOutput
* Precondition: pcOutput must be initialized as the same size as pcOrigin
* Postcondition: pcOutput contain pcOrigin converted to uppercase
***/
void toupper(char* pcOutput, const char* pcOrigin) {
    for (int iLoop = 0; pcOrigin[iLoop] != '\0'; iLoop++) {
        pcOutput[iLoop] = toupper(pcOutput[iLoop]);
    }
}



/***
* Open a file and read the content to build a matrix
* Input: char*: pcFilePath, unsigned int &uiNbOfColumnParam, unsigned int &uiNbOfLineParam
* Output: CList<CList<Type>>*, &uiNbOfColumnParam, &uiNbOfLineParam
* Precondition: /
* Postcondition: CList<CList<Type>> contains the list of lists (=matrix), uiNbOfColumnParam the number of column read:
 * the size of the sub-lists, uiNbOfLineParam the number of row: the size of the main list.
***/
template<class Type>
CList<CList<Type>>* Parser<Type>::PARParseData(char* pcFilePath, unsigned int& uiNbOfColumnParam, unsigned int& uiNbOfLineParam)
{

    ifstream fichier(pcFilePath);

    if (!fichier.is_open()) {
        CException EXCError(EXCEPTION_MissingFile);
        throw EXCError;
    }

    //Data who will be use before to be assigned to the matrix's variables
    unsigned int uiNbOfColumn = 0;
    unsigned int uiNbOfLine = 0;
    CList<CList<Type>> LISList;

    //Store which data type has been identified
    unsigned int uiIdentifiedType = 0;

    char cLigne[LINE_LENGTH];

    bool bContinueMain = true;      //the loop for the reading
    bool bMatrixReading = false;    //the sub-loop only when the matrix is read

    unsigned int uiNbLineFound = 0;   //the number of rows that were read when reading the matrix

    //Read the file line to line
    while (bContinueMain) {

        fichier.getline(cLigne, LINE_LENGTH);

        //If we are currently during the matrix's reading part
        if (bMatrixReading) {

            if (cLigne[0] == ']') {   //End of the reading
                bMatrixReading = false;
                continue;
            }

            uiNbLineFound++;
            if (uiNbLineFound > uiNbOfLine) {   //Incoherent with data read before
                throw CException(EXCEPTION_WrongMatrix);
            }

            switch (uiIdentifiedType) {       //We had a row to the matrix
            case TYPE_DOUBLE: {
                LISList.LISAddElement(new CList<double>);

            } break;
                //Other cases for other possible type
            }

            //Nb of column found
            unsigned int uiNbElementFound = 0;

            char* pcFound;
            pcFound = strtok(cLigne, " ");
            while (pcFound != nullptr) {

                uiNbElementFound++;

                if (uiNbElementFound > uiNbOfColumn) {   //Incoherent with data read before
                    throw CException(EXCEPTION_WrongMatrix);
                }

                switch (uiIdentifiedType) {
                case TYPE_DOUBLE: {
                    LISList.LISGetElement(uiNbLineFound - 1).LISAddElement(atof(pcFound));
                }break;
                    //Other cases for other possible type
                }
                pcFound = strtok(nullptr, " ");    //seek the next substring

            }//while(pcFound !=nullptr)

        }//if(bMatrixReading)

        //Identify which data is on this line
        char* pcLineIdentifier;
        pcLineIdentifier = strtok(cLigne, "=");

        //Put the word to upper to avoid case error
        char tcUpperText[strlen(pcLineIdentifier)];
        strcpy(tcUpperText, pcLineIdentifier);
        toupper(tcUpperText, pcLineIdentifier);

        pcLineIdentifier = strtok(nullptr, " ");    //pcLineIdentifier contains now the data to get

        if (strstr(tcUpperText, "TYPEMATRICE")) {               //Identification of the matrix's type

            if (strstr(tcUpperText, "DOUBLE")) {
                LISList = new CList<CList<double>>;
                //If there were more valide types, if(){}else if(){} else [...]
            }
            else {
                throw CException(EXCEPTION_InvalideType);
            }


        }
        else if (strstr(tcUpperText, "NBLIGNES")) {           //Identification of the matrix's line number

            try {
                char* pcEnd;
                uiNbOfLine = strtol(pcLineIdentifier, &pcEnd, 10);
            }
            catch (CException& e) {
                e.EXCsetValue(EXCEPTION_ConversionError);
                throw e;
            }

        }
        else if (strstr(tcUpperText, "NBCOLONNES")) {         //Identification of the matrix's column number

            try {
                char* pcEnd;
                uiNbOfColumn = strtol(pcLineIdentifier, &pcEnd, 10);
            }
            catch (CException& e) {
                e.EXCsetValue(EXCEPTION_ConversionError);
                throw e;
            }

        }
        else if (strstr(tcUpperText, "MATRICE")) {            //Identification of the matrix's content

            if (uiNbOfLine == 0 && uiNbOfColumn == 0) {
                throw CException(EXCEPTION_MissingDataMatrix);
            }

            bMatrixReading = true;

        }
        else if (*cLigne == EOF) {
            //End of file, we end the loop and we check if we have all the needed data
            if (uiNbOfColumn != 0 && uiNbOfLine != 0)
                bContinueMain = false;
            else
                throw CException(EXCEPTION_MissingDataFile);

        }

    }

    fichier.close();

    return &LISList;

}