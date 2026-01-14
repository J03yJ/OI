#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int sN=1e3+9;
#define endl '\n'
#define rint register int

inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(register int x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}

int a[N];
int op[N],l[N],r[N],k[N],ans[N];
int L[N],R[N],blk[N];

int tag=0,mx=0;
int fa[N],ra[N],val[N],siz[N];
inline void build(int b){
    tag=0,mx=0;
    memset(ra,0,sizeof(ra));
    memset(siz,0,sizeof(siz));
    for(rint i=L[b];i<=R[b];i++){
        mx=max(mx,a[i]);
        if(!ra[a[i]]){
            ra[a[i]]=i;
            fa[i]=i;
            val[i]=a[i];
        }else fa[i]=ra[a[i]];
        siz[a[i]]++;
    }
}
inline int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    if(ra[x]) fa[ra[y]]=ra[x];
    else ra[x]=ra[y],val[ra[x]]=x;
    siz[x]+=siz[y];
    siz[y]=ra[y]=0;
}

inline void modify(int x){
    if((x<<1)+tag>mx){
        for(rint i=x+tag+1;i<=mx;++i) if(ra[i]) merge(i-x,i);
        if(tag+x<mx) mx=x+tag;
    }else{
        for(rint i=x+tag;i>=tag;--i) if(ra[i]) merge(i+x,i);
        tag+=x;
    }
}
inline void modify(int b,int l,int r,int x){
    for(rint i=L[b];i<=R[b];i++){
        a[i]=val[find(i)];
        ra[a[i]]=siz[a[i]]=0;
        a[i]-=tag;
    }
    for(rint i=L[b];i<=R[b];i++) val[i]=0;
    for(rint i=l;i<=r;i++) if(a[i]>x) a[i]-=x;
    tag=0,mx=0;
    for(rint i=L[b];i<=R[b];i++){
        mx=max(mx,a[i]);
        if(!ra[a[i]]){
            ra[a[i]]=i;
            fa[i]=i;
            val[i]=a[i];
        }else fa[i]=ra[a[i]];
        siz[a[i]]++;
    }
}
inline int query(int l,int r,int x){
    if(x+tag>5e5) return 0;
    int cnt=0;
    for(rint i=l;i<=r;i++) if(val[find(i)]==x+tag) cnt++;
    return cnt;
}

int main(){
    int n=read(),m=read();
    for(rint i=1;i<=n;i++) a[i]=read();
    for(rint i=1;i<=m;i++) op[i]=read(),l[i]=read(),r[i]=read(),k[i]=read();

    int B=sqrt(n);
    for(rint i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(rint i=1;i<=n;i++){
        if(!L[blk[i]]) L[blk[i]]=i;
        R[blk[i]]=i;
    }
    
    for(rint i=1;i<=blk[n];i++){
        build(i);
        for(rint j=1;j<=m;j++){
            int ql=max(l[j],L[i]),qr=min(r[j],R[i]),qv=k[j];
            if(ql>qr) continue ;
            if(op[j]==1){
                if(ql==L[i]&&qr==R[i]) modify(qv);
                else modify(i,ql,qr,qv);
            }else{
                if(ql==L[i]&&qr==R[i]) ans[j]+=siz[qv+tag];
                else ans[j]+=query(ql,qr,qv);
            }
        }
    }

    for(rint i=1;i<=m;i++) if(op[i]==2) print(ans[i]);

    return 0;
}