## 引入

给定积性函数 $f(x)$，求：

$$\sum_{i=1}^n f(i)$$

## 解法

考虑将贡献拆成两部分：

$$\sum _{i=1}^n f(i)=\sum _{i\in P} f(i)+\sum _{i\notin P} f(i)$$

其中 $P$ 是质数集合。

### 质数贡献的计算

#### 一些定义

首先构建一个积性函数 $F(x)$：

$$F(x)=\left \{ \begin{matrix} f(x)&x\in P\\\\f(lpf(x))f(\frac {x}{lpf(x)})&x\notin P\end{matrix} \right. $$

其中 $lpf(x)$ 代表 $x$ 的最小质因数。

显然 $F(x)$ 是完全积性函数，且在质数上的取值与 $f(x)$ 相等。

然后考虑一个神仙 DP 数组 $g(x,k)$：

$$g(x,k)=\sum _{i\in P\vee lpf(i)>p_k} F(i)$$

其中 $p_k$ 表示第 $k$ 个质数，特别的，$p_0=1$。

#### 如何递推

现在需要从 $g(x,k)$ 推到 $g(x,k+1)$，首先显然有 $g(x,k) \geq g(x,k+1)$。然后发现去掉的贡献是所有 $lpf(x)=k$ 的合数 $x$ 产生的贡献，所以有：

$$g(x,k+1)=g(x,k)-F(p_{k+1})(g(\lfloor \frac {x}{p_{k+1}}\rfloor ,k)-g(p_k,k))$$

解释：

- 因为 $F(x)$ 是完全积性函数，所以可以直接提出 $F(p_{k+1})$。
- 因为 $g(\lfloor \frac{x}{p_{k+1}}\rfloor,k)$ 中包含了一部分质数，所以要减去 $g(p_k,k)$。

式子可以进一步化成：

$$g(x,k+1)=g(x,k)-f(p_{k+1})g(\lfloor \frac {x}{p_{k+1}}\rfloor ,k)+f(p_{k+1})\sum _{i=1}^k f(p_i)$$

### 计算全部的贡献

仍然考虑 DP，设 $S(x,k)$：

$$S(x,k)=\sum _{lpf(i)>p_k} f(i)$$

进一步拆贡献：

$$S(x,k)=g(x,+\infty)-\sum _{i=1}^k f(p_i)+\sum _{i>k}\sum _{p_i^e\leq x}f(p_i^e)(S(\frac {x}{p_i^e},i)+[e>1])$$

解释：

- 前半部分在计算质数的贡献。
  
  容易发现：$g(x,+\infty)=\sum _{p_i\leq x} f(p_i)$。所以 $g(x,+\infty)-\sum _{i=1}^k f(p_i)$ 本质上是在计算所有大于 $p_k$ 的质数的 $f$ 值之和。

- 后半部分在计算合数的贡献。
  
  考虑枚举 $lpf(x)$ 和其指数，这部分的贡献是 $\sum _{i>k}\sum _{p_i^e\leq x}f(p_i^e)S(\frac {x}{p_i^e},i)$，然而 $S(\frac {x}{p_i^e},i)$ 的结果并不包括 $f(1)$，所以对于 $e>1$ 的情况要把 $f(p_i^e)$ 加上。

答案即为 $S(n,0)$。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;
const int mod=1e9+7;

int sqr,n;

bool ntp[N];
int pri[N],cnt;
void InitP(){
    pri[0]=1;
    for(int i=2;i<=sqr;i++){
        if(!ntp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=sqr;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]==0) break ;
        }
    }
}
int g[3][N],sp[3][N];
int w[N],pos[2][N],tot;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1; 
    }
    return res;
}
void CalcG(){
    sqr=sqrt(n);
    const int INV2=QPow(2,mod-2);
    const int INV6=QPow(6,mod-2);

    for(int i=1;i<=cnt;i++){
        sp[1][i]=(sp[1][i-1]+pri[i])%mod;
        sp[2][i]=(sp[2][i-1]+pri[i]*pri[i]%mod)%mod;
    }
    for(int l=1,r,tmp;l<=n;l=r+1){
        r=n/(n/l);
        w[++tot]=n/l;
        tmp=w[tot]%mod;
        g[1][tot]=(tmp*(tmp+1)%mod*INV2%mod-1+mod)%mod;
        g[2][tot]=(tmp*(tmp+1)%mod*(tmp*2+1)%mod*INV6%mod-1+mod)%mod;
        if(w[tot]<=sqr) pos[0][w[tot]]=tot;
        else pos[1][n/w[tot]]=tot;
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1,x,cur;j<=tot&&pri[i]*pri[i]<=w[j];j++){
            x=w[j]/pri[i];
            if(x<=sqr) cur=pos[0][x];
            else cur=pos[1][n/x];
            g[1][j]=(g[1][j]-(g[1][cur]-sp[1][i-1]+mod)%mod*pri[i]%mod+mod)%mod;
            g[2][j]=(g[2][j]-(g[2][cur]-sp[2][i-1]+mod)%mod*pri[i]%mod*pri[i]%mod+mod)%mod;
        }
    }
}
int S(int x,int k){
    if(pri[k]>=x) return 0;
    int cur=x<=sqr?pos[0][x]:pos[1][n/x];
    int ans=((g[2][cur]-g[1][cur]+mod)%mod+(sp[1][k]-sp[2][k]+mod)%mod)%mod;
    for(int i=k+1;i<=cnt&&pri[i]*pri[i]<=x;i++){
        for(int e=1,prin=pri[i];prin<=x;e++,prin*=pri[i]){
            int tmp=prin%mod;
            ans=(ans+tmp*(tmp-1)%mod*(S(x/prin,i)+(e>1))%mod)%mod;
        }
    }
    return ans;
}

signed main(){
    cin>>n;
    sqr=sqrt(n);

    InitP();
    CalcG();
    cout<<(S(n,0)+1)%mod<<endl;

    return 0;
}
```