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
void initVector(std::vector<StructA*>& vecPtr)
{
    std::shared_ptr<StructA> pA = std::make_shared<StructA>();
    pA->i=0;
    printf("use count:%d\n",pA.use_count());
    vecPtr.push_back(pA.get());//这种方式存在问题，pA智能指针的引用计数不会+1，导致本函数结束后会失败pA的内存。

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
*/
    Conver2ParentClass();
    return ;
}