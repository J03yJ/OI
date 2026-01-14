#include<bits/stdc++.h>

using namespace std;

#define int long long
const int P=6;
const int M=(1<<P)+1;
const int p[P]={2,3,5,7,11,13};
const int mod=998244353;
const int N=16;

int cnt[N][P],f[M][M],g[M][M],m,k;

void MulAs(int f[M][M],int g[M][M]){
    int h[M][M];
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            h[i][j]=0;
            for(int k=0;k<M;k++) h[i][j]=(h[i][j]+f[i][k]*g[k][j]%mod)%mod;
        }
    }
    memcpy(f,h,sizeof h);
}
void QPowAs(int x[M][M],int y){
    int h[M][M];
    memset(h,0,sizeof h);
    for(int i=0;i<M;i++) h[i][i]=1;
    while(y){
        if(y&1) MulAs(h,x);
        MulAs(x,x);
        y>>=1;
    }
    memcpy(x,h,sizeof h);
}

signed main(){
    cin>>k>>m;
    for(int i=1;i<=m;i++){
        int tmp=i;
        for(int j=0;j<P;j++){
            while(tmp%p[j]==0) tmp/=p[j],cnt[i][j]++;
        }
    }

    for(int i=1;i<=m;i++){
        for(int sta=0;sta<(1<<P);sta++){
            for(int tta=sta;;tta=(tta-1)&sta){
                int tmp=1;
                for(int j=0;j<P;j++) if((tta>>j)&1) tmp=tmp*cnt[i][j]%mod;
                f[sta^tta][sta]=(f[sta^tta][sta]+tmp)%mod;
                if(!tta) break ;
            }
        }
    }
    f[1<<P][1<<P]=f[(1<<P)-1][1<<P]=1;
    QPowAs(f,k);
    for(int i=0;i<(1<<P);i++) g[0][i]=1;
    MulAs(g,f);

    cout<<(g[0][1<<P]+g[0][(1<<P)-1]-1)%mod<<endl;

    return 0;
}