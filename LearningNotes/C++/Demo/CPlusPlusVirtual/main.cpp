#include <iostream>
class A {
public:
    virtual void vfunc1(){
        std::cout<<"class A:vfunc1"<<std::endl;
        }
    virtual void vfunc2(){
        std::cout<<"class A:vfunc2"<<std::endl;
        }
    void func1(){
        std::cout<<"class A:func1"<<std::endl;
        }
    void func2(){
        std::cout<<"class A:func2"<<std::endl;
        }
private:
    int m_data1, m_data2;
};



class B {
public:
    virtual void vfunc1(){
        std::cout<<"class B:vfunc1"<<std::endl;
        }
    void func2(){
        std::cout<<"class B:func2"<<std::endl;
        }
private:
    int m_data3;
};

class C : public A,public B {
public:
    virtual void vfunc1(){
        std::cout<<"class C:vfunc1"<<std::endl;
        }
            void func2(){
        std::cout<<"class C:func2"<<std::endl;
        }
private:
    int m_data1, m_data4;
};

class C_Sub : public C {
public:
    virtual void vfunc1() {
        std::cout << "class C:vfunc1" << std::endl;
    }
    void func2() {
        std::cout << "class C:func2" << std::endl;
    }
private:
    int m_data1, m_data4;
};
class D : public A{
public:
    virtual void vfunc1() {
        std::cout << "class D:vfunc1" << std::endl;
    }
    void func2() {
        std::cout << "class D:func2" << std::endl;
    }
private:
    int m_data1, m_data4;
};

class D_Sub : public D {
public:
    virtual void vfunc1() {
        std::cout << "class D:vfunc1" << std::endl;
    }
    void func2() {
        std::cout << "class D:func2" << std::endl;
    }
private:
    int m_data1, m_data4;
};
int main(){
    
    A a;
    a.vfunc1();

    B b;
    b.vfunc1();

    C c;
    c.vfunc1();

    D d;
    d.vfunc1();

    C_Sub c_sub;
    c_sub.vfunc1();

    D_Sub d_sub;
    d_sub.vfunc1();

    //引用
    try{
       
        A& a_ref = dynamic_cast<A&>(c);
        a_ref.vfunc1();

        B& b_ref = dynamic_cast<B&>(c);
        b_ref.vfunc1();
    }catch (std::bad_cast bad) {
        //处理类型转换失败的情况
        std::cout << "Caught: " << bad.what();
    }

    //指针
    try {

        A* pa = dynamic_cast<A*>(&c);
        pa->vfunc1();

        B* pb = dynamic_cast<B*>(&c);
        pb->vfunc1();
    }
    catch (std::bad_cast bad) {
        //处理类型转换失败的情况
        std::cout << "Caught: " << bad.what();
    }
    return 0;
}