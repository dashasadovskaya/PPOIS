/**
 * @file tests.cpp
 * @author Садовская Д.С.
 * @brief Unit-тесты для класса Multiset (UnitTest++).
 * @date 2026
 */

#include <UnitTest++/UnitTest++.h>
#include <sstream>
#include "Multiset.h"

TEST(DefaultCtorEmpty) {
    Multiset m;
    CHECK(m.empty());
    CHECK_EQUAL(0u, m.power());
}

TEST(CtorFromCString) {
    Multiset m("{a, b, c}");
    CHECK_EQUAL(3u, m.power());
    CHECK(m["a"]);
    CHECK(m["b"]);
    CHECK(m["c"]);
}

TEST(CtorFromString) {
    std::string s = "{x, y}";
    Multiset m(s);
    CHECK_EQUAL(2u, m.power());
    CHECK(m["x"]);
    CHECK(m["y"]);
}

TEST(CopyCtorDeep) {
    Multiset a("{x, y}");
    Multiset b(a);
    CHECK(a == b);
    b.add("z");
    CHECK(a != b);   // копия независима
}

TEST(AddAtom) {
    Multiset m;
    m.add("a");
    m.add("a");
    m.add("b");
    CHECK_EQUAL(3u, m.power());
    CHECK(m["a"]);
    CHECK(m["b"]);
}

TEST(AddSubset) {
    Multiset inner("{x, y}");
    Multiset outer;
    outer.add("a");
    outer.add(inner);
    CHECK_EQUAL(2u, outer.power());
    CHECK(outer[inner]);
}

TEST(RemoveAtom) {
    Multiset m("{a, a, b}");
    CHECK(m.remove("a"));
    CHECK_EQUAL(2u, m.power());
    CHECK(m.remove("a"));
    CHECK_EQUAL(1u, m.power());
    CHECK(!m.remove("a"));
}

TEST(RemoveNonexistent) {
    Multiset m("{a}");
    CHECK(!m.remove("z"));
    CHECK_EQUAL(1u, m.power());
}

TEST(PowerCountsDuplicates) {
    Multiset m("{a, a, a}");
    CHECK_EQUAL(3u, m.power());
}

TEST(EmptyAfterRemovingAll) {
    Multiset m("{a, b}");
    m.remove("a");
    m.remove("b");
    CHECK(m.empty());
}

TEST(ContainsAtomTrue) {
    Multiset m("{a, b}");
    CHECK(m["a"]);
    CHECK(m["b"]);
}

TEST(ContainsAtomFalse) {
    Multiset m("{a, b}");
    CHECK(!m["z"]);
}

TEST(ContainsSubset) {
    Multiset inner("{a, b}");
    Multiset outer;
    outer.add(inner);
    CHECK(outer[inner]);
}

TEST(UnionSimple) {
    Multiset a("{a, b}");
    Multiset b("{b, c}");
    Multiset c = a + b;
    CHECK(c["a"]);
    CHECK(c["b"]);
    CHECK(c["c"]);
    CHECK_EQUAL(3u, c.power());
}

TEST(UnionTakesMaxCount) {
    Multiset a("{a, a}");
    Multiset b("{a}");
    Multiset c = a + b;
    CHECK_EQUAL(2u, c.power());   // max(2, 1) = 2
}

TEST(UnionAssign) {
    Multiset a("{a}");
    Multiset b("{b}");
    a += b;
    CHECK(a["a"]);
    CHECK(a["b"]);
}

TEST(IntersectionSimple) {
    Multiset a("{a, b, c}");
    Multiset b("{b, c, d}");
    Multiset c = a * b;
    CHECK(!c["a"]);
    CHECK(c["b"]);
    CHECK(c["c"]);
    CHECK(!c["d"]);
}

TEST(IntersectionTakesMinCount) {
    Multiset a("{a, a, a}");
    Multiset b("{a, a}");
    Multiset c = a * b;
    CHECK_EQUAL(2u, c.power());   // min(3, 2) = 2
}

TEST(IntersectionEmpty) {
    Multiset a("{a}");
    Multiset b("{b}");
    CHECK((a * b).empty());
}

TEST(DifferenceSimple) {
    Multiset a("{a, b, c}");
    Multiset b("{b}");
    Multiset c = a - b;
    CHECK(c["a"]);
    CHECK(!c["b"]);
    CHECK(c["c"]);
}

TEST(DifferenceCounts) {
    Multiset a("{a, a, a}");
    Multiset b("{a}");
    Multiset c = a - b;
    CHECK_EQUAL(2u, c.power());
}

TEST(DifferenceRemovesAll) {
    Multiset a("{a}");
    Multiset b("{a}");
    CHECK((a - b).empty());
}

TEST(BooleanOneElement) {
    Multiset m("{a}");
    Multiset b = m.boolean();
    CHECK_EQUAL(2u, b.power());   // {}, {a}
}

TEST(BooleanTwoElements) {
    Multiset m("{a, b}");
    Multiset b = m.boolean();
    CHECK_EQUAL(4u, b.power());   // {}, {a}, {b}, {a, b}
}

TEST(EqualitySameOrder) {
    Multiset a("{a, b, c}");
    Multiset b("{a, b, c}");
    CHECK(a == b);
}

TEST(EqualityDifferentOrder) {
    Multiset a("{a, b, c}");
    Multiset b("{c, a, b}");
    CHECK(a == b);
}

TEST(InequalityDifferentCount) {
    Multiset a("{a, a}");
    Multiset b("{a}");
    CHECK(a != b);
}

TEST(NestedSubset) {
    Multiset m("{a, {b, c}}");
    CHECK_EQUAL(2u, m.power());
    CHECK(m["a"]);
    Multiset inner("{b, c}");
    CHECK(m[inner]);
}

TEST(OutputFormat) {
    Multiset m("{a, b}");
    std::ostringstream os;
    os << m;
    CHECK_EQUAL("{a, b}", os.str());
}

TEST(InputParse) {
    std::istringstream is("{x, y, z}");
    Multiset m;
    is >> m;
    CHECK_EQUAL(3u, m.power());
    CHECK(m["x"]);
}

int main() {
    return UnitTest::RunAllTests();
}