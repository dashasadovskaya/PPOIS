/**
 * @file tests.cpp
 * @author Садовская Д.С.
 * @brief Unit-тесты для класса Rectangle (UnitTest++).
 * @date 2026
 */

#include <UnitTest++/UnitTest++.h>
#include <sstream>
#include "Rectangle.h"


TEST(DefaultCtor) {
    Rectangle r;
    CHECK_EQUAL(0, r.getWidth());
    CHECK_EQUAL(0, r.getHeight());
}

TEST(CtorNormalizesSwappedCoords) {
    Rectangle r(5, 5, 1, 1);
    CHECK_EQUAL(1, r.getLeft());
    CHECK_EQUAL(1, r.getBottom());
    CHECK_EQUAL(5, r.getRight());
    CHECK_EQUAL(5, r.getTop());
}

TEST(CopyCtor) {
    Rectangle a(1, 2, 5, 7);
    Rectangle b(a);
    CHECK(a == b);
}

TEST(AssignOperator) {
    Rectangle a(1, 2, 5, 7);
    Rectangle b;
    b = a;
    CHECK(a == b);
}

TEST(SelfAssign) {
    Rectangle a(1, 2, 5, 7);
    a = a;
    CHECK_EQUAL(1, a.getLeft());
    CHECK_EQUAL(7, a.getTop());
}


TEST(Width)  { Rectangle r(0, 0, 4, 3); CHECK_EQUAL(4, r.getWidth()); }
TEST(Height) { Rectangle r(0, 0, 4, 3); CHECK_EQUAL(3, r.getHeight()); }
TEST(Area)   { Rectangle r(0, 0, 4, 3); CHECK_EQUAL(12, r.getArea()); }


TEST(Move) {
    Rectangle r(0, 0, 2, 2);
    r.move(3, -1);
    CHECK_EQUAL(3,  r.getLeft());
    CHECK_EQUAL(-1, r.getBottom());
    CHECK_EQUAL(5,  r.getRight());
    CHECK_EQUAL(1,  r.getTop());
}

TEST(Resize) {
    Rectangle r(0, 0, 2, 2);
    r.resize(5, 7);
    CHECK_EQUAL(5, r.getWidth());
    CHECK_EQUAL(7, r.getHeight());
}

TEST(ResizeNegativeClampedToZero) {
    Rectangle r(0, 0, 2, 2);
    r.resize(-3, -5);
    CHECK_EQUAL(0, r.getWidth());
    CHECK_EQUAL(0, r.getHeight());
}


TEST(PrefixIncrement) {
    Rectangle r(0, 0, 2, 2);
    Rectangle& ref = ++r;
    CHECK_EQUAL(-1, r.getLeft());
    CHECK_EQUAL(-1, r.getBottom());
    CHECK_EQUAL(3,  r.getRight());
    CHECK_EQUAL(3,  r.getTop());
    CHECK(&ref == &r);
}

TEST(PostfixIncrement) {
    Rectangle r(0, 0, 2, 2);
    Rectangle old = r++;
    CHECK_EQUAL(0,  old.getLeft());
    CHECK_EQUAL(-1, r.getLeft());
    CHECK_EQUAL(3,  r.getRight());
}

TEST(PrefixDecrement) {
    Rectangle r(0, 0, 4, 4);
    --r;
    CHECK_EQUAL(1, r.getLeft());
    CHECK_EQUAL(1, r.getBottom());
    CHECK_EQUAL(3, r.getRight());
    CHECK_EQUAL(3, r.getTop());
}

TEST(PostfixDecrement) {
    Rectangle r(0, 0, 4, 4);
    Rectangle old = r--;
    CHECK_EQUAL(0, old.getLeft());
    CHECK_EQUAL(1, r.getLeft());
    CHECK_EQUAL(3, r.getRight());
}

TEST(DecrementDoesNotGoNegative) {
    Rectangle r(0, 0, 1, 1);
    --r;
    CHECK_EQUAL(0, r.getWidth());
    CHECK_EQUAL(0, r.getHeight());
}


TEST(Union) {
    Rectangle a(0, 0, 2, 2);
    Rectangle b(5, 5, 7, 7);
    Rectangle c = a + b;
    CHECK_EQUAL(0, c.getLeft());
    CHECK_EQUAL(0, c.getBottom());
    CHECK_EQUAL(7, c.getRight());
    CHECK_EQUAL(7, c.getTop());
}

