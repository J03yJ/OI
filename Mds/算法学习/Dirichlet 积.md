# 简介

本文搬运自 maspy 的 [Dirichlet 積と、数論関数の累積和](https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c)。

熟肉，侵删，与原文略有所不同*。

*：包括但不限于翻译细节，代码语言\*\* 等。

\*\*：本文中所有 Python 语言的的代码为 maspy 本人所写，C++ 的为译者所写。

# Dirichlet 级数和 Dirichlet 积

定义域为自然数集 $\N = \{1,2,3,\ldots \}$ 的函数 $ a, b : \N \longrightarrow \mathbb C $ 有时被称为数论函数。

由 $c(n) = \sum_{ij=n}a(i)b(j)$ 定义的函数 $c : \N \longrightarrow \mathbb C$ 被称为 $a, b$ 的 Dirichlet 积。在这篇文章中，我们用 $c = a * b$ 来表示。这个积满足交换律、结合律和分配律。

这可以看作是关于单元素 $(\N, \times)$ 的卷积运算。$(\N\cup\{0\}, +)$ 的卷积运算可以通过形式幂级数来简化和整理其性质，但在 $(\N, \times)$ 的情况下，通常用 Dirichlet 级数来表示。也就是说，数列  $\{a_n\}$ 被替换为：

$$D_a(s) = \sum_{n=1}^{\infty} a_nn^{-s}$$

这样，$c = a * b \iff D_c = D_aD_b$ 并且 Dirichlet 积转换为级数的乘积。

- 我们通过扩展 $i^{-s}\cdot j^{-s} = (ij)^{-s}$ 来定义积，以满足分配律。
- 也有考虑 $Re(s)$ 足够大的复数 $s$ 的代入的情况，但这次我们忽略收敛等细节。
- 「$-s$」 的符号是由于历史原因，但在这篇文章中并不重要。如果书写方便，可以将所有符号改为「$+s$」，也不会有不便。

此外，虽然我们使用无限数列来形式化定义，但基本上只处理数组中 $1\leq n\leq N$ 的部分。

## Dirichlet 积的时间复杂度

当 $a$ 和 $b$ 已知，并且计算 $c = a * b$ 时，可以在 $O(N \log N)$ 的时间复杂度内计算 $c(1), \ldots, c(N)$，方法如下：

```python
# Python
c = [0] * (N+1)
for i in range(1, N+1):
  for j in range(1, N//i+1):
    c[i*j] += a[i] * b[j]
```
```cpp
// C++
for(int i=1;i<=N;i++){
    for(int j=1;j<=N/i;j++) c[i*j]+=a[i]*b[j];
}
```

## 积性函数的 Dirichlet 级数

如果 $a(1)=1$ 并且对于互质的 $n,m$，$a(nm)=a(n)a(m)$ 成立，这样的数论函数 $a$ 被称为积性的，可以从素数幂的值 $a(p^k)$ 恢复所有 $a(n)$。这是著名的，例如约数的数量和和、Euler 函数等。

用 Dirichlet 级数表示，级数具有 Euler 乘积分解：

$$D_a(s) = \prod_p \Bigl(\sum_{k}a(p^k)p^{-ks}\Bigr)$$

### $O(N \log \log N)$ 时间内的计算

当 $a$ 是积性的时候，$a * b$ 的计算可以在 $O(N \log \log N)$ 时间内完成。利用 $a$ 分解为稀疏函数的 Euler 乘积，重复进行 $p$ 部分的乘法。用 Dirichlet 积表示，

```python
# Python
for p in primes:
  D_{a,p}(s) = sum a(p^k) p^{-ks}  (p-part of D_a)
  D_b(s) ← D_b(s) D_{a,p}(s)
```
```cpp
// C++
for(int p:primes){
    for(int k:{...}) D_a[p](s)=a(pow(p,k))*pow(p,k*s);
    D_b(s)*=D_a[p](s);
}
```

通过进行计算，

