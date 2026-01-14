#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e6+9;

int a[N],bel[N],c[N],lim,n,k;
inline bool Check(int m){
    for(int i=0;i<(1<<n);i++) c[i]=0;
    for(int i=1;i<=m;i++) c[bel[i]]++;
    for(int k=0;k<n;k++) for(int i=0;i<(1<<n);i++) if(~i>>k&1) c[i]+=c[i|(1<<k)];
    for(int i=0;i<(1<<n);i++) if(k*__builtin_popcount(i)>m-c[i]) return 0;
    return 1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];

    lim=2*n*k;
    for(int i=1;i<=lim;i++) for(int j=1;j<=n;j++) if((i-1)/a[j]&1) bel[i]|=1<<j-1;

    int l=0,r=lim;
    while(l+1<r){
        int mid=l+r>>1;
        if(Check(mid)) r=mid;
        else l=mid;
    }
    cout<<r<<endl;

    return 0;
}