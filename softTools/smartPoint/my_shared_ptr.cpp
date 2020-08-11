//
// Created by jdl on 2020/8/11.
//

#include <iostream>
#include <mutex>

using namespace std;

mutex g_mutex;

class MyMutex{
public:
    MyMutex(mutex& oMutex):m_oMutex(oMutex){
        m_oMutex.lock();
    }

    ~MyMutex() {m_oMutex.unlock();}
private:
    mutex& m_oMutex;
};

template<class T>
class MySharedPtr{
public:
    MySharedPtr(T* poValue){
        if(poValue){
            m_poValue = poValue;
            m_poRefCount = new uint32_t(1);
        }
    }

    MySharedPtr(const MySharedPtr<T>& rhs){
        if(&rhs != this){
            --(*m_poRefCount);
            if(*m_poRefCount == 0){
                delete m_poValue;
            }

            m_poValue = rhs.m_poValue;
            m_poRefCount = rhs.m_poRefCount;
            ++(*m_poRefCount);
        }
    }

    MySharedPtr& operator=(const MySharedPtr<T>& rhs){
        if(&rhs != this){
            --(*m_poRefCount);
            if(*m_poRefCount == 0){
                cout<<"delete point"<<endl;
                delete m_poValue;
                delete m_poRefCount;
            }

            m_poValue = rhs.m_poValue;
            m_poRefCount = rhs.m_poRefCount;
            ++(*m_poRefCount);
        }

        return *this;
    }

    ~MySharedPtr(){
        --(*m_poRefCount);
        if(*m_poRefCount == 0){
            cout<<*m_poRefCount<<endl<<"deconstruct delete point"<<endl;
            delete m_poValue;
            delete m_poRefCount;
        }else{
            cout<<"deconstruct "<<*m_poRefCount<<endl;
        }
    }

    MySharedPtr& operator*(){
        return *this;
    }

    void print(){
        cout<<*m_poRefCount<<endl;
    }
private:
    uint32_t* m_poRefCount;
    T* m_poValue;
};

int main(void){
    MySharedPtr<int> poInt(new int(10));
    poInt.print();

    MySharedPtr<int> poInt2(new int(20));
    poInt2.print();

    *poInt2 = *poInt;
    return 0;
}
