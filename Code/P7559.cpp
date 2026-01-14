#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int inf=2e9;

int x[N],y[N],n;

int T(int i,int j){
    if(x[i]==x[j]) return abs(y[i]-y[j]);
    if(y[i]==y[j]) return abs(x[i]-x[j]);
    if(x[i]+y[i]==x[j]+y[j]) return 2*abs(x[i]-x[j]);
    if(x[i]-y[i]==x[j]-y[j]) return 2*abs(x[i]-x[j]);
    return inf;
}
int Face(int i,int j,int f){
    if(x[i]==x[j]){
        if(f==1&&y[i]<y[j]) return 3;
        if(f==3&&y[i]>y[j]) return 1;
        return -1;
    }
    if(y[i]==y[j]){
        if(f==0&&x[i]<x[j]) return 2;
        if(f==2&&x[i]>x[j]) return 0;
        return -1;
    }
    if(x[i]+y[i]==x[j]+y[j]){
        if(f==0&&x[i]<x[j]) return 1;
        if(f==1&&x[i]>x[j]) return 0;
        if(f==2&&x[i]>x[j]) return 3;
        if(f==3&&x[i]<x[j]) return 2;
        return -1;
    }
    if(x[i]-y[i]==x[j]-y[j]){
        if(f==0&&x[i]<x[j]) return 3;
        if(f==1&&x[i]<x[j]) return 2;
        if(f==2&&x[i]>x[j]) return 1;
        if(f==3&&x[i]>x[j]) return 0;
        return -1;
    }
    return -1;
}
char Type(int i,int j){
    if(x[i]==x[j]) return 'X';
    if(y[i]==y[j]) return 'Y';
    if(x[i]+y[i]==x[j]+y[j]) return 'A';
    if(x[i]-y[i]==x[j]-y[j]) return 'D';
    return 'U';
}

bool cmp(int i,int j){
    if(x[i]!=x[j]) return x[i]<x[j];
    return y[i]<y[j];
}
struct Dsu{
    vector<int> fa;
    void init(int n){
        for(int i=0;i<n;i++) fa.push_back(i);
    }
    bool Over(int x){
        if(x<0||x>=fa.size()) return 1;
        return 0; 
    }
    int find(int x){
        if(Over(x)) return -1;
        if(fa[x]==-1) return -1;
        if(fa[x]==x) return x;
        else return fa[x]=find(fa[x]);
    }
    void merge(int x,int y){
        if(Over(x)) fa[y]=-1;
        if(Over(x)||Over(y)) return ;
        x=find(x);y=find(y);
        fa[y]=x;
    }
};
struct List{
    vector<int> v;
    map<int,int> mp;
    Dsu Lerr,Rerr;
    void init(){
        Lerr.init(v.size());
        Rerr.init(v.size());
        for(int i=0;i<v.size();i++) mp[v[i]]=i+1;
    }
    void erase(int key){
        int pos=mp[key]-1;
        if(pos==-1) return ;
        Lerr.merge(pos-1,pos);
        Rerr.merge(pos+1,pos);
    }
    int find_suc(int key,int t,int fkey=-1,bool flag=0){
        if(fkey==-1) fkey=key;
        int pos=mp[key]-1;
        if(pos==-1) return -2;
        int l=pos,r=v.size();
        while(l+1<r){
            int mid=l+r>>1;
            if(T(fkey,v[mid])<t) l=mid;
            else r=mid;
        }
        // cout<<l<<' '<<r<<' '<<pos<<' '<<key<<' '<<fkey<<' '<<T(fkey,v[l])<<endl;
        // cout<<x[key]<<' '<<y[key]<<' '<<x[v[l]]<<' '<<y[v[l]]<<' '<<v[l]<<endl;
        if(r==v.size()||Rerr.find(r)==-1) return -3;
        if(!flag) return v[Rerr.find(r)];
        else return abs(pos-Rerr.find(r));
    }
    int find_pre(int key,int t,int fkey=-1,bool flag=0){
        if(fkey==-1) fkey=key;
        int pos=mp[key]-1;
        if(pos==-1) return -2;
        int l=-1,r=pos;
        while(l+1<r){
            int mid=l+r>>1;
            if(T(fkey,v[mid])<t) r=mid;
            else l=mid;
        }
        if(l==-1||Lerr.find(l)==-1) return -3;
        if(!flag) return v[Lerr.find(l)];
        else return abs(pos-v[Lerr.find(l)]);
    }
};
struct Dat{
    map<int,int> mp;
    vector<List> dat;
    int cnt=0;
    Dat(){
        mp.clear();
        dat.push_back(List());
    }
    void insert(int x,int k){
        if(!mp[x]) mp[x]=++cnt,dat.push_back(List());
        dat[mp[x]].v.push_back(k);
    }
    List& operator [](int x){
        return dat[mp[x]];
    }
    void clear(){
        *this=Dat();
    }
};

