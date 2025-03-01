#pragma once
#include "MatVar.h"
#include "Number.h"
#include <queue>

class Matrix : public MatVar{
protected:
	int rows;
	int colums;
	Number** values;
public:
	Matrix(int r, int c, queue<Number>& vals);
	Matrix(int r, int c, Number** vals);
	Matrix(const Matrix& mat);
	Matrix() {};
	virtual ~Matrix();
	void print();
	Number getValue(int i, int j);
	friend ostream& operator<<(ostream& os, Matrix& mat) {
		mat.print();
		return os;
	}
	Matrix& operator=(const Matrix& mat) {
		for (int i = 0; i < rows; i++) {
			delete values[i];
		}
		delete[] values;
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
		return *this;
	}
	Matrix& operator*(const Matrix& mat) {
		int r = rows;
		int c = mat.colums;
		Number** help = new Number*[r];
		for (int i = 0; i < r; i++) {
			help[i] = new Number[c];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < mat.colums; j++) {
				help[i][j] = 0;
				for (int k = 0; k < colums; k++) {
					help[i][j] += values[i][k] * mat.values[k][j];
				}
			}
		}
		return *(new Matrix(r, c, help));
	}
	Matrix& operator+(const Matrix& mat) {
		Number** help = new Number * [rows];
		for (int i = 0; i < rows; i++) {
			help[i] = new Number[colums];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colums; j++) {
				help[i][j] = values[i][j] + mat.values[i][j];
			}
		}
		return *(new Matrix(rows, colums, help));
	}
	Matrix& operator-(const Matrix& mat) {
		Number** help = new Number * [rows];
		for (int i = 0; i < rows; i++) {
			help[i] = new Number[colums];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colums; j++) {
				help[i][j] = values[i][j] - mat.values[i][j];
			}
		}
		return *(new Matrix(rows, colums, help));
	}

	Matrix& operator*(const Number& numb) {
		Number** help = new Number * [rows];
		for (int i = 0; i < rows; i++) {
			help[i] = new Number[colums];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colums; j++) {
				help[i][j] = values[i][j] * numb;
			}
		}
		return *(new Matrix(rows, colums, help));
	}
	Matrix& operator/(const Number& numb) {
		Number** help = new Number * [rows];
		for (int i = 0; i < rows; i++) {
			help[i] = new Number[colums];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colums; j++) {
				help[i][j] = values[i][j] / numb;
			}
		}
		return *(new Matrix(rows, colums, help));
	}

	bool operator==(const Matrix& mat) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colums; j++) {
				if (values[i][j].getValue() != mat.values[i][j].getValue()) {
					return false;
				}
			}
		}
		return true;
	}

	int getRows() { return rows; }
	int getColums() { return colums; };

	virtual Matrix& trans();
};
