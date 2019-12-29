/**
 * @brief variadic version is_same
 *        https://en.cppreference.com/w/cpp/types/is_same
 */

#pragma once

#include <type_traits>

template <typename ...Ts>
struct is_all_same : std::false_type {};

template<typename T>
struct is_all_same<T> : std::true_type {};

template<typename T, typename ...Ts>
struct is_all_same<T, T, Ts...> : is_all_same<T, Ts...> {};

template <typename ...Ts>
constexpr bool is_all_same_v = is_all_same<Ts...>::value;
