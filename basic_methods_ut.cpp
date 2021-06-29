#include <gtest/gtest.h>

#include "my_shared_ptr.hpp"

// Test default constructor
TEST(Basic, DefaultCtor) {
    my_shared_ptr<int> sp;
}

// Test copy constructor
TEST(Basic, CopyCtor) {
    my_shared_ptr<int> sp;
    my_shared_ptr<int> ssp(sp);
}

// Test pointer constructor
TEST(Basic, PtrCtor) {
    my_shared_ptr<int> sp(new int(5));
}

// Test copy assignment
TEST(Basic, CopyAssignment) {
    my_shared_ptr<int> sp;
    my_shared_ptr<int> ssp = sp;
}

// Test star operator
TEST(Basic, StarOperator) {
    my_shared_ptr<int> sp;
    *sp;
}

// Test destructor
TEST(Basic, Destructor) {
    my_shared_ptr<int> sp;
    sp.~my_shared_ptr();
}
