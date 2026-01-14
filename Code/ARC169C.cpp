#include<bits/stdc++.h>

using namespace std;

const int N=5e3+9;
const int mod=998244353;

int a[N],f[N][N],c[N][N],sum[N],n;
int MergeC(int x,int y){
    if(x==-1||y==-1) return x&y;
    else if(x==y) return x;
    else return 0;
}
int Check(int l,int r,int k){
    if(c[l][r]==k||c[l][r]==-1) return 1;
    else return 0;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++){
        c[i][i]=a[i];
        for(int j=i+1;j<=n;j++) c[i][j]=MergeC(c[i][j-1],a[j]);
    }
    sum[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i]==j||a[i]==-1){
                f[i][j]=sum[i-1];
                if(i>j&&Check(i-j,i,j)){
                    f[i][j]=(f[i][j]-sum[i-j-1]+mod)%mod;
                    f[i][j]=(f[i][j]+f[i-j-1][j])%mod;
                }
            }
        }
        for(int j=1;j<=n;j++) sum[i]=(sum[i]+f[i][j])%mod;
    }

    cout<<sum[n]<<endl;

    return 0;
}