TEST(UnionOverlapping) {
    Rectangle a(0, 0, 5, 5);
    Rectangle b(3, 3, 8, 8);
    Rectangle c = a + b;
    CHECK_EQUAL(0, c.getLeft());
    CHECK_EQUAL(0, c.getBottom());
    CHECK_EQUAL(8, c.getRight());
    CHECK_EQUAL(8, c.getTop());
}

TEST(UnionAssign) {
    Rectangle a(0, 0, 2, 2);
    Rectangle b(5, 5, 7, 7);
    a += b;
    CHECK_EQUAL(0, a.getLeft());
    CHECK_EQUAL(7, a.getRight());
}


TEST(Intersection) {
    Rectangle a(0, 0, 5, 5);
    Rectangle b(3, 3, 8, 8);
    Rectangle c = a - b;
    CHECK_EQUAL(3, c.getLeft());
    CHECK_EQUAL(3, c.getBottom());
    CHECK_EQUAL(5, c.getRight());
    CHECK_EQUAL(5, c.getTop());
}

TEST(NoIntersectionProducesEmpty) {
    Rectangle a(0, 0, 2, 2);
    Rectangle b(10, 10, 12, 12);
    Rectangle c = a - b;
    CHECK_EQUAL(0, c.getWidth());
    CHECK_EQUAL(0, c.getHeight());
}

TEST(IntersectionAssign) {
    Rectangle a(0, 0, 5, 5);
    Rectangle b(3, 3, 8, 8);
    a -= b;
    CHECK_EQUAL(3, a.getLeft());
    CHECK_EQUAL(5, a.getRight());
}


TEST(Equality) {
    Rectangle a(1, 2, 3, 4);
    Rectangle b(1, 2, 3, 4);
    CHECK(a == b);
    CHECK(!(a != b));
}

TEST(Inequality) {
    Rectangle a(1, 2, 3, 4);
    Rectangle b(1, 2, 3, 5);
    CHECK(a != b);
}


TEST(OutputFormat) {
    Rectangle r(1, 2, 3, 4);
    std::ostringstream os;
    os << r;
    CHECK_EQUAL("(1,2)-(3,4)", os.str());
}

TEST(InputParse) {
    std::istringstream is("1 2 3 4");
    Rectangle r;
    is >> r;
    CHECK_EQUAL(1, r.getLeft());
    CHECK_EQUAL(4, r.getTop());
}


TEST(IntersectsTrue) {
    CHECK(intersects(Rectangle(0, 0, 5, 5), Rectangle(3, 3, 8, 8)));
}

TEST(IntersectsTouchingFalse) {
    CHECK(!intersects(Rectangle(0, 0, 2, 2), Rectangle(2, 0, 4, 2)));
}

TEST(IntersectsFalse) {
    CHECK(!intersects(Rectangle(0, 0, 2, 2), Rectangle(10, 10, 12, 12)));
}


TEST(SelfUnionEqualsSelf) {
    Rectangle a(1, 2, 3, 4);
    CHECK((a + a) == a);
}

TEST(SelfIntersectionEqualsSelf) {
    Rectangle a(1, 2, 3, 4);
    CHECK((a - a) == a);
}

TEST(MoveZeroNoChange) {
    Rectangle a(1, 2, 3, 4);
    Rectangle b = a;
    a.move(0, 0);
    CHECK(a == b);
}

TEST(ResizeThenArea) {
    Rectangle r(0, 0, 1, 1);
    r.resize(4, 5);
    CHECK_EQUAL(20, r.getArea());
}

TEST(ChainOfMoves) {
    Rectangle r(0, 0, 1, 1);
    r.move(1, 1).move(1, 1).move(1, 1);
    CHECK_EQUAL(3, r.getLeft());
    CHECK_EQUAL(3, r.getBottom());
}

TEST(PostfixIncrementReturnsOld) {
    Rectangle r(0, 0, 2, 2);
    Rectangle old = r++;
    CHECK_EQUAL(0,  old.getLeft());
    CHECK_EQUAL(-1, r.getLeft());
}

TEST(UnionCommutative) {
    Rectangle a(0, 0, 2, 2);
    Rectangle b(5, 5, 7, 7);
    CHECK((a + b) == (b + a));
}

TEST(IntersectionCommutative) {
    Rectangle a(0, 0, 5, 5);
    Rectangle b(3, 3, 8, 8);
    CHECK((a - b) == (b - a));
}


/**
 * @brief Запускает все тесты.
 * @return 0, если все тесты прошли
 */
int main() {
    return UnitTest::RunAllTests();
}