#include <iostream>
#include <vector>
#include <map>

void test_auto(){
    std::vector<int> vec={1,3,4};
    //C++ 03
    for(std::vector<int>::iterator it = vec.begin();it!=vec.end();++it)
    {
        std::cout<<*it<<std::endl;
    }

    //C++ 11
    for(auto it =vec.begin(); it != vec.end(); ++it)
    {
        std::cout<<*it<<std::endl;
    }

}


void test_auto_foreach(){
    std::vector<int> v={1,2,3};
    //C++ 03
    for(std::vector<int>::iterator it = v.begin();it!=v.end();++it)
    {
        std::cout<<*it<<std::endl;
    }

    //C++ 11

    //read only and copy
    for(auto e:v){
        std::cout<<e <<std::endl;
    }

    //const 引用
    for(const auto& e:v){
        std::cout<<e <<std::endl;
    }

    //引用 值可以修改
    for(auto& e:v){
        std::cout<<e <<std::endl;
    }
}
class A {
public:
    A() {
        vec.push_back(1);
        m_a = -1;
        std::cout << "NONE,construction" << std::endl;
    }
    A(int a):m_a(a)
    {
        vec.push_back(a);
        std::cout <<a<< ",construction" << std::endl;
    }
    // copy construction
    A(const class A& _other) {
        std::cout <<_other.get()<< "copy construction" << std::endl;
    }
    A& operator = (const A& other)
    {
        std::cout << "operator = " << std::endl;
        return A();
    }
    int get() const {
        return m_a;
    }
    ~A()
    {
        std::cout << "deconstruction" << std::endl;
    }
private:
    std::vector<int> vec;
    int m_a;
};

void test_class_vector(){

   
    std::vector<A> v;
    v.reserve(10);
    v.push_back(A(11));
   

    v.emplace_back(A(12));
    v.push_back(10);

    //C++ 03
    for(std::vector<A>::iterator it = v.begin();it!=v.end();++it)
    {
        std::cout<<(*it).get()<<std::endl;
    }

    //C++ 11

    //read only and copy
    for(auto e:v){
        std::cout<<e.get() <<std::endl;
    }

    //const 引用
    for(const auto& e:v){
        std::cout<<e.get() <<std::endl;
    }

    //引用 值可以修改
    for(auto& e:v){
        std::cout<<e.get() <<std::endl;
        
    }
}

void test_class_map()
{
     std::map<int,A> map;
     map.insert(std::make_pair(1,A(1)));
     //map.insert(std::make_pair(2, A(2)));
     map[2] = A(2);

 

     for (auto item : map)
     {
         std::cout <<"auto:" << item.second.get() << std::endl;
     }

     for (auto& item : map)
     {
         std::cout<<"auto&:" << item.second.get() << std::endl;
     }
}
int main(){
    
    //test_auto();
    //test_auto_foreach();
    test_class_vector();
    test_class_map();
    return 0;
}