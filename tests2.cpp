#include <gtest/gtest.h>

//////////////////////////////////////////////////
// mul2
//////////////////////////////////////////////////

int mul2(int x) { return x * 2; }

TEST( mul2, test_1 ) {
    ASSERT_EQ(42, mul2(21));
}

TEST( mul2, test_2 ) {
    ASSERT_EQ(0, mul2(0));
}

//////////////////////////////////////////////////
// MyClass
//////////////////////////////////////////////////

class MyClass {
    protected:
        int _a;
        int mul2() { return _a * 2; }

    public:
        MyClass(int a) : _a(a) {}
};

class MyClassTest : public MyClass {
    public:
        MyClassTest(int a) : MyClass(a) {}

        using MyClass::_a;
        using MyClass::mul2;
};

TEST( MyClass, test_1 ) {
    MyClassTest c(21);
    ASSERT_EQ(21, c._a);
    ASSERT_EQ(42, c.mul2());
}

//////////////////////////////////////////////////
// main
//////////////////////////////////////////////////

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

