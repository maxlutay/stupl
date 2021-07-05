#pragma once

#include <typeinfo>

template <typename StreamType, typename TestType, typename = void>
struct is_to_stream_writable : std::false_type {};

template <typename StreamType, typename TestType>
struct is_to_stream_writable<
    StreamType,
    TestType,
    std::void_t<decltype(std::declval<StreamType&>() << std::declval<TestType>())> >
    : std::true_type {};


template <typename StreamType, typename TestType> constexpr bool is_to_stream_writable_v =  is_to_stream_writable<StreamType,TestType>::value; 