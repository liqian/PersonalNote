#include <thread>
#include <atomic>
#include <iostream>
#include <list>
#include <vector>

std::atomic_int iAtomicCount(0);
int iCount = 0;
void threadunsafefun1()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("iCount:%d\r\n", iCount++);
    }
}
void threadunsafefun2()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("iCount:%d\r\n", iCount--);
    }
}

void threadfun1()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("iAtomicCount:%d\r\n", iAtomicCount++);
    }
}
void threadfun2()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("iAtomicCount:%d\r\n", iAtomicCount--);
    }
}

void testThreadSafe()
{
    std::list<std::thread> lstThread;
    for (int i = 0; i < 1000; i++)
    {
        lstThread.push_back(std::thread(threadfun1));
    }
    for (int i = 0; i < 1000; i++)
    {
        lstThread.push_back(std::thread(threadfun2));
    }

    for (auto& th : lstThread)
    {
        th.join();
    }

     //int x = iAtomicCount.load(std::memory_order_relaxed);
    //printf("finally iAtomicCount:%d\r\n", x);
    std::cout<<"finally iAtomicCount:"<<iAtomicCount<<std::endl;
}

void testThreadUnsafe()
{
    std::list<std::thread> lstThread;
    for (int i = 0; i < 1000; i++)
    {
        lstThread.push_back(std::thread(threadunsafefun1));
    }
    for (int i = 0; i < 1000; i++)
    {
        lstThread.push_back(std::thread(threadunsafefun2));
    }

    for (auto& th : lstThread)
    {
        th.join();
    }

    printf("finally iCount:%d\r\n",  iCount);
}

void test()
{
    testThreadSafe();
    testThreadUnsafe();

    printf("finally iCount:%d\r\n",  iCount);
    std::cout<<"finally iAtomicCount:"<<iAtomicCount<<std::endl;
}

 struct A { int a[100]; };
 struct B { int x, y; };

void testLockFree()
{
    std::atomic<A*> ptrA;
    //std::boolalpha的作用是使bool型变量按照false、true的格式输出。如不使用该标识符，那么结果会按照1、0的格式输出。
    //而std::noboolalpha的作用刚好相反
    std::cout << std::boolalpha
              << "std::atomic<A> is lock free? "
              << std::atomic<A>{}.is_lock_free() << '\n' //std::atomic<A>{} = std::atomic<A>()
              << "std::atomic<A*> is lock free? "
              << ptrA.is_lock_free() << '\n'
              << "std::atomic<B> is lock free? "
              << std::atomic<B>{}.is_lock_free() << '\n';
}

std::atomic<bool> ready (false);
std::atomic<bool> winner (false);

void count1m (int id) {
    while (!ready) {}                  // wait for the ready signal
    for (int i=0; i<1000000; ++i) {}   // go!, count to 1 million
    if (!winner.exchange(true)) { std::cout << "thread #" << id << " won!\n"; }
};

int testExchange()
{
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i=1; i<=10; ++i) threads.push_back(std::thread(count1m,i));
    ready = true;
    for (auto& th : threads) th.join();

    return 0;
}



int testCompareExchange()
{
    std::atomic_int atomic_a(0);
    
    std::cout<<++atomic_a<<" "<<atomic_a<<'\n';

    std::atomic_int atomic_b(0);
    
    std::cout<<++atomic_b;
    std::cout<<" "<<atomic_b<<'\n';

    int a(0);
    
    std::cout<<++a<<" "<<a<<'\n';

    int b(0);
    
    std::cout<<++b;
    std::cout<<" "<<b<<'\n';

    /*
    std::atomic_int cas(0);
    int expected = 5;
    std::cout<<"init:"<<" expected value:"<<expected<<" cas value:"<<cas<<'\n';
    std::cout<<std::boolalpha
             <<" compare_exchange ? "<<cas.compare_exchange_strong(expected,6);
    std::cout<<" expected value:"<<expected<<" cas value:"<<cas<<'\n';
    std::cout<<std::boolalpha         
             <<" compare_exchange ? "<<cas.compare_exchange_strong(expected,7);
    std::cout<<" expected value:"<<expected<<" cas value:"<<cas<<'\n';
    std::cout<<std::boolalpha
             <<" compare_exchange ? "<<cas.compare_exchange_strong(expected,8);
    std::cout<<" expected value:"<<expected<<" cas value:"<<cas<<'\n';
    std::cout<<std::boolalpha
             <<" compare_exchange ? "<<cas.compare_exchange_strong(expected,9);
    std::cout<<" expected value:"<<expected<<" cas value:"<<cas<<'\n';
    */
    return 0;
}
int main()
{
    //testCompareExchange();

    testLockFree();
    return 0;
}