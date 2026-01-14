#include<bits/stdc++.h>
using namespace std;

#define int long long

ifstream fin("Aventurine.in");
ofstream fout("Aventurine.out");
#define cin fin
#define cout fout

struct Vec{
    int x,y;
    Vec(){}
    Vec(int X,int Y){
        x=X;y=Y;
    }
    Vec operator +(Vec v){
        return Vec(x+v.x,y+v.y);
    }
    Vec operator -(Vec v){
        return Vec(x-v.x,y-v.y);
    }
};
int Cross(Vec u,Vec v){
    return u.x*v.y-v.x*u.y;
}

struct Basis{
    int b[30],cnt;
    Basis(){
        memset(b,0,sizeof(b));
        cnt=0;
    }
    bool insert(int x){
        // cout<<x<<' ';
        for(int i=29;~i;i--){
            if(x>>i&1){
                // cout<<i<<' ';
                if(!b[i]){
                    // cout<<endl;
                    b[i]=x;
                    cnt++;
                    return 1;
                }
                else x^=b[i];
            }
            if(!x) break ;
        }
        // cout<<":"<<endl;
        return 0;
    }
    int operator[] (int x){
        return b[x];
    }
};

const int N=1e3+9;
struct Mono{
    int a,b,c,w;
}a[N];

int K,n,ans=1e18;
bool cmp(Mono a,Mono b){
    return a.w<b.w;
}
Vec calc(){
    Vec res=Vec(0,0);
    sort(a+1,a+n+1,cmp);
    Basis tmp;
    for(int i=1;i<=n;i++){
        if(tmp.insert(a[i].a)){
            res.x+=a[i].b,res.y+=a[i].c;
        }
    }
    return res;
}
void solve(Vec A,Vec B){
    for(int i=1;i<=n;i++) a[i].w=(A.y-B.y)*a[i].b+(B.x-A.x)*a[i].c;
    Vec C=calc();ans=min(ans,C.x*C.y);
    if(Cross(B-A,C-A)<0) solve(A,C),solve(C,B);
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i].a>>a[i].b>>a[i].c;
        Basis res;
        for(int i=1;i<=n;i++) res.insert(a[i].a);
        K=res.cnt;
        for(int i=1;i<=n;i++) a[i].w=a[i].b;Vec A=calc();ans=min(ans,A.x*A.y);
        for(int i=1;i<=n;i++) a[i].w=a[i].c;Vec B=calc();ans=min(ans,B.x*B.y);
        solve(A,B);
        cout<<ans<<endl;
        ans=1e18;
    }
    return 0;
}