```python
# Python
c = b
for p in primes:
  for i in range(N//p, 0, -1):
    n = p * i
    # 当 n = (p^k) * m 时，更新 c[n] ← c[n] + a[p^k] * c[m]
    q, m = p, i
    while True:
      c[n] += a[q] * c[m]
      if m % p != 0:
        break
      q, m = q * p, m // p
```
```cpp
// C++
c=b;
for(int p:primes){
    for(int i=1;i<=N/p;i++){
        int n=i*p,q=p,m=i;
        while(true){
            c[n]+=a[q]*c[m];
            if(m%p!=0) break ;
            q*=p;
            m/=p;
        }
    }
}
```

注意更新顺序，以避免覆盖后续计算所需的部分。时间复杂度为：

$$\sum_{q=p^k\leq N}\Bigl\lfloor\frac{N}{q}\Bigr\rfloor=\sum_{p\leq N} \Bigl\lfloor\frac{N}{p}\Bigr\rfloor + O(N) = O(N\log\log N)$$

其中 $q$ 是素数幂，$p$ 是素数。

### $O(N)$ 时间内的计算

如果 $c$ 是积性的（特别是 $a, b$ 都是积性的），则当 $n$ 可以写成素数 $p$ 的恰好 $k$ 次幂 $n = p^k m$ 时，$c(n) = c(p^k)c(m)$ 成立。利用这一点，可以在 $O(N)$ 时间内计算 $c(1), \ldots, c(N)$：

1. 对于素数幂 $p^k\leq N$，直接计算 $c(p^k)$（$O(k^2)$ 时间）。
2. 按顺序计算不是素数幂的 $n = 6 ,10 ,12 
, \ldots$，通过 $n = p^k m$ 计算 $c(n) = c(p^k)c(m)$。

需要预先计算每个 $n$ 可以被 $p^k$ 除的部分。这个预处理也可以通过线性筛在 $O(N)$ 时间内完成。

# Dirichlet 积和累积和

对于数论函数 $a$，定义 $A(n) = \sum_{i=1}^n a(i)$。在这篇文章中，我们将小写字母和大写字母对应起来，表示 $a$ 的累积和为 $A$，$b$ 的累积和为 $B$，$c$ 的累积和为 $C$。

首先，确认以下内容。

> **【命题 1】** 假设 $c = a * b$，并且任意 $1 \leq i \leq N$ 对于 $a(i), b(i), A(i), B(i)$ 已知。$C(N)$ 可以在 $O(\sqrt{N})$ 的时间复杂度内计算。

先对 $C(N)$ 进行变形：

$$C(N) = \sum_{n=1}^N \sum_{ij=n}a(i)b(j) = \sum_{ij\leq N}a(i)b(j)$$

进一步，设 $M = \lfloor \sqrt{N} \rfloor$，变形为 $\sum_{i,j} = \sum_{i\leq M} + \sum_{i > M}$。

- 固定 $i \leq M$。$ij\leq N \iff j\leq \lfloor N/i \rfloor$，所以这部分可以计算为 $a(i)B(\lfloor N/i \rfloor)$。
- 当 $i > M$ 时，必须有 $j \leq M$。固定 $j$ 时，$i$ 的范围是 $M < i \leq \lfloor N/j \rfloor$，所以固定的 $j$ 的贡献为 $b(j)\bigl(A(\lfloor N/j \rfloor) – A(M)\bigr)$。

通过相加，$C(N)$ 可以在 $O(\sqrt{N})$ 的时间复杂度内计算。

* * *

当 $N$ 很大时，这种计算中所需的 $a(i), b(i), A(i), B(i)$ 的索引非常稀疏。再次设 $M = \lfloor \sqrt{N} \rfloor$。

>  **【命题 2】** 假设 $c = a * b$，并且计算了以下形式的所有内容。
>
> - 对于 $1 \leq i \leq M$ 的 $i$，$a(i), b(i)$
> - 对于 $1 \leq i \leq M$ 的 $i$，$A(\lfloor N/i \rfloor)$, $B(\lfloor N/i \rfloor)$
>
> 这时，$C(N)$ 可以在 $O(\sqrt{N})$ 的时间复杂度内计算。

计算方法完全相同。进一步进行相同的操作，可以得到以下内容。

