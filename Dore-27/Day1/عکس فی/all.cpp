// template.cpp
/*
Pragma:
If ever in doubt about whether your pragmas are correct,
turn on most compiler warnings with the command-line option -Wall(or the more specific -Wunknown-pragmas). 
use assert(__builtin_cpu_supports("avx2")) to check if intruction set is available
*/

// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
// #pragma GCC optimize("O3","unroll-loops")
// #pragma GCC optimize ("Ofast")
// __attribute__((target("avx2"), optimize("O3", "unroll-loops")))
// #pragma GCC optimize ("trapv") // kills the program on integer overﬂows (but is really slow).
#include    <bits/stdc++.h>

#pragma GCC optimize("no-stack-protector,fast-math")
#pragma GCC target("avx2,bmi,bmi2")
#pragma GCC optimize ("O2,unroll-loops")
// #pragma GCC target("sse4") // instead of avx2
#define     wall                {cout << "\n___________________" << endl;}
#define     oo                  (1000'000'000'000'000'000LL)
#define     cif(i, n)           for(int i = 0; i < n; i++)
#define     ccif(i, l, r)       for(int i = l; i < r; i++)
#define     rif(i, n)           for(int i = n-1; i >= 0; i--)
#define     rrif(i, l, r)       for(int i = r-1; i >= l; i--)
#define     scan(a, __n)        {for(int __ = 0; __ < __n; __++)cin >> a[__];}
#define     print(a, __n)       {for(int __ = 0; __ < __n; __++)cout << a[__] << ' '; cout << '\n';}
#define     sz(s)               ((int)s.size())
#define     dbg(x)              cerr << #x << " : " << x << endl;
#define     rep(i, l, r)        for(int i = l; i < r; i++)
// #define     mset(a, chr)        memset(a, chr, sizeof a)
#define     mset(a)             memset(a, 0, sizeof a)
#define     int                 ll

#define     fastIO              ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define     ff                  first
#define     ss                  second

#define     all(v)              v.begin(), v.end()
#define     uni(v)              sort(all(v)), v.resize(unique(all(v))-v.begin())

// #define     c0                  (v<<1)
// #define     c1                  (c0|1)
// #define     md                  ((l+r)/2)

using       namespace           std;

typedef     unsigned long long  ull;
typedef     long long           ll;
typedef     long double         ld;
typedef     pair<int, int>      pii;
typedef     pair<ll, ll>        pll;
typedef     vector<int>         vi;
typedef     vector<ll>          vl;
typedef     vector<pii>         vii;
typedef     vector<pll>         vll;
typedef     vector<ld>          vd;
typedef     pair<ld, ld>        pt;
typedef     vector<pt>          vpt;

ostream& operator<<(ostream& os, pt p) {return os << "(" << p.ff << "," << p.ss << ")"; }


/*****                                                             *****/


const ld PI = 3.14159265359;

// const int maxFac = 1e6+7; 
// ll fac[maxFac], _fac[maxFac];

// ll po(ll b, ll p){
//     b %= delta;
//     p %= delta-1;
//     ll r = 1;
//     while(p){
//         if(p&1)r = r*b%delta;
//         p >>= 1;
//         b = b*b%delta;
//     }
//     return r;
// }

// ll choose(ll k, ll n){
//     return fac[n]*_fac[k]%delta*_fac[n-k]%delta;
// }

// ll factorial(ll n, ll k){
//     ll ret = 1;
//     for(ll i = n; i >= n-k+1; i--){
//         ret = ret*i%delta;
//     }
//     return ret;
// }

// vii adj = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 delta) {
    u64 result = 1;
    base %= delta;
    while (e) {
        if (e & 1)
            result = (u128)result * base % delta;
        base = (u128)base * base % delta;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};


bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

const ll n = 2350194604833600LL;
// const ll n = 1ll << 50;
// const ll n = 60;
const int maxN = 1e6+7;
const int delta = 10067;

vector<pii> fact = {{2, 6}, {3, 2}, {5, 2}, {7, 1}, {17, 3}, {23, 2}, {8971, 1}};
// vector<pii> fact = {{2, 50}};
// vector<pii> fact = {{2, 2}, {3, 1}, {5, 1}};

ll cal(vi p){
    ll x = 1;
    cif(i, sz(fact)){
        // assert(p[i] >= 0 && p[i] <= fact[i].ss);
        cif(j, p[i]) x *= fact[i].ff;
    }
    return x;
}

vi fz(ll x){
    vi a(sz(fact));
    cif(i, sz(fact)){
        while(x % fact[i].ff == 0) x /= fact[i].ff, a[i]++;
    }
    if(x != 1) a[0] = 100;
    return a;
}

