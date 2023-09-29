#include<stdio.h>
#include<math.h>

#define f(x) (x/(x*x+1))
#define g(x) ((-pow(x,2)+1)/(pow(x*x+1,2)))
#define EPS (0.000001)
#define KMAX 20


void main() {
	double x0, xi, dxi, d;
	x0 = 0.33333;
	printf_s("x0=%f\n", x0);
	xi = x0;
	printf_s("i   xi        dxi       d\n");
	for (int i = 1; i <= KMAX; i++) {
		dxi = xi;
		xi = dxi - f(dxi) / g(dxi);
		d = fabs(xi-dxi);
		printf_s("%2d  %lf  %lf  %lf\n", i, xi, dxi, d);
	}
	if (d < EPS) {
		printf_s("x=%lf\n", xi);
	}
	else {
		printf_s("�������Ȃ�\n");
	}
}