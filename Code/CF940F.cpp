#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N],blk[N],cnt[N],tot[N];
int ql[N],qr[N],qt[N],p[N],ans[N];
int mpos[N],mval[N],lst[N],tmp[N];
bool Cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else if(blk[qr[x]]!=blk[qr[y]]) return blk[qr[x]]<blk[qr[y]];
    else return qt[x]<qt[y];
}
void Add(int x){
    cnt[tot[x]]--;
    tot[x]++;
    cnt[tot[x]]++;
}
void Del(int x){
    cnt[tot[x]]--;
    tot[x]--;
    cnt[tot[x]]++;
}

int main(){
    int n,m,qcnt=0,mcnt=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],tmp[i]=a[i];
    for(int i=1,x,y,op;i<=m;i++){
        cin>>op>>x>>y;
        if(op==2){
            lst[++mcnt]=tmp[x];
            mpos[mcnt]=x;
            mval[mcnt]=y;
            tmp[x]=y;
        }else{
            qt[++qcnt]=mcnt;
            ql[qcnt]=x;
            qr[qcnt]=y;
            p[qcnt]=qcnt;
        }
    }

    vector<int> val;
    for(int i=1;i<=n;i++) val.push_back(a[i]);
    for(int i=1;i<=mcnt;i++) val.push_back(mval[i]);
    map<int,int> mp;
    int vcnt=0;
    for(int x:val) if(!mp[x]) mp[x]=++vcnt;
    for(int i=1;i<=n;i++) a[i]=mp[a[i]];
    for(int i=1;i<=mcnt;i++) lst[i]=mp[lst[i]];
    for(int i=1;i<=mcnt;i++) mval[i]=mp[mval[i]];

    int B=pow(1ll*n*n,1.0/3);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(p+1,p+qcnt+1,Cmp);

    cnt[0]=1e9;
    for(int i=1,l=1,r=0,t=0,res=1;i<=qcnt;i++){
        while(r<qr[p[i]]) Add(a[++r]);
        while(l>ql[p[i]]) Add(a[--l]);
        while(r>qr[p[i]]) Del(a[r--]);
        while(l<ql[p[i]]) Del(a[l++]);
        while(t<qt[p[i]]){
            t++;
            if(l<=mpos[t]&&mpos[t]<=r) Del(a[mpos[t]]),Add(mval[t]);
            a[mpos[t]]=mval[t];
        }
        while(t>qt[p[i]]){
            if(l<=mpos[t]&&mpos[t]<=r) Del(a[mpos[t]]),Add(lst[t]);
            a[mpos[t]]=lst[t];
            t--;
        }
        res=0;
        while(cnt[res]) res++;
        ans[p[i]]=res;
    }

    for(int i=1;i<=qcnt;i++) cout<<ans[i]<<endl;

    return 0;
}