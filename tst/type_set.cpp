// Copyright (c) 2017 Bronislaw (Bronek) Kozicki
//
// Distributed under the MIT License. See accompanying file license.txt
// or copy at https://opensource.org/licenses/MIT

#include <gtest/gtest.h>

#include <type_traits>

#include <type_set.hpp>

TEST(type_set, test_type_set__unique)
{
    using namespace juno;
    using namespace juno::d;

    // not in empty list
    static_assert(std::is_same<is_in<int>::result, false_>::value, "");
    static_assert(std::is_same<is_in<void>::result, false_>::value, "");

    // int is not in (void) nor in (long, void*)
    static_assert(std::is_same<is_in<int, void>::result, false_>::value, "");
    static_assert(std::is_same<is_in<int, long, void*>::result, false_>::value, "");

    // int is in (int, void) and in (int, long, void*), in any order of elements
    static_assert(std::is_same<is_in<int, int, void>::result, true_>::value, "");
    static_assert(std::is_same<is_in<int, void, int>::result, true_>::value, "");
    static_assert(std::is_same<is_in<int, int, long, void*>::result, true_>::value, "");
    static_assert(std::is_same<is_in<int, int, void*, long>::result, true_>::value, "");
    static_assert(std::is_same<is_in<int, long, int, void*>::result, true_>::value, "");
    static_assert(std::is_same<is_in<int, long, void*, int>::result, true_>::value, "");
    static_assert(std::is_same<is_in<int, void*, long, int>::result, true_>::value, "");
    static_assert(std::is_same<is_in<int, void*, int, long>::result, true_>::value, "");

    // unique means no duplicate types, no voids
    static_assert(std::is_same<set<>::unique, set<>>::value, "");
    static_assert(std::is_same<set<void>::unique, set<>>::value, "");
    static_assert(std::is_same<set<void, void>::unique, set<>>::value, "");
    static_assert(std::is_same<set<void, void, void>::unique, set<>>::value, "");
    static_assert(std::is_same<set<int>::unique, set<int>>::value, "");
    static_assert(std::is_same<set<int, void, int>::unique, set<int>>::value, "");
    static_assert(std::is_same<set<int, int, int>::unique, set<int>>::value, "");
    static_assert(std::is_same<set<void, int, int, int, int, void, void>::unique, set<int>>::value, "");
    static_assert(std::is_same<set<long, int, void>::unique, set<long, int>>::value, "");
    static_assert(std::is_same<set<long, int, int>::unique, set<long, int>>::value, "");
    static_assert(std::is_same<set<long, int, int, void, void, int>::unique, set<long, int>>::value, "");
    static_assert(std::is_same<set<void, int, int, long>::unique, set<int, long>>::value, "");
    static_assert(std::is_same<set<long, int, int, long, int>::unique, set<long, int>>::value, "");
    static_assert(std::is_same<set<int, int, long, long, long ,int, int, int, int>::unique, set<long, int>>::value, "");
    static_assert(std::is_same<set<void, void, long, int, void, int, long, long, long, int, int, long, int>::unique, set<long, int>>::value, "");
    static_assert(std::is_same<set<void, long, void, int, long, int, int, long, int, long, long, long, long, void>::unique, set<int, long>>::value, "");

    SUCCEED();
}

