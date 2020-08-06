//
// Created by jdl on 2020/8/1.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <functional>

using namespace std;

class Observer{
public:
    virtual void Notify() {};
};

class ActivitySystem:public Observer{
public:
    void Notify() override {
        cout<<"pay finish. activity send coupon"<<endl;
    }
};

class StockSystem: public Observer{
public:
    void Notify() override {
        cout<<"pay finish. reduce stock"<<endl;
    }
};

class PayAction{
public:
    PayAction(){
        for(int i=0; i<5; ++i){
            thread t(&Observer::Notify,Observer());
            t.detach();
            m_threadList.push_back(std::move(t));
        }
    }

    void Notify(){
        for(int i = 0; i<m_vecObserverList.size(); ++i){
            poObserver->Notify();
        }
    }
    void AddObserver(shared_ptr<Observer> poObserver){
        m_vecObserverList.push_back(poObserver);
    }
private:
    vector<shared_ptr<Observer>> m_vecObserverList;
    vector<thread> m_threadList;
};

int main(void){
    PayAction oPayAction;
    oPayAction.AddObserver(make_shared<ActivitySystem>());
    oPayAction.AddObserver(make_shared<StockSystem>());

    oPayAction.Notify();
    return 0;
}