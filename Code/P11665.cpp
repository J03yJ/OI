#include<bits/stdc++.h>

using namespace std;

const int N=5e6+9;

int a[N],f[N],n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    int ans=21;
    for(int sta=0;sta<(1<<21);sta++){
        while(f[sta]<n-1&&(sta>>a[f[sta]+1]-1&1|sta>>a[f[sta]+2]-1&1)) f[sta]++;
        if(f[sta]>=n-1) ans=min(ans,__builtin_popcount(sta));
        for(int i=0;i<21;i++){
            if(sta>>i&1) continue ;
            int tta=sta|1<<i;
            if(i&&(tta>>i-1&1)) tta^=1<<i-1;
            f[tta]=max(f[tta],f[sta]);
        }
    }

    cout<<ans<<endl;

    return 0;
}