
#pragma once

#include "is_container.h"

#include <iostream>
#include <tuple>
#include <type_traits>

template <typename T>
typename std::enable_if_t<std::is_integral_v<T>> print_ip(const T& v) {
    const uint8_t len = sizeof(T);
    uint8_t byte = (v >> (8 * (len - 1))) & 0xff;
    std::cout << +byte;
    for (int8_t i = len - 2; i >= 0; --i) {
        byte = (v >> (8 * i)) & 0xff;
        std::cout << "." << +byte;
    }
    std::cout << std::endl;
}

template <typename T>
typename std::enable_if_t<is_container_v<T>> print_ip(const T& container) {
    auto it = container.begin();
    if (it == container.end()) return;

    std::cout << *it++;
    for (; it != container.end(); ++it)
        std::cout << "." << *it;
    std::cout << std::endl;
}

template <>
void print_ip(const std::string& s) {
    std::cout << s << std::endl;
}

// https://en.cppreference.com/w/cpp/utility/integer_sequence
template<typename Tuple, std::size_t... Is>
void print_tuple_impl(const Tuple& t, std::index_sequence<Is...>) {
    ((std::cout << (Is == 0? "" : ".") << std::get<Is>(t)), ...);
    std::cout << std::endl;
}

template <typename... Args>
void print_ip(const std::tuple<Args...>& t) {
    print_tuple_impl(t, std::index_sequence_for<Args...>{});
}
