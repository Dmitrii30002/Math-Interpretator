#pragma once
#include "MatVar.h"

class Number : public MatVar{
protected:
	float value;
public:
	Number(float val);
	Number() {};
	void print();
	friend ostream& operator<<(ostream& os, Number& numb) {
		numb.print();
		return os;
	}
	Number& operator*(const Number& numb) {
		return *new Number(numb.value * value);
	}
	Number& operator+(const Number& numb) {
		return *new Number(numb.value + value);
	}
	Number& operator/(const Number& numb) {
		return *new Number(value / numb.value);
	}
	Number& operator-(const Number& numb) {
		return *new Number(value - numb.value);
	}
	void operator+=(const Number& numb) {
		value = value + numb.value;
	}
	void operator-=(const Number& numb) {
		value = value - numb.value;
	}

	float getValue() const {
		return value;
	}

};
