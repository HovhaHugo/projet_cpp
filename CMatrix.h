
#ifndef DEF_CMATRIX
#define DEF_CMATRIX

#include "Parser.h"
#include "CException.h"
#include <stdio.h>


template<class Type>
class CMatrix
{
private:
	unsigned int uiMATColumnNumber;
	unsigned int uiMATLineNumber;
	Type** pptypeMatrixContent;
public:
	//Constructors
	CMatrix();
	CMatrix(Type** ptTypeMatrix,unsigned int uiNbColomn, unsigned int uiNbLine);
	CMatrix(const char* pcFilePath);
	CMatrix(CMatrix MATParam);

	//Overloaded Operators
	CMatrix operator*(double dMultiplicator);
	CMatrix operator/(double dDivisor);
	CMatrix operator*(CMatrix MATParam);
	CMatrix operator+(CMatrix MATParam);
	CMatrix operator-(CMatrix MATParam);
	CMatrix operator=(CMatrix MATParam); //Just the same as the copy constructor

	//Method
	void MATTransposer();
	void MATshow();
	unsigned int MATGetColumnNumbre();
	unsigned int MATGetLineNumbre();
	Type MATGetValue(unsigned int uiColomn, unsigned int uiLine);


	//Constructors
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
		pptypeMatrixContent = NULL;
	}

	CMatrix(Type** ptTypeMatrix, unsigned int uiNbColomn, unsigned int uiNbLine) {
		uiMATColumnNumber = uiNbColomn;
		uiMATLineNumber = uiNbLine;
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				pptypeMatrixContent[iLoopColomne][iLoopLine] = ptTypeMatrix[iLoopColomne][iLoopLine];
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
				pptypeMatrixContent[iLoopColomne][iLoopLine] = MATParam.MATGetValue(iLoopColomne, iLoopLine);
			}
		}
	}

	CMatrix operator*(double dMultiplicator){

		CMatrix<Type> MATTMatrix = new CMatrix<Type>(null,uiMATColumnNumber, uiMATLineNumber);

		//Multiplication
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				MATTMatrix.pptypeMatrixContent[iLoopColomne][iLoopLine] = MATTMatrix.MATGetValue(iLoopColomne,iLoopLine)*dMultiplicator;
			}
		}
		
		return MATTMatrix;
	}

	CMatrix operator/(double dDivisor){
		//Create a new objet and send it at the end
		if(dDivisor == 0){
			CException EXCError(EXCEPTION_MissingFile);
        	throw EXCError;
		}
		CMatrix<Type> MATTMatrix = new CMatrix<Type>(null,uiMATColumnNumber, uiMATLineNumber);

		//Division
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				MATTMatrix.pptypeMatrixContent[iLoopColomne][iLoopLine] = MATGetValue(iLoopColomne,iLoopLine)/dMultiplicator;
			}
		}
		
		return MATTMatrix;
	}


	CMatrix operator*(CMatrix MATParam){
		//We don't allow the multiplication between 2 char/object matrix
		//typeid(T) == typeid(double)
		if(uiMATColumnNumber != MATParam.MATGetLineNumbre()){
			CException EXCError(EXCEPTION_MissingFile);
        	throw EXCError;
		}
		CMatrix<Type> MATTMatrix = new CMatrix<Type>(null,uiMATColumnNumber, uiMATLineNumber);

		//Transposition
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				MATTMatrix.pptypeMatrixContent[iLoopColomne][iLoopLine] = MATGetValue(iLoopColomne,iLoopLine)*MATParamMATGetValue(iLoopColomne,iLoopLine);
			}
		}
		
		return MATTMatrix;
	}

	CMatrix operator+(CMatrix MATParam){
		if(uiMATColumnNumber != MATParam.MATGetColumnNumbre() && uiMATLineNumber != MATParam.MATGetLineNumbre()){
			CException EXCError(EXCEPTION_MissingFile);
        	throw EXCError;
		}
		CMatrix<Type> MATTMatrix = new CMatrix<Type>(null,uiMATColumnNumber, uiMATLineNumber);

		//Transposition
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				MATTMatrix.pptypeMatrixContent[iLoopColomne][iLoopLine] = MATGetValue(iLoopColomne,iLoopLine)+MATParamMATGetValue(iLoopColomne,iLoopLine);
			}
		}
		
		return MATTMatrix;
	}

	CMatrix operator-(CMatrix MATParam){
		if(uiMATColumnNumber != MATParam.MATGetColumnNumbre() && uiMATLineNumber != MATParam.MATGetLineNumbre()){
			CException EXCError(EXCEPTION_MissingFile);
        	throw EXCError;
		}
		CMatrix<Type> MATTMatrix = new CMatrix<Type>(null,uiMATColumnNumber, uiMATLineNumber);

		//Transposition
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				MATTMatrix.pptypeMatrixContent[iLoopColomne][iLoopLine] = MATGetValue(iLoopColomne,iLoopLine)-MATParamMATGetValue(iLoopColomne,iLoopLine);
			}
		}
		
		return MATTMatrix;

	}

	
	CMatrix operator=(CMatrix MATParam){

		uiColumnNumber = MATParam.uiMATColumnNumber;
		uiLineNumber = MATParam.uiMATLineNumber;

		CMatrix<Type> MATTMatrix = new CMatrix<Type>(null,uiColumnNumber, uiLineNumber);

		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				MATTMatrix.pptypeMatrixContent[iLoopColomne][iLoopLine] = MATParam.MATGetValue(iLoopColomne, iLoopLine);
			}
		}

		return MATTMatrix;
	}

	//Method
	/**
	 * @brief Transpose la matrice actuelle 
	 * 
	 * @return CMatrix La matrice transposer
	 */
	void MATTransposer() {
		//We create a new matrix to do the transposition
		CMatrix<Type> MATTMatrix = new CMatrix<Type>(null,uiMATLineNumber, uiMATColumnNumber);

		//Transposition
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				MATTMatrix.pptypeMatrixContent[iLoopColomne][iLoopLine] = pptypeMatrixContent[iLoopLine][iLoopColomne];
			}
		}
		
		uiMATColumnNumber = MATTMatrix.MATGetColumnNumbre();
		uiMATLineNumber = MATTMatrix.MATGetLineNumbre();
		pptypeMatrixContent = MATTMatrix.pptypeMatrixContent;
		
		//Not sure, might be not use that freeed this variable. 
		free(MATTMatrix);
	}

	/**
	 * @brief Permet l'affichage de la matrice.
	 * 
	 */
	void MATshow() {
		for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
			cout << "(";
			for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
				cout<<pptypeMatrixContent[iLoopColomne][iLoopLine] ;
			}
			cout << ")\n";
		}
	}
	
	/**
	 * @brief Permet la récupération du nombre de colonnes
	 * 
	 * @return unsigned int Le nombre de colonnes
	 */
	unsigned int MATGetColumnNumbre() {
		return uiMATColumnNumber;
	}

	/**
	 * @brief Permet la récupération du nombre de lignes 
	 * 
	 * @return unsigned int Le nombre de lignes
	 */
	unsigned int MATGetLineNumbre() {
		return uiMATLineNumber;
	}

	/**
	 * @brief Permet de récupérer la valeur dans la matrice à la uiColomn-iéme colonne
	 * et uiLine-iéme ligne.
	 * @param uiColomn 	La colonne
	 * @param uiLine 	La ligne
	 * @return Type 	La valeur dans la matrice.
	 */
	Type MATGetValue(unsigned int uiColomn, unsigned int uiLine) {
		//If the value are superior avec our number of colomne/line, we return an exception
		if(uiColomn > uiMATColumnNumber || uiLine > uiMATLineNumber){
			return null;
		}
		//Else, we return the value.
		else{
			for (int iLoopColomne = 0; iLoopColomne <= uiMATColumnNumber; iLoopColomne++) {
				for (int iLoopLine = 0; iLoopLine <= uiMATLineNumber; iLoopLine++) {
					if (iLoopLine == uiLine && iLoopColomne == uiColomn) {
						return pptypeMatrixContent[iLoopColomne][iLoopLine];
					}
				}
			}
		}
	}

};


#endif