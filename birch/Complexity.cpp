#include "Complexity.h"

Complexity::Complexity(float a, float i) {
	value = a;
	imag = i;
};

void Complexity::print() {
	if (value != 0) {
		cout << value;
	}
	else {
		if (imag == 0) {
			cout << value;
		}
	}
	if (imag > 0) {
		if (imag == 1) {
			if (value == 0) {
				cout << 'i';
			}
			else {
				cout << '+' << 'i';
			}
		}
		else {
			cout << '+' << imag << 'i';
		}
	}
	else {
		if (imag != 0) {
			if (imag == -1) {
				cout << '-' << 'i';
			}
			else {
				cout << imag << 'i';
			}
		}
	}
}
