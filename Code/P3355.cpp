#include<bits/stdc++.h>

using namespace std;

const int N=2e2+9;
const int M=4e4+9;
const int inf=2e9;

int n,m,a[N][N];

int fi[M],to[M<<4],ne[M<<4],w[M<<4],adj=1;
void adeg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
inline int trs(int i,int j){
    return (i-1)*n+j;
}
int dx[8]={2,1,2,-1,1,-2,-1,-2};
int dy[8]={1,2,-1,2,-2,1,-2,-1};

int lev[M<<4],cur[M];
bool bfs(int s,int t){
    for(int i=1;i<=t;i++) lev[i]=0,cur[i]=fi[i];lev[s]=1;
    queue<int> q;
    q.push(s);
    while(q.size()){
        int x=q.front();
        q.pop();
        if(x==t) return 1;
        for(int i=fi[x];i;i=ne[i]){
            if(!w[i]) continue ;
            int y=to[i];
            if(!lev[y]){
                lev[y]=lev[x]+1;
                q.push(y);
            }
        }
    }
    return 0;
}
int dfs(int x,int mn,int t){
    // cout<<x<<' '<<mn<<' '<<t<<endl;
    if(x==t) return mn;
    int k=mn;
    for(int i=cur[x];i;i=ne[i]){
        cur[x]=i;
        if(!w[i]) continue ;
        int y=to[i];
        if(lev[y]!=lev[x]+1) continue ;
        int tmp=dfs(y,min(k,w[i]),t);
        k-=tmp;
        w[i]-=tmp;
        w[i^1]+=tmp;
        if(!k) return mn;
    }
    return mn-k;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        a[x][y]=1;
    }

    int s=n*n+1,t=n*n+2;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]) continue ;
            if((i+j)%2){
                adeg(s,trs(i,j),1),adeg(trs(i,j),s,0);
                for(int k=0;k<8;k++){
                    int x=i+dx[k],y=j+dy[k];
                    if(a[x][y]) continue ;
                    if(x<1||y<1||x>n||y>n) continue ;
                    adeg(trs(i,j),trs(x,y),inf);
                    adeg(trs(x,y),trs(i,j),0);
                }
            }else adeg(trs(i,j),t,1),adeg(t,trs(i,j),0);
        }
    }

    int sum=0;
    while(bfs(s,t)){
        sum+=dfs(s,inf,t);
        // cout<<sum<<endl;
    }

    cout<<n*n-m-sum<<endl;

    return 0;
}