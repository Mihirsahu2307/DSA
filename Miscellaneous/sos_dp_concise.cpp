#include <bits/stdc++.h>
#define int long long
#define endl "\n"

using namespace std;

// Problem: https://cses.fi/problemset/task/1654

const int N = 2e6 + 5, B = 20;
int dp1[N], dp2[N], cnt[N], a[N];

int flip(int n) {
    int mask = (1 << B) - 1;
    return (unsigned) (mask & (~n));
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif


    // cout << (1 << 20) << endl;
    // cout <<(int) 1e6 + 5 << endl;

    int T = 1;
    // cin >> T;
    for (int t = 1; t < T + 1; t ++) {
        int n;
        cin >> n;
        for (int i  = 0 ; i < n; i ++) {
            cin >> a[i];
            cnt[a[i]] ++;
        }
        for (int mask = 0; mask < N; mask ++) {
            dp1[mask] += cnt[mask];
            dp2[mask] += cnt[mask];
        }

        // In the above loop, we are not handling the lsb case. We handle it all here:
        for (int i = 0; i < B; i ++) {
            for (int mask = N - 1; mask >= 0; mask --) {
                if (mask & (1 << i)) {
                    dp1[mask] += dp1[(mask ^ (1 << i))];
                }
            }
            for (int mask = 0; mask < N; mask ++) {
                if ((mask & (1 << i)) == 0) {
                    dp2[mask] += dp2[mask ^ (1 << i)];
                }
            }
        }

        for (int i = 0; i < n; i ++) {
            cout << dp1[a[i]] << ' ' << dp2[a[i]] << ' ' << n - dp1[flip(a[i])] << endl;
        }
    }

    return 0;
}