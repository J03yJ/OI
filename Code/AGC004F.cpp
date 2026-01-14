#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int a[N],c[N],vis[N],fa[N],rng[N],n,m,u,v;
void DFS(int x){
    vis[x]=1;
    a[x]=c[x];
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        if(x==u&&y==v||x==v&&y==u) continue ;
        c[y]=-c[x];
        fa[y]=x;
        DFS(y);
        a[x]+=a[y];
    }
    vis[x]=0;
}
void FindRing(int x,int fa){
    vis[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa) continue ;
        if(vis[y]){
            u=x,v=y;
            continue ;
        }
        FindRing(y,x);
    }
    vis[x]=0;
}

int main(){
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v);
        AdEg(v,u);
    }

    if(m==n-1){
        c[1]=1;
        DFS(1);
        
        int ans=0,cnt1=0,cnt2=0;
        for(int i=1;i<=n;i++){
            if(c[i]==1) cnt1++;
            else cnt2++;
            ans+=abs(a[i]);
        }

        if(cnt1==cnt2) cout<<ans<<endl;
        else cout<<-1<<endl;
    }else if(m==n){
        FindRing(1,-1);
        c[u]=1;
        DFS(u);

        int cnt=0,cur=v;
        while(cur){
            cnt++;
            cur=fa[cur];
        }

        if(cnt&1){
            int cur=v;
            while(cur){
                rng[cur]=1;
                cur=fa[cur];
            }

            int ans=0;
            for(int i=1;i<=n;i++){
                if(!rng[i]) ans+=abs(a[i]);
                else ans+=abs(a[i]-a[u]/2);
            }

            if(a[u]%2==0) cout<<ans<<endl;
            else cout<<-1<<endl;
        }else{
            vector<int> tmp;
            int cur=v;
            while(cur!=u){
                rng[cur]=1;
                tmp.push_back(a[cur]);
                cur=fa[cur];
            }
            sort(tmp.begin(),tmp.end());

            int ans=0,cnt1=0,cnt2=0,k=tmp[tmp.size()/2];
            for(int i=1;i<=n;i++){
                if(c[i]==1) cnt1++;
                else cnt2++;
                if(!rng[i]) ans+=abs(a[i]);
                else ans+=abs(a[i]-k);
            }

            if(cnt1==cnt2) cout<<ans+abs(k)<<endl;
            else cout<<-1<<endl;
        }
    }

    return 0;
}