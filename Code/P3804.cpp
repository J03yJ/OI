#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
using ll=long long;

struct Node{
    int fa,len,son[26];
}tr[N<<1];
#define fa(x) tr[x].fa
#define len(x) tr[x].len
#define son(x,k) tr[x].son[k]

int f[N<<1],cnt,lst;
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline void Insert(int c){
    int cur=Allc(),p=lst;
    len(cur)=len(lst)+1;
    while(p&&!son(p,c)) son(p,c)=cur,p=fa(p);
    int q=son(p,c);
    if(!q) fa(cur)=1;
    else if(len(q)==len(p)+1) fa(cur)=q;
    else{
        int r=Clone(q);
        len(r)=len(p)+1;
        while(p&&son(p,c)==q) son(p,c)=r,p=fa(p);
        fa(cur)=fa(q)=r;
    }
    lst=cur;
    f[cur]++;
}

vector<int> e[N<<1];
inline void DFS(int x){
    for(int y:e[x]){
        DFS(y);
        f[x]+=f[y];
    }
}
inline void Calc(){
    for(int i=1;i<=cnt;i++) e[fa(i)].push_back(i);
    DFS(1);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    
    string s;
    cin>>s;
    lst=Allc();
    for(char c:s) Insert(c-'a');

    Calc();
    ll ans=0;
    for(int i=1;i<=cnt;i++) if(f[i]>1) ans=max(ans,1ll*f[i]*len(i));
    cout<<ans<<endl;

    return 0;
}