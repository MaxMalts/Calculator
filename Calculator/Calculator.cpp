#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


/**
*	Знак числа
*
*	@param[in] var
*
*	@return -1 - минус; 1 - плюс
*/

int Sign(float var) {
	if (var < 0) {
		return -1;
	}

	return 1;
}


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
	char inpStr[100] = "";
	scanf("%s", inpStr);
	fseek(stdin, 0, SEEK_END);

	while (strcmp(inpStr, "exit") != 0) {
		curSequence = inpStr;

		int syntaxErr = 0;
		printf("%g\n\n", GetG(&syntaxErr));
		if (syntaxErr) {
			printf("Syntax error\n\n");
			return 1;
		}

		scanf("%s", inpStr);
		fseek(stdin, 0, SEEK_END);
	}

	return 0;
}