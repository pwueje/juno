#include <gtest/gtest.h>

#include <type_traits>

#include <mpl.hpp>

TEST(test_juno, test_mpl_type_tag)
{
    using namespace juno;

    const auto i = type_tag<int>::value;
    const auto ci = type_tag<const int>::value;
    const auto vi = type_tag<volatile int>::value;
    const auto cvi = type_tag<const volatile int>::value;
    const auto ri = type_tag<int&>::value;
    const auto rci = type_tag<const int&>::value;
    const auto rvi = type_tag<volatile int&>::value;
    const auto rcvi = type_tag<const volatile int&>::value;
    const auto rri = type_tag<int&&>::value;
    const auto rrci = type_tag<const int&&>::value;
    const auto rrvi = type_tag<volatile int&&>::value;
    const auto rrcvi = type_tag<const volatile int&&>::value;
    EXPECT_EQ(i, ci);
    static_assert(std::is_same<type_tag<int>::type, type_tag<const int>::type>::value, "");
    EXPECT_EQ(i, vi);
    static_assert(std::is_same<type_tag<int>::type, type_tag<volatile int>::type>::value, "");
    EXPECT_EQ(i, cvi);
    static_assert(std::is_same<type_tag<int>::type, type_tag<const volatile int>::type>::value, "");
    EXPECT_EQ(i, ri);
    static_assert(std::is_same<type_tag<int>::type, type_tag<int&>::type>::value, "");
    EXPECT_EQ(i, rci);
    static_assert(std::is_same<type_tag<int>::type, type_tag<const int&>::type>::value, "");
    EXPECT_EQ(i, rvi);
    static_assert(std::is_same<type_tag<int>::type, type_tag<volatile int&>::type>::value, "");
    EXPECT_EQ(i, rcvi);
    static_assert(std::is_same<type_tag<int>::type, type_tag<const volatile int&>::type>::value, "");
    EXPECT_EQ(i, rri);
    static_assert(std::is_same<type_tag<int>::type, type_tag<int&&>::type>::value, "");
    EXPECT_EQ(i, rrci);
    static_assert(std::is_same<type_tag<int>::type, type_tag<const int&&>::type>::value, "");
    EXPECT_EQ(i, rrvi);
    static_assert(std::is_same<type_tag<int>::type, type_tag<volatile int&&>::type>::value, "");
    EXPECT_EQ(i, rrcvi);
    static_assert(std::is_same<type_tag<int>::type, type_tag<const volatile int&&>::type>::value, "");
    static_assert(std::is_same<type_tag<int>::type, type_tag<decltype(1)>::type>::value, "");

    const auto pi = type_tag<int*>::value;
    const auto cpi = type_tag<const int*>::value;
    const auto pic = type_tag<int* const>::value;
    const auto cpic = type_tag<const int* const>::value;
    const auto rcpic = type_tag<const int* const&>::value;
    const auto rrcpi = type_tag<const int* &&>::value;
    EXPECT_NE(i, pi);
    static_assert(not std::is_same<type_tag<int>::type, type_tag<int*>::type>::value, "");
    EXPECT_NE(pi, cpi);
    static_assert(not std::is_same<type_tag<int*>::type, type_tag<const int*>::type>::value, "");
    EXPECT_EQ(pi, pic);
    static_assert(std::is_same<type_tag<int*>::type, type_tag<int* const>::type>::value, "");
    EXPECT_EQ(cpi, cpic);
    static_assert(std::is_same<type_tag<int const*>::type, type_tag<const int* const>::type>::value, "");
    EXPECT_EQ(cpi, rcpic);
    static_assert(std::is_same<type_tag<int const*>::type, type_tag<const int* const&>::type>::value, "");
    EXPECT_EQ(cpi, rrcpi);
    static_assert(std::is_same<type_tag<int const*>::type, type_tag<const int* &&>::type>::value, "");

    const auto l = type_tag<long>::value;
    EXPECT_NE(i, l);
    static_assert(not std::is_same<type_tag<int>::type, type_tag<long>::type>::value, "");
    EXPECT_NE(pi, l);
    static_assert(not std::is_same<type_tag<int*>::type, type_tag<long>::type>::value, "");
    EXPECT_NE(cpi, l);
    static_assert(not std::is_same<type_tag<const int*>::type, type_tag<long>::type>::value, "");

    const auto rsl = type_tag<signed long&>::value;
    EXPECT_EQ(l, rsl);
    static_assert(std::is_same<type_tag<long>::type, type_tag<signed long&>::type>::value, "");

    const auto ul = type_tag<unsigned long>::value;
    EXPECT_NE(i, ul);
    static_assert(not std::is_same<type_tag<int>::type, type_tag<unsigned long>::type>::value, "");
    EXPECT_NE(pi, ul);
    static_assert(not std::is_same<type_tag<int*>::type, type_tag<unsigned long>::type>::value, "");
    EXPECT_NE(cpi, ul);
    static_assert(not std::is_same<type_tag<const int*>::type, type_tag<unsigned long>::type>::value, "");
    EXPECT_NE(l, ul);
    static_assert(not std::is_same<type_tag<long>::type, type_tag<unsigned long>::type>::value, "");

    struct Foo;
    const auto f = type_tag<Foo>::value;
    EXPECT_NE(i, f);
    static_assert(not std::is_same<type_tag<int>::type, type_tag<Foo>::type>::value, "");
    EXPECT_NE(pi, f);
    static_assert(not std::is_same<type_tag<int*>::type, type_tag<Foo>::type>::value, "");
    EXPECT_NE(cpi, f);
    static_assert(not std::is_same<type_tag<const int*>::type, type_tag<Foo>::type>::value, "");
    EXPECT_NE(l, f);
    static_assert(not std::is_same<type_tag<long>::type, type_tag<Foo>::type>::value, "");
    EXPECT_NE(ul, f);
    static_assert(not std::is_same<type_tag<unsigned long>::type, type_tag<Foo>::type>::value, "");

    enum Baz { };
    const auto b = type_tag<Baz>::value;
    const auto rrb = type_tag<Baz&&>::value;
    const auto rcb = type_tag<const Baz&>::value;
    EXPECT_NE(i, b);
    static_assert(not std::is_same<type_tag<int>::type, type_tag<Baz>::type>::value, "");
    EXPECT_NE(pi, b);
    static_assert(not std::is_same<type_tag<int*>::type, type_tag<Baz>::type>::value, "");
    EXPECT_NE(cpi, b);
    static_assert(not std::is_same<type_tag<const int*>::type, type_tag<Baz>::type>::value, "");
    EXPECT_NE(l, b);
    static_assert(not std::is_same<type_tag<long>::type, type_tag<Baz>::type>::value, "");
    EXPECT_NE(ul, b);
    static_assert(not std::is_same<type_tag<unsigned long>::type, type_tag<Baz>::type>::value, "");
    EXPECT_NE(f, b);
    static_assert(not std::is_same<type_tag<Foo>::type, type_tag<Baz>::type>::value, "");
    EXPECT_EQ(b, rrb);
    static_assert(std::is_same<type_tag<Baz>::type, type_tag<Baz&&>::type>::value, "");
    EXPECT_EQ(b, rcb);
    static_assert(std::is_same<type_tag<Baz>::type, type_tag<const Baz&>::type>::value, "");
}

