#include <iostream>
#include <iomanip>

using namespace std;

const double MAX_X = 1e7;

double s, p;
int m;

double SumB(double x) {
	double cur_s = s, ai = 0.0, bi = 0.0, sum = 0.0;
	for (int i = 0; i < m; ++i) {
		cur_s -= bi;
		if (cur_s < 0) break;
		ai = cur_s*p/100.0;
		bi = x - ai;
		sum += bi;
	}
	return sum;
}

int main() {
	cin >> s >> m >> p;
	
	double l = 0.0, r = 2*s, x;
	
	while (r - l > 1e-6 && l < r) {
		x = (l + r) / 2.0;
		double sum = SumB(x);		
		if (sum < s) l = x;
		else r = x;		
	}
	cout << fixed << setprecision(6) << x << endl;
	
	return 0;
}
