#pragma once
#include <iostream>
#include <string>
#include <map>
#include <queue>

#include "MatVar.h"
#include "Number.h"
#include "Matrix.h"
#include "Vector.h"
#include "IdentityMatrix.h"
#include "Complexity.h"
#include "Fraction.h"

using namespace std;
class Test {
public:
	bool isTested = false;
	map<string, MatVar*> expValue;
	queue<string> testString;
	queue<string> testVars;
	int testCount = 0;
	int testPassed = 0;
	int quantity;
	Test() {
		//test 1
		testString.push("a = 1");
		testVars.push("a");
		expValue["a"] = new Number(1);
		//test 2
		testString.push("b = 10");
		testVars.push("b");
		expValue["b"] = new Number(10);
		//test 3
		testString.push("c = 10000");
		testVars.push("c");
		expValue["c"] = new Number(10000);
		//test 4
		testString.push("d = 14.78");
		testVars.push("d");
		expValue["d"] = new Number(14.78);
		//test 5
		testString.push("e = -23");
		testVars.push("e");
		expValue["e"] = new Number(-23);
		//test 6
		testString.push("f = 2 + 1i");
		testVars.push("f");
		expValue["f"] = new Complexity(2, 1);
		//test 7
		testString.push("g = 1 - 2i");
		testVars.push("g");
		expValue["g"] = new Complexity(1, -2);
		//test 8
		testString.push("h = -3 - 3i");
		testVars.push("h");
		expValue["h"] = new Complexity(-3, -3);
		//test 9
		testString.push("i = 1i");
		testVars.push("i");
		expValue["i"] = new Complexity(0, 1);
		//test 10
		testString.push("j = 2 + 0i");
		testVars.push("j");
		expValue["j"] = new Complexity(2, 0);
		//test 11
		testString.push("k = 1/2");
		testVars.push("k");
		expValue["k"] = new Fraction(1, 2);
		//test 12
		testString.push("l = 0/2");
		testVars.push("l");
		expValue["l"] = new Fraction(0, 2);
		//test 13
		testString.push("m = 1/1");
		testVars.push("m");
		expValue["m"] = new Fraction(1, 1);
		//test 14
		testString.push("n = 3/2");
		testVars.push("n");
		expValue["n"] = new Fraction(3, 2);
		//test 15
		testString.push("o = 1/0");
		testVars.push("o");
		expValue["o"] = nullptr;
		//test 16
		testString.push("p = [1 2 3]");
		testVars.push("p");
		Number** numb = new Number*[3];
		numb[0] = {new Number(1) };
		numb[1] = { new Number(2) };
		numb[2] = { new Number(3) };
		expValue["p"] = new Matrix(3, 1, numb);
		deleteArr(3, numb);
		//test 17
		testString.push("q = [1 2 3; 4 5 6; 7 8 9]");
		testVars.push("q");
		numb = new Number * [3];
		numb[0] = new Number[3]{ Number(1), Number(4), Number(7) };
		numb[1] = new Number[3]{ Number(2), Number(5), Number(8) };
		numb[2] = new Number[3]{ Number(3), Number(6), Number(9) };
		expValue["q"] = new Matrix(3, 3, numb);
		deleteArr(3, numb);
		//test 18
		testString.push("r = IdentityMatrix(3)");
		testVars.push("r");
		expValue["r"] = new IdentityMatrix(3);
		//test 19
		testString.push("s = q*p");
		testVars.push("s");
		numb = new Number * [3];
		numb[0] = { new Number(30) };
		numb[1] = { new Number(36) };
		numb[2] = { new Number(42) };
		expValue["s"] = new Matrix(3, 1, numb);
		deleteArr(3, numb);
		//test 21
		testString.push("t = q*r");
		testVars.push("t");
		expValue["t"] = expValue["q"];
		testString.push("u = q*0");
		testVars.push("u");
		numb = new Number * [3];
		numb[0] = new Number[3]{ Number(0), Number(0), Number(0) };
		numb[1] = new Number[3]{ Number(0), Number(0), Number(0) };
		numb[2] = new Number[3]{ Number(0), Number(0), Number(0) };
		expValue["u"] = new Matrix(3, 3, numb);
		deleteArr(3, numb);
		//test 22
		testString.push("v = q*p + s");
		testVars.push("v");
		numb = new Number * [3];
		numb[0] = { new Number(30*2) };
		numb[1] = { new Number(36*2) };
		numb[2] = { new Number(42*2) };
		expValue["v"] = new Matrix(3, 1, numb);
		deleteArr(3, numb);
		//test 23
		testString.push("w = v*q");
		testVars.push("w");
		expValue["w"] = nullptr;
		//test 24
		testString.push("x = v*q");
		testVars.push("x");
		expValue["x"] = nullptr;
		//test 25
		testString.push("y = (q + r*3)*p/3");
		testVars.push("y");
		numb = new Number * [3];
		numb[0] = { new Number(11) };
		numb[1] = { new Number(14) };
		numb[2] = { new Number(17) };
		expValue["y"] = new Matrix(3, 1, numb);
		deleteArr(3, numb);

		quantity = testString.size();
	}
	string getTestValue() {
		testCount++;
		cout << "------------------------------------------------------------------" << '\n';
		cout << "Test " << testCount << '\n' << '\n';
		cout << "Test string: " << testString.front() << '\n' << '\n';
		cout << "expected value:" << '\n';
		if(expValue[testVars.front()] == nullptr){
			cout << "null" << '\n' << '\n';
		}
		else {
			cout << *expValue[testVars.front()] << '\n' << '\n';
		}
		return testString.front();
	}
	void checkValue(MatVar& m) {
		cout << "result:" << '\n';
		if (&m == nullptr && expValue[testVars.front()] == nullptr) {
			cout << "null" << '\n' << '\n';
			testPassed++;
			cout << "test " << testCount << " was passed!" << '\n';
			cout << "------------------------------------------------------------------" << '\n';
			cout << "passed tests: " << testPassed << "/" << quantity << '\n';
			testVars.pop();
			testString.pop();
			return;
		}
		cout << m << '\n' << '\n';
		Matrix* mat = dynamic_cast<Matrix*>(&m);
		if (mat) {
			Matrix* mat2 = dynamic_cast<Matrix*>(expValue[testVars.front()]);
			if (*mat == *mat2) {
				testPassed++;
				cout << "test " << testCount << " was passed!" << '\n';
			}
			else {
				cout << "test was not passed!" << '\n';
			}
		}
		else {
			Number* numb = dynamic_cast<Number*>(&m);
			Number* numb2 = dynamic_cast<Number*>(expValue[testVars.front()]);
			if (numb->getValue() == numb2->getValue()) {
				testPassed++;
				cout << "test " << testCount << " was passed!" << '\n';
			}
			else {
				cout << "test was not passed!" << '\n';
			}
		}
		cout << "------------------------------------------------------------------" << '\n';
		cout << "passed tests: " << testPassed << "/" << quantity << '\n';
		testVars.pop();
		testString.pop();
	}

	void deleteArr(int r, Number** numb) {
		for (int i = 0; i < r; i++) {
			delete numb[i];
		}
		delete[] numb;
		numb = nullptr;
	}

};
