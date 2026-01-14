因为 Chtholly Tree 并不是树，所以 Nephren Tree 也不是树，更像是一种 trick。

## 引入

给定一个长为 $n$ 的序列，$m$ 次操作：

- 操作 1：给定 $l$ $r$，将 $[l,r]$ 的所有数加 $k$。
- 操作 2：给定 $l$ $r$ $p$，询问 $f(l,r) \bmod p$，其中：
  $$f(l,r)=\left\{ \begin{matrix} a_l^{f(l+1,r)} & l<r \\ a_l & l=r\end{matrix} \right.$$

$n\leq 10^5$，$m\leq 10^5$，$p\leq2\times 10^7$。

## 解法

先考虑没有修改怎么做。

首先有扩展欧拉定理：

$$a^b \bmod p \equiv \left\{ \begin{matrix} a^{b\bmod \varphi(p)} & b<\varphi(p) \\ a^{b\bmod \varphi(p)+\varphi(p)} & b\geq\varphi(p)\end{matrix} \right.$$

也就是说我们可以构造函数 $g(l,r,p)$ 计算 $f(l,r) \bmod p$：

$$g(l,r,p)=\left\{ \begin{matrix} a_l^{g(l+1,r,\varphi(p))}\bmod p & l<r\wedge g(l+1,r,\varphi(p)) < \varphi(p)\\ a_l^{g(l+1,r,\varphi(p))+\varphi (p)}\bmod p & l<r\wedge g(l+1,r,\varphi(p)) \geq \varphi(p)\\ a_l\bmod p & l=r\end{matrix} \right.$$

我们发现 $\varphi(p)$ 在 $p\neq 2$ 时是偶数，而 $\varphi(p)\leq \frac p2$ 在 $p$ 是偶数时成立。

所以每进行一次 $p\leftarrow \varphi(p)$ 的操作至少使 $p$ 减少一半，故单次查询执行 $p\leftarrow \varphi(p)$ 的操作的一个上界是 $O(\log p)$。

继续研究发现有修改问题不大，该用数据结构就用。

时间复杂度 $O(p+q\log^2 p)$，空间复杂度 $O(p)$，瓶颈在于快速求幂。

## 小结

容易发现 Nehpren Tree 对修改操作的要求仅仅是在线，也就是说 Nehpren Tree 支持区间异或等奇奇怪怪的操作，但是在 $p>2\times 10^7$ 的 case 中由于无法快速求 $\varphi(p)$ 使得时间复杂度变为 $O(q(k\log p+\log^2 p+\sqrt p))$ 或 $O(q(k\log p+\log^2 p+p^{\frac 14}))$，其中 $k$ 是数据结构的查询复杂度。