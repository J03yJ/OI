#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,m,k;
        cin>>n>>k>>m;
        
        int p=0,q=1,ans=2e18;
        while(q<m) p++,q*=k,q++;
        for(;p<=n;p++,q=q*k+1){
            int tmp=q-m,res=(p!=n);
            for(int i=p,pw=q;~i;i--,pw/=k){
                int j=tmp/pw;
                tmp-=j*pw;
                res+=j;
            }
            ans=min(ans,res);
        }

        cout<<ans<<endl;
    }

    return 0;
}