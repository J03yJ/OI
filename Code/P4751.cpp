#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e6+9;
const ll lnf=1e18;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int fa[N],siz[N],hson[N],w[N],n;
inline void DFS(int x){
	siz[x]=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		siz[x]+=siz[y];
		if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
	}
}

struct Node{
	int lc,rc,fa;
	int hib,lob;
	ll f[2][2];
	char op;
}tr[N<<2];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define fa(x) tr[x].fa
#define hib(x) tr[x].hib
#define lob(x) tr[x].lob
#define f(x,i,j) tr[x].f[i][j]
#define op(x) tr[x].op

inline void PushUp(int x){
	if(op(x)=='N'){
		f(x,0,0)=0;
		f(x,0,1)=w[lob(x)];
		f(x,1,0)=w[hib(x)];
		f(x,1,1)=-lnf;
	}else if(op(x)=='C'){
		f(x,0,0)=max(f(lc(x),0,0)+f(rc(x),0,0),f(lc(x),0,1)+f(rc(x),1,0)-w[lob(lc(x))]);
		f(x,0,1)=max(f(lc(x),0,0)+f(rc(x),0,1),f(lc(x),0,1)+f(rc(x),1,1)-w[lob(lc(x))]);
		f(x,1,0)=max(f(lc(x),1,0)+f(rc(x),0,0),f(lc(x),1,1)+f(rc(x),1,0)-w[lob(lc(x))]);
		f(x,1,1)=max(f(lc(x),1,0)+f(rc(x),0,1),f(lc(x),1,1)+f(rc(x),1,1)-w[lob(lc(x))]);
	}else{
		f(x,0,0)=f(lc(x),0,0)+max(f(rc(x),0,0),f(rc(x),0,1));
		f(x,0,1)=f(lc(x),0,1)+max(f(rc(x),0,0),f(rc(x),0,1));
		f(x,1,0)=f(lc(x),1,0)+max(f(rc(x),1,0),f(rc(x),1,1))-w[hib(lc(x))];
		f(x,1,1)=f(lc(x),1,1)+max(f(rc(x),1,0),f(rc(x),1,1))-w[hib(lc(x))];
	}
}

int fa[N],siz[N],hson[N];
inline void DFS(int x){

}

int id[N];
inline void Build(int x){

}

signed main(){
	return 0;
}