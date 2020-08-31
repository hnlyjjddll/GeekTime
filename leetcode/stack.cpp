#include <iostream>
#include <vector>

using namespace std;

template<class T>
class MyStack{
public:
    MyStack(){
        m_dwSize = 0;
        m_vecData.clear();
    }
    bool empty() const {
        return m_vecData.empty();
    }
    T& top(){
        return m_vecData.back();
    }

    void pop(){
        if(!m_vecData.empty()){
            m_vecData.pop_back();
            --m_dwSize();
        }
    }

    int size() const {
        return m_dwSize;
    }

    void push(T t){
        m_vecData.push_back(t);
        ++m_dwSize;
    }

private:
    vector<T> m_vecData;
    int m_dwSize;
};

int main(void){
    MyStack<int> stk;
    stk.push(1);
    stk.push(3);
    stk.push(19);
    auto& elem = stk.top();
    cout<<elem<<endl;
    elem = 2;
    cout<<stk.top()<<endl;
    return 0;
}