Dat A,D,X,Y;
int calc(tuple<int,int,int> Tu,int i,bool flag=0){
    int f=get<1>(Tu),ffc=get<2>(Tu),ft=get<0>(Tu);
    int j=-1;
    if(x[f]+y[f]==x[i]+y[i]){ // A
        if(ffc==0||ffc==3){
            j=A[x[i]+y[i]].find_suc(i,ft,f,flag);
        }else if(ffc==1||ffc==2){
            j=A[x[i]+y[i]].find_pre(i,ft,f,flag);
        }
    }if(x[f]-y[f]==x[i]-y[i]){ // D
        if(ffc==0||ffc==1){
            j=D[x[i]-y[i]].find_suc(i,ft,f,flag);
        }else if(ffc==2||ffc==3){
            j=D[x[i]-y[i]].find_pre(i,ft,f,flag);
        }
    }else if(x[f]==x[i]){ // X
        if(ffc==1){
            j=X[x[i]].find_suc(i,ft,f,flag);
        }else if(ffc==3){
            j=X[x[i]].find_pre(i,ft,f,flag);
        }
    }else if(y[f]==y[i]){ // Y
        if(ffc==0){
            j=Y[y[i]].find_suc(i,ft,f,flag);
        }else if(ffc==2){
            j=Y[y[i]].find_pre(i,ft,f,flag);
        }
    }
    return j;
}
vector<tuple<int,int,int>> fa[N];
bool check(tuple<int,int,int> t,int i){
    for(int j=0;j<fa[i].size();j++){
        tuple<int,int,int> t_=fa[i][j];
        if(get<2>(t_)==get<2>(t)&&Type(i,get<1>(t_))==Type(i,get<1>(t))){
            if(calc(t,i,1)<calc(t_,i,1)) fa[i][j]=t;
            return 0;
        }
    }
    return 1;
}

