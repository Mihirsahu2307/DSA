#include <bits/stdc++.h>
using namespace std;
#define fo(a, b, c) for(int(a) = (b); (a) < (c); (a)++)

// RMQ with sparse table, use it to answer queries when update is not required
// Copy the build and query functions and set the size of table as (n, log2(n))

int table[500][500];

void build(int a[], int n) {
	fo(i, 0, n) {
		table[i][0] = a[i];
	}

	for(int j = 1; (1 << j) <= n; j ++) {
		fo(i, 0, n) {
			int in = (i + (1 << j) - 1);
			if(in >= n)
				break;
			int index = i + (1 << (j - 1));
			table[i][j] = max(table[i][j - 1], table[index][j - 1]);	// change
		}
	}
}

int query(int l, int r) {
	int length = r - l + 1;
	int j = (int) log2(length);

	return max(table[l][j], table[r - (1 << j) + 1][j]);	// change
}

int main() {

	#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

	int a[] = { 7, 2, 3, 0, 5, 10, 3, 12, 18 };
    int n = sizeof(a) / sizeof(a[0]);
    build(a, n);
    cout << query(0, 4) << endl;
    cout << query(5, 7) << endl;
    cout << query(7, 8) << endl;
	return 0;
}