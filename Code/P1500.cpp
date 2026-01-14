#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=1e3+9;
const long long inf=1e18;
const double eps=1e-8;

int fi[N],to[N<<2],ne[N<<2],w[N<<2],cst[N<<2],adj=1;
void adeg(int x,int y,int z,int c){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
    cst[adj]=c;
}

long long dis[N];
int mx[N],pre[N];
bool spfa(int s,int t){
    for(int i=1;i<=t;i++) dis[i]=-inf,mx[i]=0;
    dis[s]=0,mx[s]=1e9,pre[s]=-1;
    queue<int> q;
    q.push(s);
    while(q.size()){
        int x=q.front();
        q.pop();
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(!w[i]) continue ;
            if(dis[x]+cst[i]<=dis[y]) continue ;
            dis[y]=dis[x]+cst[i];
            mx[y]=min(mx[x],w[i]);
            pre[y]=i;
            q.push(y);
        }
    }
    return dis[t]!=-inf;
}
long long modify(int s,int t){
    int x=t;
    while(x!=s){
        w[pre[x]]-=mx[t];
        w[pre[x]^1]+=mx[t];
        x=to[pre[x]^1];
    }
    return dis[t]*mx[t];
}

pair<int,int> a[N],b[N];
map<string,int> mpA,mpB;
int W[N][N];
long long dist2(pair<int,int> p,pair<int,int> q){
    return (p.first-q.first)*(p.first-q.first)+(p.second-q.second)*(p.second-q.second);
}
double dist(pair<int,int> p,pair<int,int> q){
    return sqrt(dist2(p,q));
}
string lowercase(string s){
    string t="";
    for(int i=0;i<s.size();i++){
        if(s[i]>'Z') t+=s[i];
        else t+=char(s[i]+' ');
    }
    return t;
}

signed main(){
    int n,k;
    cin>>k>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>a[i].first>>a[i].second>>s;
        mpA[lowercase(s)]=i;
    }
    for(int i=1;i<=n;i++){
        string s;
        cin>>b[i].first>>b[i].second>>s;
        mpB[lowercase(s)]=i;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) W[i][j]=1;
    }
    while(true){
        string s,t;int p;
        cin>>s;
        if(s=="End") break ;
        cin>>t>>p;
        if(mpA[lowercase(t)]&&mpB[lowercase(s)]) swap(s,t);
        if(!(mpA[lowercase(s)]&&mpB[lowercase(t)])) continue ;
        W[mpA[lowercase(s)]][mpB[lowercase(t)]]=p;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) if(dist(a[i],b[j])>k+eps) W[i][j]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                if(i!=k&&(abs(-dist(a[i],b[j])+dist(a[i],a[k])+dist(a[k],b[j]))<eps)){
                    W[i][j]=0;
                    break ;
                }
                if(j!=k&&(abs(-dist(a[i],b[j])+dist(a[i],b[k])+dist(b[k],b[j]))<eps)){
                    W[i][j]=0;
                    break ;
                }
            }
            // cout<<W[i][j]<<' ';
        }
        // cout<<endl;
    }

    int s=(n<<1)+1,t=(n<<1)+2;
    for(int i=1;i<=n;i++) adeg(s,i,1,0),adeg(i,s,0,0);
    for(int i=1;i<=n;i++) adeg(i+n,t,1,0),adeg(t,i+n,0,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(!W[i][j]) continue ;
            adeg(i,j+n,1,W[i][j]);
            adeg(j+n,i,0,-W[i][j]);
        }
    }
    int ans=0;
    while(spfa(s,t)) ans+=modify(s,t);

    cout<<ans<<endl;

    return 0;
}