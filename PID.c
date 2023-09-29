#include<stdio.h>

//5点微分
double bibun(double InputData,double h1)
{
	static double data[5];
	double ans = 0;
	static int cnt;
	data[cnt % 5] = InputData;

	ans = (3 * data[(cnt + 1) % 5] - 16 * data[(cnt + 2) % 5] + 36 * data[(cnt + 3) % 5] - 48 * data[(cnt + 4) % 5] + 25 * data[cnt % 5]) / (12 * h1);
	cnt++;
	if (cnt >= 5)return ans;
	else return 0;
}

//シンプソン法
double sekibun(double InputData, double h1) {
	static double sum_k;
	static double sum_g;
	static double y0;
	static double yn1;
	double Output = 0;
	static int cnt;
	if (cnt == 0) {
		y0 = InputData;
	}
	else {
		if (cnt % 2 == 0) {
			sum_k += yn1;
		}
		else {
			if (cnt == 1) {
			}
			else {
				sum_g += yn1;
			}
		}
		Output = (h1 / 3) * (y0 + InputData + 4 * sum_k + 2 * sum_g);
	}
	yn1 = InputData;
	cnt++;
	return Output;
}

//PID制御計算
double ucal(double error, double de, double ie, double kp, double ki, double kd) {
	double out = 0;
	out = kp * error + ki * de + kd * ie;
	return out;
}

//PID制御
double PID(double error, double h, double kp, double ki, double kd) {
	double de, ie, u;
	de = bibun(error, h);
	ie = sekibun(error, h);
	u = ucal(error, de, ie, kp, ki, kd);
	return u;
}

typedef struct RK4Out {
	double OutT;
	double OutX;
	double OutV;
}RK4Out;

double func_one(double t, double x, double v) {
	double dvdt;
	dvdt = v;
	return(dvdt);
}

double func_two(double t, double x, double v, double f) {
	double dbdt;
	double m = 1.0;
	double c = 1.0;
	double k = 10;
	dbdt = (1 / m) * f - (c / m) * v - (k / m) * x;
	return(dbdt);
}

RK4Out RungeKuttaSecond(double t, double x, double v, double h, double f) 
{
	 double k1, k2, k3, k4;
	 double m1, m2, m3, m4;
	 RK4Out Output;

	 //***kkk****
	 k1 = h * func_one(t, x, v);
	 m1 = h * func_two(t, x, v, f);

	 k2 = h * func_one(t * h / 2.0, x + k1 / 2.0, v + m1 / 2.0);
	 m2 = h * func_two(t * h / 2.0, x + k1 / 2.0, v + m1 / 2.0, f);

	 k3 = h * func_one(t * h / 2.0, x + k2 / 2.0, v + m2 / 2.0);
	 m3 = h * func_two(t * h / 2.0, x + k2 / 2.0, v + m2 / 2.0, f);

	 k4 = h * func_one(t * h, x + k3, v + m3);
	 m4 = h * func_two(t * h, x + k3, v + m3, f);
	 Output.OutT = t * h;
	 Output.OutX = x + 1.0 / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
	 Output.OutV = v + 1.0 / 6.0 * (m1 + 2.0 * m2 + 2.0 * m3 + m4);
	 //
	 return Output;
}

int main() {
	double t;
	double X=5;
	double Y;
	double e;
	double u=0;
	double h = 0.001;
    double kp = 1;
    double ki = 1;
    double kd = 1;

	for (int j = 0; j < 1000; j++) {
		t = j * h;
		e = X-u;
		u = PID(e, h, kp, ki, kd);
		printf_s("%lf\n", u);
	}
}