#include<bits/stdc++.h>

using namespace std;

const int N=3e2+9;
const int inf=1e9+7;

int a[N][N],c[N][N],col[N][N],n,m,k;
int w[N][N],f[N][N][1<<5],p[N*N],r[N*N],tot;
vector<int> val;

mt19937 rng(4649);
bool inq[N][N];
const int dx[4]={0,-1,0,1};
const int dy[4]={-1,0,1,0};
void SPFA(int sta){
    queue<pair<int,int>> q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!~col[i][j]) continue ;
            if(f[i][j][sta]>(inf>>1)) continue ;
            q.push({i,j}),inq[i][j]=1;
        }
    }
    while(q.size()){
        int x=q.front().first,y=q.front().second;
        q.pop(),inq[x][y]=0;
        for(int o:{0,1,2,3}){
            int xx=x+dx[o],yy=y+dy[o];
            if(xx<1||yy<1||xx>n||yy>m) continue ;
            if(!~col[xx][yy]) continue ;
            if(f[x][y][sta]+w[xx][yy]<f[xx][yy][sta]){
                f[xx][yy][sta]=f[x][y][sta]+w[xx][yy];
                if(!inq[xx][yy]) q.push({xx,yy}),inq[xx][yy]=1;
            }
        }
    }
}
int Check(int v,int base){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) w[i][j]=base+(a[i][j]>v?1:-1);
    }
    int T=200,ans=inf;
    while(T--){
        shuffle(p+1,p+tot+1,rng);
        for(int i=1;i<=tot;i++) r[p[i]]=i%k;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                col[i][j]=~c[i][j]?r[c[i][j]]:-1;
                for(int sta=0;sta<(1<<k);sta++) f[i][j][sta]=inf;
                if(~col[i][j]) f[i][j][1<<col[i][j]]=w[i][j];
            }
        }
        for(int sta=0;sta<(1<<k);sta++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    for(int tta=(sta-1)&sta;tta;tta=(tta-1)&sta){
                        f[i][j][sta]=min(f[i][j][sta],f[i][j][tta]+f[i][j][sta^tta]-w[i][j]);
                    }
                }
            }
            SPFA(sta);
        }
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ans=min(ans,f[i][j][(1<<k)-1]);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>c[i][j];
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];

        val={-1};
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) val.push_back(c[i][j]);
        sort(val.begin(),val.end());
        val.erase(unique(val.begin(),val.end()),val.end());
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) if(~c[i][j]) c[i][j]=lower_bound(val.begin(),val.end(),c[i][j])-val.begin();
        }
        tot=val.size()-1;
        iota(p+1,p+tot+1,1);
        int t=Check(-1,0);
        if(t>(inf>>1)){
            cout<<-1<<' '<<-1<<endl;
            continue ;
        }

        int l=-1,r=1e6+1;
        while(l+1<r){
            int mid=l+r>>1;
            if(Check(mid,20000)<=t*20000) r=mid;
            else l=mid;
        }
        cout<<t<<' '<<r<<endl;
    }

    return 0;
}