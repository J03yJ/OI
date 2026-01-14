#include<bits/stdc++.h>

using namespace std;

const int N=1e2+9;

long long a[N],f[N][N],g[N][N];

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) f[i][i]=g[i][i]=1;
        for(int len=2;len<=n;len++){
            for(int i=1;i<=n-len+1;i++){
                int j=i+len-1;
                if(a[j]<g[i+1][j]) f[i][j]=1;
                else f[i][j]=f[i][j-1]-g[i+1][j]+a[j]+1;
                if(a[i]<f[i][j-1]) g[i][j]=1;
                else g[i][j]=g[i+1][j]-f[i][j-1]+a[i]+1;
            }
        }
        if(f[1][n]<=a[1]) cout<<"First"<<endl;
        else cout<<"Second"<<endl;
    }
    return 0;
}