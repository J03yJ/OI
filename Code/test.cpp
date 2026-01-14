#include<bits/stdc++.h>

constexpr int N = 100'000'000;

void test_pair() {
    std::pair<int, int> p(1, 2);
    volatile int sink; // 防止优化

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        sink = p.first + p.second; // 访问测试
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Pair: " << (end - start).count() << " ns\n";
}

void test_array() {
    std::array<int, 2> a = {1, 2};
    volatile int sink;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        sink = a[0] + a[1];
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Array: " << (end - start).count() << " ns\n";
}

int main() {
    test_pair();
    test_array();
}