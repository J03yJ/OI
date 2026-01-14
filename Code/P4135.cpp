#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int sqN=4e2+9;

int L[sqN],R[sqN],blk[N],a[N],n,c,m;
int buc[N],pre[sqN][N],s[sqN][sqN];

int main(){
    cin>>n>>c>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    const int B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=n;i>=1;i--) L[blk[i]]=i;

    for(int i=1;i<=blk[n];i++){
        for(int j=i,res=0;j<=blk[n];j++){
            for(int k=L[j];k<=R[j];k++){
                if(buc[a[k]]) res--;
                else res++;
                buc[a[k]]^=1;
            }
            s[i][j]=res;
        }
        for(int j=L[i];j<=n;j++) buc[a[j]]=0;
    }
    for(int i=1;i<=blk[n];i++){
        for(int j=1;j<=c;j++) pre[i][c]=pre[i-1][c];
        for(int j=L[i];j<=R[i];j++) pre[i][a[j]]++;
    }

    int lst=0;
    while(m--){
        int l,r;
        cin>>l>>r;
        l=(l+lst)%n+1;
        r=(r+lst)%n+1;
        if(l>r) swap(l,r);
        cout<<l<<' '<<r<<endl;

        if(blk[l]==blk[r]){
            int res=0;
            for(int i=l;i<=r;i++){
                if(buc[a[i]]) res--;
                else res++;
                buc[a[i]]^=1;
            }
            res=r-l+1-res;
            cout<<(lst=res)<<endl;
            for(int i=l;i<=r;i++) buc[a[i]]=0;
        }else{
            int res=s[blk[l]+1][blk[r]-1];
            for(int i=l;i<=R[blk[l]];i++){
                buc[a[i]]=max(pre[blk[r]-1][a[i]]-pre[blk[l]][a[i]],0)&1;
            }
            for(int i=L[blk[r]];i<=r;i++){
                buc[a[i]]=max(pre[blk[r]-1][a[i]]-pre[blk[l]][a[i]],0)&1;
            }
            for(int i=l;i<=R[blk[l]];i++){
                if(buc[a[i]]) res--;
                else res++;
                buc[a[i]]^=1;
            }
            for(int i=L[blk[r]];i<=r;i++){
                if(buc[a[i]]) res--;
                else res++;
                buc[a[i]]^=1;
            }
            res=r-l+1-res;
            cout<<(lst=res)<<endl;
            for(int i=l;i<=R[blk[l]];i++) buc[a[i]]=0;
            for(int i=L[blk[r]];i<=r;i++) buc[a[i]]=0;
        }
    }

    return 0;
}