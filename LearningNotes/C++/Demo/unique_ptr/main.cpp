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
        i=-1;
        printf("_B1 alloc %d.\n",i);
    }
    B1(int _i) {
        i = _i;
        printf("_B1 alloc %d.\n",i);
    }
    ~B1(){
        printf("_B1 dealloc %d.\n",i);
    }
    int getI(){
        return i;
    }
private:
    int i;
};


class TestClassUniquePtr
{
public:
    TestClassUniquePtr()
        :
        m_p_b1(new B1())
    {
       
    }
private:
    std::unique_ptr<B1> m_p_b1;
};

class TestClassVecUniquePtr
{
public:
    TestClassVecUniquePtr()
    {
        m_p_b1.push_back(std::make_unique< B1>(1) );
        m_p_b1.push_back(std::make_unique< B1>(2));
        m_p_b1.push_back(std::make_unique< B1>(3));
    }
private:
    std::vector<std::unique_ptr<B1>> m_p_b1;
};

std::unique_ptr<B> getUniquePtr1()
{
    return std::unique_ptr<B>(new B());
}
std::unique_ptr<B> getUniquePtr2()
{
    return std::make_unique<B>();
}
std::unique_ptr<B> getUniquePtr3()
{
    std::unique_ptr<B> p(new B());
    return std::move(p);
}


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
        printf("unique_ptr is null!\n");
    } else {
        printf("unique_ptr is not null!\n");
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
    //函数返回值
    {
        std::unique_ptr<B> u_pf1 = getUniquePtr1();

        std::unique_ptr<B> u_pf2 = getUniquePtr2();

        std::unique_ptr<B> u_pf3 = getUniquePtr3();
    }
    {
        TestClassUniquePtr p1;

        //TestClassUniquePtr p2=p1;//编译错误，错误信息：尝试引用已删除的函数

    }

    
    {
        TestClassVecUniquePtr p1;
        //TestClassVecUniquePtr p2 = p1;//编译错误，错误信息：尝试引用已删除的函数
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
            int* pi = vecUniqueInt.at(i).get();
        }

        for (int i = 0; i < vecUniqueInt.size(); ++i) {
            printf("%d\n", *(vecUniqueInt[i]));
            int* pj = vecUniqueInt[i].get();
        }

        for (int i = 0; i < vecUniqueInt.size(); ++i) {
            //std::unique_ptr<int> u_t1 = vecUniqueInt[i];////编译错误，错误信息：尝试引用已删除的函数
            //std::unique_ptr<int> u_t2(vecUniqueInt[i]);//编译错误，错误信息：尝试引用已删除的函数
            std::unique_ptr<int>& u_t3 = vecUniqueInt[i];
            std::unique_ptr<int>& u_t4 = vecUniqueInt.at(i);
            
        }

        for (int i = 0; i < vecUniqueInt.size(); ++i) {
         
            std::unique_ptr<int> u_t4 = std::move(vecUniqueInt.at(i));
        }
    }
}
void func(std::unique_ptr<B1> p)
{
    printf("%d!\n", p->getI());
}

void func1(std::unique_ptr<B1>& p)
{
    printf("%d!\n", p->getI());
}
void const_func1(const std::unique_ptr<B1>& p)
{
    printf("%d!\n", p->getI());
}
void main(){
    
    //testSimple();
    //testVectorOfBaseType();
    {
        func(std::unique_ptr<B1>(new B1(1)));
    }
    {
        std::unique_ptr<B1> p(new B1(1));
        //func(p);//编译报错
        func(std::move(p));
    }

    {
        std::unique_ptr<B1> p(new B1(2));
        func1(p);
        const_func1(p);
    }
  
    return ;
}