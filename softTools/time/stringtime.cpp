//
// Created by jdl on 2020/7/17.
//

#include <iostream>
#include <ctime>

using namespace std;

int main(void){
    time_t curTime;
    time(&curTime);

    struct tm* stm;
    stm = localtime(&curTime);

    char TimeBuf[50] = {};
    strftime(TimeBuf,50,"%Y-%m-%d %H:%M:%S", stm);

    cout<<TimeBuf<<endl;

    return 0;
}

