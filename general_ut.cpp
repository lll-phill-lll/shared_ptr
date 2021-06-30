#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "my_shared_ptr.hpp"

// If there is no managed object, 0 is returned
// https://en.cppreference.com/w/cpp/memory/shared_ptr/use_count
TEST(MySharedPtr, DefaultCtorValues) {
    my_shared_ptr<int> msp;
    std::shared_ptr<int> sp;
    EXPECT_EQ(sp.use_count(), msp.use_count());

    // UB for default constructor
    // "The behavior is undefined if the stored pointer is null."
    // https://en.cppreference.com/w/cpp/memory/shared_ptr/operator*
    //
    // EXPECT_EQ(*sp,*msp);
}

TEST(MySharedPtr, PointerCtorValues) {
    std::vector<int*> msp_values = {new int(5), nullptr};
    std::vector<int*> sp_values = {new int(5), nullptr};

    for (int i = 0; i != msp_values.size(); ++i) {
        my_shared_ptr<int> msp(msp_values[i]);
        std::shared_ptr<int> sp(sp_values[i]);
        EXPECT_EQ(sp.use_count(), msp.use_count());

        // UB see 1st test
        if (msp_values[i] != nullptr) {
            EXPECT_EQ(*sp, *msp);
        }
    }
}

// Pass nullptr not casted to int*
TEST(MySharedPtr, PointerCtorNullptr) {
    my_shared_ptr<int> msp(nullptr);
    std::shared_ptr<int> sp(nullptr);
    EXPECT_EQ(sp.use_count(), msp.use_count());
}

TEST(MySharedPtr, CopyCtorValues) {
    std::vector<int*> msp_values = {new int(5), nullptr};
    std::vector<int*> sp_values = {new int(5), nullptr};

    for (int i = 0; i != msp_values.size(); ++i) {
        my_shared_ptr<int> from_msp(msp_values[i]);
        my_shared_ptr<int> to_msp(from_msp);

        std::shared_ptr<int> from_sp(sp_values[i]);
        std::shared_ptr<int> to_sp(from_sp);

        EXPECT_EQ(to_sp.use_count(), to_msp.use_count());

        // UB see 1st test
        if (msp_values[i] != nullptr) {
            EXPECT_EQ(*to_sp, *to_msp);
        }
    }
}

// Test nullptr not casted to int*
TEST(MySharedPtr, CopyCtorNullptr) {
    my_shared_ptr<int> from_msp(nullptr);
    my_shared_ptr<int> to_msp(from_msp);

    std::shared_ptr<int> from_sp(nullptr);
    std::shared_ptr<int> to_sp(from_sp);

    EXPECT_EQ(to_sp.use_count(), to_msp.use_count());
    // UB see 1st test
    // EXPECT_EQ(*to_sp, *to_msp);
}

TEST(MySharedPtr, CopyCtorLinksCount) {
    constexpr int n = 5;
    std::vector<std::shared_ptr<int>> sps;
    std::vector<my_shared_ptr<int>> msps;
    sps.reserve(n);
    msps.reserve(n);

    my_shared_ptr<int> msp(new int(3));
    std::shared_ptr<int> sp(new int(3));

    for (int i = 0; i != n; ++i) {
        sps.emplace_back(sp);
        msps.emplace_back(msp);

        EXPECT_EQ(sp.use_count(), msp.use_count());
    }
}

TEST(MySharedPtr, CopyAssignmentValues) {
    std::vector<int*> msp_values = {new int(5), nullptr};
    std::vector<int*> sp_values = {new int(5), nullptr};

    for (int i = 0; i != msp_values.size(); ++i) {
        my_shared_ptr<int> from_msp(msp_values[i]);
        my_shared_ptr<int> to_msp = from_msp;

        std::shared_ptr<int> from_sp(sp_values[i]);
        std::shared_ptr<int> to_sp = from_sp;

        EXPECT_EQ(to_sp.use_count(), to_msp.use_count());
        if (msp_values[i] != nullptr) {
            EXPECT_EQ(*to_sp, *to_msp);
        }
    }
}

// Test nullptr not casted to int*
TEST(MySharedPtr, CopyAssignmentNullptr) {
    my_shared_ptr<int> from_msp(nullptr);
    my_shared_ptr<int> to_msp = from_msp;

    std::shared_ptr<int> from_sp(nullptr);
    std::shared_ptr<int> to_sp = from_sp;

    EXPECT_EQ(to_sp.use_count(), to_msp.use_count());
    // UB see 1st test
    // EXPECT_EQ(*to_sp, *to_msp);
}

TEST(MySharedPtr, CopyAssignmentLinksCount) {
    constexpr int n = 5;
    std::vector<std::shared_ptr<int>> sps(n);
    std::vector<my_shared_ptr<int>> msps(n);

    my_shared_ptr<int> msp(new int(3));
    std::shared_ptr<int> sp(new int(3));

    for (int i = 0; i != n; ++i) {
        sps[i] = sp;
        msps[i] = msp;

        EXPECT_EQ(sp.use_count(), msp.use_count());
    }
}

TEST(MySharedPtr, CopyAssignmentSameObject) {
    my_shared_ptr<int> msp(new int(3));
    std::shared_ptr<int> sp(new int(3));

    my_shared_ptr<int> msp2(msp);
    std::shared_ptr<int> sp2(sp);

    msp = msp2;
    sp = sp2;

    EXPECT_EQ(sp.use_count(), msp.use_count());
}

TEST(MySharedPtr, CopyAssignmentChangeObject) {
    my_shared_ptr<int> msp(new int(3));
    std::shared_ptr<int> sp(new int(3));

    my_shared_ptr<int> msp2(msp);
    std::shared_ptr<int> sp2(sp);

    EXPECT_EQ(sp.use_count(), msp.use_count());
    EXPECT_EQ(*sp, *msp);

    my_shared_ptr<int> new_msp(new int(4));
    std::shared_ptr<int> new_sp(new int(4));

    msp = new_msp;
    sp = new_sp;

    EXPECT_EQ(sp.use_count(), msp.use_count());
    EXPECT_EQ(*sp, *msp);
}


TEST(MySharedPtr, DestructorLinksCount) {
    constexpr int n = 5;
    std::vector<std::shared_ptr<int>> sps;
    std::vector<my_shared_ptr<int>> msps;
    sps.reserve(n);
    msps.reserve(n);

    my_shared_ptr<int> msp(new int(3));
    std::shared_ptr<int> sp(new int(3));

    for (int i = 0; i != n; ++i) {
        sps.emplace_back(sp);
        msps.emplace_back(msp);
    }

    for (int i = 0; i != n; ++i) {
        sps.pop_back();
        msps.pop_back();

        EXPECT_EQ(sp.use_count(), msp.use_count());
    }
}

TEST(MySharedPtr, ComplexValues) {
    struct Complex {
        int a = 3;
        int b = 4;
        std::vector<double> c = {.1, .2, .3};

        bool operator==(const Complex& other) const {
            return a == other.a &&
                   b == other.b &&
                   c == other.c;
        }
    };
    my_shared_ptr<Complex> msp(new Complex());
    my_shared_ptr<Complex> msp2 = msp;
    EXPECT_EQ(2, msp.use_count());
    EXPECT_EQ(*msp, *msp2);
}
