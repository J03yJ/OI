#include<bits/stdc++.h>

using namespace std;

#define allc(x) x.begin(),x.end()
#define ssiz(x) (signed)x.size()
const int N=2e5+9;

int a[N],ans[N],n,q,B;
vector<pair<int,int>> qry[N];
int Insert(vector<vector<int>> &f,int x,bool flag){
    int i=0;
    for(vector<int> &v:f){
        i++;
        auto it=!flag?lower_bound(allc(v),x):upper_bound(allc(v),x);
        if(it==v.end()){
            v.push_back(x);
            return flag?i:(ssiz(v)>B?ssiz(v):0);
        }else swap(*it,x);
    }
    if(ssiz(f)<B){
        f.push_back(vector<int>(1,x));
        return flag?ssiz(f):0;
    }
    return 0;
}
int tr[N];
void Add(int x,int k){
    if(!x) return ;
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
int Ask(int l,int r){return Ask(r)-Ask(l-1);}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,m,k;i<=q;i++){
        cin>>m>>k;
        qry[m].push_back({i,k});
    }

    B=sqrt(n);
    vector<vector<int>> f,g;
    for(int i=1;i<=n;i++){
        Add(Insert(f,a[i],0),1);
        Add(Insert(g,-a[i],1),1);
        for(auto p:qry[i]) ans[p.first]=Ask(p.second);
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}