/**
 * @brief print_ip module
 */

#pragma once

#include "is_all_same.h"
#include "is_container.h"

#include <iostream>
#include <tuple>
#include <type_traits>

// так и не осилил на лету определять is_integral_v при ее отсутствии
#if __GLIBCXX__ < 20181206
namespace std {
    template<typename T>
    constexpr bool is_integral_v = std::is_integral<T>::value;
}
#endif


/**
 * @brief      Prints ip for integral params
 *
 * @param[in]  v     integral value to print
 */
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
void print_tuple_impl(const Tuple& t, const std::index_sequence<Is...>) {
    using type0 = std::tuple_element_t<0, Tuple>;
    constexpr int len = sizeof...(Is);

    const type0 values[len] = {(std::get<Is>(t))...};

    std::cout << values[0];
    for (int i = 1; i < len; ++i)
        std::cout << "." << values[i];
    std::cout << std::endl;
}

template <typename... Args>
typename std::enable_if_t<is_all_same_v<Args...>> print_ip(const std::tuple<Args...>& t) {
    print_tuple_impl(t, std::index_sequence_for<Args...>{});
}
