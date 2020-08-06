//
// Created by jdl on 2020/8/6.
//

#include <iostream>
#include <string>
using namespace std;

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
    ListNode(Elem oE):m_oValue(oE),m_poNext(nullptr){}
    Elem m_oValue;
    ListNode<Elem>* m_poNext;
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

//private:
    uint32_t m_dwCount;
    ListNode<Elem>* m_poBegin;
    ListNode<Elem>* m_poEnd;

public:
    class ArraryIterator: public Iterator<Elem>{
    public:
        ArraryIterator(ArraryList<Elem>& oArraryList):m_poArrayList(&oArraryList){
            m_poCurrent = oArraryList.m_poBegin;
        }

        bool HasNext() override {
            if(!m_poArrayList) return false;

            if(!m_poCurrent && m_poArrayList->Size()>0){
                m_poCurrent = m_poArrayList->m_poBegin;
                return true;
            }

            return m_poCurrent->m_poNext != nullptr;
        }

        Elem* GetCurrent() override{
            if(!m_poArrayList || !m_poCurrent){
                return nullptr;
            }

            return &(m_poCurrent->m_oValue);
        }

        void Next()override {
            m_poCurrent = m_poCurrent->m_poNext;
        }
    private:
        ListNode<Elem>* m_poCurrent;
        ArraryList<Elem>* m_poArrayList;
    };
};

int main(void){
    ArraryList<int> iArray;
    //cout<<iArray.Size()<<endl;
    iArray.Add(1);
    iArray.Add(2);
    //cout<<iArray.Size()<<endl;

    auto poIter = iArray.GetIterator();
    while(poIter->GetCurrent()){
        auto poTmp = poIter->GetCurrent();
        cout<<*poTmp<<endl;
        poIter->Next();
    }
    return 0;
}