#include "Vector.h"

Vector::Vector(int r, queue<Number>& que) {
	rows = r;
	colums = 1;
	values = new Number * [rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new Number[colums];
	}
	for (int i = 0; i < colums; i++) {
		for (int j = 0; j < rows; j++) {
			values[j][i] = que.front();
			que.pop();
		}
	}
}