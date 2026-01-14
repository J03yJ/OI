#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;

int a[N],b[N],w[N],p[N],q[N],r[N],n;
inline bool Check(int k){
    ll sum=0,res=0;
    for(int i=1;i<=n;i++) sum+=w[i];
    iota(p+1,p+n+1,1);
    sort(p+1,p+n+1,[](int i,int j){return w[i]>w[j];});
    iota(r+1,r+n+1,1);
    sort(r+k+1,r+n+1,[](int i,int j){return b[i]>b[j];});
    set<int> s(a+1,a+n+1);
    for(int i=1,j=k;i<=n;i++){
        int cur=p[i]<=k?b[p[i]]:b[r[++j]];
        if(s.upper_bound(cur)!=s.end()){
            s.erase(s.upper_bound(cur));
            res+=w[p[i]];
        }
    }
    return res*2>sum;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++) cin>>a[i];

    int l=-1,r=n+1;
    while(l+1<r){
        int mid=l+r>>1;
        if(Check(mid)) r=mid;
        else l=mid;
    }
    cout<<(r<=n?r:-1)<<endl;

    return 0;
}