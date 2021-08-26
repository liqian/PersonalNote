#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
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

bool cmp(const StructA& l, const StructA& r)
{
    return l.i < r.i;
}
void initVector(std::vector<StructA*>& vecPtr)
{
    std::shared_ptr<StructA> pA = std::make_shared<StructA>();
    pA->i=0;
    printf("use count:%d\n",pA.use_count());
    vecPtr.push_back(pA.get());//这种方式存在问题，pA智能指针的引用计数不会+1，导致本函数结束后会释放pA的内存。

    pA->i=1;
    printf("use count:%d\n",pA.use_count());
}

void initSharedPtr(std::vector<std::shared_ptr<StructA>>& vecPtr)
{
    std::shared_ptr<StructA> pA = std::make_shared<StructA>();
    pA->i=2;
    printf("use count:%d\n",pA.use_count());
    vecPtr.push_back(pA);

    pA->i=3;
    printf("use count:%d\n",pA.use_count());

    StructA& a=*pA;
    printf("A:%d\n",a.i);
}
void initAutoPtr(){
    std::auto_ptr<StructA> pA (new StructA());
}
void Conver2ParentClass(){
    std::shared_ptr<const B1> pB1 = std::make_shared<B1>();
    printf("use count:%d\n",pB1.use_count());
    std::shared_ptr<const B> pB = pB1;
    printf("use count:%d\n",pB1.use_count());

    std::shared_ptr<const B1> pB1_ = std::dynamic_pointer_cast<const B1>(pB);
    printf("use count:%d\n",pB1.use_count());
}
void Const2NonConst(){
    std::shared_ptr<const StructA> pA = std::make_shared<StructA>();

    printf("use_count:%d\n",pA.use_count());
    StructA* pB=const_cast<StructA*>(pA.get());
    pB->i=2;
    printf("use_count:%d\n",pA.use_count());
    printf("A:%d\n",pA->i);
    printf("A:%d\n",pB->i);
}

void Shared2VoidPtr(){
    std::shared_ptr<const StructA> pA = std::make_shared<StructA>();

    //void *p=(void*)pA;//error can not convert


}
void main(){
    /*
    printf("----- start ----- \n"); 
    std::vector<StructA*> vecP;      
    initVector(vecP);
    printf("%d\n",vecP[0]->i);//此处vecP[0]实际是个野指针，会在运行时随机出现Crash情况
    printf("----- end ----- \n");

    printf("----- start ----- \n"); 
    std::vector<std::shared_ptr<StructA>> vecPtr;      
    initSharedPtr(vecPtr);
    
    printf("%d\n",vecPtr[0]->i);
    printf("----- end ----- \n");
    
    printf("----- start ----- \n"); 
    initAutoPtr();
    printf("----- end ----- \n");
    
    Const2NonConst();

    //Conver2ParentClass();

    const int* p0 = new int(0);
    int const* p1 = new int(1);
    int* const p2 = new int(2);
    printf("p0=%d\n", *p0);
    printf("p1=%d\n", *p1);
    printf("p2=%d\n", *p2);

    p0 = p1;//指针指向发生变更
    *p2 = 100;//指针指向区域内容发生变更
    printf("p0=%d\n", *p0);
    printf("p1=%d\n", *p1);
    printf("p2=%d\n", *p2);

    *p0 = 200;//指针指向区域为const，不能修改，编译出错
    *p1 = 200;//指针指向区域为const，不能修改，编译出错
    p2 = p1;//指针为const，不能修改，编译出错。

    */

    std::shared_ptr<StructA> p(new StructA());
    p->i = 1;
    std::cout << p.use_count() << std::endl;

    std::shared_ptr<StructA> p1 = p;
    std::cout << p.use_count() << std::endl;

    p1.reset();

    std::cout << p.use_count() << std::endl;

    StructA& i = *p;
    std::cout << p.use_count() << std::endl;

    std::vector<StructA*> v;
    v.push_back(p.get());

    p.reset();

    {
        std::pair<int, int> a;
        a = std::make_pair<int, int>(1, 0);

        int first = 1;
        int second = 0;
        //a= std::make_pair<int, int>(first, second);//无法将参数 1 从“int”转换为“_Ty1 &&”

    }
    

    {
        std::pair<std::string, int> b;
        b = std::make_pair<std::string, int>("key", 0);
        
        std::string first = "1";
        int second = 0;
        //b = std::make_pair<std::string, int>(first, second);// 无法将参数 1 从“std::string”转换为“_Ty1 &&”
    }
    

    {
        std::pair<bool, int> b;
        b = std::make_pair<bool, int>(true, 0);

        bool isB = false;
        //b = std::make_pair<bool, int>(isB, 0);//无法将参数 1 从“bool”转换为“_Ty1 &&”

       
    }

    {
        StructA as;
        std::pair<StructA, int> b;
        //b = std::make_pair<StructA, int>(as, 0);//编译出错： 无法将参数 1 从“StructA”转换为“_Ty1 &&”  
        b = std::make_pair<StructA, int>(std::move(as), 0);//使用std::move转成右值引用
    }

    std::vector<StructA> a;
    stable_sort(a.begin(), a.end(), cmp);
    return ;
}