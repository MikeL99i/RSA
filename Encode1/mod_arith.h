#ifndef __MOD_ARITH__
#define __MOD_ARITH__

/*  op: Operand
	Rückgabewert: Anzahl der Bits, die zur Darstellung von op mindestens
				  benötigt werden (führende Nullen werden ignoriert)
	IDEE: op wird immer um 1 Bit nach rechts geschoben, bis das Nullwort entstanden ist.
		  Die Anzahl der Schiebeoperationen ist das gewuenschte Ergebnis
*/
unsigned int bits_required(unsigned int op);



/*  op1: Operand 1
	op2: Operand 2
	M:   Modul
	Rückgabewert: Ergebnis der Berechnung: op1*op2 mod M
*/
unsigned int mod_mul_limited(unsigned int op1, unsigned int op2, unsigned int M);


/*  op1: Operand 1
	op2: Operand 2
	M:   Modul
	Rückgabewert: Ergebnis der Berechnung: op1*op2 mod M
*/
unsigned int mod_mul(unsigned int op1, unsigned int op2, unsigned int M);


/*  base: Basis
	exp:  Exponent
	M:    Modul
	Rückgabewert: Ergebnis der Berechnung: base hoch exp  mod M
*/
unsigned int mod_power(unsigned int base, unsigned int exp, unsigned int M);


/*  base: Basis
	exp:  Exponent
	M:    Modul
	Rückgabewert: Ergebnis der Berechnung: base hoch exp  mod M
*/
unsigned int mod_power_bin(unsigned int base, unsigned int exp, unsigned int M);


/*
a,b: Input: zwei ganze Zahlen
Rueckgabewert: groesster gemeinsamer Teiler von a und b
*fa, *fb: Zeiger auf berechnete Faktoren fa und fb; damit kann der
groesste gemeinsamen Teilers wie folgt dargestellt werden: ggt = fa*a + fb*b
*/
unsigned int eggt(unsigned int a, unsigned int b, int *fa, int *fb);


/*
op: Input: ganze Zahl
Rückgabewert: Anzahl der teilerfremden Zahlen (Eulersche Phifunktion)
*/
unsigned int calculate_phi(unsigned int op);

/*
op: Input: ganze Zahl, die als Prdoukt zweier Primzahlen darstellbar ist
Rückgabewert: Anzahl der teilerfremden Zahlen (Eulersche Phifunktion)
*/
unsigned int calculate_phi_prim_prod(unsigned int op);


#endif /* __MOD_ARITH__ */
