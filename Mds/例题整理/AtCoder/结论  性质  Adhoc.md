## 结论 | 性质 | Adhoc

 ### ABC277F

$\tt\color{orange} Diff:2400$

#### 题目大意

给定一个 $N\times M$ 的矩阵，有些格子没有填数，允许交换任意两行或两列，次数不限，问交换后是否可以满足：

- $A_{1,1}\leq A_{1,2}\leq ... \leq A_{1,m}\leq A_{2,1}\leq A_{2,2}\leq...\leq A_{2,m}\leq ... \leq A_{n,1}\leq A_{n,2} \leq... \leq A_{n,m}$

数据范围：

- $N\times M\leq 10^6$
- $A_{i,j}\leq N\times M$

#### 题解

首先显然有交换后行内，列内元素不变，所以若列 $c_1,c_2$ 中有元素 $c_{1_i},c_{2_i}$ 满足 $c_{1_i}<c_{2_i}$，则 $\forall j\in [1,n]$ 有 $c_{1_j}<c_{2_j}$。

因此，对于一行中已经填掉的数，可以将小数的列号向大数的列号连一条有向边，如果最后的列号构成的有向图 $G$ 是一张 DAG，则一定可以按照拓扑序安排列间交换的顺序且每行内不会冲突，如果某个数是未知的，则取值为距其最近已知的数。

对于行的顺序，先处理出每行的值域 $[L_i,R_i]$，如果 $[L_i,R_i]$ 与 $[L_j,R_j]$ 有交，那么一定无解，否则直接排序即可。

#### 代码

```cpp
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
```