TEST(type_set, test_type_set__size__empty__is_in__is_same)
{
    using namespace juno;

    // test removal of "void" type from type_set
    constexpr auto e = type_set<>();
    static_assert(e.empty(), "");
    static_assert(type_set<void>::empty(), "");
    static_assert(type_set<void>::size() == 0, "");
    static_assert(type_set<void, void, void>::empty(), "");
    static_assert(type_set<void, void, void>::size() == 0, "");
    static_assert(not type_set<void, int, void>::empty(), "");
    static_assert(type_set<void, int, void>::size() == 1, "");
    static_assert(not type_set<void, int, void, void, long>::empty(), "");
    static_assert(type_set<void, int, void, void, long>::size() == 2, "");
    static_assert(not type_set<int, void, void, long, void, void>::empty(), "");
    static_assert(type_set<int, void, void, long, void, void>::size() == 2, "");

    // test removal of duplicate types and "void" from type_set
    static_assert(type_set<>::is_same<type_set<void>>(), "");
    static_assert(type_set<>::is_same<type_set<void, void>>(), "");
    static_assert(type_set<>::is_same<type_set<void, void, void>>(), "");
    static_assert(type_set<void>::is_same<type_set<>>(), "");
    static_assert(type_set<void, void>::is_same<type_set<>>(), "");
    static_assert(type_set<void, void, void>::is_same<type_set<>>(), "");
    static_assert(type_set<void, void, void>::is_same<type_set<void>>(), "");
    static_assert(type_set<void, void, void>::is_same<type_set<void, void>>(), "");
    static_assert(type_set<void, void>::is_same<type_set<void, void>>(), "");
    static_assert(type_set<void, void>::is_same<type_set<void>>(), "");
    static_assert(type_set<int>::is_same<type_set<void, int, void>>(), "");
    static_assert(type_set<void, int>::is_same<type_set<void, int, void>>(), "");
    static_assert(type_set<int>::is_same<type_set<void, const int, void, volatile int>>(), "");
    static_assert(type_set<int>::is_same<type_set<void, int&&, void, const int&, void, void>>(), "");
    static_assert(type_set<int>::is_same<type_set<void, volatile int, void, void>>(), "");
    static_assert(type_set<int>::is_same<type_set<void, void, void, const int&>>(), "");
    static_assert(type_set<void, void, int, void, const int&&, void>::is_same<type_set<void, void, void, const int&>>(), "");

    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<void>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<void, void>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<int>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<long&&>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<const unsigned long&>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<volatile long, int>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<void, int&, long&>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<const long&&, const unsigned long&>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<const long&, unsigned long&&, int&&>>(), "");
    static_assert(type_set<const int, const long, unsigned long&&>::is_in<type_set<const long, unsigned long, int, void, void>>(), "");
    static_assert(type_set<int, long, unsigned long>::is_in<type_set<const long&, unsigned long&&, int&&>>(), "");
    static_assert(type_set<int, long, unsigned long>::is_in<type_set<long, unsigned long, int>>(), "");
    static_assert(not type_set<int, long, unsigned long>::is_in<type_set<long, unsigned long, int, char>>(), "");
    static_assert(not type_set<int, long, unsigned long>::is_in<type_set<void, unsigned int, void>>(), "");

    static_assert(type_set<void, void, int, const int&&, void, void>::size() == 1, "");
    static_assert(type_set<
        int, const int, volatile int, const volatile int
        , int&, const int&, volatile int&, const volatile int&
        , int&&, const int&&, volatile int&&, const volatile int&&
        , long, const long, volatile long, const volatile long
        , long&, const long&, volatile long&, const volatile long&
        , long&&, const long&&, volatile long&&, const volatile long&&
        >::size() == 2, "");
    static_assert(type_set<
        int, const int, volatile int, const volatile int, void
        , int&, const int&, volatile int&, const volatile int&, void, void
        , int&&, const int&&, volatile int&&, const volatile int&&, void, void, void
        , long, const long, volatile long, const volatile long, void, void, void, void
        , long&, const long&, volatile long&, const volatile long&, void, void, void, void, void
        , long&&, const long&&, volatile long&&, const volatile long&&, void, void, void, void, void, void
        >::is_same<type_set<int, long>>(), "");

    constexpr auto i = type_set<int>();
    constexpr auto ci = type_set<const int>();
    constexpr auto vi = type_set<volatile int>();
    constexpr auto cvi = type_set<const volatile int>();
    constexpr auto ri = type_set<int&, void, int&>();
    constexpr auto rci = type_set<void, const int&, void, const int&>();
    constexpr auto rvi = type_set<void, void, volatile int&, void, void, volatile int&, void, void>();
    constexpr auto rcvi = type_set<void, const volatile int&, const volatile int&, void, void>();
    constexpr auto rri = type_set<int&&, int, void>();
    constexpr auto rrci = type_set<void, void, const int&&, int&>();
    constexpr auto rrvi = type_set<void, volatile int&&, void, int&&, void>();
    constexpr auto rrcvi = type_set<void, void, const volatile int&&, void, const int&, void, void, void>();

    static_assert(decltype(i)::is_same<decltype(ci)>(), "");
    static_assert(decltype(i)::is_same<decltype(vi)>(), "");
    static_assert(decltype(i)::is_same<decltype(cvi)>(), "");
    static_assert(decltype(i)::is_same<decltype(ri)>(), "");
    static_assert(decltype(i)::is_same<decltype(rci)>(), "");
    static_assert(decltype(i)::is_same<decltype(rvi)>(), "");
    static_assert(decltype(i)::is_same<decltype(rcvi)>(), "");
    static_assert(decltype(i)::is_same<decltype(rri)>(), "");
    static_assert(decltype(i)::is_same<decltype(rrci)>(), "");
    static_assert(decltype(i)::is_same<decltype(rrvi)>(), "");
    static_assert(decltype(i)::is_same<decltype(rrcvi)>(), "");

    static_assert(not i.empty(), "");
    static_assert(not ci.empty(), "");
    static_assert(not vi.empty(), "");
    static_assert(not cvi.empty(), "");
    static_assert(not ri.empty(), "");
    static_assert(not rci.empty(), "");
    static_assert(not rvi.empty(), "");
    static_assert(not rcvi.empty(), "");
    static_assert(not rri.empty(), "");
    static_assert(not rrci.empty(), "");
    static_assert(not rrvi.empty(), "");
    static_assert(not rrcvi.empty(), "");
    static_assert(i.size() == 1, "");
    static_assert(ci.size() == 1, "");
    static_assert(vi.size() == 1, "");
    static_assert(cvi.size() == 1, "");
    static_assert(ri.size() == 1, "");
    static_assert(rci.size() == 1, "");
    static_assert(rvi.size() == 1, "");
    static_assert(rcvi.size() == 1, "");
    static_assert(rri.size() == 1, "");
    static_assert(rrci.size() == 1, "");
    static_assert(rrvi.size() == 1, "");
    static_assert(rrcvi.size() == 1, "");

    static_assert(i.is_in<int>(), "");
    static_assert(i.is_in<const int>(), "");
    static_assert(i.is_in<volatile int>(), "");
    static_assert(i.is_in<const volatile int>(), "");
    static_assert(i.is_in<int&>(), "");
    static_assert(i.is_in<const int&>(), "");
    static_assert(i.is_in<volatile int&>(), "");
    static_assert(i.is_in<const volatile int&>(), "");
    static_assert(i.is_in<int&&>(), "");
    static_assert(i.is_in<const int&&>(), "");
    static_assert(i.is_in<volatile int&&>(), "");
    static_assert(i.is_in<const volatile int&&>(), "");
    static_assert(i.is_in<signed int>(), "");
    static_assert(i.is_in<const signed int>(), "");
    static_assert(i.is_in<volatile signed int>(), "");
    static_assert(i.is_in<const volatile signed int>(), "");
    static_assert(i.is_in<signed int&>(), "");
    static_assert(i.is_in<const signed int&>(), "");
    static_assert(i.is_in<volatile signed int&>(), "");
    static_assert(i.is_in<const volatile signed int&>(), "");
    static_assert(i.is_in<signed int&&>(), "");
    static_assert(i.is_in<const signed int&&>(), "");
    static_assert(i.is_in<volatile signed int&&>(), "");
    static_assert(i.is_in<const volatile signed int&&>(), "");
    static_assert(ci.is_in<int>(), "");
    static_assert(ci.is_in<const int>(), "");
    static_assert(ci.is_in<volatile int>(), "");
    static_assert(ci.is_in<const volatile int>(), "");
    static_assert(ci.is_in<int&>(), "");
    static_assert(ci.is_in<const int&>(), "");
    static_assert(ci.is_in<volatile int&>(), "");
    static_assert(ci.is_in<const volatile int&>(), "");
    static_assert(ci.is_in<int&&>(), "");
    static_assert(ci.is_in<const int&&>(), "");
    static_assert(ci.is_in<volatile int&&>(), "");
    static_assert(ci.is_in<const volatile int&&>(), "");
    static_assert(ci.is_in<signed int>(), "");
    static_assert(ci.is_in<const signed int>(), "");
    static_assert(ci.is_in<volatile signed int>(), "");
    static_assert(ci.is_in<const volatile signed int>(), "");
    static_assert(ci.is_in<signed int&>(), "");
    static_assert(ci.is_in<const signed int&>(), "");
    static_assert(ci.is_in<volatile signed int&>(), "");
    static_assert(ci.is_in<const volatile signed int&>(), "");
    static_assert(ci.is_in<signed int&&>(), "");
    static_assert(ci.is_in<const signed int&&>(), "");
    static_assert(ci.is_in<volatile signed int&&>(), "");
    static_assert(ci.is_in<const volatile signed int&&>(), "");
    static_assert(vi.is_in<int>(), "");
    static_assert(vi.is_in<const int>(), "");
    static_assert(vi.is_in<volatile int>(), "");
    static_assert(vi.is_in<const volatile int>(), "");
    static_assert(vi.is_in<int&>(), "");
    static_assert(vi.is_in<const int&>(), "");
    static_assert(vi.is_in<volatile int&>(), "");
    static_assert(vi.is_in<const volatile int&>(), "");
    static_assert(vi.is_in<int&&>(), "");
    static_assert(vi.is_in<const int&&>(), "");
    static_assert(vi.is_in<volatile int&&>(), "");
    static_assert(vi.is_in<const volatile int&&>(), "");
    static_assert(vi.is_in<signed int>(), "");
    static_assert(vi.is_in<const signed int>(), "");
    static_assert(vi.is_in<volatile signed int>(), "");
    static_assert(vi.is_in<const volatile signed int>(), "");
    static_assert(vi.is_in<signed int&>(), "");
    static_assert(vi.is_in<const signed int&>(), "");
    static_assert(vi.is_in<volatile signed int&>(), "");
    static_assert(vi.is_in<const volatile signed int&>(), "");
    static_assert(vi.is_in<signed int&&>(), "");
    static_assert(vi.is_in<const signed int&&>(), "");
    static_assert(vi.is_in<volatile signed int&&>(), "");
    static_assert(vi.is_in<const volatile signed int&&>(), "");
    static_assert(cvi.is_in<int>(), "");
    static_assert(cvi.is_in<const int>(), "");
    static_assert(cvi.is_in<volatile int>(), "");
    static_assert(cvi.is_in<const volatile int>(), "");
    static_assert(cvi.is_in<int&>(), "");
    static_assert(cvi.is_in<const int&>(), "");
    static_assert(cvi.is_in<volatile int&>(), "");
    static_assert(cvi.is_in<const volatile int&>(), "");
    static_assert(cvi.is_in<int&&>(), "");
    static_assert(cvi.is_in<const int&&>(), "");
    static_assert(cvi.is_in<volatile int&&>(), "");
    static_assert(cvi.is_in<const volatile int&&>(), "");
    static_assert(cvi.is_in<signed int>(), "");
    static_assert(cvi.is_in<const signed int>(), "");
    static_assert(cvi.is_in<volatile signed int>(), "");
    static_assert(cvi.is_in<const volatile signed int>(), "");
    static_assert(cvi.is_in<signed int&>(), "");
    static_assert(cvi.is_in<const signed int&>(), "");
    static_assert(cvi.is_in<volatile signed int&>(), "");
    static_assert(cvi.is_in<const volatile signed int&>(), "");
    static_assert(cvi.is_in<signed int&&>(), "");
    static_assert(cvi.is_in<const signed int&&>(), "");
    static_assert(cvi.is_in<volatile signed int&&>(), "");
    static_assert(cvi.is_in<const volatile signed int&&>(), "");
    static_assert(ri.is_in<int>(), "");
    static_assert(ri.is_in<const int>(), "");
    static_assert(ri.is_in<volatile int>(), "");
    static_assert(ri.is_in<const volatile int>(), "");
    static_assert(ri.is_in<int&>(), "");
    static_assert(ri.is_in<const int&>(), "");
    static_assert(ri.is_in<volatile int&>(), "");
    static_assert(ri.is_in<const volatile int&>(), "");
    static_assert(ri.is_in<int&&>(), "");
    static_assert(ri.is_in<const int&&>(), "");
    static_assert(ri.is_in<volatile int&&>(), "");
    static_assert(ri.is_in<const volatile int&&>(), "");
    static_assert(ri.is_in<signed int>(), "");
    static_assert(ri.is_in<const signed int>(), "");
    static_assert(ri.is_in<volatile signed int>(), "");
    static_assert(ri.is_in<const volatile signed int>(), "");
    static_assert(ri.is_in<signed int&>(), "");
    static_assert(ri.is_in<const signed int&>(), "");
    static_assert(ri.is_in<volatile signed int&>(), "");
    static_assert(ri.is_in<const volatile signed int&>(), "");
    static_assert(ri.is_in<signed int&&>(), "");
    static_assert(ri.is_in<const signed int&&>(), "");
    static_assert(ri.is_in<volatile signed int&&>(), "");
    static_assert(ri.is_in<const volatile signed int&&>(), "");
    static_assert(rci.is_in<int>(), "");
    static_assert(rci.is_in<const int>(), "");
    static_assert(rci.is_in<volatile int>(), "");
    static_assert(rci.is_in<const volatile int>(), "");
    static_assert(rci.is_in<int&>(), "");
    static_assert(rci.is_in<const int&>(), "");
    static_assert(rci.is_in<volatile int&>(), "");
    static_assert(rci.is_in<const volatile int&>(), "");
    static_assert(rci.is_in<int&&>(), "");
    static_assert(rci.is_in<const int&&>(), "");
    static_assert(rci.is_in<volatile int&&>(), "");
    static_assert(rci.is_in<const volatile int&&>(), "");
    static_assert(rci.is_in<signed int>(), "");
    static_assert(rci.is_in<const signed int>(), "");
    static_assert(rci.is_in<volatile signed int>(), "");
    static_assert(rci.is_in<const volatile signed int>(), "");
    static_assert(rci.is_in<signed int&>(), "");
    static_assert(rci.is_in<const signed int&>(), "");
    static_assert(rci.is_in<volatile signed int&>(), "");
    static_assert(rci.is_in<const volatile signed int&>(), "");
    static_assert(rci.is_in<signed int&&>(), "");
    static_assert(rci.is_in<const signed int&&>(), "");
    static_assert(rci.is_in<volatile signed int&&>(), "");
    static_assert(rci.is_in<const volatile signed int&&>(), "");
    static_assert(rvi.is_in<int>(), "");
    static_assert(rvi.is_in<const int>(), "");
    static_assert(rvi.is_in<volatile int>(), "");
    static_assert(rvi.is_in<const volatile int>(), "");
    static_assert(rvi.is_in<int&>(), "");
    static_assert(rvi.is_in<const int&>(), "");
    static_assert(rvi.is_in<volatile int&>(), "");
    static_assert(rvi.is_in<const volatile int&>(), "");
    static_assert(rvi.is_in<int&&>(), "");
    static_assert(rvi.is_in<const int&&>(), "");
    static_assert(rvi.is_in<volatile int&&>(), "");
    static_assert(rvi.is_in<const volatile int&&>(), "");
    static_assert(rvi.is_in<signed int>(), "");
    static_assert(rvi.is_in<const signed int>(), "");
    static_assert(rvi.is_in<volatile signed int>(), "");
    static_assert(rvi.is_in<const volatile signed int>(), "");
    static_assert(rvi.is_in<signed int&>(), "");
    static_assert(rvi.is_in<const signed int&>(), "");
    static_assert(rvi.is_in<volatile signed int&>(), "");
    static_assert(rvi.is_in<const volatile signed int&>(), "");
    static_assert(rvi.is_in<signed int&&>(), "");
    static_assert(rvi.is_in<const signed int&&>(), "");
    static_assert(rvi.is_in<volatile signed int&&>(), "");
    static_assert(rvi.is_in<const volatile signed int&&>(), "");
    static_assert(rcvi.is_in<int>(), "");
    static_assert(rcvi.is_in<const int>(), "");
    static_assert(rcvi.is_in<volatile int>(), "");
    static_assert(rcvi.is_in<const volatile int>(), "");
    static_assert(rcvi.is_in<int&>(), "");
    static_assert(rcvi.is_in<const int&>(), "");
    static_assert(rcvi.is_in<volatile int&>(), "");
    static_assert(rcvi.is_in<const volatile int&>(), "");
    static_assert(rcvi.is_in<int&&>(), "");
    static_assert(rcvi.is_in<const int&&>(), "");
    static_assert(rcvi.is_in<volatile int&&>(), "");
    static_assert(rcvi.is_in<const volatile int&&>(), "");
    static_assert(rcvi.is_in<signed int>(), "");
    static_assert(rcvi.is_in<const signed int>(), "");
    static_assert(rcvi.is_in<volatile signed int>(), "");
    static_assert(rcvi.is_in<const volatile signed int>(), "");
    static_assert(rcvi.is_in<signed int&>(), "");
    static_assert(rcvi.is_in<const signed int&>(), "");
    static_assert(rcvi.is_in<volatile signed int&>(), "");
    static_assert(rcvi.is_in<const volatile signed int&>(), "");
    static_assert(rcvi.is_in<signed int&&>(), "");
    static_assert(rcvi.is_in<const signed int&&>(), "");
    static_assert(rcvi.is_in<volatile signed int&&>(), "");
    static_assert(rcvi.is_in<const volatile signed int&&>(), "");
    static_assert(rri.is_in<int>(), "");
    static_assert(rri.is_in<const int>(), "");
    static_assert(rri.is_in<volatile int>(), "");
    static_assert(rri.is_in<const volatile int>(), "");
    static_assert(rri.is_in<int&>(), "");
    static_assert(rri.is_in<const int&>(), "");
    static_assert(rri.is_in<volatile int&>(), "");
    static_assert(rri.is_in<const volatile int&>(), "");
    static_assert(rri.is_in<int&&>(), "");
    static_assert(rri.is_in<const int&&>(), "");
    static_assert(rri.is_in<volatile int&&>(), "");
    static_assert(rri.is_in<const volatile int&&>(), "");
    static_assert(rri.is_in<signed int>(), "");
    static_assert(rri.is_in<const signed int>(), "");
    static_assert(rri.is_in<volatile signed int>(), "");
    static_assert(rri.is_in<const volatile signed int>(), "");
    static_assert(rri.is_in<signed int&>(), "");
    static_assert(rri.is_in<const signed int&>(), "");
    static_assert(rri.is_in<volatile signed int&>(), "");
    static_assert(rri.is_in<const volatile signed int&>(), "");
    static_assert(rri.is_in<signed int&&>(), "");
    static_assert(rri.is_in<const signed int&&>(), "");
    static_assert(rri.is_in<volatile signed int&&>(), "");
    static_assert(rri.is_in<const volatile signed int&&>(), "");
    static_assert(rrci.is_in<int>(), "");
    static_assert(rrci.is_in<const int>(), "");
    static_assert(rrci.is_in<volatile int>(), "");
    static_assert(rrci.is_in<const volatile int>(), "");
    static_assert(rrci.is_in<int&>(), "");
    static_assert(rrci.is_in<const int&>(), "");
    static_assert(rrci.is_in<volatile int&>(), "");
    static_assert(rrci.is_in<const volatile int&>(), "");
    static_assert(rrci.is_in<int&&>(), "");
    static_assert(rrci.is_in<const int&&>(), "");
    static_assert(rrci.is_in<volatile int&&>(), "");
    static_assert(rrci.is_in<const volatile int&&>(), "");
    static_assert(rrci.is_in<signed int>(), "");
    static_assert(rrci.is_in<const signed int>(), "");
    static_assert(rrci.is_in<volatile signed int>(), "");
    static_assert(rrci.is_in<const volatile signed int>(), "");
    static_assert(rrci.is_in<signed int&>(), "");
    static_assert(rrci.is_in<const signed int&>(), "");
    static_assert(rrci.is_in<volatile signed int&>(), "");
    static_assert(rrci.is_in<const volatile signed int&>(), "");
    static_assert(rrci.is_in<signed int&&>(), "");
    static_assert(rrci.is_in<const signed int&&>(), "");
    static_assert(rrci.is_in<volatile signed int&&>(), "");
    static_assert(rrci.is_in<const volatile signed int&&>(), "");
    static_assert(rrvi.is_in<int>(), "");
    static_assert(rrvi.is_in<const int>(), "");
    static_assert(rrvi.is_in<volatile int>(), "");
    static_assert(rrvi.is_in<const volatile int>(), "");
    static_assert(rrvi.is_in<int&>(), "");
    static_assert(rrvi.is_in<const int&>(), "");
    static_assert(rrvi.is_in<volatile int&>(), "");
    static_assert(rrvi.is_in<const volatile int&>(), "");
    static_assert(rrvi.is_in<int&&>(), "");
    static_assert(rrvi.is_in<const int&&>(), "");
    static_assert(rrvi.is_in<volatile int&&>(), "");
    static_assert(rrvi.is_in<const volatile int&&>(), "");
    static_assert(rrvi.is_in<signed int>(), "");
    static_assert(rrvi.is_in<const signed int>(), "");
    static_assert(rrvi.is_in<volatile signed int>(), "");
    static_assert(rrvi.is_in<const volatile signed int>(), "");
    static_assert(rrvi.is_in<signed int&>(), "");
    static_assert(rrvi.is_in<const signed int&>(), "");
    static_assert(rrvi.is_in<volatile signed int&>(), "");
    static_assert(rrvi.is_in<const volatile signed int&>(), "");
    static_assert(rrvi.is_in<signed int&&>(), "");
    static_assert(rrvi.is_in<const signed int&&>(), "");
    static_assert(rrvi.is_in<volatile signed int&&>(), "");
    static_assert(rrvi.is_in<const volatile signed int&&>(), "");
    static_assert(rrcvi.is_in<int>(), "");
    static_assert(rrcvi.is_in<const int>(), "");
    static_assert(rrcvi.is_in<volatile int>(), "");
    static_assert(rrcvi.is_in<const volatile int>(), "");
    static_assert(rrcvi.is_in<int&>(), "");
    static_assert(rrcvi.is_in<const int&>(), "");
    static_assert(rrcvi.is_in<volatile int&>(), "");
    static_assert(rrcvi.is_in<const volatile int&>(), "");
    static_assert(rrcvi.is_in<int&&>(), "");
    static_assert(rrcvi.is_in<const int&&>(), "");
    static_assert(rrcvi.is_in<volatile int&&>(), "");
    static_assert(rrcvi.is_in<const volatile int&&>(), "");
    static_assert(rrcvi.is_in<signed int>(), "");
    static_assert(rrcvi.is_in<const signed int>(), "");
    static_assert(rrcvi.is_in<volatile signed int>(), "");
    static_assert(rrcvi.is_in<const volatile signed int>(), "");
    static_assert(rrcvi.is_in<signed int&>(), "");
    static_assert(rrcvi.is_in<const signed int&>(), "");
    static_assert(rrcvi.is_in<volatile signed int&>(), "");
    static_assert(rrcvi.is_in<const volatile signed int&>(), "");
    static_assert(rrcvi.is_in<signed int&&>(), "");
    static_assert(rrcvi.is_in<const signed int&&>(), "");
    static_assert(rrcvi.is_in<volatile signed int&&>(), "");
    static_assert(rrcvi.is_in<const volatile signed int&&>(), "");

    static_assert(not i.is_in<long>(), "");
    static_assert(not ci.is_in<long>(), "");
    static_assert(not i.is_in<unsigned int>(), "");
    static_assert(not rci.is_in<unsigned int>(), "");
    struct Foo;
    static_assert(not i.is_in<Foo>(), "");
    static_assert(not rrvi.is_in<Foo>(), "");

    constexpr auto rci_rrl = type_set<const int&, long&&>();
    constexpr auto i_cl = type_set<int, const long>();
    constexpr auto i_rrl = type_set<int, long&&>();
    constexpr auto i_rsl = type_set<int, signed long&>();
    constexpr auto ri_rrcsl = type_set<int&, const signed long&&>();
    constexpr auto rri_rrsl = type_set<int&&, signed long&&>();
    constexpr auto rri_rrul = type_set<int&&, unsigned long&&>();

    static_assert(decltype(rci_rrl)::is_same<decltype(i_cl)>(), "");
    static_assert(decltype(rci_rrl)::is_same<decltype(i_rrl)>(), "");
    static_assert(decltype(rci_rrl)::is_same<decltype(i_rsl)>(), "");
    static_assert(decltype(rci_rrl)::is_same<decltype(ri_rrcsl)>(), "");
    static_assert(decltype(rci_rrl)::is_same<decltype(rri_rrsl)>(), "");
    static_assert(not decltype(rri_rrsl)::is_same<decltype(rri_rrul)>(), "");

    static_assert(not rci_rrl.empty(), "");
    static_assert(not i_cl.empty(), "");
    static_assert(not i_rrl.empty(), "");
    static_assert(not i_rsl.empty(), "");
    static_assert(not ri_rrcsl.empty(), "");
    static_assert(not rri_rrsl.empty(), "");
    static_assert(not rri_rrul.empty(), "");
    static_assert(rci_rrl.size() == 2, "");
    static_assert(i_cl.size() == 2, "");
    static_assert(i_rrl.size() == 2, "");
    static_assert(i_rsl.size() == 2, "");
    static_assert(ri_rrcsl.size() == 2, "");
    static_assert(rri_rrsl.size() == 2, "");
    static_assert(rri_rrul.size() == 2, "");

    static_assert(rci_rrl.is_in<int>(), "");
    static_assert(rci_rrl.is_in<const int>(), "");
    static_assert(rci_rrl.is_in<volatile int>(), "");
    static_assert(rci_rrl.is_in<const volatile int>(), "");
    static_assert(rci_rrl.is_in<int&>(), "");
    static_assert(rci_rrl.is_in<const int&>(), "");
    static_assert(rci_rrl.is_in<volatile int&>(), "");
    static_assert(rci_rrl.is_in<const volatile int&>(), "");
    static_assert(rci_rrl.is_in<int&&>(), "");
    static_assert(rci_rrl.is_in<const int&&>(), "");
    static_assert(rci_rrl.is_in<volatile int&&>(), "");
    static_assert(rci_rrl.is_in<const volatile int&&>(), "");
    static_assert(rci_rrl.is_in<signed int>(), "");
    static_assert(rci_rrl.is_in<const signed int>(), "");
    static_assert(rci_rrl.is_in<volatile signed int>(), "");
    static_assert(rci_rrl.is_in<const volatile signed int>(), "");
    static_assert(rci_rrl.is_in<signed int&>(), "");
    static_assert(rci_rrl.is_in<const signed int&>(), "");
    static_assert(rci_rrl.is_in<volatile signed int&>(), "");
    static_assert(rci_rrl.is_in<const volatile signed int&>(), "");
    static_assert(rci_rrl.is_in<signed int&&>(), "");
    static_assert(rci_rrl.is_in<const signed int&&>(), "");
    static_assert(rci_rrl.is_in<volatile signed int&&>(), "");
    static_assert(rci_rrl.is_in<const volatile signed int&&>(), "");
    static_assert(rci_rrl.is_in<long>(), "");
    static_assert(rci_rrl.is_in<const long>(), "");
    static_assert(rci_rrl.is_in<volatile long>(), "");
    static_assert(rci_rrl.is_in<const volatile long>(), "");
    static_assert(rci_rrl.is_in<long&>(), "");
    static_assert(rci_rrl.is_in<const long&>(), "");
    static_assert(rci_rrl.is_in<volatile long&>(), "");
    static_assert(rci_rrl.is_in<const volatile long&>(), "");
    static_assert(rci_rrl.is_in<long&&>(), "");
    static_assert(rci_rrl.is_in<const long&&>(), "");
    static_assert(rci_rrl.is_in<volatile long&&>(), "");
    static_assert(rci_rrl.is_in<const volatile long&&>(), "");
    static_assert(rci_rrl.is_in<signed long>(), "");
    static_assert(rci_rrl.is_in<const signed long>(), "");
    static_assert(rci_rrl.is_in<volatile signed long>(), "");
    static_assert(rci_rrl.is_in<const volatile signed long>(), "");
    static_assert(rci_rrl.is_in<signed long&>(), "");
    static_assert(rci_rrl.is_in<const signed long&>(), "");
    static_assert(rci_rrl.is_in<volatile signed long&>(), "");
    static_assert(rci_rrl.is_in<const volatile signed long&>(), "");
    static_assert(rci_rrl.is_in<signed long&&>(), "");
    static_assert(rci_rrl.is_in<const signed long&&>(), "");
    static_assert(rci_rrl.is_in<volatile signed long&&>(), "");
    static_assert(rci_rrl.is_in<const volatile signed long&&>(), "");
    static_assert(i_cl.is_in<long>(), "");
    static_assert(i_cl.is_in<const long>(), "");
    static_assert(i_cl.is_in<volatile long>(), "");
    static_assert(i_cl.is_in<const volatile long>(), "");
    static_assert(i_cl.is_in<long&>(), "");
    static_assert(i_cl.is_in<const long&>(), "");
    static_assert(i_cl.is_in<volatile long&>(), "");
    static_assert(i_cl.is_in<const volatile long&>(), "");
    static_assert(i_cl.is_in<long&&>(), "");
    static_assert(i_cl.is_in<const long&&>(), "");
    static_assert(i_cl.is_in<volatile long&&>(), "");
    static_assert(i_cl.is_in<const volatile long&&>(), "");
    static_assert(i_cl.is_in<signed long>(), "");
    static_assert(i_cl.is_in<const signed long>(), "");
    static_assert(i_cl.is_in<volatile signed long>(), "");
    static_assert(i_cl.is_in<const volatile signed long>(), "");
    static_assert(i_cl.is_in<signed long&>(), "");
    static_assert(i_cl.is_in<const signed long&>(), "");
    static_assert(i_cl.is_in<volatile signed long&>(), "");
    static_assert(i_cl.is_in<const volatile signed long&>(), "");
    static_assert(i_cl.is_in<signed long&&>(), "");
    static_assert(i_cl.is_in<const signed long&&>(), "");
    static_assert(i_cl.is_in<volatile signed long&&>(), "");
    static_assert(i_cl.is_in<const volatile signed long&&>(), "");

    static_assert(not rci_rrl.is_in<unsigned int>(), "");
    static_assert(not rci_rrl.is_in<Foo>(), "");

    static_assert(rri_rrul.is_in<int>(), "");
    static_assert(rri_rrul.is_in<int&&>(), "");
    static_assert(rri_rrul.is_in<const int>(), "");
    static_assert(rri_rrul.is_in<unsigned long>(), "");
    static_assert(rri_rrul.is_in<const unsigned long>(), "");
    static_assert(rri_rrul.is_in<volatile unsigned long>(), "");
    static_assert(rri_rrul.is_in<const volatile unsigned long>(), "");
    static_assert(rri_rrul.is_in<unsigned long&>(), "");
    static_assert(rri_rrul.is_in<const unsigned long&>(), "");
    static_assert(rri_rrul.is_in<volatile unsigned long&>(), "");
    static_assert(rri_rrul.is_in<const volatile unsigned long&>(), "");
    static_assert(rri_rrul.is_in<unsigned long&&>(), "");
    static_assert(rri_rrul.is_in<const unsigned long&&>(), "");
    static_assert(rri_rrul.is_in<volatile unsigned long&&>(), "");
    static_assert(rri_rrul.is_in<const volatile unsigned long&&>(), "");

    static_assert(not rri_rrul.is_in<unsigned int>(), "");
    static_assert(not rri_rrul.is_in<signed long>(), "");
    static_assert(not rri_rrul.is_in<const Foo&>(), "");
}

TEST(type_set, test_type_set__join)
{
    using namespace juno;

    static_assert(type_set<int, long, unsigned long>::is_same<
            decltype(type_set<int, long>::join<unsigned long>())
            >(), "");
    static_assert(type_set<int, long>::is_same<decltype(type_set<int, long>::join<long>())>(), "");
    static_assert(type_set<int, long>::is_same<decltype(type_set<int, long>::join<int>())>(), "");
    static_assert(type_set<int, long>::is_same<decltype(type_set<int, long>::join<void>())>(), "");

    static_assert(type_set<void>::is_same<decltype(type_set<>::join<type_set<>>())>(), "");
    static_assert(type_set<>::is_same<decltype(type_set<>::join<type_set<void>>())>(), "");
    static_assert(type_set<int, long>::is_same<decltype(type_set<>::join<type_set<const int, long&&>>())>(), "");
    static_assert(type_set<int, long>::is_same<decltype(type_set<int>::join<type_set<int, long>>())>(), "");
    static_assert(type_set<int, long>::is_same<decltype(type_set<int, long>::join<type_set<int, long>>())>(), "");
    static_assert(type_set<int, long>::is_same<decltype(type_set<int, long&&>::join<type_set<const int&>>())>(), "");

    SUCCEED();
}
