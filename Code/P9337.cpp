#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
const int N=5e5+9;
const int Sqr=7.1e2+9;
const int lgN=2e1;

int a[N],p[N],ql[N],qr[N],n,m,B;
vector<int> pos[N];
long long ans[N];

int maxx[N][lgN],minn[N][lgN],lg[N];
void Init(){
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++) maxx[i][0]=minn[i][0]=p[i];
    for(int k=1;k<=lg[n];k++){
        for(int i=1;i<=n;i++){
            maxx[i][k]=max(maxx[i][k-1],maxx[i+(1<<k-1)][k-1]);
            minn[i][k]=min(minn[i][k-1],minn[i+(1<<k-1)][k-1]);
        }
    }
}
int Max(int l,int r){
    int k=lg[r-l+1];
    return max(maxx[l][k],maxx[r-(1<<k)+1][k]);
}
int Min(int l,int r){
    int k=lg[r-l+1];
    return min(minn[l][k],minn[r-(1<<k)+1][k]);
}

vector<array<vector<int>::iterator,3>> seg[N];
vector<pair<int,int>> qry[N];
int blk[N],L[N],R[N];
long long s[N],bs[Sqr];
void Modify(int x,int k){bs[blk[x]]+=k,s[x]+=k;}
long long Brute(int l,int r){
    if(l==L[blk[l]]&&r==R[blk[r]]) return bs[blk[l]];
    long long sum=0;
    for(int i=l;i<=r;i++) sum+=s[i];
    return sum;
}
long long Query(int l,int r){
    if(blk[l]==blk[r]) return Brute(l,r);
    long long sum=Brute(l,R[blk[l]])+Brute(L[blk[r]],r);
    for(int i=blk[l]+1;i<blk[r];i++) sum+=bs[i];
    return sum;
}

vector<pair<int,int>> lnk[N];
int low[N],up[N],st[N],ed[N],lq[N],rq[N],top;
vector<int> val,tmp[N];
pair<int,int> rb[N<<2];
void Link(int x,long long &res){
    res+=1ll*(ed[x]-st[x]+1)*(ed[x+1]-st[x+1]+1);
    ed[st[x]]=ed[x+1],st[ed[x+1]]=st[x];
}
void RLink(int x,long long &res){
    rb[++top]={st[x],ed[x]};
    rb[++top]={st[x+1],ed[x+1]};
    Link(x,res);
}
void Rollback(){
    while(top){
        int x=rb[top].first,y=rb[top].second;
        st[x]=st[y]=x,ed[x]=ed[y]=y;
        top--;
    }
}
long long Brute(long long res,int ql,int l,int r){
    while(l>ql){
        l--;
        for(auto p:lnk[l]) if(p.first>=l&&r>=p.first) RLink(p.second,res);
    }
    Rollback();
    return res;
}
void MoAlgo(int len){
    int lim=ssiz(val),B=min((int)ceil(lim/sqrt(m)/1.5),lim);
    for(int i=0;i<lim;i++) blk[i]=i/B+1;
    for(int i=0;i<lim;i++) R[blk[i]]=i;
    for(int i=lim-1;~i;i--) L[blk[i]]=i;
    for(int i=1;i<=m;i++) lq[i]=low[ql[i]],rq[i]=up[qr[i]]-1;
    
    vector<int> c;
    for(int i=1;i<=m;i++) if(lq[i]<=rq[i]) tmp[rq[i]].push_back(i);
    for(int i=0;i<lim;i++){
        c.insert(c.end(),tmp[i].begin(),tmp[i].end());
        tmp[i].clear();
    }
    for(int x:c) if(lq[x]<=rq[x]) tmp[blk[lq[x]]].push_back(x);
    c.clear();
    
    for(int i=1;i<=blk[lim-1];i++){
        for(int j=0;j<len;j++) st[j]=ed[j]=j;
        long long res=0;int l=R[i]+1,r=R[i];
        for(int j:tmp[i]){
            if(rq[j]<=R[i]){
                ans[j]+=Brute(res,lq[j],rq[j]+1,rq[j]);
                continue ;
            }
            while(r<rq[j]){
                r++;
                for(auto p:lnk[r]) if(p.first<=r&&l<=p.first) Link(p.second,res);
            }
            ans[j]+=Brute(res,lq[j],l,r);
        }
        tmp[i].clear();
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],pos[a[i]].push_back(i);
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i];

    B=sqrt(n),Init();
    for(int i=1;i<=n;i++){
        if(ssiz(pos[i])<2||ssiz(pos[i])>2*B) continue ;
        vector<pair<int,int>> tmp;
        for(int j=1;j<ssiz(pos[i]);j++) tmp.push_back({Min(pos[i][j-1],pos[i][j]),j});
        vector<int> stk,lp(ssiz(pos[i]),0),rp(ssiz(pos[i]),ssiz(pos[i])-1);
        for(int j=0;j<ssiz(tmp);j++){
            while(ssiz(stk)&&tmp[stk.back()]>tmp[j]) stk.pop_back();
            if(ssiz(stk)) lp[j]=stk.back()+1;
            stk.push_back(j);
        }
        stk.clear();
        for(int j=ssiz(tmp)-1;~j;j--){
            while(ssiz(stk)&&tmp[stk.back()]>tmp[j]) stk.pop_back();
            if(ssiz(stk)) rp[j+1]=stk.back();
            stk.push_back(j);
        }
        auto it=pos[i].begin();
        for(int j=0;j<ssiz(tmp);j++) seg[tmp[j].first].push_back({it+lp[j],it+j+1,it+rp[j+1]+1});
    }
    for(int i=1;i<=m;i++) qry[ql[i]].push_back({i,qr[i]});
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=n;i>=1;i--) L[blk[i]]=i;
    for(int i=n;i>=1;i--){
        for(auto t:seg[i]){
            for(auto lt=t[0];lt!=t[1];lt++){
                for(auto rt=t[1];rt!=t[2];rt++) Modify(Max(*lt,*rt),1);
            }
        }
        for(auto p:qry[i]) ans[p.first]+=Query(1,p.second);
    }

    for(int i=1;i<=n;i++){
        if(ssiz(pos[i])<=2*B) continue ;
        val.clear();
        for(int j=0;j<ssiz(pos[i])-1;j++){
            val.push_back(Min(pos[i][j],pos[i][j+1]));
            val.push_back(Max(pos[i][j],pos[i][j+1]));
        }
        val.push_back(0),val.push_back(n+1);
        sort(val.begin(),val.end());
        val.erase(unique(val.begin(),val.end()),val.end());
        for(int j=0,it=0,jt=0;j<=n;j++){
            while(val[it]<j) it++;low[j]=it;
            while(val[jt]<=j) jt++;up[j]=jt;
            lnk[j].clear();
            lnk[j].reserve(8);
        }
        for(int j=0;j<ssiz(pos[i])-1;j++){
            int mn=Min(pos[i][j],pos[i][j+1]),mx=Max(pos[i][j],pos[i][j+1]);
            lnk[low[mn]].push_back({low[mx],j});
            lnk[low[mx]].push_back({low[mn],j});
        }
        MoAlgo(ssiz(pos[i]));
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}