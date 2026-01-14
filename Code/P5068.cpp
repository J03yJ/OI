#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int c[N],vis[N],n,m;

struct Fenw{
    int tr[N];
    void Add(int x,int k){
        while(x<=(n<<1)){
            tr[x]+=k;
            x+=x&-x;
        }
    }
    int Ask(int x){
        int sum=0;
        while(x){
            sum+=tr[x];
            x&=x-1;
        }
        return sum;
    }
}ans,b;

vector<int> v[N<<2];
void Insert(int x,int L,int R,int l,int r,int k){
    if(l<=L&&R<=r){
        v[x].push_back(k);
        return ;
    }
    int mid=L+R>>1;
    if(l<=mid) Insert(x<<1,L,mid,l,r,k);
    if(r>mid) Insert(x<<1|1,mid+1,R,l,r,k);
}
void Modify(int x,int L,int R,int k){
    for(int val:v[x]){
        if((c[val]-1)*val+1>L||c[val]*val<R) continue ;
        while((c[val]-1)*val+1<=n){
            if(b.Ask((c[val]-1)*val)==b.Ask(c[val]*val)) break ;
            c[val]++;
            ans.Add(val,1);
        }
        if((c[val]-1)*val+1<=n) Insert(1,1,n<<1,(c[val]-1)*val+1,c[val]*val,val);
    }
    v[x].clear();
    if(L==R) return ;
    int mid=L+R>>1;
    if(k<=mid) Modify(x<<1,L,mid,k);
    if(k>mid) Modify(x<<1|1,mid+1,R,k);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        c[i]=1;
        ans.Add(i,1);
        Insert(1,1,n<<1,1,i,i);
    }
    while(m--){
        int op;
        cin>>op;
        if(op==1){
            int x;
            cin>>x;
            if(!vis[x]) b.Add(x,1),vis[x]=1;
            Modify(1,1,n<<1,x);
        }else{
            int l,r;
            cin>>l>>r;
            cout<<ans.Ask(r)-ans.Ask(l-1)<<endl;
        }
    }
    
    return 0;
}