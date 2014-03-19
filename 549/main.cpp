#include <iostream>
#include <vector>

using namespace std;

#define MAXN 4001

int n = 0, k = 0, max_sets_count = 0, max_sum = 0, eq_count = 0;

struct MyStruct {
	int count;
	int costs[MAXN];
};

MyStruct a[MAXN];

int sums[MAXN];

int a_cmp(const void* d1, const void* d2) {
	if (((MyStruct*)d1)->count > ((MyStruct*)d2)->count) return -1;
	if (((MyStruct*)d1)->count < ((MyStruct*)d2)->count) return 1;
	return 0;
}

int i_cmp(const void* d1, const void* d2) {
	if ((*(int*)d1) > (*(int*)d2)) return -1;
	if ((*(int*)d1) < (*(int*)d2)) return 1;
	return 0;
}

int calc_sum() {
	int idx = 0, sums_count = 0, res_sum = 0;
	while (a[idx].count >= max_sets_count) {
		sums[idx] = 0;
		qsort(a[idx].costs, a[idx].count, sizeof(int), i_cmp);
		for (int i = 0; i < max_sets_count; ++i) sums[idx] += a[idx].costs[i];
		++sums_count;
		++idx;
	}
	qsort(sums, sums_count, sizeof(int), i_cmp);
	for (int i = 0; i < k; ++i) res_sum += sums[i];
	return res_sum;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d %d \n", &n, &k);

	for (int i = 0; i < n; ++i) {
		int mi, ci;
		scanf("%d %d\n", &mi, &ci);
		if (a[mi].count == 0) ++eq_count;
		a[mi].count++;
		a[mi].costs[a[mi].count - 1] = ci;
	}

	qsort(a, MAXN, sizeof(MyStruct), a_cmp);

	if (k > eq_count) printf("0 0\n");
	else {
		max_sets_count = a[k-1].count;
		max_sum = calc_sum();
		printf("%d %d\n", max_sets_count, max_sum);
	}
	

	return 0;
}