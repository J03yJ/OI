#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e1+9;
const int S=(1<<20)+9;

int f[N<<2][S],n,q;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>q>>n;

    f[0][0]=1;
    for(int i=1,msk=0;i<=3*n;i++){
        msk^=1<<(i-1)%n;
        for(int sta=0;sta<(1<<n);sta++){
            for(int j=1,x=msk;j<=n;j++,x=((x<<1)|(x>>n-1&1))&(1<<n)-1){
                f[i][sta]|=f[i-1][sta^x];
            }
        }
    }

    while(q--){
        int a=0,b=0;
        for(int i=1;i<=n;i++){
            char c;
            cin>>c;
            a|=(c=='1')<<i-1;
        }
        for(int i=1;i<=n;i++){
            char c;
            cin>>c;
            b|=(c=='1')<<i-1;
        }

        if(!a) cout<<0<<endl;
        else{
            for(int i=1;i<=3*n;i++){
                a^=b;
                if(f[i][a]){
                    cout<<i<<endl;
                    break ;
                }
                b=((b<<1)|(b>>n-1&1))&(1<<n)-1;
            }
        }
        
    }

    return 0;
}