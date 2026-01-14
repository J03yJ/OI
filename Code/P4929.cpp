#include<bits/stdc++.h>

using namespace std;

#define Iter(i,x,a) for(int i=a[x];i^x;i=a[i])
const int N=1e5+9;

int u[N],d[N],l[N],r[N],col[N],row[N];
int n,m,cnt,fi[N],siz[N];

void Remove(int c){
    l[r[c]]=l[c],r[l[c]]=r[c];
    Iter(i,c,d){
        Iter(j,i,r){
            u[d[j]]=u[j],d[u[j]]=d[j];
            siz[col[j]]--;
        }
    }
}
void Recover(int c){
    Iter(i,c,d){
        Iter(j,i,r){
            u[d[j]]=d[u[j]]=j;
            siz[col[j]]++;
        }
    }
    l[r[c]]=r[l[c]]=c;
}
void Build(int _n,int _m){
    n=_n,m=_m,cnt=m;
    for(int i=0;i<=m;i++) u[i]=d[i]=i,l[i]=i-1,r[i]=i+1;
    l[0]=m,r[m]=0;
    memset(fi,0,sizeof(int)*(n+1));
    memset(siz,0,sizeof(int)*(m+1));
}
void Insert(int x,int y){
    cnt++;
    col[cnt]=y,row[cnt]=x,siz[y]++;
    u[d[y]]=cnt,d[cnt]=d[y],u[cnt]=y,d[y]=cnt;
    if(!fi[x]) fi[x]=l[cnt]=r[cnt]=cnt;
    else l[r[fi[x]]]=cnt,r[cnt]=r[fi[x]],l[cnt]=fi[x],r[fi[x]]=cnt;
}
int ans[N],len;
bool Dance(int dep){
    if(!r[0]) return len=dep,1;
    int pos=r[0];
    Iter(i,0,r) if(siz[i]<siz[pos]) pos=i;
    Remove(pos);
    Iter(i,pos,d){
        ans[dep]=row[i];
        Iter(j,i,r) Remove(col[j]);
        if(Dance(dep+1)) return 1;
        Iter(j,i,l) Recover(col[j]);
    }
    Recover(pos);
    return 0;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    Build(n,m);
    for(int i=1;i<=n;i++){
        for(int j=1,c;j<=m;j++){
            cin>>c;
            if(c) Insert(i,j);
        }
    }
    Dance(1);
    if(len){
        for(int i=1;i<len;i++) cout<<ans[i]<<' ';cout<<endl;
    }else cout<<"No Solution!"<<endl;

    return 0;
}