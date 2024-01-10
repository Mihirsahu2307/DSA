#include <bits/stdc++.h>
#define endl "\n"

using namespace std;

int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "w", stdout);
        freopen("output.txt", "r", stdin);
    #endif

    int t = 10;
    cout << t << endl;

    for(int i = 0; i < t; i ++) {
        int n, m, a, b, c, d;
        n = random(10, 20);
        // m = random(3, 7);
        int l = 1, r = 100;
        // c = random(1, n), d = random(1, n);

        cout << n << endl;
        // cout << n << ' ' << m << endl;
        for(int i = 0; i < n; i ++)
            std::cout << random(l, r) << ' ';
        cout << endl;
    }

    return 0; 
}