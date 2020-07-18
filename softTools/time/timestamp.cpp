//
// Created by djangojiang on 2020/7/17.
//

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

int main(void){
    //获取秒时间戳
    time_t curTime = time(NULL);
    char* cTime = ctime(&curTime);
    string sTime(cTime);
    cout<<curTime<<" "<<sTime<<endl;

    //获取综合时间
    struct tm* ltm = localtime(&curTime);
    cout<<ltm->tm_year<<endl;

    //打印chrono时钟精度
    cout << "system clock          : ";
    cout << chrono::system_clock::period::num << "/" << chrono::system_clock::period::den << "s" << endl;
    cout << "steady clock          : ";
    cout << chrono::steady_clock::period::num << "/" << chrono::steady_clock::period::den << "s" << endl;
    cout << "high resolution clock : ";
    cout << chrono::high_resolution_clock::period::num << "/" << chrono::high_resolution_clock::period::den << "s" << endl;

    //chrono打印系统当前时间
    //秒级精度
    auto sec = chrono::time_point_cast<chrono::seconds>(chrono::system_clock::now());
    auto tSec = sec.time_since_epoch().count();
    cout<<"当前时间戳（秒）：" << tSec << endl;

    //毫秒精度
    auto msec = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    auto tMsec = msec.time_since_epoch().count();
    cout<<"当前时间戳（毫秒）："<<tMsec<<endl;

    //微秒精度
    auto usec = chrono::time_point_cast<chrono::microseconds>(chrono::system_clock::now());
    auto tUsec = usec.time_since_epoch().count();
    cout<<"当前时间戳（微秒）："<<tUsec<<endl;

    return 0;
}

