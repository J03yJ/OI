#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int sN=509;
#define endl '\n'

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

int a[N],n,m;
short blk[N];
int L[sN],R[sN];
short mp[N][sN],cnt[sN],val[N],Dis[N][sN];
int Lval[N],Rval[N];
inline void Chmin(short &x,short y){
    if(x>y) x=y;
}
inline void Chmin(int &x,int y){
    if(x>y) x=y;
}

int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++) a[i]=read();

    int B=200;
    for(int i=1;i<=n;i++){
        blk[i]=(i-1)/B+1;
        if(!L[blk[i]]) L[blk[i]]=i;
        R[blk[i]]=i;
    }
    memset(Dis,0x3f,sizeof(Dis));
    for(int i=1;i<=blk[n];i++){
        for(int j=L[i];j<=R[i];j++){
            if(!mp[a[j]][i]) mp[a[j]][i]=++cnt[i],Lval[cnt[i]+L[i]]=j;
            val[j]=mp[a[j]][i];Rval[val[j]+L[i]]=j;
        }
        for(int j=L[i];j<=R[i];j++){
            for(int k=j;k<=R[i];k++){
                if(val[j]<val[k]) Chmin(Dis[L[i]+val[j]][val[k]],k-j);
                else Chmin(Dis[L[i]+val[k]][val[j]],k-j);
            }
        }
    }

    int lst=0;
    while(m--){
        int op=read(),x=read(),y=read();
        x^=lst;y^=lst;
        short X,Y;
        if(op==1){
            if(x==y) continue ;
            for(register int i=1;i<=blk[n];i++){
                X=mp[x][i];Y=mp[y][i];
                if(!X) continue ;
                if(!Y){
                    mp[y][i]=mp[x][i];
                    mp[x][i]=0;
                    continue ;
                }
                for(short j=1;j<=cnt[i];j++){
                    if(Y<j){
                        if(X<j) Chmin(Dis[L[i]+Y][j],Dis[L[i]+X][j]);
                        else Chmin(Dis[L[i]+Y][j],Dis[L[i]+j][X]);
                    }else{
                        if(X<j) Chmin(Dis[L[i]+j][Y],Dis[L[i]+X][j]);
                        else Chmin(Dis[L[i]+j][Y],Dis[L[i]+j][X]);
                    }
                }
                if(Lval[X+L[i]]<Lval[Y+L[i]]) Lval[Y+L[i]]=Lval[X+L[i]];
                if(Rval[X+L[i]]>Rval[Y+L[i]]) Rval[Y+L[i]]=Rval[X+L[i]];
                mp[x][i]=0;
            }
        }else{
            int ans=n+1;
            if(x!=y){
                for(register int i=1,lx=-1,ly=-1;i<=blk[n];i++){
                    X=mp[x][i];Y=mp[y][i];
                    if(X&&Y){
                        if(X<Y) Chmin(ans,Dis[L[i]+X][Y]);
                        else Chmin(ans,Dis[L[i]+Y][X]);
                    }
                    if(X) if(~ly) Chmin(ans,Lval[X+L[i]]-ly);
                    if(Y) if(~lx) Chmin(ans,Lval[Y+L[i]]-lx);
                    if(X) lx=Rval[X+L[i]];
                    if(Y) ly=Rval[Y+L[i]];
                    if(ans<=1) break ;
                }
            }else for(int i=1;i<=blk[n];i++) if(mp[x][i]) ans=0;
            if(ans==n+1) puts("Ikaros"),lst=0;
            else print(ans),lst=ans;
        }
    }
}