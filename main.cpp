#include <iostream>

#include "my_shared_ptr.hpp"

int main() {
    my_shared_ptr<int> a(new int(5));
    my_shared_ptr<int> b(a);
    my_shared_ptr<int> c = a;

    std::cout << "Owners: " << a.use_count() << " value: " << *a << std::endl;
    return 0;
}
