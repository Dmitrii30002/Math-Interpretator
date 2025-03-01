#pragma once
#include "Number.h"

class Fraction : public Number {
protected:
	int numerator;
	int denominator;
public:
	Fraction(float a, float b);

	Fraction& operator*(const Fraction& numb) {
		float a = numerator * numb.numerator;
		float b = denominator * numb.denominator;
		if (fmod(a, b) == 0.0) {
			a = a / b;
			b = 1;
		}
		return *new Fraction(a, b);
	}
	Fraction& operator/(const Fraction& numb) {
		float a = numerator * numb.denominator;
		float b = denominator * numb.numerator;
		if (fmod(a, b) == 0.0) {
			a = a / b;
			b = 1;
		}
		return *new Fraction(a, b);
	}
	Fraction& operator+(const Fraction& numb) {
		float a = denominator;
		float b = numb.denominator;
		while (a - (int)a != 0 && b - (int)b != 0) {
			a *= 10;
			b *= 10;
		}
		int min = 0;
		if (a < b) {
			min = b;
		}
		else {
			min = a;
		}
		while (true) {
			if (min % (int)a == 0 && min % (int)b == 0) {
				break;
			}
			else {
				min++;
			}
		}
		float m =min / (a / denominator);
		float n = (numerator * (m / denominator) + numb.numerator * (m / numb.denominator));
		float d = m;
		return *new Fraction(n, d);
	}
	Fraction& operator-(const Fraction& numb) {
		float a = denominator;
		float b = numb.denominator;
		while (a - (int)a != 0 && b - (int)b != 0) {
			a *= 10;
			b *= 10;
		}
		int min = 0;
		if (a < b) {
			min = b;
		}
		else {
			min = a;
		}
		while (true) {
			if (min % (int)a == 0 && min % (int)b == 0) {
				break;
			}
			else {
				min++;
			}
		}
		float m = min / (a / denominator);
		float n = (numerator * (m / denominator) - numb.numerator * (m / numb.denominator));
		float d = m;
		return *new Fraction(n, d);
	}

	Fraction& operator*(const Number& numb) {
		float a = numerator * numb.getValue();
		float b = denominator;
		if (fmod(a, b) == 0.0) {
			a = a / b;
			b = 1;
		}
		return *new Fraction(a, b);
	}
	Fraction& operator/(const Number& numb) {
		float a = numerator;
		float b = denominator * numb.getValue();
		if (fmod(a, b) == 0.0) {
			a = a / b;
			b = 1;
		}
		return *new Fraction(a, b);
	}
	Fraction& operator+(const Number& numb) {
		float n = (numerator  + numb.getValue()*denominator);
		float d = denominator;
		return *new Fraction(n, d);
	}
	Fraction& operator-(const Number& numb) {
		float n = (numerator - numb.getValue() * denominator);
		float d = denominator;
		return *new Fraction(n, d);
	}

	void print();
};