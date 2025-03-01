#pragma once
#include "Matrix.h"
class IdentityMatrix : public Matrix{
public:
	IdentityMatrix(int a);
	Matrix& trans();
};
