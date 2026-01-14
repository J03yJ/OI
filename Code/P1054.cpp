#include<bits/stdc++.h>

using namespace std;

#define int long long
#define Allc(x) x.begin(),x.end()
const int mod=1e9+7;
const int N=1e3+9;
const int cnt=5;

int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

int brc[N],x[cnt];
vector<int> a[N],b[N],c[N],d[N];
void Set(){
    mt19937 myrand(time(0));
    for(int i=0;i<cnt;i++) x[i]=myrand()%mod;
    // for(int i=0;i<cnt;i++) cout<<x[i]<<' ';cout<<endl;
}
void Init(string &s){
    for(int i=0;i<s.size();i++){
        a[i].clear();
        b[i].clear();
        c[i].clear();
        d[i].clear();
    }
    vector<int> stk;
    s="(((((((((("+s;
    for(int i=0;i<s.size();i++){
        if(s[i]=='(') stk.push_back(i);
        if(s[i]==')'){
            assert(stk.size());
            int j=stk.back();
            stk.pop_back();
            brc[i]=j,brc[j]=i;
        }
        if(s[i]=='+') a[stk.size()].push_back(i);
        if(s[i]=='-') b[stk.size()].push_back(i);
        if(s[i]=='*') c[stk.size()].push_back(i);
        if(s[i]=='^') d[stk.size()].push_back(i);
    }
    while(stk.size()){
        s.push_back(')');
        int i=s.size()-1;
        int j=stk.back();
        stk.pop_back();
        brc[i]=j,brc[j]=i;
    }
}
int AToI(string &s,int l,int r){
    int res=0;
    for(int i=l;i<=r;i++){
        res=res*10%mod;
        res=(res+s[i]-'0')%mod;
    }
    return res;
}
int F(string &s,int l,int r,int dep,int k){
    // cout<<s.substr(l,r-l+1)<<' '<<l<<' '<<r<<' '<<dep<<' '<<k<<endl;
    if(s[l]=='('&&s[r]==')'&&brc[l]==r) return F(s,l+1,r-1,dep+1,k);
    auto pos1=--upper_bound(Allc(a[dep]),r);
    if(pos1!=a[dep].begin()-1&&*pos1>=l){
        return (F(s,l,*pos1-1,dep,k)+F(s,*pos1+1,r,dep,k))%mod;
    }
    auto pos2=--upper_bound(Allc(b[dep]),r);
    if(pos2!=b[dep].begin()-1&&*pos2>=l){
        // cout<<" : "<<*pos2<<endl;
        return (F(s,l,*pos2-1,dep,k)-F(s,*pos2+1,r,dep,k)+mod)%mod;
    }
    auto pos3=--upper_bound(Allc(c[dep]),r);
    if(pos3!=c[dep].begin()-1&&*pos3>=l){
        return F(s,l,*pos3-1,dep,k)*F(s,*pos3+1,r,dep,k)%mod;
    }
    auto pos4=--upper_bound(Allc(d[dep]),r);
    if(pos4!=d[dep].begin()-1&&*pos4>=l){
        return QPow(F(s,l,*pos4-1,dep,k),F(s,*pos4+1,r,dep,k));
    }
    if(l==r&&s[l]=='a') return k;
    else return AToI(s,l,r);
}
string Work(string &s){
    string t;
    for(int i=0;i<s.size();i++) if(s[i]>' ') t+=s[i];
    return t;
}
array<int,cnt> Solve(string s){
    s=Work(s);
    array<int,cnt> res;
    for(int i=0;i<cnt;i++){
        Init(s);
        res[i]=F(s,0,s.size()-1,0,x[i]);
    }
    return res;
}
void Read(string &s){
    while(!s.size()||s[0]=='\r'||s[0]=='\n') getline(cin,s);
}

signed main(){
    Set();
    string s;
    Read(s);
    auto std=Solve(s);
    int T;
    cin>>T;
    // for(int x:std) cout<<x<<' ';cout<<endl;
    for(char i='A';i<'A'+T;i++){
        string t;
        Read(t);
        auto ans=Solve(t);
        // for(int x:ans) cout<<x<<' ';cout<<endl;
        if(ans==std) cout<<i;
        // else cout<<"*";
    }
    cout<<endl;

    return 0;
}