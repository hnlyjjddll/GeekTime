//
// Created by jdl on 2020/8/1.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Observer{
public:
    virtual void Notify() = 0;
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
    void Notify(){
        for(const auto poObserver: m_vecObserverList){
            poObserver->Notify();
        }
    }
    void AddObserver(shared_ptr<Observer> poObserver){
        m_vecObserverList.push_back(poObserver);
    }
private:
    vector<shared_ptr<Observer>> m_vecObserverList;
};

int main(void){
    PayAction oPayAction;
    oPayAction.AddObserver(make_shared<ActivitySystem>());
    oPayAction.AddObserver(make_shared<StockSystem>());

    oPayAction.Notify();
    return 0;
}