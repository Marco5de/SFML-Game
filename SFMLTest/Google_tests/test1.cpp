//
// Created by marco on 04.12.19.
//


#include "gtest/gtest.h"
#include "../src/Game.h"


class BasicTest : public ::testing::Test {
protected:

virtual void TearDown() {
}

virtual void SetUp() {
}

public:

BasicTest() : Test() {

}

virtual ~

BasicTest() {

}

};

TEST_F(BasicTest, add_check){
    int val = addFloatTestFunc(2.0,2.0);
    EXPECT_EQ(val,4.0);
}

