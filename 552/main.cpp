#include <iostream>
#include <map>

using namespace std;

#define MAXLEN 12
#define P 91
#define SPACE 32

map<long long, int> counts;
int n = 0, m = 0;

long long powers[MAXLEN*4];

struct HashDescr {
	long long hash;
	long long len;
};

void get_powers() {
	long long pw = 1;
	for (int i = 0; i < MAXLEN*4; ++i) {
		powers[i] = pw;
		pw *= P;
	}
}

int cmp(const void* d1, const void* d2) {
	if (((HashDescr*)d1)->hash == ((HashDescr*)d2)->hash) return 0;
	return ((HashDescr*)d1)->hash > ((HashDescr*)d2)->hash;
}

HashDescr get_hash(char s[]) {
	HashDescr res;
	res.len = strlen(s);
	long long h = 0;
	for (int i = 0; i < res.len; ++i) h += (s[i] - SPACE + 1)*powers[i];
	res.hash = h;	
	return res;
}

void calc_hashes(HashDescr h[], int ki) {	
	// For key-value count = 1
	for (int i = 0; i < ki; ++i) counts[h[i].hash]++;
	
	// For key-value count = 2
	for (int i = 0; i < ki - 1; ++i) for (int j = i + 1; j < ki; ++j) {
		long long cur_h = h[i].hash + 1*powers[h[i].len] + h[j].hash*powers[h[i].len + 1];
		counts[cur_h]++;
	}
	
	// For key-value count = 3
	for (int i = 0; i < ki - 1; ++i) for (int j = i + 1; j < ki - 1; ++j) for (int k = j + 1; k < ki; ++k) {
		long long cur_h = 
			h[i].hash + 1*powers[h[i].len] + 
			h[j].hash*powers[h[i].len + 1] + 1*powers[h[i].len + h[j].len + 1] + 
			h[k].hash*powers[h[i].len + h[j].len + 2];
		counts[cur_h]++;
	}
	
	// For key-value count = 4
	if (ki == 4) {
		long long cur_h = h[0].hash + 1*powers[h[0].len] + 
			h[1].hash*powers[h[0].len + 1] + 1*powers[h[0].len + h[1].len + 1] +
			h[2].hash*powers[h[0].len + h[1].len + 2] + 1*powers[h[0].len + h[1].len + h[2].len + 2] +
			h[3].hash*powers[h[0].len + h[1].len + h[2].len + 3];
		counts[cur_h]++;
	}	
}


long long calc_qhash(HashDescr h[], int ki) {
	switch (ki) {
	case 1: return h[0].hash;
	case 2: return h[0].hash + 1*powers[h[0].len] + h[1].hash*powers[h[0].len + 1];
	case 3: return h[0].hash + 1*powers[h[0].len] + h[1].hash*powers[h[0].len + 1] + 1*powers[h[0].len + h[1].len + 1] + h[2].hash*powers[h[0].len + h[1].len + 2];
	case 4: return h[0].hash + 1*powers[h[0].len] + 
			h[1].hash*powers[h[0].len + 1] + 1*powers[h[0].len + h[1].len + 1] +
			h[2].hash*powers[h[0].len + h[1].len + 2] + 1*powers[h[0].len + h[1].len + h[2].len + 2] + 
			h[3].hash*powers[h[0].len + h[1].len + h[2].len + 3];		
	}	
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
	get_powers();

	scanf("%d\n", &n);
	for (int i = 0; i < n; ++i) {
		int ki = 0;
		scanf("%d ", &ki);
		HashDescr *hashes = new HashDescr[ki];
		for (int k = 0; k < ki; ++k) {
			char *str = new char[MAXLEN];
			scanf("%s", str);
			hashes[k] = get_hash(str);
			delete [] str;
		}
		qsort(hashes, ki, sizeof(HashDescr), cmp);
		calc_hashes(hashes, ki);
		delete [] hashes;
	}

	scanf("%d\n", &m);
	for (int i = 0; i < m; ++i) {
		int li = 0;
		scanf("%d ", &li);
		HashDescr *hashes = new HashDescr[li];
		for (int l = 0; l < li; ++l) {
			char *str = new char[MAXLEN];
			scanf("%s", str);
			hashes[l] = get_hash(str);
			delete [] str;
		}
		qsort(hashes, li, sizeof(HashDescr), cmp);
		long long qhash = calc_qhash(hashes, li);
		delete [] hashes;
		printf("%d\n", counts[qhash]);		
	}
	return 0;
}