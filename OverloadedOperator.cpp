
#include "OverloadedOperator.h"
#include "CMatrix.h"

template<typename Type>
CMatrix<Type>* operator*(double dConstantParam, const CMatrix<Type>& MATMatrixParam) {
	return MATMatrixParam * dConstantParam;
}
