#pragma once

template <typename T>
class my_shared_ptr {
private:
    T* ptr = nullptr;

    // need pointer to share the value across
    // all the instances of shared_ptr
    size_t *count = nullptr;
public:
    // Default ctor
    constexpr my_shared_ptr() noexcept { }

    constexpr my_shared_ptr(std::nullptr_t) noexcept { }

    // Pointer ctor
    explicit my_shared_ptr(T* ptr)
        : ptr(ptr)
        , count(new size_t(1)) { }


    // Copy ctor
    // From documentation:
    // "Constructs a shared_ptr which shares ownership of the object managed by r.
    // If r manages no object, *this manages no object too."
    // https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    my_shared_ptr(const my_shared_ptr& other) noexcept
        : ptr(other.ptr)
        , count(other.count) {

        // increment number of owners of object
        if (ptr != nullptr && count != nullptr) {
            ++(*count);
        }
    }

    // Need this method for tests
    // From documentation:
    // Returns the number of different shared_ptr instances (this included) managing the current object.
    // If there is no managed object, 0 is returned.
    // https://en.cppreference.com/w/cpp/memory/shared_ptr/use_count
    size_t use_count() const noexcept {
        if (count == nullptr) {
            return 0;
        }
        return *count;
    }

    // Need this method for operator=
    // check test: CopyAssignmentSameObject
    // https://en.cppreference.com/w/cpp/memory/shared_ptr/get
    T* get() const noexcept {
        return ptr;
    }

    my_shared_ptr& operator=(const my_shared_ptr& other) noexcept {
        if (this->get() == other.get()) {
            return *this;
        }

        // check if object has any other owners
        // ""If *this already owns an object and it is the last shared_ptr owning it,
        // and r is not the same as *this, the object is destroyed through the owned deleter.
        // https://en.cppreference.com/w/cpp/memory/shared_ptr/operator%3D
        if (count != nullptr) {
            --(*count);
            if (*count == 0) {
                delete count;
                if (ptr != nullptr) {
                    delete ptr;
                }
            }
        }

        ptr = other.ptr;
        count = other.count;
        // increment number of owners of object
        if (ptr != nullptr && count != nullptr) {
            ++(*count);
        }

        return *this;
    }

    T& operator*() const noexcept {
        return *ptr;
    }

    ~my_shared_ptr() {
        if (count != nullptr && *count > 1) {
            // decrement number of owners of the object
            // don't delete pointers because there are
            // other owners alive
            --(*count);
            return;
        }

        if (ptr != nullptr) {
            delete ptr;
        }

        if (count != nullptr) {
            delete count;
        }
    }

};