> **【命题 3】** 假设 $c = a * b$，并且计算了以下形式的所有内容。
>
> - 对于 $1 \leq i \leq M$ 的 $i$，$a(i), b(i)$
> - 对于 $1 \leq i \leq M$ 的 $i$，$A(\lfloor N/i \rfloor)$, $B(\lfloor N/i \rfloor)$
> 
> 这时，以下所有内容都可以在总共 $O(N^{3/4})$ 的时间复杂度内计算。
> 
> - 对于 $1 \leq i \leq M$ 的 $i$，$c(i)$
> - 对于 $1 \leq i \leq M$ 的 $i$，$C(\lfloor N/i \rfloor)$

计算 $c(1), \ldots, c(M)$ 需要 $O(M\log M) = O(N^{1/2}\log N)$ 时间。

每个 $C(\lfloor N/i \rfloor)$ 的计算每次需要 $O(\sqrt{N/i})$ 的时间复杂度。

但是，$\int_{1}^M\frac{1}{\sqrt{t}}dt = O(\sqrt{M})$ 等等，从整体上看，总共是 $O(N^{3/4})$ 的时间复杂度。

* * *

通过使用 $\sqrt{n}$ 划分的思想，自然地得到了 $O(N^{3/4})$ 这样的计算量，但实际上这个计算量可以很容易地降低。

> **【命题 4】** 设 $N \leq KL$。假设 $c = a * b$，并且计算了以下形式的所有内容。
>
> - 对于 $1 \leq i \leq K$ 的 $i$，$a(i), b(i)$
> - 对于 $1 \leq i \leq L$ 的 $i$，$A(\lfloor N/i \rfloor)$, $B(\lfloor N/i \rfloor)$
>
> 这时，以下所有内容都可以在总共 $O(K\log K + (NL)^{1/2})$ 的时间复杂度内计算。
>
> - 对于 $1 \leq i \leq K$ 的 $i$，$c(i)$
> - 对于 $1 \leq i \leq L$ 的 $i$，$C(\lfloor N/i \rfloor)$
>
> 特别是，当 $K = \lceil (N/\log N)^{2/3} \rceil$, $L = \lceil N^{1/3}(\log N)^{2/3} \rceil$ 时，时间复杂度是 $O(N^{2/3}(\log N)^{1/3})$。
>
> 此外，这个时间复杂度可以根据以下条件减少。
>
> - 如果 $a, b$ 其中之一是积性的，则时间复杂度是 $O(N^{2/3}(\log \log N)^{1/3})$
> - 如果 $a, b$ 都是积性的，则时间复杂度是 $O(N^{2/3})$

$C(N)$ 单个计算时，$N^{1/2}$ 的划分是最优的，但是当一起计算许多值时，$N^{2/3}$ 左右的划分可以使顺序得到改善。

算法相同，

- 计算 $c(1), \ldots, c(K)$，需要 $O(K\log K)$ 时间。
- 计算 $A(1), \ldots, A(K)$ 以及 $B(1), \ldots, B(K)$ 需要 $O(K)$ 的时间复杂度。
- 对于每个 $1 \leq i \leq L$，计算 $C(\lfloor N/i \rfloor)$，每个 $i$ 需要 $O(\sqrt{N/i})$ 的时间复杂度（【命题 2】）。$1 \leq i \leq L$ 的总时间复杂度是 $O((NL)^{1/2})$。

因此，总共是 $O(K\log K + (NL)^{1/2})$。

另外，如果 $a, b$ 都是积性的，Dirichlet 积的计算会更快速，上述计算总共是 $O(K + (NL)^{1/2})$ 的时间复杂度。这时，$K = \lceil N^{2/3} \rceil$, $L = \lceil N^{1/3} \rceil$，所以时间复杂度是 $O(N^{2/3})$。

### 除法的计算

通过巧妙地追溯相同的讨论，可以进行以下操作。需要 $a_1 \neq 0$。