TEST(test_juno, test_mpl_type_set)
{
    using namespace juno;

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

    constexpr auto i = type_set<int>();
    constexpr auto ci = type_set<const int>();
    constexpr auto vi = type_set<volatile int>();
    constexpr auto cvi = type_set<const volatile int>();
    constexpr auto ri = type_set<int&>();
    constexpr auto rci = type_set<const int&>();
    constexpr auto rvi = type_set<volatile int&>();
    constexpr auto rcvi = type_set<const volatile int&>();
    constexpr auto rri = type_set<int&&>();
    constexpr auto rrci = type_set<const int&&>();
    constexpr auto rrvi = type_set<volatile int&&>();
    constexpr auto rrcvi = type_set<const volatile int&&>();

    static_assert(std::is_same<decltype(i)::type, decltype(ci)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(vi)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(cvi)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(ri)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(rci)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(rvi)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(rcvi)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(rri)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(rrci)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(rrvi)::type>::value, "");
    static_assert(std::is_same<decltype(i)::type, decltype(rrcvi)::type>::value, "");

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

    static_assert(std::is_same<decltype(rci_rrl)::type, decltype(i_cl)::type>::value, "");
    static_assert(std::is_same<decltype(rci_rrl)::type, decltype(i_rrl)::type>::value, "");
    static_assert(std::is_same<decltype(rci_rrl)::type, decltype(i_rsl)::type>::value, "");
    static_assert(std::is_same<decltype(rci_rrl)::type, decltype(ri_rrcsl)::type>::value, "");
    static_assert(std::is_same<decltype(rci_rrl)::type, decltype(rri_rrsl)::type>::value, "");
    static_assert(not std::is_same<decltype(rri_rrsl)::type, decltype(rri_rrul)::type>::value, "");

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

TEST(test_juno, test_mpl_type_set_uniqueness)
{
    using namespace juno::d;

    // not in empty list
    static_assert(std::is_same<is_in<int>::result, false_e>::value, "");
    static_assert(std::is_same<is_in<void>::result, false_e>::value, "");

    // int is not in (void) nor in (long, void*)
    static_assert(std::is_same<is_in<int, void>::result, false_e>::value, "");
    static_assert(std::is_same<is_in<int, long, void*>::result, false_e>::value, "");

    // int is in (int, void) and in (int, long, void*), in any order of elements
    static_assert(std::is_same<is_in<int, int, void>::result, true_e>::value, "");
    static_assert(std::is_same<is_in<int, void, int>::result, true_e>::value, "");
    static_assert(std::is_same<is_in<int, int, long, void*>::result, true_e>::value, "");
    static_assert(std::is_same<is_in<int, int, void*, long>::result, true_e>::value, "");
    static_assert(std::is_same<is_in<int, long, int, void*>::result, true_e>::value, "");
    static_assert(std::is_same<is_in<int, long, void*, int>::result, true_e>::value, "");
    static_assert(std::is_same<is_in<int, void*, long, int>::result, true_e>::value, "");
    static_assert(std::is_same<is_in<int, void*, int, long>::result, true_e>::value, "");

    static_assert(std::is_same<set<>::result, set<>>::value, "");
    static_assert(std::is_same<set<int>::result, set<int>>::value, "");
    static_assert(std::is_same<set<int, int>::result, set<int>>::value, "");
    static_assert(std::is_same<set<int, int, int>::result, set<int>>::value, "");
    static_assert(std::is_same<set<int, int, int, int>::result, set<int>>::value, "");
    static_assert(std::is_same<set<long, int>::result, set<long, int>>::value, "");
    static_assert(std::is_same<set<long, int, int>::result, set<long, int>>::value, "");
    static_assert(std::is_same<set<long, int, int, int>::result, set<long, int>>::value, "");
    static_assert(std::is_same<set<int, int, long>::result, set<int, long>>::value, "");
    static_assert(std::is_same<set<long, int, int, long, int>::result, set<long, int>>::value, "");
    static_assert(std::is_same<set<int, int, long, long, long ,int, int, int, int>::result, set<long, int>>::value, "");
    static_assert(std::is_same<set<long, int, int, long, long, long, int, int, long, int>::result, set<long, int>>::value, "");
    static_assert(std::is_same<set<long, int, long, int, int, long, int, long, long, long, long>::result, set<int, long>>::value, "");

    SUCCEED();
}
