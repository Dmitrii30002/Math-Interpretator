#pragma once
#include "Matrix.h"

class Vector : public Matrix {
private:
	Number* value;
public:
	Vector(int rows, queue<Number>& que);
};