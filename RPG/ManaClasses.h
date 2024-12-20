#pragma once

#include "Core.h"

template <typename AnyT>
class ManaType{
private:
    AnyT value;

public:
    ManaType(AnyT v = 0) : value(v) {
        UseMana(sizeof(AnyT), typeid(AnyT).name());
    }

    AnyT Extract() { return value;}
    AnyT Get() { return Extract(); }
};

template <typename T>
class ManaInt {
private:
    T value;

public:
    // Constructor
    ManaInt(T v = 0) : value(v) {
        UseMana(sizeof(T), typeid(T).name());
    }

    // Overloaded assignment operator
    ManaInt& operator=(T v) {
        value = v;
        return *this;
    }

    operator int() const {
        return static_cast<int>(value);
    }

        // Arithmetic operators with another ManaInt
    ManaInt operator+(const ManaInt& other) const { return ManaInt(value + other.value); }
    ManaInt operator-(const ManaInt& other) const { return ManaInt(value - other.value); }
    ManaInt operator*(const ManaInt& other) const { return ManaInt(value * other.value); }
    ManaInt operator/(const ManaInt& other) const { return ManaInt(value / other.value); }
    ManaInt operator%(const ManaInt& other) const { return ManaInt(value % other.value); }

    // Arithmetic operators with an int
    ManaInt operator+(int other) const { return ManaInt(value + static_cast<T>(other)); }
    ManaInt operator-(int other) const { return ManaInt(value - static_cast<T>(other)); }
    ManaInt operator*(int other) const { return ManaInt(value * static_cast<T>(other)); }
    ManaInt operator/(int other) const { return ManaInt(value / static_cast<T>(other)); }
    ManaInt operator%(int other) const { return ManaInt(value % static_cast<T>(other)); }

    ManaInt operator+(size_t other) const { return ManaInt(value + static_cast<T>(other)); }
    ManaInt operator-(size_t other) const { return ManaInt(value - static_cast<T>(other)); }
    ManaInt operator*(size_t other) const { return ManaInt(value * static_cast<T>(other)); }
    ManaInt operator/(size_t other) const { return ManaInt(value / static_cast<T>(other)); }
    ManaInt operator%(size_t other) const { return ManaInt(value % static_cast<T>(other)); }

