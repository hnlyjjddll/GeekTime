//
// Created by jdl on 2020/7/28.
//

#include <iostream>
#include <string>
#include <mutex>

using namespace std;

mutex g_mtx;

class MutexLock{
public:
    MutexLock(mutex& mutex):mtx(mutex) {mtx.lock();}
    ~MutexLock() {mtx.unlock();}
private:
    mutex& mtx;
};

class SingleA{
public:
    static const SingleA& getInstance() {
        if(!pa){
            MutexLock lock(g_mtx);
            if(!pa){
                pa = new SingleA(200);
            }
        }

        return *pa;
    }

    void print()const{cout<<ii<<endl;}
private:
    SingleA(int i){ii = i;}
    int ii;
    static SingleA* pa;
};

SingleA* SingleA::pa = nullptr;

int main(void){
    const auto& oA = SingleA::getInstance();
    oA.print();

    return 0;
}
