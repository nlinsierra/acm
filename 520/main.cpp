#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX_COUNT 1002

struct City {
	int fire;
	int state;
};

int g[MAX_COUNT][MAX_COUNT];
City c[MAX_COUNT];

vector<int> SetFired(int n, vector<int> fired) {
	vector<int> res;
	for (int i = 0; i < fired.size(); ++i)
		for (int j = 1; j <= n; ++j) {
			if (g[fired[i]][j] == 1 && c[j].fire == 0) {
				c[j].fire = 1;
				res.push_back(j);
			}
		}
	return res;
}

void SetUnfired(vector<int> fired) {
	for (int i = 0; i< fired.size(); ++i) {
		c[fired[i]].fire = 0;
	}
}

int doAll(int cur_city, int n, vector<int> all_fired) {
	if (c[cur_city].state != -1) return c[cur_city].state;
	vector<int> fired;
	for (int i = 1; i <= n; ++i) {
		if (g[cur_city][i] == 1 && c[i].fire != 1) {
			fired = SetFired(n, all_fired);
			int res = doAll(i, n, fired);
			SetUnfired(fired);
			if (res == 0) {
				c[cur_city].state = 1;
				return 1;			
			}
		}
	}
	c[cur_city].state = 0;
	return 0;	
}

int main() {
	int n = 0, m = 0;
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	vector<int> fired;

	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int c1, c2;
		cin >> c1 >> c2;
		g[c1][c2] = g[c2][c1] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		c[i].fire = 0;
		c[i].state = -1;
	}
	c[1].fire = 1;
	fired.push_back(1);
	if (doAll(1, n, fired) == 0) cout << "Nikolay" << endl;
	else cout << "Vladimir" << endl;

	return 0;
}