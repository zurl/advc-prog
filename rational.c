#include<stdio.h>

typedef struct __rationalT {
	int num;
	int den;
}rationalT;

int gcd(int x, int y) {
	return (y == 0) ? x : gcd(y, x%y);
}
void Simplify(rationalT *r) {
	int t = gcd(r->num, r->den);
	r->num /= t;
	r->den /= t;
	if (r->den < 0) {
		r->den = -r->den;
		r->num = -r->num;
	}
}

rationalT CreateRational(int num, int den) {
	rationalT ret;
	ret.num = num;
	ret.den = den;
	Simplify(&ret);
	return ret;
}
rationalT AddRational(rationalT r1, rationalT r2) {
	rationalT ret;
	ret.num = r1.num * r2.den + r1.den * r2.num;
	ret.den = r1.den * r2.den;
	Simplify(&ret);
	return ret;
}
rationalT MultiplyRational(rationalT r1, rationalT r2) {
	rationalT ret;
	ret.num = r1.num * r2.num;
	ret.den = r1.den * r2.den;
	Simplify(&ret);
	return ret;
}
void GetRational(rationalT *r) {
	scanf("%d/%d", &r->num, &r->den);
}
void PrintRational(rationalT r) {
	printf("%d/%d", r.num, r.den);
}

int main() {
	rationalT a, b ,sum,product;
	printf("Please input two rational numbers:\n");
	GetRational(&a);
	GetRational(&b);
	sum = AddRational(a, b);
	product = MultiplyRational(a, b);
	printf("The sum of "); PrintRational(a); printf(" and "); PrintRational(b); printf(" is :\n");
	PrintRational(sum); printf("\n");
	printf("The product of "); PrintRational(a); printf(" and "); PrintRational(b); printf(" is :\n");
	PrintRational(product); printf("\n");
	return 0;
}