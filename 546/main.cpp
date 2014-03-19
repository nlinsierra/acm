#include <iostream>
#include <map>
#include <vector>

using namespace std;

#define MAXLEN 201

int n, a, b, max_counts;
map<char, int> counts, need, diff;
char pwd[MAXLEN];

struct Pivot {
	char ch;
	char rem1, rem2;
	short sign;
};

Pivot p;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d %d %d\n", &n, &a, &b);
	if (a + b > n) printf("-1\n");
	else {
		counts['0'] = counts['1'] = counts['2'] = 0;
		need['0'] = a; need['1'] = b; need['2'] = n - a - b;
		for (int i = 0; i < n; ++i) {
			char c;
			scanf("%c", &c);
			pwd[i] = c;
			counts[c]++;
		}
		pwd[n] = '\0';
		diff['0'] = need['0'] - counts['0'];
		diff['1'] = need['1'] - counts['1'];
		diff['2'] = need['2'] - counts['2'];

		max_counts = abs(diff['0']);
		p.ch = '0';
		p.rem1 = '1';
		p.rem2 = '2';
		if (abs(diff['1']) > max_counts) {
			max_counts = abs(diff['1']);
			p.ch = '1';
			p.rem1 = '0';
			p.rem2 = '2';
		}
		if (abs(diff['2']) > max_counts) {
			max_counts = abs(diff['2']);
			p.ch = '2';
			p.rem1 = '1';
			p.rem2 = '0';
		}
		p.sign = diff[p.ch] > 0 ? 1 : -1;
		printf("%d\n", max_counts);

		for (int i = 0; i < n, diff[p.ch] != 0; ++i) {
			if (pwd[i] == p.ch && p.sign < 0 && diff[p.rem1] != 0) {
				pwd[i] = p.rem1;
				diff[p.rem1]--;
				diff[p.ch]++;
			}
			if (pwd[i] == p.ch && p.sign < 0 && diff[p.rem2] != 0) {
				pwd[i] = p.rem2;
				diff[p.rem2]--;
				diff[p.ch]++;
			}
			if (pwd[i] == p.rem1 && p.sign > 0 && diff[p.rem1] != 0) {
				pwd[i] = p.ch;
				diff[p.rem1]++;
				diff[p.ch]--;
			}
			if (pwd[i] == p.rem2 && p.sign > 0 && diff[p.rem2] != 0) {
				pwd[i] = p.ch;
				diff[p.rem2]++;
				diff[p.ch]--;
			}
		}

		for (int i = 0; i < n; ++i) printf("%c", pwd[i]);
	}
	

	return 0;
}