#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int V=5e5+9;

int a[N],n,m;
int siz[V],st[V],cnt[V];
int val[N*500],fa[N*500];

inline void chmax(int &x,int y){
    if(y>x) x=y;
}

inline int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    fa[find(y)]=find(x);
}

long long tr[N];
void add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
long long ask(int x){
    long long ans=0;
    while(x){
        ans+=tr[x];
        x&=x-1;
    }
    return ans;
}
long long ask(int l,int r){
    if(l>r) return 0;
    return ask(r)-ask(l-1);
}


inline void modify(int l,int r,int k){
    if(k==1) return ;
    int posl=lower_bound(val+st[k],val+st[k+1],l)-val;
    int posr=upper_bound(val+st[k],val+st[k+1],r)-val-1;
    // cout<<posl<<'~'<<posr<<endl;
    if(posl>posr) return ;
    for(int i=find(posl);i<=posr;i=find(i+1)){
        // cout<<i<<' '<<val[i]<<endl;
        if(a[val[i]]%k==0){
            add(val[i],a[val[i]]/k-a[val[i]]);
            a[val[i]]/=k;
        }
        // if(i>=posr) break ;
        if(a[val[i]]%k) merge(i+1,i);
    }
    // cout<<"Done"<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int Max=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        chmax(Max,a[i]);
        siz[a[i]]++;
        add(i,a[i]);
    }

    int tot=0;
    for(int i=1;i<=Max;i++){
        for(int j=i<<1;j<=Max;j+=i) siz[i]+=siz[j];
        st[i]=tot+1,tot+=siz[i];
    }
    st[Max+1]=tot+1;
    for(int i=1;i<=tot;i++) fa[i]=i;
    for(int i=1;i<=n;i++){
        for(int j=1;j*j<=a[i];j++){
            if(a[i]%j) continue ;
            val[st[j]+(cnt[j]++)]=i;
            if(j*j!=a[i]) val[st[a[i]/j]+(cnt[a[i]/j]++)]=i;
        }
    }

    while(m--){
        int op;
        cin>>op;
        if(op==1){
            int l,r,k;
            cin>>l>>r>>k;
            modify(l,r,k);
        }else{
            int l,r;
            cin>>l>>r;
            cout<<ask(l,r)<<endl;
            // for(int i=1;i<=n;i++) cout<<a[i]<<' ';cout<<endl;
        }
    }

    return 0;
}