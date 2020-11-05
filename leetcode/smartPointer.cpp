//
// Created by jdl on 2020/11/5.
//

#include <list>
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

template<typename T>
class MySmartPointer{
public:
  MySmartPointer(){
    m_pRefCnt = nullptr;
    m_pVal = nullptr;
  }

  ~MySmartPointer(){
    cout<<"begin deconstrcut"<<endl;
    if(*m_pRefCnt == 1){
      cout<<"it is the last reference. release all memory"<<endl;
      delete m_pVal;
      delete m_pRefCnt;
    }else{
      *m_pRefCnt = *m_pRefCnt - 1;
      cout<<"reduce reference. new reference count is "<<*m_pRefCnt<<endl;
    }
  }

  MySmartPointer<T>(T* pt){
    if(pt){
      m_pVal = pt;
      m_pRefCnt = new int;
      *m_pRefCnt = 1;

      cout<<"construct MySmartPointer. reference count is "<<*m_pRefCnt<<endl;
    }
  }

  MySmartPointer(const MySmartPointer& rhs){
    cout<<"copy construct begin"<<endl;
    if(this != &rhs){

      m_pVal = rhs.m_pVal;
      m_pRefCnt = rhs.m_pRefCnt;
      *m_pRefCnt = *m_pRefCnt + 1;
      cout<<"add right reference. new right reference count is "<<*m_pRefCnt<<endl;
    }
  }

  MySmartPointer<T>& operator=(MySmartPointer& rhs) {
    cout<<"assign begin"<<endl;
    if (this != &rhs) {
      if(m_pVal && m_pRefCnt){
        if (*m_pRefCnt == 1) {
          delete m_pVal;
          delete m_pRefCnt;
          cout<<"it is the last reference. release all memory"<<endl;
        } else {
          *m_pRefCnt = *m_pRefCnt - 1;
          cout<<"reduce left reference. new left reference count is "<<*m_pRefCnt<<endl;
        }
      }

      m_pRefCnt = rhs.m_pRefCnt;
      *m_pRefCnt = *m_pRefCnt + 1;
      m_pVal = rhs.m_pVal;
      cout<<"add right reference. new right reference count is "<<*m_pRefCnt<<endl;
    }

    return *this;
  }

  int* m_pRefCnt;
  T* m_pVal;
};

int main(void){
  MySmartPointer<int> pa(new int(100));
  MySmartPointer<int> pb(pa);
  MySmartPointer<int> pc;
  pc = pb;
  return 0;
}

