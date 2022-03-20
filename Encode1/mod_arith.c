#include "mod_arith.h"

unsigned int bits_required(unsigned int op)
{
	/*  op: Operand
		Rückgabewert: Anzahl der Bits, die zur Darstellung von op mindestens
					  benötigt werden (führende Nullen werden ignoriert)
		IDEE: op wird immer um 1 Bit nach rechts geschoben, bis das Nullwort entstanden ist.
			  Die Anzahl der Schiebeoperationen ist das gewuenschte Ergebnis
	*/
	unsigned int cnt = 0;

	while (op != 0)
	{
		op = op >> 1;
		cnt++;
	}

	return cnt;
}



unsigned int mod_mul_limited(unsigned int op1, unsigned int op2, unsigned int M)
/*  op1: Operand 1
	op2: Operand 2
	M:   Modul
	Rückgabewert: Ergebnis der Berechnung: op1*op2 mod M
*/
{
	unsigned int temp;

	temp = op1 * op2;	// overflow moeglich !!!!
	return temp % M;
}

unsigned int mod_mul(unsigned int op1, unsigned int op2, unsigned int M)
/*  op1: Operand 1
	op2: Operand 2
	M:   Modul
	Rückgabewert: Ergebnis der Berechnung: op1*op2 mod M
*/
{
	unsigned long long int val;

	val = (unsigned long long int) op1 * (unsigned long long int) op2;
	val = val % (unsigned long long int)M;

	return (unsigned int)val;
}

unsigned int mod_power(unsigned int base, unsigned int exp, unsigned int M)
/*  base: Basis
	exp:  Exponent
	M:    Modul
	Rückgabewert: Ergebnis der Berechnung: base hoch exp  mod M
*/
{

	int i;
	unsigned int res = 1;

	for (i = 1; i <= exp; i++) {
		res = mod_mul(res, base, M);
	}

	return res;
}


unsigned int mod_power_bin(unsigned int base, unsigned int exp, unsigned int M)
/*  base: Basis
	exp:  Exponent
	M:    Modul
	Rückgabewert: Ergebnis der Berechnung: base hoch exp  mod M
*/
{// res = 0 ist nur ein kommentar eigentlich res
	unsigned int res, squa;
	res = 0;

	/* TO DO */

	return res;
}


unsigned int eggt(unsigned int a, unsigned int b, int *fa, int *fb)
/*
a,b: Input: zwei ganze Zahlen
Rueckgabewert: groesster gemeinsamer Teiler von a und b
*fa, *fb: Zeiger auf berechnete Faktoren fa und fb; damit kann der
groesste gemeinsamen Teilers wie folgt dargestellt werden: ggt = fa*a + fb*b
*/
{
	unsigned int k;
	int fa_for_a = 1, fb_for_a = 0, fa_for_b = 0, fb_for_b = 1;
	/* a = fa_for_a*a + fb_for_a*b
	   b = fa_for_b*a + fb_for_b*b */

	while (1) {
		if (a == 0) {
			*fa = fa_for_b;
			*fb = fb_for_b;
			return b;
		}
		if (b == 0) {
			*fa = fa_for_a;
			*fb = fb_for_a;
			return a;
		}
		if (a > b) {
			k = a / b;
			a -= k * b;
			fa_for_a -= k * fa_for_b;
			fb_for_a -= k * fb_for_b;
		}
		else {
			k = b / a;
			b -= k * a;
			fa_for_b -= k * fa_for_a;
			fb_for_b -= k * fb_for_a;
		}
	}
}


unsigned int calculate_phi(unsigned int op)
/*
op: Input: ganze Zahl
Rückgabewert: Anzahl der teilerfremden Zahlen (Eulersche Phifunktion)
*/
{
	unsigned int i, cnt;
	int f1, f2;

	for (i = 1, cnt = 0; i <= op - 1; i++) {
		if (eggt(i, op, &f1, &f2) == 1) cnt++;
	}

	return cnt;
}

unsigned int calculate_phi_prim_prod(unsigned int op)
/*
op: Input: ganze Zahl, die als Prdoukt zweier Primzahlen darstellbar ist
Rückgabewert: Anzahl der teilerfremden Zahlen (Eulersche Phifunktion)
*/
{
	unsigned int res;

	for (res = 2; res <= ~0; res++) {
		if (op%res == 0) break;
	}

	return (res - 1)*(op / res - 1);
}
