#include<bits/stdc++.h>

using namespace std;

#define int long long
#define Allc(x) x.begin(),x.end()
void Solve(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];

    int m=n>>1,sum0=0,sum1=0;
    for(int i=0;i<m;i++) sum0+=a[i];
    for(int i=m;i<n;i++) sum1+=a[i];
    vector<vector<int>> c(m+1);
    for(int sta=0;sta<(1<<m);sta++){
        int sum=0;
        for(int i=0;i<m;i++) if(sta>>i&1) sum+=a[i];
        sum=sum0-sum-sum;
        // cout<<sta<<' '<<sum<<endl;
        c[__builtin_popcount(sta)].push_back(sum);
    }
    for(int i=0;i<=m;i++){
        c[i].push_back(-1e18);
        c[i].push_back(1e18);
        sort(Allc(c[i]));
    }
    int ans=1e18;
    for(int sta=0;sta<(1<<n-m);sta++){
        if(n%2&&!sta) continue ;
        int cnt=__builtin_popcount(sta);
        int sum=0;
        for(int i=0;i<n-m;i++) if(sta>>i&1) sum+=a[i+m];
        sum=sum1-sum-sum;
        // cout<<sta<<' '<<sum<<' '<<n-m-cnt<<endl;
        int pos=lower_bound(Allc(c[n-m-cnt]),-sum)-c[n-m-cnt].begin();
        ans=min(ans,min(abs(c[n-m-cnt][pos]+sum),abs(c[n-m-cnt][pos-1]+sum)));
    }
    cout<<ans<<endl;
}

signed main(){
    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}