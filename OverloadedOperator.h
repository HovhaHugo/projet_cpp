
#ifndef DEF_OVERLOADINGOPERATOR
#define DEF_OVERLOADINGOPERATOR

#include "CMatrix.h"

template<typename Type>
CMatrix<Type>* operator*(double dConstantParam, const CMatrix<Type>& MATMatrixParam);

#endif
