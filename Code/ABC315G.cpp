#include<bits/stdc++.h>

using namespace std;

#define allc(x) x.begin(),x.end()
#define int long long

map<int,vector<int>[2]> mp;

signed main(){
    int n,a,b,c,m,ans=0;
    cin>>n>>a>>b>>c>>m;
    
    for(int i=1;i<=n;i++){
        mp[i*a%b][0].push_back(i*a+b);
        mp[i*a%b][1].push_back(i*a+n*b+1);
    }
    for(int i=1;i<=n;i++){
        int k=m-i*c;
        if(k<=0) break ;
        auto &v=mp[k%b];
        ans+=upper_bound(allc(v[0]),k)-v[0].begin();
        ans-=upper_bound(allc(v[1]),k)-v[1].begin();
    }
    cout<<ans<<endl;

    return 0;
}