vector<vi> divs;
vector<pair<vi, vi>> pdiv;
int tim;

map<pair<ll, vl>, vl> mp;

vl f(int ind, vi po){
    vi pip = po;
    if(mp.count({ind, pip}) > 0) return mp[{ind, pip}];
    if(*max_element(all(po)) == 0) return {1};
    if(ind == sz(pdiv)) return {};
    if(tim++%10000 == 0){
        cout << ind << "*=" << cal(pdiv[ind].ff) << " "; print(po, sz(po));
    }
    auto [pw, pw2] = pdiv[ind];
    int kk = 100;
    vl ret = f(ind+1, po);
    cif(i, sz(po)) {
        if(po[i] < pw[i]) return ret;
        if(pw2[i]) kk = min(kk, po[i] / pw2[i]);
    }
    // cout << ind << "=" << cal(pdiv[ind].ff) << " " << kk << " :"; print(po, sz(po));
    ll q = (cal(pw)+1);
    ll r = q%delta;
    cif(i, sz(po)) po[i] -= pw[i];
    // cout << "QQ";
    auto qq = f(ind+1, po);
    for(auto x : qq) ret.push_back(x*r%delta);
    
    cif(i, kk){
        r = r * q %delta;
        cif(i, sz(po)) po[i] -= pw2[i];
        auto qq = f(ind+1, po);
        for(auto x : qq) ret.push_back(x*r%delta);
    }
    return mp[{ind, pip}] = ret;
}
vi phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i - 1;

    for (int i = 2; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
              phi[j] -= phi[i];
    return phi;
}

inline void slv(){
    vi po(sz(fact));
    while(po[0] <= fact[0].ss){
        divs.push_back(po);
        if(MillerRabin(cal(po) + 1)){
            pdiv.push_back({po, fz(cal(po) + 1)});
        }
        po[sz(fact)-1]++;
        rrif(i, 1, sz(fact)){
            if(po[i] > fact[i].ss) po[i] = 0, po[i-1]++;
            else break;
        }
    }
    // for(auto p : divs) cout << cal(p) << ' ';
    // wall
    // for(auto p : pdiv) cout << cal(p.ff) << ' ';
    // wall
    // for(auto p : pdiv) if(p.ss[0] < 100) cout << cal(p.ff) << ' ';
    // wall
    // for(auto x : divs) print(x, sz(x));
    // wall

    sort(all(pdiv));
    cif(i, sz(po)) po[i] = fact[i].ss;
    auto ret = f(0, po);
    ll ans = 0;
    
    // for(auto x : ret) cout << x << ' ';
    // cout << '\n';
    for(auto x : ret) (ans += x%delta*(x % delta)) %= delta;
    cout << ans << '\n';

    // vi phis = phi_1_to_n(100000);

    // for(auto x : ret){
    //     cout << phis[x] << ' ';
    // }
    cout << '\n';
    
    // ccif(i, 1, 10000){
    //     if(phis[i] == n){
    //         cout << i << ' ';
    //     }
    // }
    // cout << '\n';
}


/*
3024 divisors
*/

inline void prep(){
    
    // fac[0] = 1;
    // for(int i = 1; i < maxFac; i++)fac[i] = 1ll*fac[i-1]*i%delta;
    // _fac[maxFac-1] = po(fac[maxFac-1], delta-2);
    // for(int i = maxFac-2; i >= 0; i--)_fac[i] = 1ll*_fac[i+1]*(i+1)%delta;

    // w[0] = 1;
    // for(int i = 1; i < maxN; i++)w[i] = 1ll*w[i-1]*p%delta;
    // _w[maxN-1] = po(w[maxN-1], delta-2);
    // for(int i = maxN-2; i >= 0; i--)_w[i] = 1ll*_w[i+1]*p%delta;
    
    // for(int i = 2; i < maxN; i++){
    //     if(lp[i] == 0){
    //         lp[i] = i;
    //         pr.push_back(i);
    //     }
    //     for (int j = 0; i * pr[j] < maxN; ++j) {
    //         lp[i * pr[j]] = pr[j];
    //         if (pr[j] == lp[i]) {
    //             break;
    //         }
    //     }
    // }
}

signed main(){
    // freopen("inp.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    fastIO;

    // cout << fixed << setprecision (15);

    prep();
    
    int t = 1;
    // cin >> t;
    while(t--){
        // cout << slv() << '\n';
        slv();
        // string s;
        // cin >> s;
        // bool x = slv();
        // cout << (x?"YES":"NO") << '\n';
    }
    cout.flush();
}

/*

*/