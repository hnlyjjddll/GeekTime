#include <list>
#include <iostream>

using namespace std;


int main(void){
    list<int> iList{1,2,3,4,5};
    list<int>::iterator it = iList.end();
    //cout<<*(++it)<<endl;
    cout<<*(--it)<<endl;
    return 0;
}