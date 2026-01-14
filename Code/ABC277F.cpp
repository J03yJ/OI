#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()

const int N=4e6+9;

int fi[N],ne[N<<1],to[N<<1],in[N],out[N],adj,cnt;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    in[y]++;
    out[x]++;
}

int tfn[N],n,m,tcnt;
bool Topo(){
    queue<int> q;
    for(int i=0;i<m;i++) if(!in[i]&&out[i]) q.push(i);
    while(q.size()){
        int x=q.front();
        q.pop();
        tfn[++tcnt]=x;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            in[y]--;
            if(!in[y]) q.push(y);
        }
    }
    for(int i=0;i<m;i++) if(in[i]) return 1;
    return 0;
}

int main(){
    cin>>n>>m;
    cnt=m;

    vector<vector<int>> a(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>a[i][j];
    }

    for(int i=0;i<n;i++){
        vector<pair<int,int>> v;
        map<int,int> mp;
        for(int j=0;j<m;j++){
            if(!a[i][j]) continue ;
            v.push_back({a[i][j],j});
            if(!mp[a[i][j]]) mp[a[i][j]]=++cnt;
        }
        for(int j=0;j<m;j++){
            if(!a[i][j]) continue ;
            AdEg(j,mp[a[i][j]]);
            auto it=mp.lower_bound(a[i][j]);
            if(it==mp.begin()) continue ;
            it--;
            AdEg(it->second,j);
        }
    }
    if(Topo()){
        cout<<"No"<<endl;
        return 0;
    }

    vector<pair<int,int>> seg;
    for(int i=0;i<n;i++){
        int mx=0,mn=m*n+1;
        for(int x:a[i]) if(x) mx=max(mx,x),mn=min(mn,x);
        if(mx) seg.push_back({mn,mx});
    }

    int err=0;
    sort(seg.begin(),seg.end());
    for(int i=0,lst=0;i<ssiz(seg);i++){
        if(lst>seg[i].first) err=-1;
        lst=seg[i].second;
    }

    if(err==-1) cout<<"No"<<endl;
    else cout<<"Yes"<<endl;

    return 0;
}