    // Friend functions for symmetry: int + ManaInt, int - ManaInt, etc.
    friend ManaInt operator+(int lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) + rhs.value); }
    friend ManaInt operator-(int lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) - rhs.value); }
    friend ManaInt operator*(int lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) * rhs.value); }
    friend ManaInt operator/(int lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) / rhs.value); }
    friend ManaInt operator%(int lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) % rhs.value); }

    friend ManaInt operator+(size_t lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) + rhs.value); }
    friend ManaInt operator-(size_t lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) - rhs.value); }
    friend ManaInt operator*(size_t lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) * rhs.value); }
    friend ManaInt operator/(size_t lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) / rhs.value); }
    friend ManaInt operator%(size_t lhs, const ManaInt& rhs) { return ManaInt(static_cast<T>(lhs) % rhs.value); }

    // Compound assignment operators with another ManaInt
    ManaInt& operator+=(const ManaInt& other) { value += other.value; return *this; }
    ManaInt& operator-=(const ManaInt& other) { value -= other.value; return *this; }
    ManaInt& operator*=(const ManaInt& other) { value *= other.value; return *this; }
    ManaInt& operator/=(const ManaInt& other) { value /= other.value; return *this; }
    ManaInt& operator%=(const ManaInt& other) { value %= other.value; return *this; }

    // Compound assignment operators with an int
    ManaInt& operator+=(int other) { value += static_cast<T>(other); return *this; }
    ManaInt& operator-=(int other) { value -= static_cast<T>(other); return *this; }
    ManaInt& operator*=(int other) { value *= static_cast<T>(other); return *this; }
    ManaInt& operator/=(int other) { value /= static_cast<T>(other); return *this; }
    ManaInt& operator%=(int other) { value %= static_cast<T>(other); return *this; }

    ManaInt& operator+=(size_t other) { value += static_cast<T>(other); return *this; }
    ManaInt& operator-=(size_t other) { value -= static_cast<T>(other); return *this; }
    ManaInt& operator*=(size_t other) { value *= static_cast<T>(other); return *this; }
    ManaInt& operator/=(size_t other) { value /= static_cast<T>(other); return *this; }
    ManaInt& operator%=(size_t other) { value %= static_cast<T>(other); return *this; }

    // Comparison operators
    bool operator==(const ManaInt& other) const { return value == other.value; }
    bool operator!=(const ManaInt& other) const { return value != other.value; }
    bool operator<(const ManaInt& other) const { return value < other.value; }
    bool operator<=(const ManaInt& other) const { return value <= other.value; }
    bool operator>(const ManaInt& other) const { return value > other.value; }
    bool operator>=(const ManaInt& other) const { return value >= other.value; }

    // Comparison operators with an int
    bool operator==(int other) const { return value == static_cast<T>(other); }
    bool operator!=(int other) const { return value != static_cast<T>(other); }
    bool operator<(int other) const { return value < static_cast<T>(other); }
    bool operator<=(int other) const { return value <= static_cast<T>(other); }
    bool operator>(int other) const { return value > static_cast<T>(other); }
    bool operator>=(int other) const { return value >= static_cast<T>(other); }

    bool operator==(size_t other) const { return value == static_cast<T>(other); }
    bool operator!=(size_t other) const { return value != static_cast<T>(other); }
    bool operator<(size_t other) const { return value < static_cast<T>(other); }
    bool operator<=(size_t other) const { return value <= static_cast<T>(other); }
    bool operator>(size_t other) const { return value > static_cast<T>(other); }
    bool operator>=(size_t other) const { return value >= static_cast<T>(other); }

    // Friend functions for symmetry
    friend bool operator==(int lhs, const ManaInt& rhs) { return static_cast<T>(lhs) == rhs.value; }
    friend bool operator!=(int lhs, const ManaInt& rhs) { return static_cast<T>(lhs) != rhs.value; }
    friend bool operator<(int lhs, const ManaInt& rhs) { return static_cast<T>(lhs) < rhs.value; }
    friend bool operator<=(int lhs, const ManaInt& rhs) { return static_cast<T>(lhs) <= rhs.value; }
    friend bool operator>(int lhs, const ManaInt& rhs) { return static_cast<T>(lhs) > rhs.value; }
    friend bool operator>=(int lhs, const ManaInt& rhs) { return static_cast<T>(lhs) >= rhs.value; }

    friend bool operator==(size_t lhs, const ManaInt& rhs) { return static_cast<T>(lhs) == rhs.value; }
    friend bool operator!=(size_t lhs, const ManaInt& rhs) { return static_cast<T>(lhs) != rhs.value; }
    friend bool operator<(size_t lhs, const ManaInt& rhs) { return static_cast<T>(lhs) < rhs.value; }
    friend bool operator<=(size_t lhs, const ManaInt& rhs) { return static_cast<T>(lhs) <= rhs.value; }
    friend bool operator>(size_t lhs, const ManaInt& rhs) { return static_cast<T>(lhs) > rhs.value; }
    friend bool operator>=(size_t lhs, const ManaInt& rhs) { return static_cast<T>(lhs) >= rhs.value; }

    // Bitwise operators
    ManaInt operator&(const ManaInt& other) const { return ManaInt(value & other.value); }
    ManaInt operator|(const ManaInt& other) const { return ManaInt(value | other.value); }
    ManaInt operator^(const ManaInt& other) const { return ManaInt(value ^ other.value); }
    ManaInt operator~() const { return ManaInt(~value); }
    ManaInt operator<<(int shift) const { return ManaInt(value << shift); }
    ManaInt operator>>(int shift) const { return ManaInt(value >> shift); }

    // Compound assignment operators
    ManaInt& operator&=(const ManaInt& other) { value &= other.value; return *this; }
    ManaInt& operator|=(const ManaInt& other) { value |= other.value; return *this; }
    ManaInt& operator^=(const ManaInt& other) { value ^= other.value; return *this; }

    // Numeric literal support
    ManaInt operator&(int num) const { return ManaInt(value & num); }
    ManaInt operator|(int num) const { return ManaInt(value | num); }
    ManaInt operator^(int num) const { return ManaInt(value ^ num); }
    ManaInt& operator&=(int num) { value &= num; return *this; }
    ManaInt& operator|=(int num) { value |= num; return *this; }

    // Increment and decrement operators
    ManaInt& operator++() { // Prefix
        ++value;
        return *this;
    }
    ManaInt operator++(int) { // Postfix
        ManaInt temp = *this;
        ++value;
        return temp;
    }
    ManaInt& operator--() { // Prefix
        --value;
        return *this;
    }
    ManaInt operator--(int) { // Postfix
        ManaInt temp = *this;
        --value;
        return temp;
    }

    // Implicit cast to T
    operator T() const { return value; }

    // Implicit cast to std::string
    operator std::string() const {
        return std::to_string(value);
    }

    T Extract() const { return value; }
    T Get() const { return value; }
    T get() const { return value; }
};

