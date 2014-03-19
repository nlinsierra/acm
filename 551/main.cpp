#include <iostream>

using namespace std;

int n, t1, t2;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d %d %d\n", &n, &t1, &t2);

	int tt1 = 0, tt2 = 0, count = 0;
	int cur_time = 0;

	while (true) {
		tt1 += t1;
		tt2 += t2;
		if (tt1 < tt2 && count < n) {
			cur_time = tt1;
			count++;
			tt2 -= t2;
		}
		else if (tt1 > tt2 && count < n) {
			cur_time = tt2;
			count++;
			tt1 -= t1;
		}
		else if (tt1 == tt2 && count < n){
			cur_time = tt1;
			count += 2;
		}
		if (count < n) continue;
		if (tt1 < tt2 && count == n) {
			tt1 += t1;
			cur_time = tt1 > tt2 ? tt1 : tt2;
			count++;
		}
		else if (tt1 > tt2 && count == n) {
			tt2 += t2;
			cur_time = tt1 > tt2 ? tt1 : tt2;
			count++;
		}
		break;
	}

	printf("%d %d\n", count, cur_time);

	return 0;
}