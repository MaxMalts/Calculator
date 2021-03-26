#pragma once

DEF_FUNC(sin, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = sin(arg);
	})

DEF_FUNC(cos, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = cos(arg);
	})

DEF_FUNC(tg, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = tan(arg);
	})

DEF_FUNC(ctg, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = 1 / tan(arg);
	})

DEF_FUNC(arcsin, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = asin(arg);
	})

DEF_FUNC(arccos, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = acos(arg);
	})


DEF_FUNC(arctg, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = atan(arg);
	})


DEF_FUNC(arcctg, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = atan(1 / arg);
	})

DEF_FUNC(exp, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = exp(arg);
	})

DEF_FUNC(abs, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = fabs(arg);
	})

DEF_FUNC(floor, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = floor(arg);
	})

DEF_FUNC(sqrt, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = floor(arg);
	})

DEF_FUNC(ln, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = log(arg);
	})

DEF_FUNC(lg, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = log10(arg);
	})

DEF_FUNC(log, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg1 = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ',') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg2 = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = log(arg2) / log(arg1);
	})

DEF_FUNC(pow, {
		if (*curSequence != '(') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg1 = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ',') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		float arg2 = GetE(syntaxErr);
		assert_syntax(*syntaxErr);

		if (*curSequence != ')') {
			*syntaxErr = 1;
		}
		assert_syntax(*syntaxErr);
		curSequence++;

		val = pow(arg1, arg2);
	})