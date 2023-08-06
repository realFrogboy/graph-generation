#pragma once

#include <memory>

namespace graph::utils {

template <class T>
class MakeUnique {
    public:
    explicit MakeUnique(size_t Value) : Value{Value} {}
    operator std::unique_ptr<T>() {
        return std::unique_ptr<T>(new T(Value));
    }
    MakeUnique &operator++() { ++Value; return *this; }

    private:
    size_t Value;
};

} // namespace graph::utils