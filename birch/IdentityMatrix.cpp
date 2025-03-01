#include "IdentityMatrix.h"

IdentityMatrix::IdentityMatrix(int a) {
	rows = a;
	colums = a;
	values = new Number * [rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new Number[colums];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colums; j++) {
			if (i == j) {
				values[i][j] = 1;
			}
			else {
				values[i][j] = 0;
			}
		}
	}
}

Matrix& IdentityMatrix::trans() {
	return *new Matrix(*this);
}