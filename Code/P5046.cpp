#include<bits/stdc++.h>

using namespace std;

const int N=8e1+9;
const int W=13;
const int M=5e3+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Add(int x,int y){AddAs(x,y);return x;}
inline int Sub(int x,int y){SubAs(x,y);return x;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

string opt;
void FWT(int *a,int lim){
    for(int k=0;(1<<k)<lim;k++){
        for(int i=0;i<lim;i++){
            if(i>>k&1) continue ;
            if(opt[k]=='&') AddAs(a[i],a[i+(1<<k)]);
            else if(opt[k]=='|') AddAs(a[i+(1<<k)],a[i]);
            else{
                int x=a[i],y=a[i+(1<<k)];
                a[i]=Add(x,y),a[i+(1<<k)]=Sub(x,y);
            }
        }
    }
}
const int inv2=mod+1>>1;
void IFWT(int *a,int lim){
    for(int k=0;(1<<k)<lim;k++){
        for(int i=0;i<lim;i++){
            if(i>>k&1) continue ;
                if(opt[k]=='&') SubAs(a[i],a[i+(1<<k)]);
            else if(opt[k]=='|') SubAs(a[i+(1<<k)],a[i]);
            else{
                int x=a[i],y=a[i+(1<<k)];
                a[i]=1ll*Add(x,y)*inv2,a[i+(1<<k)]=1ll*Sub(x,y)*inv2;
            }
        }
    }
}

int a[N][N][1<<W],r[N][N],cnt[1<<W],n,m,w;
int Det(int a[N][N],int n){
    int res=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(a[j][i]){
                swap(a[i],a[j]);
                if(j!=i) res=mod-res;
                break ;
            }
        }
        if(!a[i][i]) return 0;
        for(int j=i+1;j<=n;j++){
            int t=1ll*Inv(a[i][i])*a[j][i]%mod;
            for(int k=i;k<=n;k++) SubAs(a[j][k],1ll*a[i][k]*t%mod);
        }
    }
    for(int i=1;i<=n;i++) res=1ll*res*a[i][i]%mod;
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    
    cin>>n>>m>>opt;
    for(int i=1,u,v,x;i<=m;i++){
        cin>>u>>v>>x;
        AddAs(a[u][u][x],1);
        AddAs(a[v][v][x],1);
        SubAs(a[u][v][x],1);
        SubAs(a[v][u][x],1);
    }
    w=opt.size();

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) FWT(a[i][j],1<<w);
    }
    for(int x=0;x<(1<<w);x++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) r[i][j]=a[i][j][x];
        }
        cnt[x]=Det(r,n-1);
    }

    IFWT(cnt,1<<w);
    for(int i=(1<<w)-1;~i;i--){
        if(cnt[i]){
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;

    return 0;
}