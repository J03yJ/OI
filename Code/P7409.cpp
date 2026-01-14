#include<bits/stdc++.h>

using namespace std;

using ll=long long;
using bint=__int128;
const int N=3e6+9;
const int lgN=23;
const ll mod=23333333333333333;
inline void AddAs(ll &x,ll y){x+=y;if(x>=mod) x-=mod;}

char s[N];
struct Node{
    int fa,len,son[26];
}tr[N<<1];
#define fa(x) tr[x].fa
#define len(x) tr[x].len
#define son(x,k) tr[x].son[k]

int suf[N],cnt=1,lst=1;
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline int Append(int c){
    int cur=Allc(),p=lst;
    len(cur)=len(lst)+1;
    while(p&&!son(p,c)) son(p,c)=cur,p=fa(p);
    int q=son(p,c);
    if(!q) fa(cur)=1;
    else if(len(q)==len(p)) fa(cur)=q;
    else{
        int r=Clone(q);
        len(r)=len(p)+1;
        while(p&&son(p,c)==q) son(p,c)=r,p=fa(p);
        fa(cur)=fa(q)=r;
    }
    return lst=cur;
}

vector<int> e[N<<1];
int elr[N<<1],pos[N],ecnt,n;
inline void DFS(int x){
    elr[++ecnt]=x;
    pos[x]=ecnt;
    for(int y:e[x]){
        DFS(y);
        elr[++ecnt]=x;
    }
}
int mn[N<<1][lgN],lg[N<<1];
inline void InitAnc(){
    for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
    for(int k=1;k<=lg[ecnt];k++){
        for(int i=1;i<=ecnt-(1<<k)+1;i++) mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
    }
}
inline int LCA(int x,int y){
    if(pos[x]>pos[y]) swap(x,y);
    int k=lg[pos[y]-pos[x]+1];
    return elr[min(mn[pos[x]][k],mn[pos[y]-(1<<k)+1][k])];
}

int siz[N],root,q;
vector<int> vtr,imp,v[N];
inline void Build(){
    sort(imp.begin(),imp.end(),[](int x,int y){return pos[x]<pos[y];});
    imp.erase(unique(imp.begin(),imp.end()),imp.end());
    vtr=imp;
    for(int i=1;i<imp.size();i++) vtr.push_back(LCA(imp[i-1],imp[i]));
    sort(vtr.begin(),vtr.end(),[](int x,int y){return pos[x]<pos[y];});
    vtr.erase(unique(vtr.begin(),vtr.end()),vtr.end());
    for(int i=1;i<vtr.size();i++) v[LCA(vtr[i-1],vtr[i])].push_back(vtr[i]);
    root=vtr.front();
    for(int x:imp) siz[x]++;
}
ll ans;
inline void Calc(int x){
    for(int y:v[x]){
        Calc(y);
        AddAs(ans,bint(siz[x])*siz[y]*len(x)%mod);
        siz[x]+=siz[y];
    }
}
inline void Clear(){
    for(int x:vtr) siz[x]=0,v[x].clear();
    imp.clear(),vtr.clear();
    ans=root=0;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>s[i];
    
    for(int i=n;i>=1;i--) suf[i]=Append(s[i]-'a');
    for(int i=2;i<=cnt;i++) e[fa(i)].push_back(i);
    DFS(1);
    InitAnc();

    while(q--){
        int k,x;
        cin>>k;
        while(k--) cin>>x,imp.push_back(suf[x]);

        Build();
        Calc(root);
        cout<<ans<<endl;
        Clear();
    }

    return 0;
}