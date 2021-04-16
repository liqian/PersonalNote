#include <memory>
#include <iostream>
#include <vector>
typedef struct _StructA StructA;

struct _StructA
{
    int i;
    _StructA(): i(int())
    {
        printf("_StructA alloc \n");
    };
    
    ~_StructA()
    {
        printf("_StructA dealloc \n");
    };
} ;

class B{
public:
    B(){
        printf("_B alloc \n");
    }

    virtual ~B(){
        printf("_B dealloc \n");
    }
};

class B1: public B {
public:
    B1(){
        i=1;
        printf("_B1 alloc \n");
    }
    ~B1(){
        printf("_B1 dealloc \n");
    }
    int getI(){
        return i;
    }
private:
    int i;
};

void testSimple()
{
    //初始化的方式
    std::unique_ptr<int> u_p1(new int(1));
    std::unique_ptr<int> u_p2 = std::make_unique<int>(1);

    std::unique_ptr<B> u_st_p1(new B());
    std::unique_ptr<B> u_st_p2 = std::make_unique<B>();

    std::unique_ptr<int> u_p3;
    u_p3.reset(new int());
    int* p = u_p3.release(); //释放所有权

    std::unique_ptr<int> ptr;
    std::unique_ptr<int> ptr1(nullptr);

    //判断空指针
    if (ptr) {
        printf("unique_ptr is null!");
    } else {
        printf("unique_ptr is not null!");
    }

    //赋值
    {
        std::unique_ptr<int> u_p1(new int(1));
        //std::unique_ptr<int> u_p2(u_p1);//编译错误，错误信息：尝试引用已删除的函数
    }
    //拷贝
    {
        std::unique_ptr<int> u_p1(new int(1));
        //std::unique_ptr<int> u_p2 =u_p1;//编译错误，错误信息：尝试引用已删除的函数
    }

    //移动赋值
    {
        std::unique_ptr<int> u_p1(new int(1));
        std::unique_ptr<int> u_p2(std::move(u_p1));
    }
    //移动拷贝
    {
        std::unique_ptr<int> u_p1(new int(1));
        std::unique_ptr<int> u_p2 =std::move(u_p1);
    }
}
void testVectorOfBaseType()
{
    std::vector<std::unique_ptr<int>> vecUniqueInt;

    //vecUniqueInt.push_back(1);//编译错误

    {
        std::unique_ptr<int> u_p(new int(1));
        //vecUniqueInt.push_back(u_p);//编译错误，错误信息：尝试引用已删除的函数
        printf("test unique_ptr\n");
    }

    {
        std::unique_ptr<int> u_p(new int(1));
        vecUniqueInt.push_back(std::move(u_p));
        
        for (int i = 0; i < vecUniqueInt.size(); ++i) {
            printf("%d\n", *(vecUniqueInt.at(i)));
        }

        for (int i = 0; i < vecUniqueInt.size(); ++i) {
            printf("%d\n", *(vecUniqueInt[i]));
        }

        for (int i = 0; i < vecUniqueInt.size(); ++i) {
            //std::unique_ptr<int> u_t1 = vecUniqueInt[i];////编译错误，错误信息：尝试引用已删除的函数
            //std::unique_ptr<int> u_t2(vecUniqueInt[i]);//编译错误，错误信息：尝试引用已删除的函数
            std::unique_ptr<int>& u_t3 = vecUniqueInt[i];
            std::unique_ptr<int>& u_t4 = vecUniqueInt.at(i);
            
        }
    }
}
void main(){
    
    testSimple();
    testVectorOfBaseType();
    return ;
}