#include<stdio.h>

double heikin(int a,double b[a]) {
	double ans = 0;
	for (int j = 0; j < a; j++) {
		ans += b[j];
	}
	ans /= a;
	return ans;
}

double zurashi(int a, double b[a], double c) {
	for (int j = 0; j < a - 1; j++) {
		b[j] = b[j + 1];
	}
	b[a] = c;
	return b;
}

int main() {
	int a;
	int out;
	scanf_s("%d", &a);
	double data[a];
	while (1) {
		int i = 0;
		scanf_s("%lf", &data[i]);
		if (i >= a-1) {
			out = heikin(a, data);
		}
		i++;
		printf_s("out=%lf", out);
	}
}