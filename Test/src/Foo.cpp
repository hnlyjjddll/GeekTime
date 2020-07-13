//
// Created by djangojiang on 2020/7/8.
//
#include <iostream>
#include "Foo.h"

using Fooo::Foo;

int Foo::testFun(int i, std::string s){
    std::cout<<"Foo testFun: i: " << i << " s:"<<s<<std::endl;
    return 0;
}

void Foo::fun(){
    int32_t iRet = testFun(0,"fff");
    //std::cout<<"fun finish"<<std::end;
}