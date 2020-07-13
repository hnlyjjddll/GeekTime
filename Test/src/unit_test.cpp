//
// Created by djangojiang on 2020/7/8.
//

#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
//#include "Foo.h"
using namespace std;
using namespace testing;
//using Fooo::Foo;

void f2(){
    cout<<"f2"<<endl;
}

int fun1(){
    f2();
    cout<<"finish"<<endl;
    return 0;
}

class Boo{
public:
    virtual int testFun(int i,std::string str) {std::cout<<"111"<<std::endl;};
    void fun() {testFun(1,"2");}
};

class FooMock:public Boo{
public:
    MOCK_METHOD(int,testFun,(int i,std::string str),(override));
};

class FooTest : public ::testing::Test{
protected:
    void SetUp() override {
        cout<<"SetUp"<<endl;
    }

    void TearDown() override {
        cout<<"TearDown"<<endl;
    }

    static void SetUpTestSuite(){
        cout<<"setup testsuit"<<endl;
    }

    static void TearDownTestSuite(){
        cout <<"teardown testsuite"<<endl;
    }
};

class ZooTest : public ::testing::Test {
protected:
    void SetUp() override {
        cout<<"SetUp"<<endl;
    }

    void TearDown() override {
        cout<<"TearDown"<<endl;
    }

    static void SetUpTestSuite(){
        cout<<"setup zoo testsuit"<<endl;
    }

    static void TearDownTestSuite(){
        cout <<"teardown zoo testsuite"<<endl;
    }
};



TEST_F(FooTest, testFun) {

    FooMock fooMock;
    EXPECT_CALL(fooMock,testFun(_,_)).
    Times(AtLeast(1)).
    WillOnce([](int i,std::string s){std::cout<<"123"<<std::endl; return 0;});
    Boo* boo = &fooMock;
    boo->fun();

    int32_t iRet = 0;

    EXPECT_EQ(iRet,0);
}

/*TEST_F(FooTest, testFun2) {
    int32_t iRet = 1;

    EXPECT_EQ(iRet,0) << "value is error";
    ASSERT_EQ(iRet, 0);
}*/

TEST_F(ZooTest, testFun){
    int32_t iRet = 0;
    ASSERT_EQ(iRet,0);
}



/*int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/