using uint8_c = ManaInt<uint8_t>;
using uint16_c = ManaInt<uint16_t>;
using uint32_c = ManaInt<uint32_t>;
using uint64_c = ManaInt<uint64_t>;
using int8_c = ManaInt<int8_t>;
using int16_c = ManaInt<int16_t>;
using int32_c = ManaInt<int32_t>;
using int64_c = ManaInt<int64_t>;


template <typename T>
class ManaFloat {
private:
    T value;

public:
    // Constructor
    ManaFloat(T v = 0) : value(v) {
        UseMana(sizeof(T), "ManaFloat");
    }

    // Overloaded assignment operator
    ManaFloat& operator=(T v) {
        value = v;
        return *this;
    }

    // Arithmetic operators
    ManaFloat operator+(const ManaFloat& other) const { return ManaFloat(value + other.value); }
    ManaFloat operator-(const ManaFloat& other) const { return ManaFloat(value - other.value); }
    ManaFloat operator*(const ManaFloat& other) const { return ManaFloat(value * other.value); }
    ManaFloat operator/(const ManaFloat& other) const {
        if (other.value == 0) throw std::runtime_error("Division by zero!");
        return ManaFloat(value / other.value);
    }

    // Comparison operators
    bool operator==(const ManaFloat& other) const { return value == other.value; }
    bool operator!=(const ManaFloat& other) const { return value != other.value; }
    bool operator<(const ManaFloat& other) const { return value < other.value; }
    bool operator>(const ManaFloat& other) const { return value > other.value; }
    bool operator<=(const ManaFloat& other) const { return value <= other.value; }
    bool operator>=(const ManaFloat& other) const { return value >= other.value; }

    // Increment and decrement operators
    ManaFloat& operator++() { // Prefix
        ++value;
        return *this;
    }
    ManaFloat operator++(int) { // Postfix
        ManaFloat temp = *this;
        ++value;
        return temp;
    }
    ManaFloat& operator--() { // Prefix
        --value;
        return *this;
    }
    ManaFloat operator--(int) { // Postfix
        ManaFloat temp = *this;
        --value;
        return temp;
    }

    // Implicit cast to T
    operator T() const { return value; }

    // Implicit cast to std::string
    operator std::string() const {
        return std::to_string(value);
    }

    T Extract() const { return value; }
    T Get() { return Extract(); }
};

// Typedefs for specific floating-point types
using float_c = ManaFloat<float>;
using double_c = ManaFloat<double>;
using long_double_c = ManaFloat<long double>;

class bool_c {
private:
    bool value;

public:
    // Constructor
    bool_c(bool v = false) : value(v) {
        UseMana(sizeof(bool), "bool");
    }

    // Overloaded assignment operator
    bool_c& operator=(bool v) {
        value = v;
        return *this;
    }

    bool_c operator!() const { return bool_c(!value); }
    bool_c operator&&(const bool_c& other) const { return bool_c(value && other.value); }
    bool_c operator||(const bool_c& other) const { return bool_c(value || other.value); }
    bool operator==(const bool_c& other) const { return value == other.value; }
    bool operator!=(const bool_c& other) const { return value != other.value; }