> **【命题 5】** 设 $N \leq KL$。假设 $a * b = c$，并且计算了以下形式的所有内容。
> 
> - 对于 $1 \leq i \leq K$ 的 $i$，$a(i), c(i)$
> - 对于 $1 \leq i \leq L$ 的 $i$，$A(\lfloor N/i \rfloor)$, $C(\lfloor N/i \rfloor)$
> 
> 这时，以下所有内容都可以在总共 $O(K\log K + (NL)^{1/2})$ 时间内计算。
> 
> - 对于 $1 \leq i \leq K$ 的 $i$，$b(i)$
> - 对于 $1 \leq i \leq L$ 的 $i$，$B(\lfloor N/i \rfloor)$
> 
> 特别是，当 $K = \lceil (N/\log N)^{2/3} \rceil$, $L = \lceil N^{1/3}(\log N)^{2/3} \rceil$ 时，是 $O(N^{2/3}(\log N)^{1/3})$ 时间。
> 
> 此外，这个时间计算量可以根据以下条件减少。
> 
> - 如果 $a, c$ 其中之一是乘法的，则是 $O(N^{2/3}(\log \log N)^{1/3})$ 时间
> - 如果 $a, c$ 都是乘法的，则是 $O(N^{2/3})$ 时间

【命题 4】的类似。【命题 1】中出现的变形等，用于从较小的 $b(i)$, $B(i)$ 依次计算。例如，从 Dirichlet 积的定义 $c(n) = a(1)b(n) +$ 更小的 $b(i)$ 的贡献，可以计算 $b(1), b(2), \ldots, b(K)$。计算累积和得到 $B(1), \ldots, B(K)$。从 $C(n) = a(1)B(n) +$ 更小的 $B(i)$ 的贡献，可以依次计算 $B(\lfloor N/i \rfloor)$。 

虽然不介绍详细的实现，但请在解决后面的问题的同时考虑细节。

**【命题 2】的类似不成立。** 也就是说，即使只需要一个点 $C(N)$ 的值，也需要在计算大 $N$ 的 $C(N)$ 时使用小的 $C(i)$ 的值，因此时间复杂度为 $O(N^{2/3 + \epsilon})$。

# 具体例子

代表性的 Dirichlet 级数是 $\zeta(s) = \sum_{n=1}^{\infty}n^{-s}$。此外，这种平行移动 $\zeta(s-k) = \sum_{n=1}^{\infty}n^kn^{-s}$ 也经常出现。仅通过这些组合，就可以涵盖许多著名的数论函数。

### 约数函数的累积和

设 $\sigma_k(n) = \sum_{d|n} d^k$。特别的，$k=0$ 就是约数的数量，$k = 1$ 就是约数的和。Dirichlet 级数可以表示为

$$\sum_{n=1}^{\infty} \sigma_k(n)n^{-s} = \zeta(s)\zeta(s-k)$$

$\zeta(s)$ 或 $\zeta(s-k)$ 的第 $n$ 个值或前 $n$ 个值的和，当 $k$ 被视为常数时，都可以在 $O(1)$ 时间内计算。因此，第 $N$ 个之前的总和可以通过【命题 1】在 $O(\sqrt{N})$ 时间内计算。

这个例子归根结底是计算 $\sum_{ij\leq N}i^k$，至少有一方是 $\sqrt{N}$ 或以下，这是一个非常基本的计算。当想要重新审视到目前为止的命题的简单情况时，这可能会有所帮助。

如果你想列举所有 $i$ 对 $\lfloor N/i \rfloor$ 之前的总和，可以通过【命题 4】在 $O(N^{2/3})$ 的时间复杂度内计算。

### Möbius 函数的累积和（Mertens 函数）

Möbius 函数 $\mu(n)$ 的累积和 $M(n) = \sum_{i=1}^n\mu(i)$ 被称为 Mertens 函数。Möbius 函数在 Dirichlet 积中非常基本，相当于 $\zeta(s)$ 的逆元：

$$\frac{1}{\zeta(s)} = \sum_{n=1}^{\infty}\mu(n)n^{-s}.$$

通过使用【命题 5】，Mertens 函数 $M(N)$ 可以在 $O(N^{2/3})$ 的时间复杂度内计算。

### Euler 函数的累积和

关于 Euler 函数 $\varphi(n)$，以下是基本的：$n = \sum_{d|n}\varphi(d)$。也就是说，$\zeta(s-1) = D_{\varphi}(s)\zeta(s)$ 成立。$D_{\varphi}(s) = \frac{\zeta(s-1)}{\zeta(s)}$ 可以知道。

另外，这可以通过 Euler 乘积 $D_{\varphi}(s) = \prod_{p} (1 + (p-1)p^{-s} + (p^2-p)p^{-2s} + \cdots) = \prod_{p}\frac{1-p^{-s}}{1-p\cdot p^{-s}}$ 来确认。

