
## C++ 11 override关键字:(虚函数描述符override)
1. override关键字作用：  
如果派生类在函数声明时使用了override描述符，那么该函数必须重写其基类中的同名函数并且基类的同名函数是virtual，否则代码将无法通过编译。

```C++

class Base 
{
    virtual void Turing() = 0;
    virtual void Dijkstra() = 0;
    virtual void VNeumann(int g) = 0;
    virtual void DKnuth() const;
    void Print();
};
class DerivedMid: public Base 
{
    void Turing() override;
    void Dikjstra() override; //无法通过编译，拼写错误，并非重写
    void VNeumann(double g) override; //无法通过编译，参数不一致，并非重写   
    void DKnuth() override; //无法通过编译，常量性不一致，并非重写
    void Print() override; //无法通过编译，非虚函数重写
};

```

**NODE: 建议在C++多态实现时，使用 override关键字**
2. override后，函数是否还需要virtual？ 不需要了
在C++11之前，关于子类覆写父类虚函数后，子类的虚函数还要不要加virtual关键字，还是个值得争论的问题。  
人们一开始之所以想在子类的覆写函数上也加上virtual，就是为了提醒读代码的人这是个覆写的虚函数。  
但是在有了override之后，这个关键字本身就起了这个作用，之前的做法也就不是必须的了。  
**所以建议的做法是，在最顶层的虚函数上加上virtual关键字后，其余的子类覆写后就不再加virtual了，但是要统一加上override。**
```
Prefer to use override whenever you are overriding a virtual function  
and virtual only for the topmost declaration of that function.
```

## C++ 11 final关键字
1. 禁用继承
C++11中允许将类标记为final，方法时直接在类名称后面使用关键字final，如此，意味着继承该类会导致编译错误。
```C++
class Super final
{
  //......
};

```
2. 禁用重写
C++中还允许将方法标记为final，这意味着无法再子类中重写该方法。这时final关键字至于方法参数列表后面.
```C++
class A
{
pulic:
  virtual void func() const;
};
class  B: A
{
pulic:
  void func() const override final; //OK
};
class C: B
{
pulic:
 void func()const; //error, B::func is final
};

```
**C::func()是否声明为override没关系，一旦一个虚函数被声明为final，派生类不能再重载它。**