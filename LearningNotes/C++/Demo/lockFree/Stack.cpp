#include <thread>
#include <atomic>
#include <mutex>
#include <iostream>
#include <list>
#include <vector>
#include <string>

class Node
{
public:
    Node(const std::string& name){
        //m_name=name; 
        m_next=nullptr;
    }
    ~Node(){}
    bool hasNextNode(){return m_next != nullptr; }
    Node* getNextNode(){ return m_next;}
    void  setNextNode( Node* n){  m_next=n;}
    std::string toString()
    {
        //return std::string("The Node Name is " + m_name);
        return std::string("The Node Name is ");
    }
private:
    //std::string m_name;
    Node* m_next;
};

class BaseStack
{
public:
    //atomic 如果没有进行初始化，未出现未预料的数据。依赖编译器，所以最好显示初始化
    BaseStack():m_total_cnt(0),m_head(nullptr) {}
    virtual ~BaseStack(){
    
        Node* headNode = m_head.load();
        while (nullptr != headNode) {
            Node* nextNode = headNode->getNextNode();

            delete headNode;//relase memory

            headNode = nextNode;
        }
    };
    virtual void push(Node* n)=0;
    virtual Node* pop() = 0;

    virtual std::string getClassName() = 0;
    virtual int getTotalNodeCnt() const
    {
        return m_total_cnt.load();
    }
    //打印出所有队列中的数据，主要为了调试和观察使用，所以这里 用了 mutex，进行阻塞。
    virtual void printAll()
    {
        m_base_mutex.lock();
        std::cout << "print beg:========================" << std::endl;
        int iTotalCnt = 0;
        Node* n = m_head.load();
        while (nullptr != n)
        {
            //std::cout << n->toString() << std::endl;
            n = n->getNextNode();
            ++iTotalCnt;
        }
 
        std::cout <<"TotalCnt:"<< iTotalCnt << std::endl;

        std::cout << "print end:========================" << std::endl;
        m_base_mutex.unlock();
    }
protected:
    std::atomic<Node*> m_head;
    std::atomic_int m_total_cnt;
private:
    std::mutex m_base_mutex;
};
////////////////////////////////////////////////////////////////////////////////////////////
//              NormalQueue: 不考虑线程并行
/// ////////////////////////////////////////////////////////////////////////////////////////

class NormalStack:public BaseStack
{

public:
    NormalStack() = default;
    ~NormalStack(){
    }
    void push(Node * n) override
    {
        n->setNextNode(m_head.load());
        m_head.store( n);
        ++m_total_cnt;
    }

    Node* pop() override
    {
        Node* head = m_head.load();
        if (nullptr != head) {
            m_head.store(head->getNextNode());
            --m_total_cnt;
        }
        return head;
    }
    std::string getClassName() override
    {
        return "NormalStack";
    }
};

void testNormalStack()
{
    NormalStack nq;
    for(int i=0; i < 10000;++i){
        Node * n = new Node(std::to_string(i));
        nq.push(n);
    }

    nq.printAll();

    for (int i = 0; i < 10000; ++i) {
        Node* n = nq.pop();

        if (nullptr != n) {
            delete n;
            n = nullptr;
        }
    }
    nq.printAll();
}


////////////////////////////////////////////////////////////////////////////////////////////
//              MutexQueue: 使用互斥变量 确保多线程安全
/// ////////////////////////////////////////////////////////////////////////////////////////

class MutexStack:public BaseStack
{

public:
    MutexStack() = default;
    ~MutexStack() { }

    void push(Node* n) override
    {
        m_mutex.lock();
        n->setNextNode(m_head.load());
        m_head.store(n);
        ++m_total_cnt;
        m_mutex.unlock();
    }

    Node* pop() override
    {
        m_mutex.lock();
        Node* head = m_head.load();
        if (nullptr != head) {
            m_head.store(head->getNextNode());
            --m_total_cnt;
        }
        
        m_mutex.unlock();
        return head;
    }
    std::string getClassName() override
    {
        return "MutexStack";
    }
private:
    std::mutex m_mutex;
};

