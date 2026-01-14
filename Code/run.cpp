#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    // 检查是否提供了文件名作为命令行参数
    if (argc < 2) {
        std::cerr << "format: " << argv[0] << " <filename> [-w]" << std::endl;
        return 1;
    }

    std::string filename = argv[1]; // 获取文件名
    string command;

    if(argc==2){
        command = filename + ".exe < " + filename + ".in > "+filename+".out";
    }else if(argc==3){
        string tmp=argv[2];
        if(tmp=="-w") command = filename + ".exe";
        else{
            cout<<"Incorrect format ."<<endl;
            return 1;
        }
    }else{
        cout<<"Incorrect format ."<<endl;
        return 1;
    }

    std::cout << "Running " << filename << "..." << std::endl;

    // 使用system函数执行编译命令
    int tm = clock();
    int result = system(command.c_str());

    cout << "Returned " << result << "." << endl;
    cout << "Real time : " << clock() - tm << "ms." << endl;
}


