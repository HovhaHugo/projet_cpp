
#include "OverloadedOperator.h"
#include "CMatrix.h"

template<typename Type>
CMatrix<Type>* operator*(double dConstantParam, CMatrix<Type>& MATMatrixParam);
