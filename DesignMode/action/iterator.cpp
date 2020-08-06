//
// Created by jdl on 2020/8/6.
//

#include <iostream>
#include <string>
#include <chrono>
#include <climits>
using namespace std;

uint64_t GetMsTime(){
    auto msec = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    return msec.time_since_epoch().count();
}

template<class Elem>
class Iterator{
public:
    virtual bool HasNext() = 0;
    virtual Elem* GetCurrent()=0;
    virtual void Next()=0;
};

template<class Elem>
class ListNode{
public:
    ListNode(Elem oE):m_oValue(oE),m_poNext(nullptr),m_ddwCreateTime(GetMsTime()),m_ddwDeleteTime(ULONG_MAX){
        cout<<"ListNode create time: "<<m_ddwCreateTime<<endl<<"delete time: "<<m_ddwDeleteTime<<endl;
    }
    Elem m_oValue;
    ListNode<Elem>* m_poNext;
    uint64_t m_ddwCreateTime;
    uint64_t m_ddwDeleteTime;
};

template<class Elem>
class ArraryList{
public:
    ArraryList():m_dwCount(0),m_poBegin(nullptr){}
    void Add(Elem oE){
        if(!m_poBegin || m_dwCount == 0){
            m_poBegin = new ListNode<Elem>(oE);
            m_poEnd = m_poBegin;
            m_dwCount = 1;
        }else{
            auto poTmp = new ListNode<Elem>(oE);
            m_poEnd->m_poNext = poTmp;
            m_dwCount++;
            m_poEnd = poTmp;
        }
    }

    uint32_t Size(){return m_dwCount;}

    Iterator<Elem>* GetIterator(){
        return new ArraryIterator(*this);
    }

    void Remove(const Elem& oE){
        auto poTmp = m_poBegin;
        while(poTmp){
            if(poTmp->m_oValue == oE){
                poTmp->m_ddwDeleteTime = GetMsTime();
                cout<<"remove time: "<<poTmp->m_ddwDeleteTime<<endl;
                break;
            }
            poTmp = poTmp->m_poNext;
        }
    }

//private:
    uint32_t m_dwCount;
    ListNode<Elem>* m_poBegin;
    ListNode<Elem>* m_poEnd;

public:
    class ArraryIterator: public Iterator<Elem>{
    public:
        ArraryIterator(ArraryList<Elem>& oArraryList):m_poArrayList(&oArraryList){
            m_poCurrent = oArraryList.m_poBegin;
            m_ddwCreateTime = GetMsTime();
            cout<<"iteraotr create time: "<<m_ddwCreateTime<<endl;
        }

        bool HasNext() override {
            if(!m_poArrayList) return false;

            auto poTmp = m_poCurrent;
            while(poTmp&&poTmp->m_poNext){
                poTmp = poTmp->m_poNext;
                if(poTmp->m_ddwCreateTime<m_ddwCreateTime
                   && poTmp->m_ddwDeleteTime>m_ddwCreateTime){
                    return true;
                }

                poTmp = poTmp->m_poNext;
            }

            return false;
        }

        Elem* GetCurrent() override{
            if(!m_poArrayList){
                return nullptr;
            }

            while(m_poCurrent){
                if(m_poCurrent->m_ddwCreateTime<m_ddwCreateTime
                      && m_poCurrent->m_ddwDeleteTime>m_ddwCreateTime){
                    return &(m_poCurrent->m_oValue);
                }

                m_poCurrent = m_poCurrent->m_poNext;
            }

            return nullptr;
        }

        void Next()override {
            m_poCurrent = m_poCurrent->m_poNext;
            while(m_poCurrent){

                if(m_poCurrent->m_ddwCreateTime<m_ddwCreateTime
                   && m_poCurrent->m_ddwDeleteTime>m_ddwCreateTime){
                    break;
                }

                m_poCurrent = m_poCurrent->m_poNext;
            }
        }
    private:
        ListNode<Elem>* m_poCurrent;
        ArraryList<Elem>* m_poArrayList;
        uint64_t m_ddwCreateTime;
    };
};

int main(void){
    ArraryList<int> iArray;
    //cout<<iArray.Size()<<endl;
    iArray.Add(1);
    iArray.Add(2);
    //cout<<iArray.Size()<<endl;

    auto poIter = iArray.GetIterator();
    while(poIter){
        auto poTmp = poIter->GetCurrent();
        if(poTmp){
            cout<<*poTmp<<endl;
        }

        if(!poIter->HasNext()){
            break;
        }

        poIter->Next();
    }

    ArraryList<string> sArray;
    //cout<<iArray.Size()<<endl;
    sArray.Add("123");
    sArray.Add("dsafagdsgd");
    //cout<<iArray.Size()<<endl;
    sArray.Remove("123");

    auto poIter2 = sArray.GetIterator();
    while(poIter2){
        auto poTmp = poIter2->GetCurrent();
        if(poTmp){
            cout<<*poTmp<<endl;
        }

        if(!poIter2->HasNext()){
            break;
        }

        poIter2->Next();
    }
    return 0;
}