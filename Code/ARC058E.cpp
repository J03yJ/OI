#include<bits/stdc++.h>

using namespace std;

const int N=4e1+9;
const int mod=1e9+7;
void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}

int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}

int f[N][1<<17],n,x,y,z;

int main(){
    cin>>n>>x>>y>>z;

    int ng=((1<<x|1)<<y|1)<<z-1,mask=(1<<x+y+z)-1;
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int sta=0;sta<=mask;sta++){
            for(int k=0;k<10;k++) AddAs(f[i][((sta<<k+1)|(1<<k))&mask],f[i-1][sta]);
        }
        for(int sta=0;sta<=mask;sta++) f[i][sta|ng]=0;
    }

    int sum=0;
    for(int sta=0;sta<=mask;sta++) AddAs(sum,f[n][sta]);
    cout<<(QPow(10,n)-sum+mod)%mod<<endl;

    return 0;
}