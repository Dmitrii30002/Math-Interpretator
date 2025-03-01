#pragma once
#include "Number.h"

class Complexity : public Number{
protected:
	float imag;
public:
	Complexity(float a, float i);
	Complexity& operator*(const Number& numb) {
		return *new Complexity(numb.getValue() * value, imag* numb.getValue());
	}
	Complexity& operator/(const Number& numb) {
		return *new Complexity(value/numb.getValue(), imag / numb.getValue());
	}
	Complexity& operator+(const Number& numb) {
		return *new Complexity(numb.getValue() + value, imag);
	}
	Complexity& operator-(const Number& numb) {
		return *new Complexity(value-numb.getValue(), imag);
	}

	Complexity& operator*(const Complexity& numb) {
		float v = value * numb.value - imag * numb.imag;
		float i = value * numb.imag + imag * numb.value;
		return *new Complexity(v,i);
	}
	Complexity& operator/(const Complexity& numb) {
		float v = (value*numb.value + imag*numb.imag)/(numb.value*numb.value + numb.imag*numb.imag);
		float i = (imag * numb.value - value * numb.imag) / (numb.value * numb.value + numb.imag * numb.imag);
		return *new Complexity(v, i);
	}
	Complexity& operator+(const Complexity& numb) {
		return *new Complexity(value+numb.value, imag+numb.imag);
	}
	Complexity& operator-(const Complexity& numb) {
		return *new Complexity(value - numb.value, imag - numb.imag);
	}

	void print();

	float getImag() { return imag; }
};
