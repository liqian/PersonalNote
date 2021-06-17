#include <time.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "Stack.h"
int main()
{
 
    std::vector<std::string> infos;
    clock_t beg = clock();
    clock_t end = clock();
    testNormalStack();
    end = clock();
    infos.push_back("testNormalStack: " + std::to_string(end - beg));

    beg = clock();
    testMutexStack();
    end = clock();
    
    infos.push_back("testMutexStack: " + std::to_string(end - beg));

    beg = clock();
    testLockFreeStack();
    end = clock();

    infos.push_back("testLockFreeStack: " + std::to_string(end - beg));

    std::cout << "=============================================================" << std::endl;
    for (const auto& info : infos) {
        std::cout << info << std::endl;
    }

    compareEachStack();
    return 0;
}