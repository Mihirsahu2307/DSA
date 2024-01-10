#include <bits/stdc++.h>
#define int long long
#define endl "\n"

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("output.txt", "r", stdin);
        freopen("validate.txt", "w", stdout);
    #endif

    int T = 1;
    // cin >> T;
    for(int t = 1; t < T + 1; t ++) {
        int n;
        // cin >> n;
        const int N = 8;
        // int a[N] = {1, 4, 9, 2, 5};
        for(int i = 0; i < 100; i ++) {
            int x, y;
            cin >> x >> y;
            if(x != y) {
                cout << x << ' ' << y << endl;
                cout << i << endl;
            }
        }

        // for(int i = 0; i < N; i ++) {
        //     cout << a[i] << ' ';
        // }
        // cout << endl;
    }

    return 0; 
}