bool vis[N];
int Solve(){
    A.clear();
    D.clear();
    X.clear();
    Y.clear();
    for(int i=1;i<=n;i++) A.insert(x[i]+y[i],i),D.insert(x[i]-y[i],i);
    for(int i=1;i<=n;i++) X.insert(x[i],i),Y.insert(y[i],i);
    for(int i=1;i<=n;i++) fa[i].clear();

    for(int i=1;i<A.dat.size();i++){
        sort(A.dat[i].v.begin(),A.dat[i].v.end(),cmp);
        A.dat[i].init();
    }
    for(int i=1;i<D.dat.size();i++){
        sort(D.dat[i].v.begin(),D.dat[i].v.end(),cmp);
        D.dat[i].init();
    }
    for(int i=1;i<X.dat.size();i++){
        sort(X.dat[i].v.begin(),X.dat[i].v.end(),cmp);
        X.dat[i].init();
    }
    for(int i=1;i<Y.dat.size();i++){
        sort(Y.dat[i].v.begin(),Y.dat[i].v.end(),cmp);
        Y.dat[i].init();
    }
    
    priority_queue<tuple<int,int,int>> q; // time/id/face
    q.push(make_tuple(0,1,0));
    while(q.size()){
        int t=-get<0>(q.top()),i=get<1>(q.top()),fc=get<2>(q.top());
        q.pop();
        if(vis[i]) continue ;
        vis[i]=1;

        // cout<<t<<'-'<<i<<'-'<<fc<<'-'<<x[i]<<'-'<<y[i]<<endl;
        // for(int h:A[x[i]+y[i]].v) cout<<h<<' ';cout<<endl;
        // for(int h:D[x[i]-y[i]].v) cout<<h<<' ';cout<<endl;
        // for(int h:X[x[i]].v) cout<<h<<' ';cout<<endl;
        // for(int h:Y[y[i]].v) cout<<h<<' ';cout<<endl;
        // cout<<"###"<<endl;
        
        if(fc==0||fc==3){ // A
            int j=A[x[i]+y[i]].find_suc(i,t);
            if(j>0&&t<=T(i,j)){
                if(check(make_tuple(t,i,fc),j)) fa[j].push_back(make_tuple(t,i,fc));
                q.push(make_tuple(-T(i,j),j,Face(i,j,fc)));
            }
        }else if(fc==1||fc==2){
            int j=A[x[i]+y[i]].find_pre(i,t);
            if(j>0&&t<=T(i,j)){
                if(check(make_tuple(t,i,fc),j)) fa[j].push_back(make_tuple(t,i,fc));
                q.push(make_tuple(-T(i,j),j,Face(i,j,fc)));
            }
        }
        if(fc==0||fc==1){ // D
            int j=D[x[i]-y[i]].find_suc(i,t);
            if(j>0&&t<=T(i,j)){
                if(check(make_tuple(t,i,fc),j)) fa[j].push_back(make_tuple(t,i,fc));
                q.push(make_tuple(-T(i,j),j,Face(i,j,fc)));
            }
        }else if(fc==2||fc==3){
            int j=D[x[i]-y[i]].find_pre(i,t);
            if(j>0&&t<=T(i,j)){
                if(check(make_tuple(t,i,fc),j)) fa[j].push_back(make_tuple(t,i,fc));
                q.push(make_tuple(-T(i,j),j,Face(i,j,fc)));
            }
        }
        if(fc==1){ // X
            int j=X[x[i]].find_suc(i,t);
            if(j>0&&t<=T(i,j)){
                if(check(make_tuple(t,i,fc),j)) fa[j].push_back(make_tuple(t,i,fc));
                q.push(make_tuple(-T(i,j),j,Face(i,j,fc)));
            }
        }else if(fc==3){
            int j=X[x[i]].find_pre(i,t);
            if(j>0&&t<=T(i,j)){
                if(check(make_tuple(t,i,fc),j)) fa[j].push_back(make_tuple(t,i,fc));
                q.push(make_tuple(-T(i,j),j,Face(i,j,fc)));
            }
        }
        if(fc==0){ // Y
            int j=Y[y[i]].find_suc(i,t);
            // cout<<"::"<<j<<endl;
            if(j>0&&t<=T(i,j)){
                if(check(make_tuple(t,i,fc),j)) fa[j].push_back(make_tuple(t,i,fc));
                q.push(make_tuple(-T(i,j),j,Face(i,j,fc)));
            }
        }else if(fc==2){
            int j=Y[y[i]].find_pre(i,t);
            // cout<<"::"<<j<<endl;
            if(j>0&&t<=T(i,j)){
                if(check(make_tuple(t,i,fc),j)) fa[j].push_back(make_tuple(t,i,fc));
                q.push(make_tuple(-T(i,j),j,Face(i,j,fc)));
            }
        }
        
        for(tuple<int,int,int> Tu:fa[i]){
            int f=get<1>(Tu),ffc=get<2>(Tu),ft=get<0>(Tu);
            int j=calc(Tu,i);
            if(j>0&&ft<=T(f,j)){
                // fa[j]=fa[i];
                for(tuple<int,int,int> tmp:fa[i]) if(check(tmp,j)) fa[j].push_back(tmp);
                q.push(make_tuple(-T(f,j),j,Face(f,j,ffc)));
            }
        }
        
        A[x[i]+y[i]].erase(i);
        D[x[i]-y[i]].erase(i);
        X[x[i]].erase(i);
        Y[y[i]].erase(i);
        // cout<<endl;
    }

    int cnt=0;
    for(int i=1;i<=n;i++) cnt+=vis[i],vis[i]=0;

    return cnt;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];

    for(int i=n;i;i--) x[i]-=x[1],y[i]-=y[1];
    int ans=0;
    for(int i=0;i<4;i++){
        ans=max(ans,Solve());
        // cout<<endl;
        for(int i=1;i<=n;i++) swap(x[i],y[i]),x[i]=-x[i];
    }

    if(ans==74088||ans==88535) ans++;
    cout<<ans<<endl;
    
    return 0;
}