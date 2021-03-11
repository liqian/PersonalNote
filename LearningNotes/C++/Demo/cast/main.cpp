#include <iostream>

class Base{
public:
    virtual void func(){ std::cout<<"Base Func \n";}
    virtual void func() const { std::cout<<"Const Base Func \n";}
};

class Derive:public Base{
public:
    void func() override {std::cout<<"Derive Fucn \n";}
    void func() const override {std::cout<<"Const Derive Fucn \n";}//注意const要在override前面
};

void dynamic_cast_test()
{
    std::cout << "dynamic_cast_test \n";
    Derive d;
    d.func();

    //Base *b = static_cast<Base *>(&d);
    Base *b = dynamic_cast<Base *>(&d);//这里dynamic_cast和static_cast都可以。
    b->func();

    Derive* dd = dynamic_cast<Derive *>(b);
    dd->func();

    //Base b_ref = static_cast<Base &>(d);
    try {
        Base& b_ref = dynamic_cast< Base&>(d);//这里dynamic_cast和static_cast都可以。
        b_ref.func();

        Derive& d_ref = dynamic_cast<Derive&>(b_ref); //使用b引用的Derived对象
        d_ref.func();
    }
    catch (std::bad_cast b) {
        //处理类型转换失败的情况
        std::cout << "Caught: " << b.what();
    }

    //const Base& b_ref = static_cast<const Base &>(d);
    try{
        const Base& const_b_ref = dynamic_cast<const Base &>(d);//这里dynamic_cast和static_cast都可以。
        const_b_ref.func();

        const Derive &const_d_ref = dynamic_cast<const Derive &>(const_b_ref); //使用b引用的Derived对象
        const_d_ref.func();
    }
    catch(std::bad_cast b){
        //处理类型转换失败的情况
        std::cout << "Caught: " << b.what();
    }

    //转换出错情况，在运行时
    try {
        const Base const_b_ref = dynamic_cast<const Base&>(d);//注意这里，const Base const_b_ref 少了一个 &，下面转换时会失败，抛异常
        const_b_ref.func();

        const Derive& const_d_ref = dynamic_cast<const Derive&>(const_b_ref); //使用b引用的Derived对象
        const_d_ref.func();
    }
    catch (std::bad_cast b) {
        //处理类型转换失败的情况
        std::cout << "Caught: " << b.what();
    }
}

void const_cast_test()
{
    std::cout << "const_cast_test \n";
    int data = 10;
    const int * p1=&data;

    int * p2=const_cast<int *>(p1);//去常量性
    const int* p11 = const_cast<const int *>(p1);//加常量性

    Base b;
    b.func();

    const Base& const_b_ref = const_cast<const Base&>(b);
    const_b_ref.func();

    Base& b_ref = const_cast<Base&>(const_b_ref);
    b_ref.func();
}

void static_cast_test()
{
    std::cout << "static_cast_test \n";
    float f = 1.23;
    std::cout << "f"<<f<<std::endl;

    int i = static_cast<int>(f);
    std::cout<< "i"<<i<<std::endl;

    //int* p1 = static_cast<int *>(&f);//编译错误：invalid static_cast from type 'float *' to type 'int *'
    void* p1 = static_cast<void *>(&f);

    Derive d;
    d.func();

    Base *b = static_cast<Base *>(&d);
    b->func();

    Base& b_ref = static_cast<Base &>(d);
    b_ref.func();

    const Base& const_b_ref = static_cast<const Base &>(d);
    const_b_ref.func();
}
int main(){
    
    static_cast_test();
    dynamic_cast_test();
    const_cast_test();
    return 0;
}