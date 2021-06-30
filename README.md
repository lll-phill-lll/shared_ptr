# My shared_ptr test project

## Task: implement shared_ptr

## Expected methods:
1. Default constructor [v]
2. Copy constructor [v]
3. Pointer constructor [v]
4. Copy assignment [v]
5. Destructor [v]
6. Operator* [v]

## About implementation:
All the methods are implemented using documentation on cppreference.
Specific places of realisation are commented and links are provided.
There are some others methods implemented. These methods are required
for testing purposes and correct behaviour of requested methods (operator=).
These methods are standard for shared_ptr.

## Run unit tests:
1. `cmake -S . -B build`
2. `cmake --build build`
3. `cd build && ctest`

## Memory leaks. Valgrind:
To test how the implementation manages the memory you may want
to use valgrind. Here is the tutorial. We will use valgrind with
test binary from previous step.
1. Install valgrind `apt install valgrind` Note: linux only
2. Run test executable with leaks check: `valgrind --tool=memcheck --leak-check=yes build/unit_tests`

### Results:
```
==22058== HEAP SUMMARY:
==22058==     in use at exit: 0 bytes in 0 blocks
==22058==   total heap usage: 461 allocs, 461 frees, 134,390 bytes allocated
==22058==
==22058== All heap blocks were freed -- no leaks are possible
==22058==
==22058== For lists of detected and suppressed errors, rerun with: -s
==22058== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

I also tried to remove `delete` from class and got leaks errors.
So The test really catches the problems.

## How to run main.cpp:
1. `g++ -std=gnu++14 main.cpp`
2. `./a.out`


## About unit tests:
Tests are written using gtest framework. There are 2 types of tests:
simple tests to check that all the methods are implemented and more
complicated tests for documented behaviour in cppreference. In most
tests results are compared to std::shared_ptr results.
