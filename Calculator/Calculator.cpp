#pragma comment(linker, "/STACK:100000000")

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


/**
*	���� �����
*
*	@param[in] var
*
*	@return -1 - �����; 1 - ����
*/

int Sign(float var) {
	if (var < 0) {
		return -1;
	}

	return 1;
}


/**
*	������� ����� foat �� ��� ����� � ������� ������
*
*	@param[in] intPart ����� ����� (����� ���� �������������)
*	@param[in] fracPart ������� ����� (������ �������������)
*
*	@return ����� float
*/

float CreateFloat(int intPart, int fracPart) {
	int tenPow = 1;
	while (fracPart / tenPow != 0) {
		tenPow *= 10;
	}

	float res = intPart + Sign(intPart) * (float)fracPart / tenPow;

	return res;
}



#define assert_syntax(syntaxErr) \
	if(syntaxErr) {\
		return 0;\
	}


const char* curSequence = "";

float GetG(int* syntaxErr);

float GetE(int* syntaxErr);

float GetT(int* syntaxErr);

float GetP(int* syntaxErr);

float GetFunc(int* syntaxErr);

float GetF(int* syntaxErr);

int GetI(int* syntaxErr);

int GetN(int* syntaxErr);



/**
*	������� ��� ��������� ��������� (G::=E'\0')
*
*	@param[out] syntaxErr �������� �� �������������� ������ (1 ��� 0)
*
*	@return �������� ���������
*/

float GetG(int* syntaxErr) {
	assert(syntaxErr != NULL);

	float val = GetE(syntaxErr);
	assert_syntax(*syntaxErr);

	if (*curSequence != '\0') {
		*syntaxErr = 1;
	}
	assert_syntax(*syntaxErr);

	curSequence++;

	return val;
}


/**
*	������� ��� ��������� �����, �������� (E::=T{[+-]T}*)
*
*	@param[out] syntaxErr �������� �� �������������� ������ (1 ��� 0)
*
*	@return �������� ���������
*/

float GetE(int* syntaxErr) {
	assert(syntaxErr != NULL);

	float val = GetT(syntaxErr);
	assert_syntax(*syntaxErr);

	while (*curSequence == '+' || *curSequence == '-') {
		char op = *curSequence;
		curSequence++;

		int val1 = GetT(syntaxErr);
		assert_syntax(*syntaxErr);

		switch (op) {
		case '+':
			val += val1;
			break;
		case '-':
			val -= val1;
			break;
		}
	}

	return val;
}


/**
*	������� ��� ��������� ���������, ������� (T::=P{[/*]P}*)
*
*	@param[out] syntaxErr �������� �� �������������� ������ (1 ��� 0)
*
*	@return �������� ���������
*/

float GetT(int* syntaxErr) {
	assert(syntaxErr != NULL);

	float val = GetP(syntaxErr);
	assert_syntax(*syntaxErr);

	while (*curSequence == '*' || *curSequence == '/') {
		char op = *curSequence;
		curSequence++;

		float val1 = GetP(syntaxErr);
		assert_syntax(*syntaxErr);

		switch (op) {
		case '*':
			val *= val1;
			break;
		case '/':
			val /= val1;
			break;
		}
	}

	return val;
}


/**
*	������� ��� ��������� ��������� � �������, ������ ��� �����(P::='('E')'|Func|F).\
 ����� ����������, ��� ������ ��������, ������� ������ ������.
*
*	@param[out] syntaxErr �������� �� �������������� ������ (1 ��� 0)
*
*	@return �������� ���������
*/

float GetP(int* syntaxErr) {
	assert(syntaxErr != NULL);

	float val = 0;

	if (*curSequence == '(') {
		curSequence++;

		val = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;
	}
	else if (isalpha(*curSequence)) {
		val = GetFunc(syntaxErr);
		assert_syntax(*syntaxErr);
	}
	else {
		val = GetF(syntaxErr);
		assert_syntax(*syntaxErr);
	}

	return val;
}


/**
*	������� ��� ��������� ������� ( Func::="sin"'('E')'|"cos"'('E')'...|"pow"'('E','E')' )
*
*	@param[out] syntaxErr �������� �� �������������� ������ (1 ��� 0)
*
*	@return �������� �������
*/

float GetFunc(int* syntaxErr) {
	assert(syntaxErr != NULL);

	float val = 0;

#define DEF_FUNC(str, code)\
	else if(strncmp(curSequence, #str, sizeof(#str) - 1) == 0){\
		curSequence = curSequence + sizeof(#str) - 1;\
		code;\
	}

	if (0) {}
#include "Functions.h"

#undef DEF_FUNC

	return val;
}


/**
*	������� ��� ��������� ����� float ( F::=I{'.'N}? )
*
*	@param[out] syntaxErr �������� �� �������������� ������ (1 ��� 0)
*
*	@return ����� float
*/

float GetF(int* syntaxErr) {
	assert(syntaxErr != NULL);

	float val = 0;

	int intPart = GetI(syntaxErr);
	assert_syntax(*syntaxErr);

	int fracPart = 0;
	if (*curSequence == '.') {
		curSequence++;

		fracPart = GetN(syntaxErr);
		assert_syntax(*syntaxErr);
	}

	val = CreateFloat(intPart, fracPart);

	return val;
}


/**
*	������� ��� ��������� ������ ����� ( I::=[+-]?N )
*
*	@param[out] syntaxErr �������� �� �������������� ������ (1 ��� 0)
*
*	@return ����� �����
*/

int GetI(int* syntaxErr) {
	assert(syntaxErr != NULL);

	int val = 0;
	int sign = 1;

	if (*curSequence == '-') {
		sign = -1;
		curSequence++;
	}
	else if (*curSequence == '+') {
		curSequence++;
	}
	
	val = GetN(syntaxErr);
	assert_syntax(*syntaxErr);

	val *= sign;

	return val;
}


/**
*	������� ��� ��������� ������ �������������� ����� ( N::=['0'-'9']+ )
*
*	@param[out] syntaxErr �������� �� �������������� ������ (1 ��� 0)
*
*	@return ����� ������������� �����
*/

int GetN(int* syntaxErr) {
	assert(syntaxErr != NULL);

	int val = 0;

	if (!('0' <= *curSequence && *curSequence <= '9')) {
		*syntaxErr = 1;
	}
	assert_syntax(*syntaxErr);

	while ('0' <= *curSequence && *curSequence <= '9') {
		val = val * 10 + (*curSequence - '0');
		curSequence++;
	}

	return val;
}


int main() {
	char inpStr[10000] = "";
	scanf("%s", inpStr);
	fseek(stdin, 0, SEEK_END);

	while (strcmp(inpStr, "exit") != 0) {
		curSequence = inpStr;

		int syntaxErr = 0;
		float ans = GetG(&syntaxErr);
		
		if (!syntaxErr) {
			printf("%g\n\n", ans);
		}
		else {
			printf("Syntax error\n\n");
		}

		scanf("%s", inpStr);
		fseek(stdin, 0, SEEK_END);
	}

	return 0;
}