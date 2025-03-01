#include "Fraction.h"

Fraction::Fraction(float a, float b) { 
	numerator = a; 
	denominator = b; 
	value = a / b; 
}

void Fraction::print() {
	if (numerator == 0) {
		cout << 0;
	}
	else {
		if (denominator == -1 || denominator == 1) {
			if (denominator == -1) {
				cout << -numerator;
			}
			else {
				cout << numerator;
			}
		}
		else {
			if (numerator * denominator > 0) {
				if (numerator < 0 && denominator < 0) {
					cout << -numerator << '/' << -denominator;
				}
				else {
					cout << numerator << '/' << denominator;
				}
			}
			else {
				if (numerator < 0) {
					cout << numerator << '/' << denominator;
				}
				else {
					cout << '-' << numerator << '/' << -denominator;
				}
			}
		}
	}
}