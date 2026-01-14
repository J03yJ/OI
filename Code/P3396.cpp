#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=3e5+9;
const int B=4e2+9;

int ans[B+9][B+9],a[N];

signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        for(int j=1;j<=B&&j<=n;j++){
            ans[j][i%j]+=a[i];
        }
    }
    while(m--){
        char op;int x,y;
        cin>>op>>x>>y;
        if(op=='A'){
            if(x<=B) cout<<ans[x][y]<<endl;
            else{
                int ans=0;
                for(int pos=y;pos<=n;pos+=x) ans+=a[pos];
                cout<<ans<<endl;
            }
        }else if(op=='C'){
            for(int i=1;i<=B&&i<=n;i++){
                ans[i][x%i]+=y-a[x];
            }
            a[x]=y;
        }
    }
    return 0;
}