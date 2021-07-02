#include "mixed.h"

int32_t mixed_set(sMixedNumber *pNumber, int32_t a, int32_t b, int32_t c)
{
	pNumber->whole = a;
	pNumber->numerator = b;
	pNumber->denominator = c;

	if (a != (int32_t)a || b != (int32_t)b || c != (int32_t)c)
		return -1;
	if (abs(b) > c)
		return -1;
	if (c < 0)
		return -1;
	if (GCD(abs(b), c) != 1)
		return -1;
	if (b < 0 && a != 0)
		return -1;
	if (c == 0 && b != 0)
		return -1;
	return 0;
}

int32_t GCD(int32_t a, int32_t b)
{
	if (b)
		while ((a %= b) && (b %= a))
			;
	return a + b;
}
int32_t LCM(int32_t a, int32_t b)
{
	return a * b / GCD(a, b);
}

int32_t mixed_print(const sMixedNumber number)
{
	printf("(%d, %d, %d)\n", number.whole, number.numerator, number.denominator);
	return 0;
}

void mixed_add(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
	int32_t n1, n2;
	int32_t d1 = r1.denominator, d2 = r2.denominator;
	if (r1.whole < 0)
	{
		n1 = r1.denominator * r1.whole - r1.numerator;
	}
	else
	{
		n1 = r1.denominator * r1.whole + r1.numerator;
	}

	if (r2.whole < 0)
	{
		n2 = r2.denominator * r2.whole - r2.numerator;
	}
	else
	{
		n2 = r2.denominator * r2.whole + r2.numerator;
	}

	if (d1 == 0 || d2 == 0)
	{
		pNumber->denominator = d1 + d2;
		pNumber->numerator = r1.numerator + r2.numerator;
		pNumber->whole = r1.whole + r2.whole;
	}
	else
	{
		pNumber->denominator = LCM(d1, d2);
		pNumber->numerator = abs(n1 * (LCM(d1, d2) / d1) + n2 * (LCM(d1, d2) / d2)) % LCM(d1, d2);
		pNumber->whole = (n1 * (LCM(d1, d2) / d1) + n2 * (LCM(d1, d2) / d2)) / LCM(d1, d2);
	}

	if (pNumber->whole == 0 && (n1 * (LCM(d1, d2) / d1) + n2 * (LCM(d1, d2) / d2)) % LCM(d1, d2) < 0)
		pNumber->numerator = -(pNumber->numerator);
	int32_t gcd = GCD(abs(pNumber->denominator), abs(pNumber->numerator));
	if (gcd != 1)
	{
		pNumber->denominator /= gcd;
		pNumber->numerator /= gcd;
	}
}

void mixed_sub(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
	int32_t n1, n2;
	int32_t d1 = r1.denominator, d2 = r2.denominator;
	if (r1.whole < 0)
	{
		n1 = r1.denominator * r1.whole - r1.numerator;
	}
	else
	{
		n1 = r1.denominator * r1.whole + r1.numerator;
	}

	if (r2.whole < 0)
	{
		n2 = r2.denominator * r2.whole - r2.numerator;
	}
	else
	{
		n2 = r2.denominator * r2.whole + r2.numerator;
	}

	if (d1 == 0)
	{
		pNumber->denominator = d2;
		pNumber->numerator = abs(d2 * r1.whole - n2) % d2;
		pNumber->whole = (d2 * r1.whole - n2) / d2;
		int32_t gcd = GCD(abs(pNumber->denominator), abs(pNumber->numerator));
		if (gcd != 1)
		{
			pNumber->denominator /= gcd;
			pNumber->numerator /= gcd;
		}
		return;
	}
	else if (d2 == 0)
	{
		pNumber->denominator = d1;
		pNumber->numerator = abs(n1 - d1 * r2.whole) % d1;
		pNumber->whole = (n1 - d1 * r2.whole) / d1;
		int32_t gcd = GCD(abs(pNumber->denominator), abs(pNumber->numerator));
		if (gcd != 1)
		{
			pNumber->denominator /= gcd;
			pNumber->numerator /= gcd;
		}
		return;
	}
	else
	{
		pNumber->denominator = LCM(d1, d2);
		pNumber->numerator = abs(n1 * (LCM(d1, d2) / d1) - n2 * (LCM(d1, d2) / d2)) % LCM(d1, d2);
		pNumber->whole = (n1 * (LCM(d1, d2) / d1) - n2 * (LCM(d1, d2) / d2)) / LCM(d1, d2);
	}

	if (pNumber->whole == 0 && (n1 * (LCM(d1, d2) / d1) + n2 * (LCM(d1, d2) / d2)) % LCM(d1, d2) < 0)
		pNumber->numerator = -(pNumber->numerator);
	int32_t gcd = GCD(abs(pNumber->denominator), abs(pNumber->numerator));
	if (gcd != 1)
	{
		pNumber->denominator /= gcd;
		pNumber->numerator /= gcd;
	}
}

