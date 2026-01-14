#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
const int N=3e5+9;
const int mod=19260817;
const int inv2=mod+1>>1;
using pii=pair<int,int>;
using lint=long long;
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int len[N],qx[N],qi[N],qval[N],ans[N],n,m,tot;
vector<int> a[N],b[N];
void Discr(){
    vector<int> val;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=len[i];j++) val.push_back(a[i][j]);
    }
    for(int i=1;i<=m;i++) val.push_back(qval[i]);
    val.push_back(-1);
    sort(allc(val));
    val.erase(unique(allc(val)),val.end());
    for(int i=1;i<=n;i++){
        for(int j=1;j<=len[i];j++) a[i][j]=lower_bound(allc(val),a[i][j])-val.begin();
    }
    for(int i=1;i<=m;i++) qval[i]=lower_bound(allc(val),qval[i])-val.begin();
    tot=ssiz(val)-1;
}

vector<int> op[N<<2],tmp[N],ptmp[N];
vector<pii> cc[N];
#define T(x) 1ll*(x)*((x)+1)%mod*inv2%mod

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>len[i];
    for(int i=1;i<=n;i++){
        a[i]=vector<int>(len[i]+1);
        for(int j=1;j<=len[i];j++) cin>>a[i][j];
    }
    for(int i=1;i<=m;i++) cin>>qx[i]>>qi[i]>>qval[i];
    Discr();

    for(int i=1;i<=n;i++) b[i]=a[i];
    for(int i=1;i<=m;i++){
        if(b[qx[i]][qi[i]]==qval[i]) continue ;
        op[b[qx[i]][qi[i]]].push_back(i);
        op[qval[i]].push_back(i);
        b[qx[i]][qi[i]]=qval[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=len[i];j++) cc[a[i][j]].push_back({i,j});
    }

    int prod=1;
    for(int i=1;i<=n;i++) prod=1ll*prod*T(len[i]);
    for(int i=1;i<=tot;i++){
        int cur=prod,zcnt=0;
        vector<int> pos;
        for(pii &p:cc[i]){
            ptmp[p.first].push_back(p.second);
            pos.push_back(p.first);
        }
        for(int j:op[i]){
            tmp[qx[j]].push_back(j);
            pos.push_back(qx[j]);
        }
        sort(allc(pos));
        pos.erase(unique(allc(pos)),pos.end());
        vector<array<int,3>> mul;
        for(int j:pos){
            int res=T(len[j]);
            cur=1ll*cur*Inv(res)%mod;
            set<int> s({0,len[j]+1});
            auto Insert=[&s,&res](int pos)->void{
                auto it=s.upper_bound(pos);
                int l=*prev(it),r=*it;
                SubAs(res,T(r-l-1));
                AddAs(res,T(pos-l-1));
                AddAs(res,T(r-pos-1));
                s.insert(pos);
            };
            auto Erase=[&s,&res](int pos)->void{
                auto it=s.lower_bound(pos);
                int l=*prev(it),r=*next(it);
                SubAs(res,T(pos-l-1));
                SubAs(res,T(r-pos-1));
                AddAs(res,T(r-l-1));
                s.erase(it);
            };
            for(int k:ptmp[j]) Insert(k);
            mul.push_back({0,res,1});
            for(int k:tmp[j]){
                mul.push_back({k,res,0});
                if(qval[k]==i) Insert(qi[k]);
                else Erase(qi[k]);
                mul.push_back({k,res,1});
            }
        }
        for(pii &p:cc[i]) ptmp[p.first].pop_back();
        for(int j:op[i]) tmp[qx[j]].pop_back();

        sort(allc(mul));
        for(int s=0,t=0,lst=0;s<ssiz(mul);s=t){
            while(t<ssiz(mul)&&mul[++t][0]==mul[s][0]) ;
            for(int k=s;k<t;k++){
                if(mul[k][2]){
                    if(mul[k][1]) cur=1ll*cur*mul[k][1]%mod;
                    else zcnt++;
                }else{
                    if(mul[k][1]) cur=1ll*cur*Inv(mul[k][1])%mod;
                    else zcnt--;
                }
            }
            int tmp=zcnt?0:cur;
            AddAs(ans[mul[s][0]],Sub(tmp,lst));
            lst=tmp;
        }
    }

    int ctmp=1ll*tot*prod%mod;
    for(int i=1;i<=m;i++) AddAs(ans[i],ans[i-1]);
    for(int i=0;i<=m;i++) cout<<Sub(ctmp,ans[i])<<endl;

    return 0;
}