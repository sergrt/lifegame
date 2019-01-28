#pragma once

template <typename T, typename Parameter>
class NamedType {
    ////////////////////////////////
    // Named type to allow to distinguish different types with the same
    // underlying type. Like, Row and Col are both integer types, but it is
    // wise to disallow them to be interchanged

public:
    explicit NamedType(T const& value)
    : value_(value) {

    }
    T& get() {
        return value_;
    }
    const T& get() const {
        return value_;
    }

private:
    T value_;
};
