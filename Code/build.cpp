#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    // 检查是否提供了文件名作为命令行参数
    if (argc != 2) {
        std::cerr << "format: " << argv[0] << " <filename.cpp>" << std::endl;
        return 1;
    }

    std::string filename = argv[1]; // 获取文件名
    std::string command = "g++ " + filename + ".cpp -o " + filename + ".exe -O2 -Wall -Wextra -std=c++14"; // 构建编译命令

    std::cout << "Compiling " << filename << "..." << std::endl;

    // 使用system函数执行编译命令
    int result = system(command.c_str());

    if (result) {
        std::cerr << "Failed." << std::endl;
        return 1;
    } else {
        std::cout << "Compiled successfully." << std::endl;
        return 0;
    }
}