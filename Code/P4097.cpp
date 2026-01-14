#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const double eps=1e-8;
const int V=4e4;
const int M1=39989;
const int M2=1e9;

inline int cmp(double x,double y){
    if(x-y>eps) return 1;
    if(y-x>eps) return -1;
    return 0;
}

struct Seg{
    int x0,x1,y0,y1;
    double b,k;
    void calc(){
        if(x0==x1){
            k=0,b=max(y0,y1);
            return ;
        }
        k=(y1-y0)/double(x1-x0);
        b=y0-x0*k;
    }
    Seg(){k=b=0;}
    Seg(int X0,int Y0,int X1,int Y1){
        x0=X0;y0=Y0;x1=X1;y1=Y1;
        calc();
    }
    double get(int x){
        if(x<x0||x>x1) return 0;
        return x*k+b;
    }
};
vector<Seg> s(1,Seg());

struct node{
    int l,r,dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

void build(int x,int l,int r){
    l(x)=l;r(x)=r;
    if(l==r) return ;
    int mid=l(x)+r(x)>>1;
    build(2*x,l,mid);build(2*x+1,mid+1,r);
}
void upd(int x,int u){
    int mid=l(x)+r(x)>>1,&v=dat(x);
    int bmid=cmp(s[u].get(mid),s[v].get(mid));
    if(bmid==1||!bmid&&u<v) swap(u,v);
    // cout<<l(x)<<' '<<r(x)<<' '<<v<<endl;
    if(l(x)==r(x)) return ;
    int bl=cmp(s[u].get(l(x)),s[v].get(l(x))),br=cmp(s[u].get(r(x)),s[v].get(r(x)));
    if(bl==1||!bl&&u<v) upd(2*x,u);
    if(br==1||!br&&u<v) upd(2*x+1,u);
}
void insert(int x,int l,int r,int u){
    if(l<=l(x)&&r(x)<=r){
        upd(x,u);
        return ;
    }
    int mid=l(x)+r(x)>>1;
    if(l<=mid) insert(2*x,l,r,u);
    if(r>mid) insert(2*x+1,l,r,u);
}
pair<double,int> cmp(pair<double,int> x,pair<double,int> y){
    // cout<<x.first<<' '<<x.second<<' '<<y.first<<' '<<y.second<<endl;
    // cout<<cmp(x.first,y.first)<<endl;
    if(cmp(x.first,y.first)==1) return x;
    else if(cmp(x.first,y.first)==-1) return y;
    else return x.second<y.second?x:y;
}
pair<double,int> query(int x,int k){
    // cout<<dat(x)<<endl;
    if(l(x)==r(x)) return make_pair(s[dat(x)].get(k),dat(x));
    int mid=l(x)+r(x)>>1;pair<double,int> res;
    if(k<=mid) res=cmp({s[dat(x)].get(k),dat(x)},query(2*x,k));
    else res=cmp({s[dat(x)].get(k),dat(x)},query(2*x+1,k));
    // cout<<dat(x)<<'-'<<s[dat(x)].get(k)<<' '<<k<<endl;
    // cout<<res.first<<' '<<res.second<<endl;
    return res;
}

inline void F(int &x,int y,int p){
    x=(x+y-1)%p+1;
}

int main(){
    build(1,1,V);
    int Q,lst=0;
    cin>>Q;
    while(Q--){
        int op;
        cin>>op;
        if(!op){
            int x;
            cin>>x;
            F(x,lst,M1);
            lst=query(1,x).second;
            cout<<lst<<endl;
        }else{
            s.push_back(Seg());
            cin>>s.back().x0>>s.back().y0>>s.back().x1>>s.back().y1;
            F(s.back().x0,lst,M1);F(s.back().x1,lst,M1);
            F(s.back().y0,lst,M2);F(s.back().y1,lst,M2);
            if(s.back().x0>s.back().x1) swap(s.back().x0,s.back().x1),swap(s.back().y0,s.back().y1);
            s.back().calc();
            insert(1,s.back().x0,s.back().x1,s.size()-1);
        }
    }
    return 0;
}