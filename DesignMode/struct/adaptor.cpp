//
// Created by jdl on 2020/8/1.
//

#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;

class Adaptee{
public:
    void Play(){cout<<"play basketball"<<endl;}
    int UglyNaming(){return 1;}
    void TooManyParam(int a,int b,int c,int d){cout<<"too many param"<<endl;}
    void LowPerformance(){cout<<"low performence"<<endl;}
};

class AdaptorIf {
public:
    virtual void Play() = 0;

    virtual int Count() = 0;

    //virtual void TooManyParam(const Adaptor::Param &oParam) = 0;

    virtual void LowPerformance() = 0;
};

class Adaptor:public AdaptorIf{
public:
    class Param;
    void Play(){m_oAdaptee.Play();}
    int Count(){
        return m_oAdaptee.UglyNaming();
    }
    void TooManyParam(const Param& oParam){
        m_oAdaptee.TooManyParam(oParam.GetA(),oParam.GetB(),oParam.GetC(),oParam.GetD());
    }
    void LowPerformance(){cout<<"refactor"<<endl;}
private:
    Adaptee m_oAdaptee;
public:
    class Param{
    public:
        Param(int a,int b,int c,int d):m_dwA(a),m_dwB(b),m_dwC(c),m_dwD(d){}
        int GetA()const{return m_dwA;}
        int GetB()const{return m_dwB;}
        int GetC()const{return m_dwC;}
        int GetD()const{return m_dwD;}
    private:
        int m_dwA;
        int m_dwB;
        int m_dwC;
        int m_dwD;
    };
};

int main(void){
    Adaptor oAdaptor;
    oAdaptor.Play();
    cout<<oAdaptor.Count()<<endl;
    oAdaptor.TooManyParam(Adaptor::Param(1,2,3,4));
    oAdaptor.LowPerformance();
    return 0;
}

