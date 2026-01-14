#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    // 检查是否提供了文件名作为命令行参数
    if (argc < 2) {
        std::cerr << "format: " << argv[0] << " <filename> [-w]" << std::endl;
        return 1;
    }

    std::string filename = argv[1]; // 获取文件名
    string a=filename+".in";
    string b=filename+".out";
    string c=filename+".cpp";
    ofstream fout1(a.c_str());
    ofstream fout2(b.c_str());
    ofstream fout3(c.c_str());
}