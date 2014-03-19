#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXCOUNT 210000

struct Bank {
	int idx;
	int x;
	int w;
};


struct BanksPair {
	int b1, b2, sum;	
};

int cmp(const void *d1, const void *d2) {
	if (((Bank*)d1)->w > ((Bank*)d2)->w) return -1;
	if (((Bank*)d1)->w < ((Bank*)d2)->w) return 1;
	return 0;
}

/*int bp_cmp(const void *d1, const void *d2) {
	if (((BanksPair*)d1)->sum > ((BanksPair*)d2)->sum) return -1;
	if (((BanksPair*)d1)->sum < ((BanksPair*)d2)->sum) return 1;
	return 0;
}*/

bool bp_cmp (BanksPair &bp1, BanksPair &bp2) { return (bp1.sum > bp2.sum);}

Bank b[MAXCOUNT];
BanksPair bp;

int n, d, b1 = 0, b2 = 0, max_sum = -1;

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n >> d;

	for (int i = 0; i < n; ++i) {
		b[i].idx = i + 1;
		cin >> b[i].x >> b[i].w;
	}

	bp.b1 = -1;
	bp.b2 = -1;
	bp.sum = 0;

	if (d > b[n - 1].x - b[0].x) printf("-1 -1\n");
	else {
		qsort(b, n, sizeof(Bank), cmp);
		for (int i = 0; i < n - 1; ++i) {
			b1 = b[i].idx;
			for (int j = i + 1; j < n; ++j) {
				if (abs(b[i].x - b[j].x) >= d && bp.sum < b[i].w + b[j].w) {
					b2 = b[j].idx;
					bp.b1 = b1;
					bp.b2 = b2;
					bp.sum = b[i].w + b[j].w;
				}
			}
		}

		printf("%d %d\n", bp.b1, bp.b2);
	}

	return 0;
}