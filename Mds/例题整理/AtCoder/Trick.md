## 阈值分治

### ABC259Ex

$\tt\color{orange} Diff:2406$

#### 题目大意

给定一个 $N\times N$ 的矩阵 $a$，$a_{i,j}$ 表示 $(i,j)$ 处的颜色为 $a_{i,j}$。求起点和终点颜色相同的路径的数目。

数据范围：

- $N\leq 4\times 10^2$
- $a_{i,j}\leq N^2$

#### 题解

考虑阈值分治，对于颜色 $c$：

- 若颜色为 $c$ 的格子数 $cnt_c\leq N$，则枚举颜色均为 $c$ 的点对 $(i,j)$ 与 $(p,q)$，贡献为 $C_{p-i+q-j}^{p-i}$。时间复杂度为 $O(N^3)$。
- 若颜色为 $c$ 的格子数 $cnt_c\gt N$，则考虑 DP。设 $f_{i,j}$ 表示从一个颜色为 $c$ 的点到 $(i,j)$ 的路径数，初值是 $f_{i,j}=[a_{i,j}=c]$，贡献 $\displaystyle\sum_{i,j} f_{i,j} [a_{i,j}=c]$。 由于此类颜色最多有 $N$ 个，所以时间复杂度为 $O(N^3)$。

#### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define ssiz(x) (signed)x.size()
const int N=4e2+9;
const int M=N*N;
const int K=1e3;
const int mod=998244353;

int a[N][N],c[K+9][K+9],f[N][N],n,ans;
vector<pair<int,int>> d[M];
#define F(x,y,z,w) c[(z)-(x)+(w)-(y)][(z)-(x)]
#define G(x,y) F(x.first,x.second,y.first,y.second)
void Solve1(int x){
    for(int i=0;i<ssiz(d[x]);i++){
        for(int j=0;j<ssiz(d[x]);j++){
            if(d[x][i].first>d[x][j].first) continue ;
            if(d[x][i].second>d[x][j].second) continue ;
            ans=(ans+G(d[x][i],d[x][j]))%mod;
        }
    }
}
void Solve2(int x){
    memset(f,0,sizeof f);
    for(auto p:d[x]) f[p.first][p.second]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=(f[i][j]+f[i-1][j])%mod;
            f[i][j]=(f[i][j]+f[i][j-1])%mod;
        }
    }
    for(auto p:d[x]) ans=(ans+f[p.first][p.second])%mod;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            d[a[i][j]].push_back({i,j});
        }
    }
    for(int i=0;i<=K;i++){
        c[i][0]=1;
        for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }
    for(int i=1;i<=n*n;i++){
        if(ssiz(d[i])>n) Solve2(i);
        else Solve1(i);
    }

    cout<<ans<<endl;

    return 0;
}
```