通过使用【命题 5】对 $\zeta(s)$ 和 $\zeta(s-1)$，$\sum_{i=1}^N \varphi(i)$ 可以在 $O(N^{2/3})$ 时间内计算。或者，从 $D_{\varphi}(s) = \zeta(s-1)\cdot \frac{1}{\zeta(s)}$ 开始，使用 Mertens 函数和【命题 4】也是可能的。

### 无平方数的计数

如果不存在使 $n$ 可以被 $p^2$ 整除的素数 $p$，则 $n$ 称为无平方数（square-free）。如果你想计算 $N$ 以下的无平方数的数量，这是一个问题。这是 Dirichlet 级数

$$f(s) = \prod_{p} (1 + p^{-s})$$

中 $n^{-s}$ 系数的累积和问题。从 $1 + p^{-s} = \frac{1-p^{-2s}}{1-p^{-s}}$ 可以得出 $f(s) = \frac{\zeta(s)}{\zeta(2s)}$。因此，$\zeta(s)$ 或 $\zeta(2s)$ 可以通过【命题 5】的形式管理。

$\zeta(2s)$ 只对平方数有系数 $1$，因此累积和也可以作为平方数的计数来轻松进行。因此，$N$ 以下的无平方数的计数可以在 $O(N^{2/3})$ 的时间复杂度内完成。

### 稀疏的变体

让我们来看一些更困难的例子。例如，设 $a(n) = \sigma_0(100n)$（$\sigma_0$ 是约数的数量）。考虑一下计算 $\sum_{n=1}^N a(n)$ 的问题。

$\sigma_0(n)$ 或 $a(n)$ 可以通过 $n$ 的素因数分解来计算。这表明 Dirichlet 级数 $D_{\sigma_0}$, $D_a$ 具有“Euler 乘积分解”。例如，

- $f\_p(s) = 1 + 2p^{-s} + 3p^{-2s} + \cdots = \frac{1}{(1-X)^2}$（其中 $X = p^{-s}$）
- $D_{\sigma_0}(s) = \prod_{p} f\_p(s)$ 成立

可以知道。当 $n$ 可以被 $p$ 整除 $k$ 次时，$k + 1$ 会乘以它。这种计算步骤对应于项 $(k+1)p^{-ks}$。另外，$D_{\sigma_0}(s) = \zeta(s)^2$ 已经知道，通过使用 $\zeta(s) = \prod_{p} (1-p^{-s})^{-1}$ 也可以得出相同的结论。

$D_a$ 是怎样的呢？当 $n$ 可以被 $p$ 整除 $k$ 次时，$p \neq 2, 5$ 时 $\sigma_0$ 与之前相同。因此，$D_a$ 可以从 $D_{\varphi}$ 进行稀疏的变体。

- $g\_2(s) = 3 + 4X + 5X^2 + 6X^3 + \cdots$（其中 $X = 2^{-s}$）
- $g\_5(s) = 3 + 4X + 5X^2 + 6X^3 + \cdots$（其中 $X = 5^{-s}$）

通过设置，$D_a(n) = \prod_{p\neq 2, 5}f\_p(s)\cdot g\_2(s)\cdot g\_5(s)$ 可以知道。

$$D_{a}(s) = D_{\sigma_0}(s)\cdot \frac{g\_2(s)g\_5(s)}{f\_2(s)f\_5(s)}$$ 可以得出。$F(s) = \frac{g\_2(s)g\_5(s)}{f\_2(s)f\_5(s)}$ 是一个非常稀疏的 Dirichlet 级数，只在 $n = 2^a5^b$ 的地方有非零值。

因此，所有项的计算和累积和的计算都很容易进行，$\sum_{n=1}^N \sigma_0(100n)$ 可以在 $O(N^{2/3})$ 时间内计算。另外，利用 $F$ 非常稀疏的事实，$\sigma_0$ 的累积和只需要在 $n = \lfloor N/(2^a5^b) \rfloor$ 这样的 $n$ 上进行，总共可以在 $O(\sqrt{N})$ 时间内计算。

“稀疏的变体”作为例子，少数素数部分的变体或所有 $p$ 的 $2$ 次以上可以整除的数（powerful number）部分的变体是代表性的。