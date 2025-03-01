// birch.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <fstream> 
#include <string>
#include <map>
#include <queue>
#include <stack>

#include "MatVar.h"
#include "Number.h"
#include "Matrix.h"
#include "Vector.h"
#include "IdentityMatrix.h"
#include "Complexity.h"
#include "Fraction.h"
#include "Bauer.h"
#include "Test.h"

using namespace std;

bool isCreationMatrix(string str);
bool isIdentityMat(string str);
bool createMatrix(string str);
bool isNumbCorect(string numb);
bool createIdentityMatrix(string str);
bool isPrinting(string str);
bool print(string str);
void printINFO();

map<string, MatVar*> VARS;

int main() {
	setlocale(LC_CTYPE, "rus");
	string str;
	Test test = Test();
	ifstream file;
	bool workWithFile = false;
	while (true) {
		if (workWithFile) {
			if (!getline(file, str)) {
				workWithFile = false;
				file.close();
				continue;
			}
			else {
				cout << str << '\n';
			}
		}
		else {
			if (!test.isTested) {
				getline(cin, str);
			}
			else {
				if (test.testString.size() != 0) {
					if (test.testCount > 0) {
						test.checkValue(*VARS[test.testVars.front()]);
						if (test.testCount == test.quantity) {
							VARS.clear();
						}
					}
					if (test.testCount < test.quantity) {
						str = test.getTestValue();
					}
				}
				else {
					test.isTested = false;
					test = Test();
				}
			}
		}
		if (str == "file") {
			cout << "Введите полный путь к файлу" << '\n';
			getline(cin, str);
			file = ifstream(str);
			workWithFile = true;
			if (file.is_open()) {
				file = ifstream(str);
				workWithFile = true;
			}
			else {
				cout << "файл не найден" << '\n';
				workWithFile = false;
			}
			continue;
		}
		if (str == "help") {
			printINFO();
			continue;
		}
		if (str == "test") {
			test.isTested = true;
			continue;
		}
		if (isCreationMatrix(str)) {
			if (!createMatrix(str)) {
				cout << "матрица задана некорректно" << '\n';
			}
			continue;
		}
		if (isIdentityMat(str)) {
			if (!createIdentityMatrix(str)) {
				cout << "Единичная матрица задана некорректно" << '\n';
			}
			continue;
		}
		if (isPrinting(str)) {
			if (!print(str)) {
				cout << "Данной команды не существует" << '\n';
			}
			continue;
		}
		else {
			Bauer bauer = Bauer(str, VARS);
			if (!bauer.isSucces()) {
				cout << "Данное выражение некорректно" << '\n';
			}
			continue;
		}
	}

}

bool isPrinting(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '=') {
			return false;
		}
	}
	return true;
}

bool print(string str) {
	bool end = false;
	string varName = "";
	for (int i = 0; i < str.length(); i++) {
		if ((str[i] >= 'A' && str[i] <= 'z') || str[i] == '_' || (str[i] >= '0' && str[i] <= '9')) {
			if (end) {
				return false;
			}
			varName += str[i];
		}
		else {
			if (str[i] == ' ') {
				end = true;
			}
			else {
				return false;
			}
		}
	}
	if (VARS.count(varName)) {
		cout << *VARS[varName] << '\n';
		return true;
	}
	else {
		return false;
	}
}

bool isCreationMatrix(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '[') {
			return true;
		}
	}
	return false;
}

bool isIdentityMat(string str) {
	int i = 0;
	string word = "";
	while (str[i] != '=') {
		i++;
		if (i == str.length()) {
			return false;
		}
	}
	for (;i < str.length(); i++) {
		if (str[i] >= 'A' && str[i] <= 'z') {
			word += str[i];
		}
		if (word == "IdentityMatrix") {
			return true;
		}
	}
	return false;
}

bool createIdentityMatrix(string str) {
	string varName = "";
	string numb = "";
	string word = "";
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
		if (str[i] != ' ') {
			return false;
		}
		i++;
	}
	i++;
	while (str[i] != 'I') {
		if (str[i] != ' ') {
			return false;
		}
		i++;
	}
	while (str[i] != '(') {
		if (str[i] >= 'A' && str[i] <= 'z') {
			word += str[i];
		}
		i++;
	}
	i++;
	if (word != "IdentityMatrix") {
		return false;
	}
	while (str[i] != ')') {
		if (str[i] >= '0' && str[i] <= '9') {
			numb += str[i];
		}
		else {
			return false;
		}
		i++;
	}
	i++;
	while (i < str.length()) {
		if (str[i] != ' ') {
			return false;
		}
		i++;
	}
	if(numb == "0" || numb == "") {
		return false;
	}
	MatVar* mat = new IdentityMatrix(stoi(numb));
	if (VARS.count(varName)) {
		delete VARS[varName];
	}
	VARS[varName] = mat;
	return true;
}

bool createMatrix(string str) {
	queue<Number> que;
	int i = 0;
	int colums = 0;
	int rows = 0;
	string varName = "";
	string numb = "";
	bool rowsCounted = false;
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
		if (str[i] != ' ') {
			return false;
		}
		i++;
		if (i == str.length() - 1) {
			return false;
		}
	}
	i++;
	while (str[i] != '[') {
		if (str[i] != ' ') {
			return false;
		}
		if (i == str.length() - 1) {
			return false;
		}
		i++;
	}
	i++;
	while (str[i] != ']') {
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] == '.') || (str[i] == '-')) {
			numb += str[i];
		}
		else {
			if (numb != "") {
				if (!rowsCounted) {
					rows++;
				}
				if (str[i] == ';') {
					colums++;
					rowsCounted = true;
				}
				if (isNumbCorect(numb)) {
					que.push(stof(numb));
					numb = "";
				}
				else {
					return false;
				}
			}
		}
		if (i == str.length() - 1) {
			return false;
		}
		i++;
	}
	colums++;
	if (numb != "") {
		if (!rowsCounted) {
			rows++;
		}
		if (isNumbCorect(numb)) {
			que.push(stof(numb));
			numb = "";
		}
		else {
			return false;
		}
	}
	i++;
	while (i < str.length()) {
		if (str[i] != ' ') {
			return false;
		}
		i++;
	}
	if (VARS.count(varName)) {
		delete VARS[varName];
	}
	if (rows == que.size() / colums) {
		if (colums == 1) {
			MatVar* mat = new Vector(rows, que);
			VARS[varName] = mat;
		}
		else {
			MatVar* mat = new Matrix(rows, colums, que);
			VARS[varName] = mat;
		}
	}
	else {
		return false;
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
		if (numb[i] == '-') {
			if (i != 0) {
				return false;
			}
		}
	}
	return true;
}

void printINFO() {
	cout << "Задание матрицы выглядит так: A = [1 2 3; 4 5 6; 7 8 9]" << '\n';
	cout << "Чтобы задать единичную матрицу: A = IdentityMatrix(3)" << '\n';
	cout << "Пример математических выражений: a = 1 + 2 + a - 2/3 + A" << '\n';
	cout << "Чтобы вывести переменную просто напишите её имя: a" << "\n";
	cout << "Чтобы умножить переменную на -1 необходимо записать значение -1 в другую переменную и после перемножить данные переменные" << '\n';
	cout << "Для работы с файлом необходимо прописать ключевое слово file" << '\n';
}



