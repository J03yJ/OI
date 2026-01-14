#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int inf=1e9+7ll;

int ql[N],qr[N],m;
int a[N],b[N],p[N],ans[N],n;
bool CmpX(int x,int y){return a[x]<a[y];}
bool CmpY(int x,int y){return b[x]<b[y];}

struct Tag{
    int a,b,c,d;
    Tag(){}
    Tag(int k,int op){
        a=b=op?-inf:k;
        c=d=op?k:-inf;
    }
    Tag(int _a,int _b,int _c,int _d):
        a{max(_a,-inf)},b{max(_b,-inf)},c{max(_c,-inf)},d{max(_d,-inf)}{}
    Tag operator *(Tag t){
        return Tag(a+t.a,max(a+t.b,b),max(c+t.a,t.c),max(c+t.b,max(d,t.d)));
    }
    void operator *=(Tag t){*this=*this*t;}
    int Max(){return max(a,c);}
    int HMax(){return max(b,d);}
};
struct Node{
    int lx,rx,ly,ry;
    Tag tag;
    Node(){}
    Node(int a,int b,int c,int d,Tag t):
        lx{a},rx{b},ly{c},ry{d},tag{t}{}
}tr[N<<2];
#define lx(x) tr[x].lx
#define rx(x) tr[x].rx
#define ly(x) tr[x].ly
#define ry(x) tr[x].ry
#define tag(x) tr[x].tag

void PushDown(int x){
    tag(x<<1)*=tag(x);
    tag(x<<1|1)*=tag(x);
    tag(x)=Tag(0,0);
}
void Build(int x,int l=1,int r=n,int op=0){
    tag(x)=Tag(0,0);
    if(l==r){
        lx(x)=rx(x)=a[p[l]];
        ly(x)=ry(x)=b[p[l]];
        return ;
    }
    int mid=l+r>>1;
    nth_element(p+l,p+mid,p+r+1,op?CmpY:CmpX);
    Build(x<<1,l,mid,!op);
    Build(x<<1|1,mid+1,r,!op);
    lx(x)=min(lx(x<<1),lx(x<<1|1));
    rx(x)=max(rx(x<<1),rx(x<<1|1));
    ly(x)=min(ly(x<<1),ly(x<<1|1));
    ry(x)=max(ry(x<<1),ry(x<<1|1));
}
void Modify(int x,Node q){
    if(q.rx<lx(x)||q.lx>rx(x)||q.ry<ly(x)||q.ly>ry(x)) return ;
    if(q.lx<=lx(x)&&q.rx>=rx(x)&&q.ly<=ly(x)&&q.ry>=ry(x)){
        tag(x)*=q.tag;
        return ;
    }
    PushDown(x);
    Modify(x<<1,q);
    Modify(x<<1|1,q);
}
void Solve(int x,int l=1,int r=n){
    if(l==r){
        ans[p[l]]=tag(x).HMax();
        return ;
    }
    int mid=l+r>>1;
    PushDown(x);
    Solve(x<<1,l,mid);
    Solve(x<<1|1,mid+1,r);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>m>>n;
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i];
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    iota(p+1,p+n+1,1);

    Build(1);
    for(int i=1;i<=m;i++){
        Modify(1,Node(-inf,qr[i],ql[i],inf,Tag(1,0)));
        Modify(1,Node(qr[i]+1,inf,ql[i],inf,Tag(0,1)));
        Modify(1,Node(-inf,inf,-inf,ql[i]-1,Tag(0,1)));
    }
    Solve(1);
    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;

    return 0;
}