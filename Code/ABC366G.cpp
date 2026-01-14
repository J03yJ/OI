#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=6e1+9;

int a[N][N],ans[N],n,m;

signed main(){
    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++) cin>>x>>y,a[x][y]^=1,a[y][x]^=1;

    for(int i=1;i<=n;i++){
        if(!a[i][i]){
            for(int j=i+1;j<=n;j++){
                if(a[j][i]){
                    swap(a[i],a[j]);
                    break ;
                }
            }
        }
        if(!a[i][i]) continue ;
        for(int j=i+1;j<=n;j++){
            if(a[j][i]) for(int k=1;k<=n;k++) a[j][k]^=a[i][k];
        }
    }
    for(int i=n;i>=1;i--){
        if(!a[i][i]){
            ans[i]=(1ll<<i)-1;
            continue ;
        }
        ans[i]=0;
        for(int j=i+1;j<=n;j++) if(a[i][j]) ans[i]^=ans[j];
        if(!ans[i]){
            cout<<"No"<<endl;
            return 0;
        }
    }
    cout<<"Yes"<<endl;
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    cout<<endl;

    return 0;
}