    // Implicit cast to bool
    operator bool() const { return value; }

    // Implicit cast to std::string
    operator std::string() const { return value ? "true" : "false"; }

    bool Extract() const { return value; }
    bool Get() { return Extract(); }
};

class char_c {
private:
    char value;

public:
    // Constructor
    char_c(char v = '\0') : value(v) {
        UseMana(sizeof(char), "char");
    }

    // Overloaded assignment operator
    char_c& operator=(char v) {
        value = v;
        return *this;
    }

    // Arithmetic Operators
    char_c operator+(int offset) const { return char_c(value + offset); }
    char_c operator-(int offset) const { return char_c(value - offset); }

    // Comparison Operators
    bool operator==(const char_c& other) const { return value == other.value; }
    bool operator!=(const char_c& other) const { return value != other.value; }
    bool operator<(const char_c& other) const { return value < other.value; }
    bool operator>(const char_c& other) const { return value > other.value; }
    bool operator<=(const char_c& other) const { return value <= other.value; }
    bool operator>=(const char_c& other) const { return value >= other.value; }

    // Increment and Decrement Operators
    char_c& operator++() { // Prefix
        ++value;
        return *this;
    }
    char_c operator++(int) { // Postfix
        char_c temp = *this;
        ++value;
        return temp;
    }
    char_c& operator--() { // Prefix
        --value;
        return *this;
    }
    char_c operator--(int) { // Postfix
        char_c temp = *this;
        --value;
        return temp;
    }

    // Implicit cast to char
    operator char() const { return value; }

    // Implicit cast to std::string
    operator std::string() const { return std::string(1, value); }

    char Extract() const { return value; }
    char Get() { return Extract(); }
};

#include <cstring>
#include <iostream>
#include <stdexcept>

class string_c {
private:
    char* value;    // Dynamically allocated string
    size_t length;  // Length of the string

public:
    // Default Constructor
    string_c(const char* str = "") {
        length = std::strlen(str);
        UseMana(length * sizeof(char), "string_c");
        value = new char[length + 1];              
        std::strcpy(value, str);
    }

    // Copy Constructor
    string_c(const string_c& other) {
        length = other.length;
        UseMana(length * sizeof(char), "string_c");
        value = new char[length + 1];
        std::strcpy(value, other.value);
    }

    // Move Constructor
    string_c(string_c&& other) noexcept : value(other.value), length(other.length) {
        other.value = nullptr;
        other.length = 0;
    }

    // Destructor
    ~string_c() {
        if (value) {
            delete[] value;
        }
    }

    // Overloaded Assignment Operator
    string_c& operator=(const string_c& other) {
        if (this == &other) return *this; // Self-assignment check
        delete[] value;

        length = other.length;
        value = new char[length + 1];
        std::strcpy(value, other.value);
        return *this;
    }

    // Move Assignment Operator
    string_c& operator=(string_c&& other) noexcept {
        if (this == &other) return *this; // Self-assignment check
        delete[] value;

        value = other.value;
        length = other.length;
        other.value = nullptr;
        other.length = 0;
        return *this;
    }

    // Concatenation
    string_c operator+(const string_c& other) const {
        size_t newLength = length + other.length;
        UseMana(newLength * sizeof(char), "char");
        char* newValue = new char[newLength + 1];

        std::strcpy(newValue, value);
        std::strcat(newValue, other.value);

        string_c result(newValue);
        delete[] newValue;
        return result;
    }

    // Equality Comparison
    bool operator==(const string_c& other) const {
        return std::strcmp(value, other.value) == 0;
    }

    bool operator!=(const string_c& other) const {
        return !(*this == other);
    }

    // Access Characters
    char& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Index out of range");
        return value[index];
    }

    const char& operator[](size_t index) const {
        if (index >= length) throw std::out_of_range("Index out of range");
        return value[index];
    }

    // Get Length
    size_t size() const { return length; }

    // Implicit Cast to std::string
    operator std::string() const { return std::string(value); }

    // Getter
    const char* c_str() const { return value; }
};