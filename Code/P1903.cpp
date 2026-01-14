#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N],blk[N],cnt[N];
int ql[N],qr[N],qt[N],p[N],ans[N];
int mpos[N],mval[N],lst[N],tmp[N];
bool Cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else if(blk[qr[x]]!=blk[qr[y]]) return blk[qr[x]]<blk[qr[y]];
    else return qt[x]<qt[y];
}
void Add(int x,int &res){
    if(!cnt[x]) res++;
    cnt[x]++;
}
void Del(int x,int &res){
    cnt[x]--;
    if(!cnt[x]) res--;
}

int main(){
    int n,m,qcnt=0,mcnt=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],tmp[i]=a[i];
    for(int i=1,x,y;i<=m;i++){
        char op;
        cin>>op>>x>>y;
        if(op=='R'){
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

    int B=pow(1ll*n*n,1.0/3);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(p+1,p+qcnt+1,Cmp);

    for(int i=1,l=1,r=0,t=0,res=0;i<=qcnt;i++){
        while(r<qr[p[i]]) Add(a[++r],res);
        while(l>ql[p[i]]) Add(a[--l],res);
        while(r>qr[p[i]]) Del(a[r--],res);
        while(l<ql[p[i]]) Del(a[l++],res);
        while(t<qt[p[i]]){
            t++;
            if(l<=mpos[t]&&mpos[t]<=r) Del(a[mpos[t]],res),Add(mval[t],res);
            a[mpos[t]]=mval[t];
        }
        while(t>qt[p[i]]){
            if(l<=mpos[t]&&mpos[t]<=r) Del(a[mpos[t]],res),Add(lst[t],res);
            a[mpos[t]]=lst[t];
            t--;
        }
        ans[p[i]]=res;
    }

    for(int i=1;i<=qcnt;i++) cout<<ans[i]<<endl;

    return 0;
}