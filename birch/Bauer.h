#pragma once
#include "MatVar.h"
#include "Number.h"
#include "Matrix.h"
#include "Vector.h"
#include "IdentityMatrix.h"
#include "Complexity.h"
#include "Fraction.h"

#include <stack>
#include <map>
#include <string>

class Bauer {
private:
	map<string, MatVar*>* VARS;
	stack<MatVar*> E;
	stack<char> T;
	string str;
	int F [6][7] = {
		{6,1,1,1,1,1,5},
		{5,1,1,1,1,1,3},
		{4,1,2,2,1,1,4},
		{4,1,2,2,1,1,4},
		{4,1,4,4,2,2,4},
		{4,1,4,4,2,2,4}
	};
	string newVarName;
	bool succes = true;

	bool addZero() {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == '-') {
				return true;
			}
			else {
				if (str[i] != ' ') {
					return false;
				}
			}
		}
		return false;
	}
	bool findVarName() {
		string varName;
		int i = 0;
		while (str[i] != ' ' && str[i] != '=') {
			if ((str[i] >= 'A' && str[i] <= 'z') || str[i] == '_' || (str[i] >= '0' && str[i] <= '9')) {
				varName += str[i];
			}
			else {
				return false;
			}
			i++;
			if (i == str.length()) {
				return false;
			}
		}
		while (str[i] != '=') {
			i++;
		}
		str = str.substr(i + 1, str.length() - i - 1);
		newVarName = varName;
		return true;
	}
	bool calculate() {
		string var;
		for (int i = 0; i < str.length(); i++) {
			if ((str[i] >= 'A' && str[i] <= 'z') || (str[i] == '_') || (str[i] >= '0' && str[i] <= '9') || (str[i] == '.')) {
				var += str[i];
			}
			else {
				if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '(' || str[i] == ')' || str[i] == '$' || str[i] == ' ') {
					if (var != "") {
						if (!addToStack(var)) {
							return false;
						}
					}
					var = "";
					if (str[i] != ' ') {
						switch (getNumOfOper(T.top(), str[i])) {
						case 1:
							T.push(str[i]);
							break;
						case 2:
							if (!makeOperation()) {
								return false;
							}
							T.push(str[i]);
							break;
						case 3:
							T.pop();
							break;
						case 4:
							if (!makeOperation()) {
								return false;
							}
							i--;
							break;
						case 5:
							return false;
							break;
						case 6:
							if ((*VARS).count(newVarName)) {
								delete (*VARS)[newVarName];
							}
							(*VARS)[newVarName] = E.top();
							break;
						}
					}
				}
				else {
					return false;
				}
			}
		}
		return true;
	}
	int getNum(char a) {
		int n1 = -1;
		switch (a) {
		case '$':
			n1 = 0;
			break;
		case '(':
			n1 = 1;
			break;
		case '+':
			n1 = 2;
			break;
		case '-':
			n1 = 3;
			break;
		case '*':
			n1 = 4;
			break;
		case '/':
			n1 = 5;
			break;
		case ')':
			n1 = 6;
			break;
		}
		return n1;
	}
	int getNumOfOper(char a, char b) {
		int n1 = getNum(a);
		int n2 = getNum(b);
		return F[n1][n2];
	}
	bool addToStack(string var) {
		if (var[0] >= '0' && var[0] <= '9' || var[0] == '-') {
			if (var[var.length() - 1] == 'i') {
				if (var.length() == 1) {
					if (T.top() == '-') {
						E.push(new Complexity(0, -1));
						T.pop();
						T.push('+');
					}
					else {
						E.push(new Complexity(0, 1));
					}
				}
				else {
					if (isNumbCorect(var.substr(0, var.length() - 1))) {
						if (T.top() == '-') {
							E.push(new Complexity(0, stof("-" + var)));
							T.pop();
							T.push('+');
						}
						else {
							E.push(new Complexity(0, stof(var)));
						}
					}
					else {
						return false;
					}
				}
			}
			else {
				if (isNumbCorect(var.substr(0, var.length()))) {
					E.push(new Number(stof(var)));
				}
				else {
					return false;
				}
			}
		}
		else {
			if ((*VARS).count(var)) {
				E.push((*VARS)[var]);
			}
			else {
				return false;
			}
		}
		return true;
	}
	bool isNumbCorect(string numb) {
		int countDots = 0;
		if (numb[0] == '0' && numb.length() > 1 && numb[1] != '.') {
			return false;
		}
		for (int i = 0; i < numb.length(); i++) {
			if (numb[i] == '.') {
				countDots++;
				if (countDots > 1) {
					return false;
				}
			}
		}
		return true;
	}
	bool makeOperation() {
		MatVar* var2 = E.top();
		E.pop();
		MatVar* var1 = E.top();
		E.pop();
		Matrix* mat = dynamic_cast<Matrix*>(var1);
		if (mat) {
			Matrix* mat2 = dynamic_cast<Matrix*>(var2);
			if (mat2) {
				switch (T.top()) {
				case '+':
					if (mat->getRows() == mat2->getRows() && mat->getColums() == mat2->getColums()) {
						E.push(&((*mat) + (*mat2)));
					}
					else {
						return false;
					}
					break;
				case '-':
					if (mat->getRows() == mat2->getRows() && mat->getColums() == mat2->getColums()) {
						E.push(&((*mat) - (*mat2)));
					}
					else {
						return false;
					}
					break;
				case '*':
					if (mat->getColums() == mat2->getRows()) {
						E.push(&((*mat) * (*mat2)));
					}
					else {
						return false;
					}
					break;
				case '/':
					return false;
					break;
				}
			}
			else {
				switch (T.top()) {
				case '+':
					return false;
					break;
				case '-':
					return false;
					break;
				case '*':
					E.push(&((*mat) * (*dynamic_cast<Number*>(var2))));
					break;
				case '/':
					Number * numb = dynamic_cast<Number*>(var2);
					if (numb->getValue() == 0) {
						return false;
					}
					else {
						E.push(&((*mat) / (*numb)));
					}
					break;
				}
			}
		}
		else {
			Matrix* mat2 = dynamic_cast<Matrix*>(var2);
			if (mat2) {
				E.push(var2);
				E.push(var1);
				return makeOperation();
			}
			else {
				Complexity* comp = dynamic_cast<Complexity*>(var1);
				if (comp) {
					Complexity* comp2 = dynamic_cast<Complexity*>(var2);
					if (comp2) {
						switch (T.top()) {
						case '+':
							E.push(&((*comp) + (*comp2)));
							break;
						case '-':
							E.push(&((*comp) - (*comp2)));
							break;
						case '*':
							E.push(&((*comp) * (*comp2)));;
							break;
						case '/':
							if (comp2->getValue() != 0 && comp2->getImag() != 0) {
								E.push(&((*comp) / (*comp2)));
							}
							else {
								return false;
							}
							break;
						}
					}
					else {
						Number* numb = dynamic_cast<Number*>(var2);
						switch (T.top()) {
						case '+':
							E.push(&((*comp) + (*numb)));
							break;
						case '-':
							E.push(&((*comp) - (*numb)));
							break;
						case '*':
							E.push(&((*comp) * (*numb)));
							break;
						case '/':
							if (numb->getValue() != 0) {
								E.push(&((*comp) / (*numb)));
							}
							else {
								return false;
							}
							break;
						}
					}
				}
				else {
					Complexity* comp2 = dynamic_cast<Complexity*>(var2);
					if (comp2) {
						E.push(var2);
						E.push(var1);
						return makeOperation();
					}
					else {
						Number* numb = dynamic_cast<Number*>(var1);
						Number* numb2 = dynamic_cast<Number*>(var2);
						switch (T.top()) {
						case '+':
							E.push(&((*numb) + (*numb2)));
							break;
						case '-':
							E.push(&((*numb) - (*numb2)));
							break;
						case '*':
							E.push(&((*numb) * (*numb2)));
							break;
						case '/':
							if (numb2->getValue() != 0) {
								if (fmod(numb->getValue(), numb2->getValue()) == 0.0) {
									E.push(&((*numb) / (*numb2)));
								}
								else {
									E.push(new Fraction(numb->getValue(), numb2->getValue()));
								}
							}
							else {
								return false;
							}
							break;
						}
					}
				}
			}
		}
		T.pop();
		return true;
	}
public:
	Bauer(string s, map<string, MatVar*>& v) {
		str = s + "$";
		T.push('$');
		VARS = &v;
		if (!findVarName()) {
			succes = false;
		}
		else {
			if (addZero()) {
				str = "0" + str;
			}
			if (!calculate()) {
				succes = false;
			}
		}
	}
	bool isSucces() { return succes; };
};
