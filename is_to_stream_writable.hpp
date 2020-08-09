#pragma once

#include <typeinfo>

template <typename S, typename T, typename = void>
struct is_to_stream_writable : std::false_type {};

template <typename S, typename T>
struct is_to_stream_writable<
    S,
    T,
    std::void_t<decltype(std::declval<S&>() << std::declval<T>())> >
    : std::true_type {};


template <typename S, typename T> inline constexpr bool is_to_stream_writable_v =  is_to_stream_writable<S,T>::value; 