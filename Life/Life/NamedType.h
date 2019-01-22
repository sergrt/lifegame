#pragma once

template <typename T, typename Parameter>
class NamedType {
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