void mixed_mul(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
	int32_t n1, n2;
	int32_t d1 = r1.denominator, d2 = r2.denominator;
	if (r1.whole < 0)
	{
		n1 = r1.denominator * r1.whole - r1.numerator;
	}
	else
	{
		n1 = r1.denominator * r1.whole + r1.numerator;
	}

	if (r2.whole < 0)
	{
		n2 = r2.denominator * r2.whole - r2.numerator;
	}
	else
	{
		n2 = r2.denominator * r2.whole + r2.numerator;
	}

	if (r1.whole == 0 || r2.whole == 0)
	{
		pNumber->denominator = 0;
		pNumber->numerator = 0;
		pNumber->whole = 0;
		return;
	}
	else if (d1 == 0 || d2 == 0)
	{
		pNumber->denominator = d1 + d2;
		pNumber->numerator = abs(r1.numerator * r2.whole + r2.numerator * r1.whole) % (d1 + d2);
		pNumber->whole = r1.whole * r2.whole + abs(r1.numerator * r2.whole + r2.numerator * r1.whole) / (d1 + d2);
		int32_t gcd = GCD(abs(pNumber->denominator), abs(pNumber->numerator));
		return;
	}
	else
	{
		pNumber->denominator = d1 * d2;
		pNumber->numerator = abs(n1 * n2) % (d1 * d2);
		pNumber->whole = (n1 * n2) / (d1 * d2);
	}

	if (pNumber->whole == 0 && (n1 * n2) % (d1 * d2) < 0)
		pNumber->numerator = -(pNumber->numerator);
	int32_t gcd = GCD(abs(pNumber->denominator), abs(pNumber->numerator));
	if (gcd != 1)
	{
		pNumber->denominator /= gcd;
		pNumber->numerator /= gcd;
	}
}

void mixed_div(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
	int32_t n1, n2;
	int32_t d1 = r1.denominator, d2 = r2.denominator;
	if (r1.whole < 0)
	{
		n1 = r1.denominator * r1.whole - r1.numerator;
	}
	else
	{
		n1 = r1.denominator * r1.whole + r1.numerator;
	}

	if (r2.whole < 0)
	{
		n2 = r2.denominator * r2.whole - r2.numerator;
	}
	else
	{
		n2 = r2.denominator * r2.whole + r2.numerator;
	}

	if (d1 == 0 && d2 == 0)
	{
		pNumber->denominator = r2.whole;
		pNumber->numerator = abs(r1.whole) % abs(r2.whole);
		pNumber->whole = r1.whole / r2.whole;
		return;
	}
	else if (d1 == 0)
	{
		pNumber->denominator = n2;
		pNumber->numerator = abs(r1.whole * r2.denominator) % n2;
		pNumber->whole = (r1.whole * r2.denominator) / n2;
		int32_t gcd = GCD(abs(pNumber->denominator), abs(pNumber->numerator));
		if (gcd != 1)
		{
			pNumber->denominator /= gcd;
			pNumber->numerator /= gcd;
		}
		return;
	}
	else if (d2 == 0)
	{
		pNumber->denominator = r1.denominator * r2.whole;
		pNumber->numerator = n1 % pNumber->denominator;
		pNumber->whole = n1 / pNumber->denominator;
		int32_t gcd = GCD(abs(pNumber->denominator), abs(pNumber->numerator));
		if (gcd != 1)
		{
			pNumber->denominator /= gcd;
			pNumber->numerator /= gcd;
		}
		return;
	}
	else
	{
		pNumber->denominator = abs(d1 * n2);
		pNumber->numerator = abs(n1 * d2) % abs(d1 * n2);
		pNumber->whole = (n1 * d2) / (d1 * n2);
	}

	if (pNumber->whole == 0 && ((n1 * d2) < 0 || (d1 * n2) < 0))
		pNumber->numerator = -(pNumber->numerator);
	int32_t gcd = GCD(abs(pNumber->denominator), abs(pNumber->numerator));
	if (gcd != 1)
	{
		pNumber->denominator /= gcd;
		pNumber->numerator /= gcd;
	}
}