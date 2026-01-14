#include<bits/stdc++.h>

using namespace std;

const int N=1e2+9;
const int M=5e2+9;
const int K=10;

int f[N][1<<K],p[N],n,m,k;
int fi[N],ne[M<<1],to[M<<1],w[M<<1],adj;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int inq[N];
void SPFA(int sta){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(f[i][sta]==0x3f3f3f3f) continue ;
        q.push(i),inq[i]=1;
    }
    while(q.size()){
        int x=q.front();
        q.pop(),inq[x]=0;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(f[x][sta]+w[i]<f[y][sta]){
                f[y][sta]=f[x][sta]+w[i];
                if(!inq[y]) q.push(y),inq[y]=1;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>k;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        AdEg(u,v,w),AdEg(v,u,w);
    }
    for(int i=1;i<=k;i++) cin>>p[i];

    memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++) f[i][0]=0;
    for(int i=1;i<=k;i++) f[p[i]][1<<i-1]=0;
    for(int sta=0;sta<(1<<k);sta++){
        for(int tta=sta;tta;tta=(tta-1)&sta){
            for(int i=1;i<=n;i++) f[i][sta]=min(f[i][sta],f[i][tta]+f[i][sta^tta]);
        }
        SPFA(sta);
    }

    int ans=0x3f3f3f3f;
    for(int i=1;i<=n;i++) ans=min(ans,f[i][(1<<k)-1]);
    cout<<ans<<endl;

    return 0;
}