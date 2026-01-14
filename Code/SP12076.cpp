#include<bits/stdc++.h>

using namespace std;

using ull=unsigned long long;

template<int N> struct Bitset{
    ull a[N];
    inline ull& operator [](int x){return a[x];}
    inline Bitset operator &(Bitset b){
        Bitset c;
        for(int i=0;i<N;i++) c[i]=a[i]&b[i];
        return c;
    }
    inline Bitset operator ^(Bitset b){
        Bitset c;
        for(int i=0;i<N;i++) c[i]=a[i]^b[i];
        return c;
    }
    inline Bitset operator |(Bitset b){
        Bitset c;
        for(int i=0;i<N;i++) c[i]=a[i]|b[i];
        return c;
    }
    inline Bitset operator -(Bitset b){
        Bitset c;
        ull lst=0;
        for(int i=0;i<N;i++){
            c[i]=a[i]-b[i]-lst;
            lst=(a[i]<b[i])||(a[i]==b[i]&&lst);
        }
        return c;
    }
    inline void Set(int pos){a[pos>>6]|=1ull<<(pos&63);}
    inline int PopCount(){
        int ans=0;
        for(int i=0;i<N;i++) ans+=__builtin_popcountll(a[i]);
        return ans;
    }
};
template<int N> Bitset<N> Shift(Bitset<N> a){
    Bitset<N> b;
    ull lst=1;
    for(int i=0;i<N;i++){
        b[i]=a[i]<<1|lst;
        lst=a[i]>>63&1;
    }
    return b;
}

#define endl '\n'
const int N=5e4+9;
const int M=(N>>6)+9;

string s,t;
Bitset<M> f[N],g[N],occ[26];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>s>>t;
    int n=s.size(),m=t.size();
    s.insert(s.begin(),' ');
    t.insert(t.begin(),' ');
    for(int i=1;i<=n;i++) occ[s[i]-'a'].Set(i);
    
    for(int i=1;i<=m;i++){
        g[i]=f[i-1]|occ[t[i]-'a'];
        f[i]=g[i]&(g[i]^(g[i]-Shift(f[i-1])));
    }
    cout<<f[m].PopCount()<<endl;

    return 0;
}