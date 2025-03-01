#pragma once
#include <iostream>
using namespace std;

class MatVar {
public:
	MatVar() {};
	virtual void print() = 0;
	friend ostream& operator<<(ostream& os, MatVar& var) {
		var.print();
		return os;
	}
};
