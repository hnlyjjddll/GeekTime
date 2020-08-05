//
// Created by jdl on 2020/8/3.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class IHandler{
public:
    virtual bool Handle()=0;
};

class ReportHandler: public IHandler{
public:
    bool Handle(){cout<<"report"<<endl;return false;}
};

class LogHandler: public IHandler{
public:
    bool Handle(){cout<<"log"<<endl;return true;}
};

class HandlerChain{
public:
    void AddHandler(shared_ptr<IHandler> poHandler){
        m_vecHandlerList.push_back(poHandler);
    }

    bool Handler(){
        for(auto poHandler: m_vecHandlerList){
            if(!poHandler->Handle()){
                cout<<"handle fail"<<endl;
                break;
            }
        }
    }
private:
    vector<shared_ptr<IHandler>> m_vecHandlerList;
};

int main(void){
    HandlerChain oChain;
    oChain.AddHandler(make_shared<LogHandler>());
    oChain.AddHandler(make_shared<ReportHandler>());
    oChain.Handler();
    return 0;
}