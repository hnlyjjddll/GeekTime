//
// Created by jdl on 2020/8/2.
//

#include <iostream>
#include <string>
#include <functional>

using namespace std;

class ICallBack{
public:
    virtual void CallBack() const =0;
};

class TestCallBack:public ICallBack{
    virtual void CallBack() const override {
        cout<<"callback "<<endl;
    }
};

class TestTemplate{
public:
    void Process(const ICallBack& oCallBack){
        Begin();
        oCallBack.CallBack();
        End();
    }

    void Begin(){
        cout<<"begin"<<endl;
    }

    void End(){
        cout<<"end"<<endl;
    }
};

int main(void){
    TestTemplate().Process(TestCallBack());
    return 0;
}
