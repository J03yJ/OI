#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()

const int N=1e5+9;
const int B=1e2;

int a[N],tmp[N],n;
int ql[N],qr[N],ans[N],q;

pair<int,int> Brute(int l,int r){
    for(int i=l;i<=r;i++) tmp[i]=i;
    sort(tmp+l,tmp+r+1,[](int x,int y){return a[x]<a[y];});
    int p1=-1,p2=-1,res=1e9;
    for(int i=l;i<r;i++){
        int t=a[tmp[i+1]]-a[tmp[i]];
        if(!t) continue ;
        if(t<res){
            res=t;
            p1=tmp[i],p2=tmp[i+1];
        }
    }
    if(p1>p2) swap(p1,p2);
    return {p1,p2};
}
int F(int l,int r){
    for(int i=l;i<=r;i++) tmp[i]=a[i];
    sort(tmp+l,tmp+r+1);
    int res=1e9;
    for(int i=l;i<r;i++) if(tmp[i+1]^tmp[i]) res=min(res,tmp[i+1]-tmp[i]);
    return res;
}
void Solve(vector<int> &v){
    if(!ssiz(v)) return ;
    int l=1e9,r=0;
    for(int i:v) l=min(l,ql[i]),r=max(r,qr[i]);
    if(r-l+1<=B){
        for(int i:v) ans[i]=F(ql[i],qr[i]);
        return ;
    }
    auto p=Brute(l,r);
    int p1=p.first,p2=p.second,res=abs(a[p2]-a[p1]);
    vector<int> q1,q2;
    for(int i:v){
        if(ql[i]<=p1&&p2<=qr[i]) ans[i]=res;
        else if(qr[i]<p2) q1.push_back(i);
        else q2.push_back(i);
    }
    v.clear();
    Solve(q1);
    Solve(q2);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

    vector<int> qry(q);
    iota(allc(qry),1);
    Solve(qry);
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}