void threadRun(MutexStack& mq,int nodeCnt,const std::string& base_name) {
    for (int i = 0; i < nodeCnt; ++i) {
        Node* n = new Node(base_name+std::to_string(i));
        mq.push(n);
    }
}
void threadPop(MutexStack& mq, int nodeCnt, const std::string& base_name) {
    for (int i = 0; i < nodeCnt; ++i) {
        Node* n = mq.pop();

        if (nullptr != n) {
            delete n;
            n = nullptr;
        }
    }
}
void testMutexStack()
{
    MutexStack mq;
    {
        std::thread t1(threadRun, std::ref(mq), 5000, "t1 ");

        std::thread t2(threadRun, std::ref(mq), 3000, "t2 ");

        std::thread t3(threadRun, std::ref(mq), 2000, "t3 ");

        t1.join();
        t2.join();
        t3.join();

        mq.printAll();
    }

    {
        std::thread t1(threadPop, std::ref(mq), 5000, "t1 ");

        std::thread t2(threadPop, std::ref(mq), 3000, "t2 ");

        std::thread t3(threadPop, std::ref(mq), 3000, "t3 ");

        t1.join();
        t2.join();
        t3.join();

        mq.printAll();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
//              LockFreeQueue: 使用CAS 原语既的互斥，确保CPU指令是原子的
/// ////////////////////////////////////////////////////////////////////////////////////////

class LockFreeStack:public BaseStack
{

public:
    LockFreeStack() = default;

    ~LockFreeStack() { }

    void push(Node* n) override
    {
        Node* headNode = m_head.load();
        do {
            n->setNextNode(headNode);
        } 
        while (!m_head.compare_exchange_strong(headNode, n));//只有在headNode同m_head相等式，才会将n赋值给m_head
        ++m_total_cnt;
    }

    Node* pop() override
    {
        Node* headNode = m_head.load();

        if (nullptr != headNode) {
            while (!m_head.compare_exchange_strong(headNode, headNode->getNextNode()));
            --m_total_cnt;
        }
        
        return headNode;
    }

    std::string getClassName() override
    {
        return "LockFreeStack";
    }
};

void threadLockFreeRun(LockFreeStack& stack, int nodeCnt, const std::string& base_name) {
    for (int i = 0; i < nodeCnt; ++i) {
        Node* n = new Node(base_name + std::to_string(i));
        stack.push(n);
    }
}

void threadLockFreePop(LockFreeStack& stack, int nodeCnt, const std::string& base_name) {
    for (int i = 0; i < nodeCnt; ++i) {
        Node* n = stack.pop();

        if (nullptr != n) {
            delete n;
            n = nullptr;
        }
    }
}
void testLockFreeStack()
{
    LockFreeStack stack;

    {
        //std::thread 默认情况使用的是浅拷贝，所以如果想要应用需要使用std::ref
        std::thread t1(threadLockFreeRun, std::ref(stack), 5000, "t1 ");

        std::thread t2(threadLockFreeRun, std::ref(stack), 3000, "t2 ");

        std::thread t3(threadLockFreeRun, std::ref(stack), 2000, "t3 ");

        t1.join();
        t2.join();
        t3.join();
        stack.printAll();
    }
    

    {
        std::thread t1(threadLockFreePop, std::ref(stack), 5000, "t1 ");

        std::thread t2(threadLockFreePop, std::ref(stack), 3000, "t2 ");

        std::thread t3(threadLockFreePop, std::ref(stack), 3000, "t3 ");

        t1.join();
        t2.join();
        t3.join();
        stack.printAll();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void PerformMonitor(const std::vector<BaseStack*>& allStacks )
{
    while (true) {
        //定时 打印一次
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        for (const auto a : allStacks) {
            std::cout << a->getClassName() << ":" << a->getTotalNodeCnt() << " ";
        }

        std::cout << std::endl;
    }
}
void push_stack(BaseStack* ns)
{
    int i = 0;
    while (true) {
        Node* n = new Node(std::to_string(i));
        ns->push(n);
    }
}

void addMultiThread(BaseStack* stack,int threadCnt) {
    std::vector<std::thread> threads;
    for (int i = 0; i < threadCnt; ++i) {
        threads.push_back(std::thread(push_stack,stack));
    }

    for (auto& a : threads) {
        a.join();
    }

}
//死循环 直至不退出，用于监控测试结果
/*
1. 只有一个线程 三种性能几乎一样
2. 多个线程时候，LockFree 性能比Mutex高出至少一倍以上，随着线程数增加，性能成倍提升。（前提LockFree Mutex线程数一致）
*/
void compareEachStack()
{
    NormalStack ns;
    MutexStack ms;
    LockFreeStack lfs;

    std::vector<BaseStack*> allStacks;
    allStacks.push_back(&ns);
    allStacks.push_back(&ms);
    allStacks.push_back(&lfs);

    std::thread monitor_thread(PerformMonitor, std::ref(allStacks));

    std::thread normal_single(push_stack,&ns);

    std::thread mutex_control(addMultiThread, &ms,2);
    std::thread lockfree_control(addMultiThread, &lfs,2);

    monitor_thread.join();
    return;
}   