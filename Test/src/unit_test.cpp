//
// Created by djangojiang on 2020/7/8.
//

#include <iostream>
#include "gtest/gtest.h"
using namespace std;

class FooTest : public ::testing::Test {
protected:
    void SetUp() override {
        cout<<"SetUp"<<endl;
    }

    void TearDown() override {
        cout<<"TearDown"<<endl;
    }
};

TEST_F(FooTest, testFun) {
    int32_t iRet = 0;

    EXPECT_EQ(iRet,0);
}

TEST_F(FooTest, testFun2) {
    int32_t iRet = 1;

    EXPECT_EQ(iRet,0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
