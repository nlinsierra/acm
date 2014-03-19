#include <iostream>

using namespace std;

struct SegTree {
	int val;
	int min_val;
};

#define MAXN 201000
#define INF INT_MAX

int n = 0;
int ranges[MAXN];
SegTree t[4*MAXN];
int killed = 0, last_killed = 0, cur_dragon_idx = 0, killed_dragon_idx = 0;


/**********************************************************************/
void build (int a[], int v, int tl, int tr) {
	if (tl > tr) return;
	if (tl == tr) {
		t[v].val = a[tl];
		t[v].min_val = a[tl];
	}
	else {
		int tm = (tl + tr) / 2;
		build (a, v*2, tl, tm);
		build (a, v*2+1, tm + 1, tr);
		t[v].min_val = min(t[2*v].min_val, t[2*v + 1].min_val);
		t[v].val = 0;
	}
}

int get_min (int v, int tl, int tr, int l, int r) {
	if (l > r) return INF;
	if (l == tl && r == tr) return t[v].min_val;
	int tm = (tl + tr) / 2;
	return min(
		get_min (v*2, tl, tm, l, min(r,tm)), 
		get_min (v*2+1, tm+1, tr, max(l,tm+1), r)
	) + t[v].val;
}
 
void update_dec (int v, int tl, int tr, int l, int r) {
	if (l > r) return;
	if (l == tl && tr == r) {
		t[v].val--;
		t[v].min_val--;
	}
	else {
		int tm = (tl + tr) / 2;
		update_dec (v*2, tl, tm, l, min(r,tm));
		update_dec (v*2+1, tm+1, tr, max(l,tm+1), r);
		t[v].min_val = min(t[2*v].min_val, t[2*v + 1].min_val) + t[v].val;
	}
}
/**********************************************************************/

struct Dragon {
	int idx;
	int gold;
	bool is_killed;
	int range;
};

Dragon dragons[200000];

int cmp(const void* d1, const void* d2) {
	if (((Dragon*)d1)->gold > ((Dragon*)d2)->gold) return 1;
	if (((Dragon*)d1)->gold < ((Dragon*)d2)->gold) return -1;
	return 0;
}

int cmp_idx(const void* d1, const void* d2) {
	if (((Dragon*)d1)->idx > ((Dragon*)d2)->idx) return 1;
	if (((Dragon*)d1)->idx < ((Dragon*)d2)->idx) return -1;
	return 0;
}

int killDragon(int dragons_count, int ranges_count) {
	for (int i = cur_dragon_idx; i >= 0; --i) {

		int cur_range = get_min(1, 0, ranges_count - 2, dragons[i].range, ranges_count - 2);

		if (!dragons[i].is_killed && cur_range > 1 && cur_range != INF) {
			dragons[i].is_killed = true;
			update_dec(1, 0, ranges_count - 2, dragons[i].range, ranges_count - 2);
			++killed;
			cur_dragon_idx = i;
			return dragons[i].gold;
		}
	}
	return -1;
}

int killLastDragons(int dragons_count, int ranges_count) {
	int i = dragons_count - 1, sum = 0;
	while (i >= 0 && dragons[i].range == ranges_count - 1) {
		sum += dragons[i].gold;
		dragons[i].is_killed = true;
		++last_killed;
		--i;
	}
	return sum;
}

int main() {
	int ranges_count = 0, dragons_count = 0;
	int gold_sum = 0;

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d\n", &n);
	for (int i = 2; i <= n; ++i) {
		char c;
		int w = 0;
		scanf("%c %d\n", &c, &w);
		if (c == 'd') {
			dragons[dragons_count].idx = i;
			dragons[dragons_count].is_killed = false;
			dragons[dragons_count].range = ranges_count;
			dragons[dragons_count].gold = w;
			++dragons_count;
		}
		else if (c == 'p') {
			ranges[ranges_count] = w;
			++ranges_count;
		}
	}

	build(ranges, 1, 0, ranges_count - 2);

	cur_dragon_idx = dragons_count - last_killed - 1;

	gold_sum += killLastDragons(dragons_count, ranges_count);

	qsort(dragons, dragons_count - last_killed, sizeof(Dragon), cmp);


	int cur_range = ranges[ranges_count - 2];

	while (killed < cur_range) {
		if (killed == cur_range - 1) break;
		int cur_gold = killDragon(dragons_count, ranges_count);
		if (cur_gold != -1) {
			gold_sum += cur_gold;
		}
		else break;
	}

	killed += last_killed;
	qsort(dragons, dragons_count, sizeof(Dragon), cmp_idx);

	if (killed < ranges[ranges_count - 1]) cout << -1 << endl;
	else {
		printf("%d\n%d\n", gold_sum, killed);		

		for (int i = 0; i < dragons_count; ++i) if (dragons[i].is_killed) cout << dragons[i].idx << " ";
	}
	
	return 0;
}