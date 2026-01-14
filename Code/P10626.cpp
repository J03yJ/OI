#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int V=1e9+7;

int n,m;
string s;

namespace SgT{
    struct Node{
        int lc,rc,rev,ass=-1,dat;
    }tr[N<<5];
    #define lc(x) tr[x].lc
    #define rc(x) tr[x].rc
    #define rev(x) tr[x].rev
    #define ass(x) tr[x].ass
    #define dat(x) tr[x].dat

    int trs[N<<5],cnt,top;
    inline int Alloc(){
        return top?trs[top--]:++cnt;
    }
    inline void Delete(int x){
        lc(x)=rc(x)=rev(x)=dat(x)=0;
        ass(x)=-1;
        trs[++top]=x;
    }
    inline void Clear(int x){
        if(!x) return ;
        Clear(lc(x)),Clear(rc(x));
        Delete(x);
    }
    inline void PushAss(int x,int k){
        ass(x)=dat(x)=k;
        rev(x)=0;
    }
    inline void PushRev(int x){
        if(~ass(x)) ass(x)^=1;
        else rev(x)^=1;
        dat(x)^=1;
    }
    inline void PushDown(int x){
        if(!lc(x)) lc(x)=Alloc();
        if(!rc(x)) rc(x)=Alloc();
        if(~ass(x)){
            PushAss(lc(x),ass(x));
            PushAss(rc(x),ass(x));
            ass(x)=-1;
        }else if(rev(x)){
            PushRev(lc(x));
            PushRev(rc(x));
            rev(x)=0;
        }
    }
    int Assign(int x,int L,int R,int l,int r,int k){
        if(!x) x=Alloc();
        if(l<=L&&R<=r) return PushAss(x,k),x;
        PushDown(x);
        int mid=L+R>>1;
        if(l<=mid) lc(x)=Assign(lc(x),L,mid,l,r,k);
        if(r>mid) rc(x)=Assign(rc(x),mid+1,R,l,r,k);
        return x;
    }
    int Merge(int x,int y,int L,int R,char op){
        if(~ass(x)){
            if(!ass(x)) return op=='&'?(Clear(y),x):(Clear(x),y);
            else{
                Clear(x);
                if(op=='&') return y;
                else if(op=='^') return PushRev(y),y;
                else return PushAss(y,1),y;
            }
        }
        if(~ass(y)){
            if(!ass(y)) return op=='&'?(Clear(x),y):(Clear(y),x);
            else{
                Clear(y);
                if(op=='&') return x;
                else if(op=='^') return PushRev(x),x;
                else return PushAss(x,1),x;
            }
        }
        if(L==R){
            if(op=='&') dat(x)&=dat(y);
            if(op=='^') dat(x)^=dat(y);
            if(op=='|') dat(x)|=dat(y);
            Delete(y);
            return x;
        }
        PushDown(x),PushDown(y);
        int mid=L+R>>1;
        lc(x)=Merge(lc(x),lc(y),L,mid,op);
        rc(x)=Merge(rc(x),rc(y),mid+1,R,op);
        Delete(y);
        return x;
    }
    int Flip(int x){
        return PushRev(x),x;
    }
    int Query(int x,int L,int R,int k){
        if(!x) return 0;
        if(L==R) return dat(x);
        PushDown(x);
        int mid=L+R>>1;
        if(k<=mid) return Query(lc(x),L,mid,k);
        else return Query(rc(x),mid+1,R,k);
    }
}
namespace Expr{
    int brc[N];
    vector<int> apos[N],opos[N],xpos[N];
    void InitB(){
        vector<int> stk[2];
        for(int i=0;i<s.size();i++){
            if(s[i]=='(') stk[0].push_back(i);
            if(s[i]==')') brc[stk[0].back()]=i,stk[0].pop_back();
            if(s[i]=='[') stk[1].push_back(i);
            if(s[i]==']') brc[stk[1].back()]=i,stk[1].pop_back();
            if(s[i]=='&') apos[stk[0].size()].push_back(i);
            if(s[i]=='^') xpos[stk[0].size()].push_back(i);
            if(s[i]=='|') opos[stk[0].size()].push_back(i);
        }
        for(int i=0;i<s.size();i++){
            apos[i].push_back(s.size());
            xpos[i].push_back(s.size());
            opos[i].push_back(s.size());
        }
    }
    int Build(int l,int r,int dep){
        if(s[l]=='('&&s[r]==')'&&brc[l]==r){
            return Build(l+1,r-1,dep+1);
        }
        if(s[l]=='['&&s[r]==']'&&brc[l]==r){
            int x=atoi(s.substr(l+1,r-l-1).c_str());
            return SgT::Assign(SgT::Assign(0,0,V,0,x-1,0),0,V,x,V,1);
        }
        int op=*lower_bound(opos[dep].begin(),opos[dep].end(),l);
        if(op<=r){
            return SgT::Merge(Build(l,op-1,dep),Build(op+1,r,dep),0,V,'|');
        }
        int xp=*lower_bound(xpos[dep].begin(),xpos[dep].end(),l);
        if(xp<=r){
            return SgT::Merge(Build(l,xp-1,dep),Build(xp+1,r,dep),0,V,'^');
        }
        int ap=*lower_bound(apos[dep].begin(),apos[dep].end(),l);
        if(ap<=r){
            return SgT::Merge(Build(l,ap-1,dep),Build(ap+1,r,dep),0,V,'&');
        }
        return SgT::Flip(Build(l+1,r,dep));
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'
    
    cin>>n>>m>>s;

    Expr::InitB();
    int root=Expr::Build(0,s.size()-1,0);
    while(m--){
        int x;
        cin>>x;
        if(SgT::Query(root,0,V,x)) cout<<"True"<<endl;
        else cout<<"False"<<endl;
    }

    return 0;
}