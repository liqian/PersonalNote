#include <iostream>


void print()
{
}

template <typename T, typename... Types>                //这里的...是关键字的一部分
void print(const T& firstArg, const Types&... args)     //这里的...要写在自定义类型Types后面
{
    std::cout << firstArg << std::endl;

    //这里的...要写在变量args后面
    print(args...);                                       // call print() for remaining arguments

}
int main(){
    
    print(1,2,3.4,"name");
    return 0;
}