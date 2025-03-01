#include "Matrix.h"

Matrix::Matrix(int r, int c, queue<Number>& vals) {
	rows = r;
	colums = c;
	values = new Number*[rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new Number[colums];
	}
	for (int i = 0; i < colums; i++) {
		for (int j = 0; j < rows; j++) {
			values[j][i] = vals.front();
			vals.pop();
		}
	}
}

Matrix::Matrix(int r, int c, Number** vals) {
	rows = r;
	colums = c;
	values = new Number * [rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new Number[colums];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colums; j++) {
			values[i][j] = vals[i][j];
		}
	}
}

Matrix::Matrix(const Matrix& mat) {
	rows = mat.rows;
	colums = mat.colums;
	values = new Number*[rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new Number[colums];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colums; j++) {
			values[i][j] = mat.values[i][j];
		}
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < rows; i++) {
		delete values[i];
	}
	delete[] values;
}


void Matrix::print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colums; j++) {
			cout << values[i][j] << ' ';
		}
		cout << '\n';
	}
}

Number Matrix::getValue(int i, int j) {
	return values[i][j];
}


Matrix& Matrix::trans() {
	Number** help = new Number * [colums];
	for (int i = 0; i < colums; i++) {
		help[i] = new Number[rows];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colums; j++) {
			help[j][i] = values[i][j];
		}
	}
	return *new Matrix(colums, rows, help);
}