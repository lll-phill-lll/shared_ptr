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

## How to run main.cpp:
1. `g++ -std=gnu++14 main.cpp`
2. `./a.out`


## About unit tests:
Tests are written using gtest framework. There are 2 types of tests:
simple tests to check that all the methods are implemented and more
complicated tests for documented behaviour in cppreference. In most
tests results are compared to std::shared_ptr results.
