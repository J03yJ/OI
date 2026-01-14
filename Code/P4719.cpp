#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
inline void ChMax(int &x,int y){if(y>x) x=y;}
const int inf=1e9;

const int N=1e5+9;

struct Mat{
    int a[2][2];
    Mat(){}
    Mat(int k){a[0][0]=a[0][1]=a[1][0]=a[1][1]=k;}
    int *operator [](int x){return a[x];}
};
Mat Mul(Mat x,Mat y){
    Mat res(-inf);
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++) ChMax(res[i][k],x[i][j]+y[j][k]);
        }
    }
    return res;
}

struct Node{
    int l,r;
    Mat dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=Mul(dat(x<<1),dat(x<<1|1));}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,dat(x)=Mat(0);
    if(l(x)==r(x)) return;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
}
inline void Modify(int x,int pos,Mat &k){
    if(l(x)==r(x)) return dat(x)=k,void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    PushUp(x);
}
inline Mat Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return Mul(Query(x<<1,l,r),Query(x<<1|1,l,r));
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N],dep[N],siz[N],hson[N];
void DFS1(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x,dep[y]=dep[x]+1;
        DFS1(y);
        siz[x]+=siz[y];
        if(siz[y]>siz[hson[x]]) hson[x]=y;
    }
}
int dfn[N],idfn[N],top[N],eoc[N],dcnt;
int f[N][2],a[N];
Mat mat[N];
void DFS2(int x,int t){
    dfn[x]=++dcnt,idfn[dcnt]=x;
    top[x]=t,ChMax(eoc[top[x]],dfn[x]);
    if(hson[x]) DFS2(hson[x],t);
    f[x][0]=0,f[x][1]=a[x];
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        DFS2(y,y);
        f[x][0]+=max(f[y][0],f[y][1]);
        f[x][1]+=f[y][0];
    }
    mat[x][0][0]=mat[x][0][1]=f[x][0];
    mat[x][1][0]=f[x][1],mat[x][1][1]=-inf;
    if(hson[x]){
        f[x][0]+=max(f[hson[x]][0],f[hson[x]][1]);
        f[x][1]+=f[hson[x]][0];
    }
}

void Update(int x,int k){
    mat[x][1][0]+=k-a[x],a[x]=k;
    while(x){
        Mat lst=Query(1,dfn[top[x]],eoc[top[x]]);
        Modify(1,dfn[x],mat[x]);
        Mat cur=Query(1,dfn[top[x]],eoc[top[x]]);
        x=fa[top[x]];
        if(!x) break ;
        mat[x][0][0]=mat[x][0][1]+=max(cur[0][0],cur[1][0])-max(lst[0][0],lst[1][0]);
        mat[x][1][0]+=cur[0][0]-lst[0][0];
    }
}

int n,m;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);

    DFS1(1),DFS2(1,1),Build(1,1,n);
    for(int i=1;i<=n;i++) Modify(1,dfn[i],mat[i]);
    while(m--){
        int x,k;
        cin>>x>>k;
        Update(x,k);
        Mat res=Query(1,dfn[1],eoc[1]);
        cout<<max(res[0][0],res[1][0])<<endl;
    }

    return 0;
}