#include <iostream>

using namespace std;

#define DSUM 14

int n = 0, d = 0;

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n;

	d = n / DSUM;

	if (d == 1 && n != 21) printf("-1\n");
	else if (n - DSUM*d <= 12 && n - DSUM*d > 1 && d != 0) printf("%d\n", d);
	else printf("-1\n");

	return 0;
}