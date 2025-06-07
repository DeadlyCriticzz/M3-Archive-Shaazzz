#include <bits/stdc++.h>

using namespace std;

int delta = 10007;

signed main(){
    vector<int> v = {2, 3, 5, 9, 8, 7, 10, 1, 4, 6};
    int n = v.size();
    for(int i = 0; i < n; i++){
        v[i]--;
    }
    long long ans = 1;
    for(int i = 0; i < n; i++){
        bool bl = 1;
        int c = 0;
        int x = i;
        do{
            c++;
            x = v[x];
            if(x < i) bl = 0;
        }while(x != i);
        if(bl) (ans *= (1 << c) - c) %= delta;
    }
    cout << ans << '\n';
}