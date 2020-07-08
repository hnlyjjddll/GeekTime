//
// Created by djangojiang on 2020/7/8.
//
#include <iostream>
#include "src/Foo.h"

namespace Foo;

int Foo::testFun(int i, std::string s){
    std::cout<<"Foo testFun: i: " << i << " s:"<<s<<endl;
    return 0;
}